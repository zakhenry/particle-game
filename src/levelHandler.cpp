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
    ofColor black;
    black.r = 0;
    black.g = 0;
    black.b = 0;
    red = blue = green = black;
    
    red.r = 255;
    green.g = 255;
    blue.b = 255;
    
    
}

bool LevelHandler::saveLevel(string name, vector<ParticleAttractor>attractors, vector<ParticleEmitter>emitters, vector<ParticleObstacle>obstacles){
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
    
    
    
    xml.saveFile(name+".sol");
    
    return true; //possibly will be some condition later that means save could fail
}

bool LevelHandler::loadLevel(string name, vector<ParticleAttractor>&attractors, vector<ParticleEmitter>&emitters, vector<ParticleObstacle>&obstacles){
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
        ParticleAttractor newFixedAttractor(xml.getValue("x", 0), xml.getValue("y", 0), xml.getValue("range", 0.0), red, true, 100);
        attractors.push_back(newFixedAttractor);
        //        cout << "posX is: "<<newFixedAttractor.posX<<", posY is: "<<newFixedAttractor.posY<<", range is: "<<newFixedAttractor.range<<"\n";
        xml.popTag();
    }
    xml.popTag();
    
    xml.pushTag("emitters");
    for (int i=0; i<xml.getNumTags("emitter"); i++){
        xml.pushTag("emitter", i);
        ParticleEmitter newEmitter(xml.getValue("x", 0), xml.getValue("y", 0), xml.getValue("angle", 0), xml.getValue("speed", 0), green); //int posX, int posY, float angle, float particleSpeed, ofColor color
        emitters.push_back(newEmitter);
        xml.popTag();
    }
    xml.popTag();
    
    xml.pushTag("obstacles");
    for (int i=0; i<xml.getNumTags("obstacle"); i++){
        xml.pushTag("obstacle", i);
        ParticleObstacle newObstacle(ofRectangle(xml.getValue("x", 0), xml.getValue("y", 0), xml.getValue("width", 0), xml.getValue("height", 0)), xml.getValue("x", 0), false, blue); //ofRectangle rectangle, float rotation, bool reflect, ofColor color
        obstacles.push_back(newObstacle);
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
