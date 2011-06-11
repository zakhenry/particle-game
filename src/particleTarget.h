//
//  particleTarget.h
//  emptyExample
//
//  Created by Zak Henry on 25/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _PARTICLE_TARGET // if this class hasn't been defined, the program can define it
#define _PARTICLE_TARGET // by using this if statement you prevent the class to be called more 
// than once which would confuse the compiler

#include "ofMain.h"
#include "particle.h"

class Particle; //forward declaration so this class can access the methods and vars of particle

class ParticleTarget {
	
	//private
    
    void rotateCoordAboutPoint(float angle, float originX, float originY, float xInit, float yInit, float &xEnd, float &yEnd);
    
    bool particleInRange(double particlePosX, double particlePosY);
    float particleDistanceOff(double particlePosX, double particlePosY);
    
    vector<Particle>fixedParticles;
    
    
    
public:
    
    int posX, posY;
    float radius;
    
    bool full;
    
    int color;
    ParticleTarget(int posX, int posY, int radius, int color); //constructor (void)
    
    
    int influenceParticles(vector<Particle>& particles);
    
    ofSoundPlayer beat;
    
    
	int draw(bool GL3D, float &target);
    int updatePos(int posX, int posY);
	
	
};









#endif