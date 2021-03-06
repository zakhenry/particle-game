//
//  particle.h
//  particle attractor
//
//  Created by Zak Henry on 15/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _PARTICLE // if this class hasn't been defined, the program can define it
#define _PARTICLE // by using this if statement you prevent the class to be called more 
// than once which would confuse the compiler

#include "ofMain.h"
#include "particleAttractor.h"
#include "particleObstacle.h"
#include "particleTarget.h"

class Particle {
    
    bool inBoundingBox(int boundingX, int boundingY, int boxWidth, int boxHeight);
	
public:
    
    Particle(float posX, float posY, float speed, float direction, int color); //constructor (void)
    
    float posX;
    float posY;
    bool destroy;
    float speed;
    float direction; //degrees
    
    int color;
    
    void update();
    
	int draw(bool GL3D);
	
};









#endif 