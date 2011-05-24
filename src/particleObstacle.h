//
//  particleObstacle.h
//  emptyExample
//
//  Created by Zak Henry on 24/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef _PARTICLE_OBSTACLE // if this class hasn't been defined, the program can define it
#define _PARTICLE_OBSTACLE // by using this if statement you prevent the class to be called more 
// than once which would confuse the compiler

#include "ofMain.h"
#include "particle.h"

class Particle; //forward declaration so this class can access the methods and vars of particle

class ParticleObstacle {
	
	//private
    
    
    bool particleInHitbox(float particlePosX, float particlePosY);
    void rotateCoordAboutPoint(float angle, float originX, float originY, float xInit, float yInit, float &xEnd, float &yEnd);
    
    bool reflectParticles;
    
    
    
    
	
public:
    ofColor color;
    ofRectangle rectangle;
    float rotation;
    ParticleObstacle(ofRectangle rectangle, float rotation, bool reflect, ofColor color); //constructor (void)
    
    
    int influenceParticles(vector<Particle>& particles);
    void setNewParticleVelocity(Particle& particle, bool reflect);
    
    
	int draw(bool GL3D);
    int updatePosDim(ofRectangle);
	
	
};









#endif