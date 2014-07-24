#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

using namespace cv;
using namespace ofxCv;

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
	
	
	int kw;
	int kh;
	
	ofImage				kittensOI;
	ofxCvColorImage		kittensOCV;
	cv::Mat				kittensCVM;
	unsigned char*		kittensUC;
	ofPixels			kittensP;
	ofTexture			kittensT;
	
	ofxCvColorImage		regionOCV;
	void				extractRectangleRegion();
	void				getNewExtractions(); 
	
	vector<ofRectangle>		rectanglesOF;
	vector<ofxCvColorImage> regionsCV;
	vector<ofxCvColorImage> regionsUpsideDownCV;
	vector<ofxCvGrayscaleImage>	regionsUpsideDownAndGrayCV;
	
};
