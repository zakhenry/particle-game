//
//  noise.cpp
//  emptyExample
//
//  Created by Todd Ziller on 25/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "noise.h"


Noise::Noise(float newPitch){
    
    
    beat.loadSound("sounds/electric.wav");
    beat.setSpeed(1.0f);
    beat.play();
    
    //cout<< "constructor with Pitch" << newPitch;
    //z = newPitch*3;
    
    //cout<< "Pass newPitch:" << z;
    
    //
    //beats.loadSound(ofToDataPath("/sounds/beat2.wav"));
    
    // beat.loadSound("sounds/electric.wav");
    //cout << ofToDataPath("/sounds/beat2.wav");
    beat.setVolume(0.75f);
//    beat.setMultiPlay(false);
    beat.setLoop(true);
// 
    beat.setSpeed(0.2f);
    
     cout << "newnoise played\n";
}