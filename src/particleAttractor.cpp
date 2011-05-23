/*
 *  deltaKinematics.cpp
 *  Delta Sim
 *
 *  Created by Zak Henry on 8/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "particleAttractor.h"


ParticleAttractor::ParticleAttractor(int newX, int newY, float newRange, ofColor newColor, bool newFixedPoint, int newMax){ //constructor
//	cout << "Particle attractor created \n";
    posX = newX;
    posY = newY;
    
    range = newRange;
    
    color = newColor;
    max = newMax;
    fixedPoint = newFixedPoint;
}

float ParticleAttractor::angleBetweenAngles(float angleA, float angleB, bool clockwise){
    float diff = angleA - angleB;
    if (diff>=PI){
        diff-=PI*2;
    }else if(diff<=-PI){
        diff += PI*2;
    }
    if (diff<0&&clockwise){
        diff+=PI*2; //always clockwise
    }
    return diff;
}


bool ParticleAttractor::particleInRange(double particlePosX, double particlePosY, float& distanceOff){
    distanceOff = particleDistanceOff(particlePosX, particlePosY);
    
    if (distanceOff<=1){
        return true;
    }else{
        return false;
    }
}

float ParticleAttractor::particleDistanceOff(double particlePosX, double particlePosY){ //(number 0 to 1 if in range)
    return powf((pow(posX-particlePosX, 2)+pow(posY-particlePosY, 2)), 0.5)/range;
}

int ParticleAttractor::influenceParticles(vector<Particle>& particles){
    
    for (int i=0; i<particles.size(); i++){
        float distanceOff; //empty as it is passed by reference to particleInRange
        if (particleInRange(particles[i].posX, particles[i].posY, distanceOff)){
            setNewParticleVelocity(particles[i], 2, distanceOff);
        }
    }
    
    return 0;
}

void ParticleAttractor::setNewParticleVelocity(Particle& particle, float attractionBaseline, float proximity){
    
    float angleBetweenPandA = -atan2f((particle.posY-posY),(particle.posX-posX))+PI;
    float particleDirection = ofDegToRad(particle.direction);
    float directionDifference = angleBetweenAngles(particleDirection, angleBetweenPandA, true);
    
//    cout << "particle direction" << ofRadToDeg(particleDirection) << "\n";
//    cout << "angle between particle and attractor" << ofRadToDeg(angleBetweenPandA) << "\n";
//    cout << "direction difference: " << ofRadToDeg(directionDifference) << "\n\n";
//    cout << "test angle difference: " << ofRadToDeg(angleBetweenAngles(ofDegToRad(300), ofDegToRad(90)))<<"\n\n";
    
//    cout << "proximity = " << proximity << "\n";
    
    
    float attractionStrength = (1-proximity)*attractionBaseline;
    
    if (proximity<0.2){
        particle.destroy = true;
    }
  
    if(directionDifference>PI){
        particle.direction += attractionStrength;
    }else{
        particle.direction -= attractionStrength;
    }
    
    float absoluteAngleDifference = abs(angleBetweenAngles(particleDirection, angleBetweenPandA, false));
    
//    cout << "Cos absolute angle diff x current speed" << cos(absoluteAngleDifference)*particle.speed <<"\n";
    
    particle.speed = particle.speed + (cos(absoluteAngleDifference)*particle.speed)*(attractionStrength)*0.01;

    
    
    
    
}

int ParticleAttractor::updatePos(int newX, int newY){
    posX = newX;
    posY = newY;
    return 0;
}


int ParticleAttractor::draw(bool GL3D){
    ofSetColor(color.r, color.g, color.b);
    
    if (GL3D){
        ofNoFill();
        ofCircle(posX, 10, posY, range, 'y');
    }else{
        ofFill();		// draw "filled shapes"
        ofCircle(posX, posY, 5);
        ofNoFill();
        ofCircle(posX, posY, range );
        ofFill();
    }
    
    
    
}