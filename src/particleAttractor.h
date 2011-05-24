//
//  particleAttractor.h
//  particle attractor
//
//  Created by Zak Henry on 15/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _PARTICLE_ATTRACTOR // if this class hasn't been defined, the program can define it
#define _PARTICLE_ATTRACTOR // by using this if statement you prevent the class to be called more 
// than once which would confuse the compiler

#include "ofMain.h"
#include "particle.h"

class Particle;

class ParticleAttractor {
	
	//private
    
    
    float particleDistanceOff(double particlePosX, double particlePosY);
    float angleBetweenAngles(float angleA, float angleB, bool clockwise);

	
public:
    ofColor color;
    
    ParticleAttractor(int posX, int posY, float range, ofColor color); //constructor (void)
    
    int posX;
    int posY;
    float range;

    int influenceMagnitude;
    
    bool particleInRange(double particlePosX, double particlePosY, float& distanceOff);
    int influenceParticle(int particlePosX, int particlePosY, float particleDirection, float particleVelocity, float& particleNewDirection, float& particleNewVelocity);
    
    
    int influenceParticles(vector<Particle>& particles);
    void setNewParticleVelocity(Particle& particle, float attractionStrength, float proximity);
    
    
	int draw(bool GL3D);
    int updatePos(int newX, int newY);
	
    //	int calcInverse(float, float, float, float&, float&, float&); // inverse kinematics
	
};









#endif