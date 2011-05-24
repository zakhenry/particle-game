//
//  particleObstacle.cpp
//  emptyExample
//
//  Created by Zak Henry on 24/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "particleObstacle.h"


ParticleObstacle::ParticleObstacle(ofRectangle newRectangle, float newRotation, ofColor newColor){ //constructor
    cout << "Particle obstacle created \n";
    
    rectangle = newRectangle;
    rotation = newRotation;
    color = newColor;
}


int ParticleObstacle::influenceParticles(vector<Particle>& particles){
    
//    cout << "obstacle is influencing "<<particles.size()<<" particles \n"; 
    
    for (int i=0; i<particles.size(); i++){
        float particleRotX, particleRotY;
        rotateCoordAboutPoint(rotation, rectangle.x+rectangle.width/2, rectangle.y+rectangle.height/2, particles[i].posX, particles[i].posY, particleRotX, particleRotY);
        
        if (rectangle.inside(particleRotX, particleRotY)){
//            cout << "particle is inside obstacle\n";
            setNewParticleVelocity(particles[i]);
        }
    }
    
    return 0;
}

void ParticleObstacle::setNewParticleVelocity(Particle& particle){
    
    particle.destroy = true; // 'absorb' the particle

}

int ParticleObstacle::updatePosDim(ofRectangle newRect){
    rectangle = newRect;
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
        		// draw "filled shapes"
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(0, 0, rectangle.width, rectangle.height);
        ofSetRectMode(OF_RECTMODE_CORNER); //go back to normal mode
        
        ofSetColor(0, 0, 0);
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