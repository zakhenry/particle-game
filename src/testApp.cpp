#include "testApp.h"
#include "particle.h"
#include "particleAttractor.h"
#include "particleEmitter.h"
#define OF_ADDON_USING_OFXXMLSETTINGS //dunno why this is necessary, but meh, ofwiki told me to

vector<Particle>particles;
vector<ParticleAttractor>attractors;
vector<ParticleAttractor>fixedAttractors;
vector<ParticleEmitter>emitters;

vector<ofPoint>touches2;
vector<MTouch> touches;

int emitterX, emitterY;
float currentTouchScale = 0;
float cameraVerticalAngle, current3TouchHeight = 0;

bool alphaTrail = true, GL3D = false;

bool fixedPoint = false;
bool buildMode = false; //allows build and setup
bool saving = false; //when saving is true the key input functions are locked down
string saveString;

ofColor playerColor, particleColor, red, green, blue, cyan, magenta, yellow, black;


//--------------------------------------------------------------
void testApp::setup(){
	ofSetCircleResolution(50);
	ofBackground(0, 0, 0);
	ofSetWindowTitle("graphics example");
    
    ofHideCursor();
    
    
    
//	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    
    // --- add the listeners
    ofAddListener(pad.update, this, &testApp::padUpdates);
    ofAddListener(pad.touchAdded, this, &testApp::newTouch);
    ofAddListener(pad.touchRemoved, this, &testApp::removedTouch);
    
    
    playerColor.r = 0;
    playerColor.g = 255;
    playerColor.b = 200;
    
    black.r = 0;
    black.g = 0;
    black.b = 0;
    
    red = blue = green = cyan = magenta = yellow = black;
    
    red.r = 255;
    green.g = 255;
    blue.b = 255;
    
    cyan.b = 255;
    cyan.g = 255;
    magenta.r = 255;
    magenta.b = 255;
    yellow.r = 255;
    yellow.g = 255;
    
    particleColor = playerColor;
    particleColor.r = 200;
    
    ParticleAttractor newAttractor(-100, -100, 100, cyan, false, -1);
    for (int i=0; i<5; i++){ //maybe to delete
        attractors.push_back(newAttractor);
    }
//    ParticleAttractor newAttractor(200, 400, 100, cyan, false, -1); //cursor
//    ;
    
    ParticleEmitter newEmitter(100, 100, -45, 2, yellow);
    emitters.push_back(newEmitter);
    
    ParticleEmitter anotherEmitter(100, 500, 0, 3, cyan);
    emitters.push_back(anotherEmitter);
    
    
    //some model / light stuff
   // glEnable (GL_DEPTH_TEST);
    //glShadeModel (GL_SMOOTH);
     
}

