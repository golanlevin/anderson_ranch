#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	kittensOI.loadImage("kittens.jpg");
	kw = kittensOI.width;
	kh = kittensOI.height;
	kittensOCV.allocate(kw, kh);
	
	kittensUC  = kittensOI.getPixels(); // extract unsigned chars
	kittensOCV = kittensUC;
	kittensCVM = toCv(kittensOI);


	getNewExtractions();
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofBackground (100);
	
	ofSetColor(255);
	// kittensOI.draw(0,0);
	kittensOCV.draw(0,0);

	// draw all of the source rectangles
	for (int i=0; i<rectanglesOF.size(); i++){
		ofNoFill();
		ofSetColor(ofColor::greenYellow);
		ofRect(rectanglesOF[i]);
	}
	
	
	if (regionsCV.size() > 0){
		int nRegions = regionsCV.size();
		
		//----------------------
		// draw the extracted regions
		ofPushMatrix();
		ofTranslate(0, kittensOCV.height + 10);
		ofScale(0.5, 0.5);
	
		for (int i=0; i<nRegions; i++){
			float px = (i%6)*150;
			float py = (i/6)*100;
			ofSetColor(255);
			regionsCV[i].draw(px,py);
		}
		ofPopMatrix();
		
		
		//----------------------
		// draw the upside-down regions
		ofPushMatrix();
		ofTranslate(kittensOCV.width+10, kittensOCV.height + 10);
		ofScale(0.5, 0.5);

		for (int i=0; i<nRegions; i++){
			float px = (i%6)*150;
			float py = (i/6)*100;
			ofSetColor(255);
			regionsUpsideDownCV[i].draw(px,py);
		}
		ofPopMatrix();
		
		
		
		//----------------------
		// draw the upside-down regions
		ofPushMatrix();
		ofTranslate(0, kittensOCV.height + 10 + 200);
		ofScale(0.5, 0.5);
		
		for (int i=0; i<nRegions; i++){
			float px = (i%6)*150;
			float py = (i/6)*100;
			ofSetColor(255);
			regionsUpsideDownAndGrayCV[i].draw(px,py);
			//drawMat(regionsUpsideDownAndGrayCV[i], px,py);
		}
		ofPopMatrix();

		
		
		
		
		
		
		
	}
	
	
}


//--------------------------------------------------------------
void ofApp::getNewExtractions(){
	
	
	int nRectangles = (int)ofRandom(10,20);
	
	// Make some rectangles
	rectanglesOF.clear();
	for (int i=0; i<nRectangles; i++){
		float rx = kittensOI.width  * ofRandom(0.00, 0.79);
		float ry = kittensOI.height * ofRandom(0.00, 0.79);
		float rw = kittensOI.width  * ofRandom(0.10, 0.20);
		float rh = kittensOI.height * ofRandom(0.10, 0.20);
		ofRectangle R;
		R.set(rx,ry,rw,rh);
		rectanglesOF.push_back(R);
	}
	
	//----------------
	//Extract some regions
	regionsCV.clear();
	for (int i=0; i<nRectangles; i++){
		int rwi = (int) rectanglesOF[i].width;
		int rhi = (int) rectanglesOF[i].height;
		
		ofxCvColorImage aRegionOCV;
		aRegionOCV.allocate(rwi,rhi);
		
		ofRectangle aRectangle = rectanglesOF[i];
		kittensOCV.setROI(aRectangle);
		aRegionOCV = kittensOCV.getRoiPixels();
		
		regionsCV.push_back(aRegionOCV);
	}
	
	//----------------
	// Take the extracted ones, and make upside-down copies
	regionsUpsideDownCV.clear();
	for (int i=0; i<nRectangles; i++){
		ofxCvColorImage anUpsideDownRegionOCV;
		anUpsideDownRegionOCV = regionsCV[i];
		anUpsideDownRegionOCV.mirror(true, false);
		regionsUpsideDownCV.push_back(anUpsideDownRegionOCV);
	}
	
	
	//----------------
	// Get gray versions
	regionsUpsideDownAndGrayCV.clear();
	for (int i=0; i<nRectangles; i++){
		int rwi = (int) rectanglesOF[i].width;
		int rhi = (int) rectanglesOF[i].height;
		
		ofxCvGrayscaleImage aLocalGrayscaleVersion;
		aLocalGrayscaleVersion.allocate(rwi, rhi);
		aLocalGrayscaleVersion.setFromColorImage (regionsUpsideDownCV[i]);
		aLocalGrayscaleVersion.threshold(127);
		//aLocalGrayscaleVersion.erode();
		
		regionsUpsideDownAndGrayCV.push_back(aLocalGrayscaleVersion);
	}
	
	

}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	getNewExtractions();

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
