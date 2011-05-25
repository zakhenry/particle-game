//
//  particleEmitter.h
//  emptyExample
//
//  Created by Zak Henry on 7/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _PARTICLE_EMITTER // if this class hasn't been defined, the program can define it
#define _PARTICLE_EMITTER // by using this if statement you prevent the class to be called more 
// than once which would confuse the compiler

#include "ofMain.h"
#include "particle.h"

class Particle;

class ParticleEmitter {
	
	//private
    
    
    bool addParticle;
    int lastSecondFired;
    
    
	
public:
    
    int posX, posY;
    
    ofColor color;
    
    float particleSpeed, streamAngle;
    string type;
    vector<Particle>particles;

    ParticleEmitter(int posX, int posY, float angle, float particleSpeed, ofColor color); //stream constructor
    
    void updatePosition(int newX, int newY);
    
	void update(vector<ParticleAttractor>&attractors, vector<ParticleObstacle>&obstacles, vector<ParticleTarget>&targets);
    void draw(bool GL3D);
};









#endif