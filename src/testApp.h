#ifndef _TEST_APP
#define _TEST_APP
#define OF_ADDON_USING_OFXXMLSETTINGS

#include "ofMain.h"
#include "ofxMultiTouchPad.h"
#include "ofxXmlSettings.h"

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
    
    bool saveLevel(string name);
    bool loadLevel(string name);
    
    float 	counter;
    bool	bSmooth;
    
    void padUpdates(int & t);
    void newTouch(int & n);
    void removedTouch(int & r);
    
    float distanceBetweenTouches(MTouch t1, MTouch t2);
    
//private:
    ofxMultiTouchPad pad;
    
    ofxXmlSettings xml;
    
    
};

#endif