//--------------------------------------------------------------
void testApp::update(){
        
    ofSetBackgroundAuto(!alphaTrail);
    if (attractors.size()>0&&buildMode){
        attractors[0].updatePos(mouseX, mouseY); //move the first emitter with the mouse
    }
    
    for (int i=0; i<emitters.size(); i++){
        emitters[i].update(attractors); //update every emitter (and in turn every particle will be updated)
        emitters[i].update(fixedAttractors); //update every emitter (and in turn every particle will be updated)
    }
    
    
    
    if (pad.getTouchCount()>0&&!buildMode){
        
        pad.getTouchesAsOfPoints(touches2); //function already cleans up the touches vector
        
        for (int i=0; i<pad.getTouchCount(); i++){
            attractors[i].updatePos(touches2[i].x*ofGetWidth(), touches2[i].y*ofGetHeight());
        }
    }
    
    
    
//    cout << "there is "<<attractors.size()<<" attractors on the pad\n";
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    /*for (int i=0; i<emitters.size(); i++){
        emitters[i].draw();
    }*/
    
    if (GL3D){
        
        glTranslatef(ofGetWidth()/2,ofGetHeight()/2,0);
        //tumble according to mouse
        glRotatef(cameraVerticalAngle,1,0,0);
        //	glRotatef(mouseX,0,1,0);
        glTranslatef(-ofGetWidth()/2,-ofGetHeight()/2,0);
        
        
        
        glPushMatrix();
        
        ofSetColor(255, 0, 255);
        glBegin(GL_LINES); //vertical axis
        glVertex3f(0, -300, 0);
        glVertex3f(0, 300, 0);
        glEnd();
        
        glPopMatrix();
        
        //fake wall
        ofSetColor(50, 50, 50);
        
        glPushMatrix();
        
        glBegin(GL_QUADS);
        glVertex3f(0.0, 0, 0);
        glVertex3f(ofGetWidth(), 0, 0);
        glVertex3f(ofGetWidth(), 0, ofGetHeight());
        glVertex3f(0, 0, ofGetHeight());
        glEnd();
        
        //cursor
        ofSetColor(50, 255, 50);
        ofFill();
        ofCircle(mouseX, 10, mouseY, 10, 'z');
        
        ofCircle(0, 10, 0, 10, 'y');
        ofCircle(100, 10, 100, 10, 'y');
        
    }
    
    for (int i=0; i<emitters.size(); i++){
        emitters[i].draw(GL3D);
    }
    
    for (int i=0; i<attractors.size(); i++){
        attractors[i].draw(GL3D);
    }
    
    for (int i=0; i<fixedAttractors.size(); i++){
        fixedAttractors[i].draw(GL3D);
    }
    
    if (GL3D){
        glPopMatrix();
        
    }
    
    
    
    if (alphaTrail){
        ofSetColor(0, 0, 0, 10);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());   
    }
    
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    cout << "Key #" << key << " pressed \n";
    if (saving){
        
        if (key == 13){ //enter (endl)
            //go through save routine
            
            saveLevel(saveString);
            
            cout << "save string is \""<<saveString<<"\"\n";
            
            saving = false;
        }else{
            if(key==8 && saveString.size()>0) { // backspace
                saveString = saveString.substr(0, saveString.size()-1); // delete one character
            } else {
                saveString.append (1, (char)key );
            }
        }
        
    }else{
        switch (key) {
                
            case 'a':
                alphaTrail = !alphaTrail; //toggle alpha trail
                break;
                
            case '3':
                GL3D = !GL3D; //toggle 3D perspective
                break;
                
            case 'r':
                attractors.erase(attractors.begin()+1, attractors.begin()+attractors.size());
                fixedAttractors.erase(fixedAttractors.begin(), fixedAttractors.begin()+fixedAttractors.size());
                break;
                
            case 'f':
                fixedPoint = !fixedPoint;
                break;
                
            case 13:
                buildMode = !buildMode;
                break;
                
            case 'c': //clear
                attractors.erase(attractors.begin()+1, attractors.begin()+attractors.size());
                break;
                
            case 's': //save
                saving = true;
                break;
                
            case 'l': //load
                loadLevel("new file");
                break;
                
                
                
            default:
                //            Particle newParticle(emitterX, emitterY, currentEmitterSpeed, -45); //uniform direction for testing
                //            particles.push_back(newParticle);
                cout << "Key #" << key << " pressed \n";
                break;
        } //end switch
    }//end if saving
    
    
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    if (buildMode){
        switch (button){
            case 0: //left click?
            {
                ParticleAttractor newAttractor(x, y, attractors[0].range, green, false, -1);
                attractors.push_back(newAttractor);
            }
                break;
                
            case 2: //right click
            {
                ParticleAttractor newFixedAttractor(x, y, attractors[0].range, red, true, 100);
                fixedAttractors.push_back(newFixedAttractor);
            }
                break;
        }
    }
    
    
    cout << "mousebutton "<<button<<"pressed\n";
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

