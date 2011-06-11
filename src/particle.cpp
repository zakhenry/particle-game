//
//  particle.cpp
//  particle attractor
//
//  Created by Zak Henry on 15/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "particle.h"



Particle::Particle(float newX, float newY, float newSpeed, float newDirection, int newColor){ //constructor
    
    posX = newX;
    posY = newY;
    speed = newSpeed;
    direction = newDirection;
    
    destroy = false;
    color = newColor;
    
    //	cout << "Particle attractor created. "<<"Velocity is: "<<speed<<" \n";
}

void Particle::update(){
    
    if (direction>180){
        direction = -360+direction;
    }else if (direction<(-180)){
        direction = 360+direction;
    }
    
//    cout << "angle of particle is: " << direction << "\n";
    
    posX += cos(ofDegToRad(-direction))*speed;
    posY += sin(ofDegToRad(-direction))*speed;
    
    if (!inBoundingBox(0, 0, ofGetWidth(), ofGetHeight())){
        destroy = true;
    }
    
}
 
bool Particle::inBoundingBox(int boundingX, int boundingY, int boxWidth, int boxHeight){
    
    if (posX<boundingX||posX>(boxWidth-boundingX)){
        return false;
    }else if (posY<boundingY||posY>(boxHeight-boundingY)){
        return false;
    }
    
    return true;
}

int Particle::draw(bool GL3D){
    
    ofSetColor(color);
    
    if (GL3D){
        glVertex3f(posX, 10, posY);
    }else{
        ofFill();		// draw "filled shapes"
        ofCircle(posX, posY, 5);
    }
    
    
    

    return 0;
}





