// 1. place listen() in update
// 2. can use either listen() to get the vector array
//    or getPoints();





#include "oscClient.h"

oscClient::oscClient(){
    receiver.setup(3333);
}

vector<ofPoint> oscClient::listen(){
    
    vector<ofPoint> _points;
    
    while( receiver.hasWaitingMessages() )
    {

        ofxOscMessage m;
        receiver.getNextMessage( &m );
        
        if ( m.getAddress() == "/point" )
        {
            float x = ofMap(m.getArgAsFloat(0), 0, 1, 0, ofGetWidth());
            float y = ofMap(m.getArgAsFloat(1), 0, 1, 0, ofGetHeight());
            _points.push_back(ofPoint(x,y, 0.0));
//            cout << m.getArgAsFloat(0) << " : " << m.getArgAsFloat(1) << "\n";
        }
    }
    
    points = _points;
    return _points;
}


vector<ofPoint> oscClient::getPoints(){
    return points;
}