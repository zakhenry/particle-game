//
//  oscClient.h
//  emptyExample
//
//  Created by Tarei on 24/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#ifndef _OSCCLIENT // if this class hasn't been defined, the program can define it
#define _OSCCLIENT // by using this if statement you prevent the class to be called more 
// than once which would confuse the compiler
#include "ofxOsc.h"
#include "ofMain.h"

class oscClient {
public:
    oscClient();
    
    vector<ofPoint> listen();
    vector<ofPoint> getPoints();
    
    
    vector<ofPoint> points;
    
    
    ofxOscReceiver receiver;
    
    
};


#endif