void testApp::padUpdates(int & touchCount) {
//    cout << "pad updates & has "<<t<<" touches\n";
    
    if (buildMode){
        
        if (touchCount==2){ //scaling
            MTouch t1,t2;
            if (pad.getTouchAt(0,&t1) && pad.getTouchAt(1,&t2) ){
                float newTouchScale = distanceBetweenTouches(t1, t2);
                if (newTouchScale>currentTouchScale){
                    attractors[0].range += 0.5;
                }else{
                    attractors[0].range -= 0.5;
                }
                currentTouchScale = distanceBetweenTouches(t1, t2);
                //            cout << "Distance between two fingers is: "<<distanceBetweenTouches(t1, t2)<<"\n";
            }
        }else if (touchCount==3){
            
            MTouch t1, t2, t3;
            
            if (pad.getTouchAt(0,&t1) && pad.getTouchAt(1,&t2) && pad.getTouchAt(2,&t3)){
                
                float averageTouchHeight = ((t1.y)+(t2.y)+(t3.y))/3;
                
                //            cout << "The averageTouchHeight is: " << averageTouchHeight << "\n";
                
                if (abs(averageTouchHeight-current3TouchHeight)>0.05){
                    if (averageTouchHeight>current3TouchHeight){
                        cameraVerticalAngle+=5;
                    }else{
                        cameraVerticalAngle-=5;
                    }
                    current3TouchHeight = averageTouchHeight;
                }
            }
        }
        
    }else{ //play mode
        
    }
    
}

void testApp::newTouch(int & n) {
//    cout << "++++++ a new touch"<<n<<"\n";
    
    if (!buildMode){
//        MTouch newTouch;
//        touches.push_back(newTouch);
//        ParticleAttractor newAttractor(-100, -100, 100, green, false, -1);
//        attractors.push_back(newAttractor);
    }
}

void testApp::removedTouch(int & r) {
//    cout << "------ a removed touch"<<r<<"\n";
    
    currentTouchScale = 0;
    
    if (!buildMode){
        
//        touches.erase(touches.end()); //pop the last element off 
//        attractors.erase(attractors.end()); //pop the last element off 
    }
}

float testApp::distanceBetweenTouches(MTouch t1, MTouch t2){
    return powf((pow(t1.x-t2.x, 2)+pow(t1.y-t2.y, 2)), 0.5);
}

bool testApp::saveLevel(string name){
//    xml.clear(); //bump loaded data out of the xml object (later could have progress save options by omitting this?)
    
    xml.addTag("fixedAttractors");
        xml.pushTag("fixedAttractors");
            for (int i=0; i<fixedAttractors.size(); i++){
                xml.addTag("attractor");
                xml.pushTag("attractor", xml.getNumTags("attractor")-1); //push last tag (the one just added)
                    xml.addValue("posX",fixedAttractors[i].posX);
                    xml.addValue("posY",fixedAttractors[i].posY);
                    xml.addValue("range",fixedAttractors[i].range);
                xml.popTag();
            }
        xml.popTag();
    
    xml.saveFile(name+".sol");
    
    return true; //possibly will be some condition later that means save could fail
}

bool testApp::loadLevel(string name){
    xml.clear();
    if (!xml.loadFile(name+".sol")){
        cout << "The level \""<<name<<".sol\" could not be found\n";
        return false; //
    }
    
    string xmlDump;
    xml.copyXmlToString(xmlDump);
    
    cout <<"loaded string gives: "<<xmlDump<<"\n";
    
    xml.pushTag("fixedAttractors");
    
    for (int i=0; i<xml.getNumTags("attractor"); i++){
        xml.pushTag("attractor", i);
        
        ParticleAttractor newFixedAttractor(xml.getValue("posX", 0), xml.getValue("posY", 0), xml.getValue("range", 0.0), red, true, 100);
        fixedAttractors.push_back(newFixedAttractor);
        cout << "posX is: "<<newFixedAttractor.posX<<", posY is: "<<newFixedAttractor.posY<<", range is: "<<newFixedAttractor.range<<"\n";
        
        xml.popTag();
    }
    xml.popTag();
    
    return true;
}
