#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

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
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofVideoGrabber cam;
    int camw;
    int camh;
	ofImage foundOrangeImage;
    unsigned char *foundOrangePixels;
    
    ofColor myOrangeColor;
    ofxCv::ContourFinder contourFinder;
    ofPolyline filteredPolyline;
    float fingerX;
    float fingerY; 
    
    ofxPanel gui;
    ofxFloatSlider threshold;
    ofxFloatSlider smoothing;
    //float threshold;
    
    
		
};
