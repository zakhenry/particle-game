//
//  particleObstacle.cpp
//  emptyExample
//
//  Created by Zak Henry on 24/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "particleObstacle.h"


ParticleObstacle::ParticleObstacle(ofRectangle newRectangle, float newRotation, bool newReflect, ofColor newColor){ //constructor
    //	cout << "Particle attractor created \n";
    
    rectangle = newRectangle;
    rotation = newRotation;
    color = newColor;
    reflectParticles = newReflect;
}


int ParticleObstacle::influenceParticles(vector<Particle>& particles){
    
//    cout << "obstacle is influencing "<<particles.size()<<" particles \n"; 
    
    for (int i=0; i<particles.size(); i++){
        float particleRotX, particleRotY;
        rotateCoordAboutPoint(rotation, rectangle.x+rectangle.width/2, rectangle.y+rectangle.height/2, particles[i].posX, particles[i].posY, particleRotX, particleRotY);
        
        if (rectangle.inside(particleRotX, particleRotY)){
//            cout << "particle is inside obstacle\n";
            setNewParticleVelocity(particles[i], reflectParticles);
        }
    }
    
    return 0;
}

void ParticleObstacle::setNewParticleVelocity(Particle& particle, bool reflect){
    
    if (reflect){
        //work some reflection magic
    }else{
        particle.destroy = true; // 'absorb' the particle
    }
    
}

int ParticleObstacle::updatePosDim(ofRectangle newRect, float newRotation){
    rectangle = newRect;
    rotation = newRotation;
    return 0;
}


int ParticleObstacle::draw(bool GL3D){
    ofSetColor(color.r, color.g, color.b);
    
    if (GL3D){
        ofNoFill();
//        ofRect(rectangle.x, rectangle.y, rectangle.width, rectangle.height);
    }else{
        ofPushMatrix();
        ofTranslate(rectangle.x+rectangle.width/2, rectangle.y+rectangle.height/2, 0);//, rectangle.x+rectangle.width/2, 0, rectangle.y+rectangle.height/2
        ofRotateZ(rotation);
        ofFill();		// draw "filled shapes"
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(0, 0, rectangle.width, rectangle.height);
        ofPopMatrix();
    }
    
    
    
}

void ParticleObstacle::rotateCoordAboutPoint(float angle, float originX, float originY, float xInit, float yInit, float &xEnd, float &yEnd){
    
    float radAngle = ofDegToRad(angle);
    xInit -= originX; //move global origin to specified origin
    yInit -= originY; 
    
	xEnd = xInit*cos(radAngle)+yInit*sin(radAngle);
	yEnd = -xInit*sin(radAngle)+yInit*cos(radAngle);
    
    xEnd += originX; //pop back global origin
    yEnd += originY;
}