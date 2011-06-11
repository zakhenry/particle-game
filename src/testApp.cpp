#include "testApp.h"

#define OF_ADDON_USING_OFXXMLSETTINGS //dunno why this is necessary, but meh, ofwiki told me to



//build cursors

ofColor tmp;

int attractorColor = 0x0098D4;
int particleColor = 0xE34700;
int obstacleColor = 0x01BB00;
int targetColor = 0xDEE8E9;

ParticleAttractor attractorCursor(-100, -100, 100, attractorColor);
ParticleEmitter emitterCursor(-100, -100, 0, 3, particleColor);
ParticleObstacle obstacleCursor(ofRectangle(-100, -100, 100, 100), 0, obstacleColor); //colors wont work yet
ParticleTarget targetCursor(200, 200, 50, targetColor);

int emitterX, emitterY;
float currentTouchScale = 0;
float cameraVerticalAngle, current3TouchHeight = 0;

bool alphaTrail = true, GL3D = false;

bool buildMode = false; //allows build and setup
bool kinectMode = false;

bool targetPlaced = false;

enum buildItem {emitter, attractor, obstacle, target} currentBuildItem;

bool saving = false; //when saving is true the key input functions are locked down
string saveString;




//--------------------------------------------------------------
void testApp::setup(){
	ofSetCircleResolution(50);
	ofBackground(255, 255, 255);
	ofSetWindowTitle("graphics example");
    
    ofHideCursor();
    
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glClear (GL_COLOR_BUFFER_BIT);
    glEnable (GL_BLEND);
    glEnable (GL_POLYGON_SMOOTH);
    glDisable (GL_DEPTH_TEST);
    glLineWidth(4.0);
    
    beat.loadSound("sounds/electric.wav");
    beat.setLoop(true);
    beat.setSpeed(0.1);
    beat.play();
    
    
    
    
    
    
    
//	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    
    // --- add the listeners
    ofAddListener(pad.update, this, &testApp::padUpdates);
    ofAddListener(pad.touchAdded, this, &testApp::newTouch);
    ofAddListener(pad.touchRemoved, this, &testApp::removedTouch);
    
    
    int cursorColor = 0xabcdef;
    ParticleAttractor newAttractor(-100, -100, 100, cursorColor); //attractors for the kinect or mouse to access
    for (int i=0; i<2; i++){ //maybe to delete
        attractors.push_back(newAttractor);
    }

    /*
    ParticleEmitter newEmitter(100, 100, -45, 2, yellow);
    emitters.push_back(newEmitter);
    
    ParticleEmitter anotherEmitter(100, 500, 0, 3, cyan);
    emitters.push_back(anotherEmitter);
    
    ParticleObstacle newObstacle(ofRectangle(300, 450, 200, 100), -45, green);
    obstacles.push_back(newObstacle);
    
    */
    currentBuildItem = attractor;
    
    
     
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    
        
    ofSetBackgroundAuto(!alphaTrail);
    
    vector<ParticleAttractor>allAttractors; //concat vectors
    
    allAttractors.insert(allAttractors.end(), attractors.begin(), attractors.end());
    allAttractors.insert(allAttractors.end(), fixedAttractors.begin(), fixedAttractors.end());
    
    vector<ParticleObstacle>allObstacles; //concat vectors
    vector<ParticleTarget>allTargets; //concat vectors
    allObstacles.insert(allObstacles.end(), obstacles.begin(), obstacles.end()); //chuck existing obstacles into temp vector
    allTargets.insert(allTargets.end(), targets.begin(), targets.end()); //chuck existing targets into temp vector
    
    if (buildMode){
        
        switch (currentBuildItem) {
            case attractor:
                //do something
                attractorCursor.updatePos(mouseX, mouseY);
                allAttractors.insert(allAttractors.end(), attractorCursor);
                break;
                
            case emitter:
                //do something
                emitterCursor.updatePosition(mouseX, mouseY);
                emitterCursor.update(allAttractors, obstacles, targets);
                break;
                
            case obstacle:
                //do something
                obstacleCursor.updatePosDim(ofRectangle(mouseX, mouseY, obstacleCursor.rectangle.width, obstacleCursor.rectangle.height));
                
                allObstacles.insert(allObstacles.end(), obstacleCursor);

                break;
                
            case target:
                //do something
                targetCursor.updatePos(mouseX, mouseY);
                
                allTargets.insert(allTargets.end(), targetCursor);
                
                break;
                
            default:
                break;
        }
                    
    }
    
    for (int i=0; i<emitters.size(); i++){
        emitters[i].update(allAttractors, allObstacles, targets); //update every emitter (and in turn every particle will be updated, so the attractors will work)
    }
    
    if (kinectMode){
        
        vector<ofPoint>kinectPoints;
        
        kinectPoints = reciever.listen();
        
        if (kinectPoints.size()>0){
            for (int i=0; i<kinectPoints.size(); i++){
                attractors[i].updatePos(kinectPoints[i].x, kinectPoints[i].y);
//                cout << "x: "<<kinectPoints[i].x<<"y:"<<kinectPoints[i].y<<"\n";
            }
        }
        
        
    }else{
        if (pad.getTouchCount()>0&&!buildMode){
            
            pad.getTouchesAsOfPoints(touches2); //function already cleans up the touches vector
            
            for (int i=0; i<pad.getTouchCount(); i++){
                attractors[i].updatePos(touches2[i].x*ofGetWidth(), touches2[i].y*ofGetHeight());
            }
        }
    }
    
    
    
    
    
//    cout << "there is "<<attractors.size()<<" attractors on the pad\n";
    
//    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
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
    
    for (int i=0; i<obstacles.size(); i++){
        obstacles[i].draw(GL3D);
    }
    
    for (int i=0; i<fixedAttractors.size(); i++){
        fixedAttractors[i].draw(GL3D);
    }
    
    for (int i=0; i<targets.size(); i++){ //should only go once
        float completed;
        
        targets[i].draw(GL3D, completed);
        beat.setSpeed(completed);
    }
    
    for (int i=0; i<attractors.size(); i++){
        attractors[i].draw(GL3D);
    }
    
    
    
    
    
    
    
    
    
    if (buildMode){
        switch (currentBuildItem) {
            case attractor:
                //do something
                attractorCursor.draw(GL3D);
                break;
                
            case emitter:
                //do something
                emitterCursor.draw(GL3D);
                break;
                
            case obstacle:
                //do something
                obstacleCursor.draw(GL3D);
                break;
                
            case target:
                //do something
                float nothing;
                targetCursor.draw(GL3D, nothing);
                break;
                
            default:
                break;
        }
    }
    
    
    
    if (GL3D){
        glPopMatrix();
        
    }
    
    
    
    if (alphaTrail){
        ofSetColor(250, 250, 250, 50);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        
        //TRAIL 
//        float trail = 16.0;
//        glAccum(GL_MULT, trail/32); 
//        glAccum(GL_ACCUM, 1 - (trail/32));
//        glAccum(GL_RETURN, 1);
        
    }
    
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    cout << "Key #" << key << " pressed \n";
    if (saving){
        
        if (key == 13){ //enter (endl)
            //go through save routine
            
            levelHandler.saveLevel(saveString, fixedAttractors, emitters, obstacles, targets);
            
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
                
            case 'b':
                alphaTrail = !alphaTrail; //toggle alpha blending
                break;
                
            case '3':
                GL3D = !GL3D; //toggle 3D perspective
                break;
                
            case 'r':
            {
                if (buildMode){
                    clearLevel();
                }
            }
            break;
                
            case 13:
                buildMode = !buildMode;
                break;
                
            case 'c': //clear
                if (buildMode){
                    attractors.erase(attractors.begin(), attractors.end());
                }
                break;
                
            case 's': //save
                saving = true;
                break;
                
            case 'l': //load
                clearLevel(); //stops overwriting the points
                levelHandler.loadLevel("savegame", fixedAttractors, emitters, obstacles, targets);
                break;
                
            case 'a': //attractor mode
                currentBuildItem = attractor;
                break;
                
            case 'e': //emitter mode
                currentBuildItem = emitter;
                break;
                
            case 'o': //obstacle mode
                currentBuildItem = obstacle;
                break;
                
            case 't': //obstacle mode
                currentBuildItem = target;
                break;
                
            case 'k': //obstacle mode
                kinectMode = !kinectMode; //toggle between using the osc recieved kinect points and the trackpad
                break;
                
                
            case 127: //backspace
            {
                switch (currentBuildItem) {
                    case attractor:
                        if (fixedAttractors.size()!=0){
                            fixedAttractors.erase(fixedAttractors.end());
                        }
                        break;
                        
                    case emitter:
                        if (emitters.size()!=0){
                            emitters.erase(emitters.end());   
                        }
                        break;
                        
                    case obstacle:
                        if (obstacles.size()!=0){
                            obstacles.erase(obstacles.end());
                        }
                        break;
                        
                    case target:
                        if (targets.size()!=0){
                            targets.erase(targets.end());
                            targetPlaced = false;
                        }
                        break;
                        
                        
                        
                    default:
                        break;
                }
            }
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
                switch (currentBuildItem) {
                    case attractor:
                        
                        cout << "placed an attractor\n";
                        fixedAttractors.push_back(attractorCursor);
                        break;
                        
                    case emitter:
                        emitters.push_back(emitterCursor);
                        break;
                        
                    case obstacle:
                        obstacles.push_back(obstacleCursor);
                        break;
                        
                    case target:
                        if (!targetPlaced){
                            targets.push_back(targetCursor);
                        }
                        targetPlaced = true;
                        break;
                        
                    default:
                        break;
                }
                
            }
                break;
                
            case 2: //right click
            {
                if (currentBuildItem==attractor){
                    ParticleAttractor newUserAttractor(x, y, attractorCursor.range, attractorColor);
                    attractors.push_back(newUserAttractor);
                }
                
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
                float alteration = 0;
                    if (newTouchScale>currentTouchScale){
                        alteration ++;
                    }else{
                        alteration --;
                    }
                
                switch (currentBuildItem) {
                    case attractor:
                        attractorCursor.range += alteration/2;
                        break;
                        
                    case emitter:
                        emitterCursor.particleSpeed += alteration/40;
                        break;
                        
                    case obstacle:
                        //do something
                        obstacleCursor.rectangle.width += alteration/2;
                        obstacleCursor.rectangle.height += alteration/2;
                        break;
                        
                    case target:
                        //do something
                        targetCursor.radius += alteration/4;
                        break;
                        
                    default:
                        break;
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
                    float alteration;
                    
                    if (averageTouchHeight>current3TouchHeight){
                        alteration++;
                    }else{
                        alteration--;
                    }
                    
                    if (!buildMode&&GL3D){
                        
                        cameraVerticalAngle += alteration*5;
                        
                    }else if (buildMode){
                        switch (currentBuildItem) {
                            case attractor:
                                //do nothing
                                break;
                                
                            case emitter:
                                emitterCursor.streamAngle -= alteration*2;
                                break;
                                
                            case obstacle:
                                //do something
                                obstacleCursor.rotation += alteration*2;
                                break;
                                
                            default:
                                break;
                        }

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

}

float testApp::distanceBetweenTouches(MTouch t1, MTouch t2){
    return powf((pow(t1.x-t2.x, 2)+pow(t1.y-t2.y, 2)), 0.5);
}

void testApp::clearLevel(){
//    attractors.erase(attractors.begin(), attractors.begin()+attractors.size());
    fixedAttractors.erase(fixedAttractors.begin(), fixedAttractors.begin()+fixedAttractors.size());
    emitters.erase(emitters.begin(), emitters.end());
    obstacles.erase(obstacles.begin(), obstacles.end());
    targets.erase(targets.begin(), targets.end());
    
    /*ParticleAttractor newAttractor(-100, -100, 100, cyan); //attractor for the trackpad to access
    for (int i=0; i<5; i++){ //maybe to delete
        attractors.push_back(newAttractor);
    }*/
}
