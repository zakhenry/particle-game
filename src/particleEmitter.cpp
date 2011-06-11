//
//  particleEmitter.cpp
//  emptyExample
//
//  Created by Zak Henry on 7/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "particleEmitter.h"

ParticleEmitter::ParticleEmitter(int newPosX, int newPosY, float angle, float newParticleSpeed, int newColor){ //stream constructor

    cout << "Particle stream created\n";
    lastSecondFired = 0;
    addParticle = true;
    particleSpeed = newParticleSpeed;
    posX = newPosX;
    posY = newPosY;
    streamAngle = angle;
    color = newColor;
}

void ParticleEmitter::update(vector<ParticleAttractor>&attractors, vector<ParticleObstacle>&obstacles, vector<ParticleTarget>&targets){ //yes this is a seriously weird way to pass around influence
    
    if (particles.size()>0){
        
        for (int i=0; i<particles.size(); i++){
            particles[i].update();
            
            if (particles[i].destroy){
                particles.erase(particles.begin()+i);
            }
        }
        for (int i=0; i<attractors.size(); i++){ //for every attractor
            attractors[i].influenceParticles(particles);
        }
        
        for (int i=0; i<obstacles.size(); i++){ //for every obstacle
            obstacles[i].influenceParticles(particles);
        }
        
        for (int i=0; i<targets.size(); i++){ //for every target
            targets[i].influenceParticles(particles);
        }
    }
    
    if(ofGetElapsedTimeMillis() % 5 == 0) {
        if (lastSecondFired!=ofGetElapsedTimeMillis()){
			lastSecondFired = ofGetElapsedTimeMillis();
            
            for (int i=0; i<10; i++){
                Particle newParticle(posX, posY, particleSpeed, streamAngle, color);
                particles.push_back(newParticle);
                
            }
		}
    }
}

void ParticleEmitter::draw(bool GL3D){
    
    if (GL3D){
        glPointSize(3.0);
        glBegin(GL_POINTS); //vertical axis
    }
    
    
    for (int i=0; i<particles.size(); i++){
        particles[i].draw(GL3D);
    }
    
    if (GL3D){
        glEnd();
    }
    
//    cout << "Drawing " << particles.size() << " particles\n";
}


void ParticleEmitter::updatePosition(int newX, int newY){
    posX = newX;
    posY = newY;
}
