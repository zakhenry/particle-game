//
//  particleTarget.cpp
//  emptyExample
//
//  Created by Zak Henry on 25/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "particleTarget.h"


ParticleTarget::ParticleTarget(int newX, int newY, int newRadius, ofColor newColor){ //constructor
    cout << "Particle target created \n";
    
    posX = newX;
    posY = newY;
    radius = newRadius;
    color = newColor;
}


int ParticleTarget::influenceParticles(vector<Particle>& particles){
    
    //    cout << "obstacle is influencing "<<particles.size()<<" particles \n"; 
    
    for (int i=0; i<particles.size(); i++){
        
        if (particleInRange(particles[i].posX, particles[i].posY)){
            //            cout << "particle is inside obstacle\n";
            particles[i].destroy = true;
        }
    }
    
    return 0;
}

int ParticleTarget::updatePos(int newX, int newY){
    posX = newX;
    posY = newY;
    return 0;
}

int ParticleTarget::draw(bool GL3D){
    ofSetColor(color.r, color.g, color.b);
    
    ofFill();		// draw "filled shapes"
    ofCircle(posX, posY, radius);
    
        /*if (counter){
         ofBeginShape();
         int resolution = 100;
         float sweep = trappedParticles.size()/particleMax; //0 to 1
         //            cout <<"particle count: "<<trappedParticles.size()<<" max:"<<particleMax<<"\n";
         if (sweep>1){
         sweep = 1;
         color.g = 255;
         }
         float radius1 = min(rectangle.width, rectangle.height)/2-10;
         float radius2 = radius1-10;
         for(int i = 0; i <= resolution; i++) { 
         float angle = i*sweep*2*PI/resolution; 
         ofVertex((cos(angle) * radius1), (sin(angle) * radius1));
         }
         for(int i = resolution+1; i != 0; i--) { 
         float angle = i*sweep*2*PI/resolution; 
         ofVertex((cos(angle) * radius2), (sin(angle) * radius2));
         }
         ofEndShape();
         }*/
    
    
    
}


void ParticleTarget::rotateCoordAboutPoint(float angle, float originX, float originY, float xInit, float yInit, float &xEnd, float &yEnd){
    
    float radAngle = ofDegToRad(angle);
    xInit -= originX; //move global origin to specified origin
    yInit -= originY; 
    
	xEnd = xInit*cos(radAngle)+yInit*sin(radAngle);
	yEnd = -xInit*sin(radAngle)+yInit*cos(radAngle);
    
    xEnd += originX; //pop back global origin
    yEnd += originY;
}

bool ParticleTarget::particleInRange(double particlePosX, double particlePosY){
    float distanceOff = particleDistanceOff(particlePosX, particlePosY);
    
    if (distanceOff<=1){
        return true;
    }else{
        return false;
    }
}

float ParticleTarget::particleDistanceOff(double particlePosX, double particlePosY){ //(number 0 to 1 if in range)
    return powf((pow(posX-particlePosX, 2)+pow(posY-particlePosY, 2)), 0.5)/radius;
}