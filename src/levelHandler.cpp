//
//  levelHandler.cpp
//  emptyExample
//
//  Created by Zak Henry on 24/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "levelHandler.h"
#define OF_ADDON_USING_OFXXMLSETTINGS //possibly not necessary

LevelHandler::LevelHandler(){ //stream constructor
    
    cout << "Level handler created\n";
    listLevels("../../../data", levels);
    
    cout << "There is "<<levels.size()<<" levels available (";
    for (int i=0; i<levels.size(); i++){
        cout << levels[i]<<", ";
    }
    cout << ")\n";
    
    ofColor black;
    black.r = 0;
    black.g = 0;
    black.b = 0;
    red = blue = green = black;
    
    red.r = 255;
    green.g = 255;
    blue.b = 255;
    magenta = red;
    magenta.b = 255;
    
    
}

bool LevelHandler::saveLevel(string name, vector<ParticleAttractor>attractors, vector<ParticleEmitter>emitters, vector<ParticleObstacle>obstacles, vector<ParticleTarget>targets){
    //    xml.clear(); //bump loaded data out of the xml object (later could have progress save options by omitting this?)
    
    xml.addTag("attractors");
    xml.pushTag("attractors");
    for (int i=0; i<attractors.size(); i++){
        xml.addTag("attractor");
        xml.pushTag("attractor", xml.getNumTags("attractor")-1); //push last tag (the one just added)
        xml.addValue("x",attractors[i].posX);
        xml.addValue("y",attractors[i].posY);
        xml.addValue("range",attractors[i].range);
        xml.popTag();
    }
    xml.popTag();
    
    xml.addTag("emitters");
    xml.pushTag("emitters");
    for (int i=0; i<emitters.size(); i++){
        xml.addTag("emitter");
        xml.pushTag("emitter", xml.getNumTags("emitter")-1); //push last tag (the one just added)
        xml.addValue("x",emitters[i].posX);
        xml.addValue("y",emitters[i].posY);
        xml.addValue("angle",emitters[i].streamAngle);
        xml.addValue("speed",emitters[i].particleSpeed);
        xml.popTag();
    }
    xml.popTag();
    
    xml.addTag("obstacles");
    xml.pushTag("obstacles");
    for (int i=0; i<obstacles.size(); i++){
        xml.addTag("obstacle");
        xml.pushTag("obstacle", xml.getNumTags("obstacle")-1); //push last tag (the one just added)
        xml.addValue("x",obstacles[i].rectangle.x);
        xml.addValue("y",obstacles[i].rectangle.y);
        xml.addValue("width",obstacles[i].rectangle.width);
        xml.addValue("height",obstacles[i].rectangle.height);
        xml.addValue("rotation",obstacles[i].rotation);
        xml.popTag();
    }
    xml.popTag();
    
    xml.addTag("targets");
    xml.pushTag("targets");
    for (int i=0; i<targets.size(); i++){
        xml.addTag("target");
        xml.pushTag("target", xml.getNumTags("target")-1); //push last tag (the one just added)
        xml.addValue("x",targets[i].posX);
        xml.addValue("y",targets[i].posY);
        xml.addValue("radius",targets[i].radius);
        xml.popTag();
    }
    xml.popTag();
    
    
    
    xml.saveFile(name+".sol");
    
    return true; //possibly will be some condition later that means save could fail
}

bool LevelHandler::loadLevel(string name, vector<ParticleAttractor>&attractors, vector<ParticleEmitter>&emitters, vector<ParticleObstacle>&obstacles, vector<ParticleTarget>&targets){
    xml.clear();
    if (!xml.loadFile(name+".sol")){
        cout << "The level \""<<name<<".sol\" could not be found\n";
        return false; //
    }
    
    string xmlDump;
    xml.copyXmlToString(xmlDump);
    
    cout <<"loaded string gives: "<<xmlDump<<"\n";
    
    xml.pushTag("attractors");
    for (int i=0; i<xml.getNumTags("attractor"); i++){
        xml.pushTag("attractor", i);
        ParticleAttractor newFixedAttractor(xml.getValue("x", 0), xml.getValue("y", 0), xml.getValue("range", 0.0), red);
        attractors.push_back(newFixedAttractor);
        //        cout << "posX is: "<<newFixedAttractor.posX<<", posY is: "<<newFixedAttractor.posY<<", range is: "<<newFixedAttractor.range<<"\n";
        xml.popTag();
    }
    xml.popTag();
    
    xml.pushTag("emitters");
    for (int i=0; i<xml.getNumTags("emitter"); i++){
        xml.pushTag("emitter", i);
        ParticleEmitter newEmitter(xml.getValue("x", 0), xml.getValue("y", 0), xml.getValue("angle", 0), xml.getValue("speed", 0.0), green); //int posX, int posY, float angle, float particleSpeed, ofColor color
        emitters.push_back(newEmitter);
        xml.popTag();
    }
    xml.popTag();
    
    xml.pushTag("obstacles");
    for (int i=0; i<xml.getNumTags("obstacle"); i++){
        xml.pushTag("obstacle", i);
        ParticleObstacle newObstacle(ofRectangle(xml.getValue("x", 0), xml.getValue("y", 0), xml.getValue("width", 0), xml.getValue("height", 0)), xml.getValue("x", 0), blue); 
        obstacles.push_back(newObstacle);
        xml.popTag();
    }
    xml.popTag();
    
    xml.pushTag("targets");
    for (int i=0; i<xml.getNumTags("target"); i++){
        xml.pushTag("target", i);
        ParticleTarget newTarget(xml.getValue("x", 0), xml.getValue("y", 0), xml.getValue("radius", 0), magenta); //int posX, int posY, int radius, ofColor color
        targets.push_back(newTarget);
        xml.popTag();
    }
    xml.popTag();
    
    return true;
}

int LevelHandler::listLevels(string dir, vector<string> &levels){
    
    vector<string>files;
    
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    
    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    
    string fileext = ".sol";
    for (int i=0; i<files.size(); i++){
        if (files[i].find(fileext)!=string::npos){ //if string is found
            levels.push_back(files[i]);
        }
    }
    return 0;
}
