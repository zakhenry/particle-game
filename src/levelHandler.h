//
//  levelHandler.h
//  emptyExample
//
//  Created by Zak Henry on 24/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _LEVEL_HANDLER // if this class hasn't been defined, the program can define it
#define _LEVEL_HANDLER // by using this if statement you prevent the class to be called more 
// than once which would confuse the compiler

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "particleAttractor.h"
#include "particleEmitter.h"
#include "particleObstacle.h"

class LevelHandler {
	
	//private
    ofxXmlSettings xml;
    vector<string>levels;
    int attractorColor, particleColor, obstacleColor, targetColor;
    
public:
    
    LevelHandler(); //constructor
    
    bool saveLevel(string name, vector<ParticleAttractor>attractors, vector<ParticleEmitter>emitters, vector<ParticleObstacle>obstacles, vector<ParticleTarget>targets); //set item positions
    bool loadLevel(string name, vector<ParticleAttractor>&attractors, vector<ParticleEmitter>&emitters, vector<ParticleObstacle>&obstacles, vector<ParticleTarget>&targets); //get item positions
//    void clearLevel();
    int listLevels(string dir, vector<string> &files);
    
};









#endif