#ifndef _TEST_APP
#define _TEST_APP
#define OF_ADDON_USING_OFXXMLSETTINGS

#include "ofMain.h"
#include "ofxMultiTouchPad.h"
#include "particle.h"
#include "particleAttractor.h"
#include "particleEmitter.h"
#include "particleObstacle.h"
#include "levelHandler.h"
#include "particleTarget.h"
#include "oscClient.h"
#include "noise.h"

class testApp : public ofBaseApp{
	
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    
    
    float 	counter;
    bool	bSmooth;
    
    void padUpdates(int & t);
    void newTouch(int & n);
    void removedTouch(int & r);
    
    float distanceBetweenTouches(MTouch t1, MTouch t2);
    
    void clearLevel();
    
    vector<Particle>particles;
    vector<ParticleAttractor>attractors;
    vector<ParticleAttractor>fixedAttractors;
    vector<ParticleEmitter>emitters;
    vector<ParticleObstacle>obstacles;
    vector<ParticleTarget>targets;
    
//    ofColor playerColor, particleColor, red, green, blue, cyan, magenta, yellow, black;
    int attractorColor, particleColor, obstacleColor, targetColor;
    
    
    vector<ofPoint>touches2;
    vector<MTouch> touches;
    
    ofSoundPlayer beat;
    
    
    oscClient reciever;

    ofxMultiTouchPad pad;
    
    
    LevelHandler levelHandler;

    
    //private:
    
    
};

#endif

