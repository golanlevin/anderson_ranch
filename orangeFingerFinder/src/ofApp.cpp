#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){

    cam.initGrabber(640, 480);
    myOrangeColor.set(ofColor::salmon);
    
    camw = cam.getWidth();
    camh = cam.getHeight();
    foundOrangePixels = new unsigned char [camw * camh];
    foundOrangeImage.allocate(camw,camh,OF_IMAGE_GRAYSCALE);
    
    
    contourFinder.setUseTargetColor(true);
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(200);
    
    gui.setup(); // most of the time you don't need a name
    gui.add(threshold.setup("threshold", 42, 0, 255, 256,20 ));
    gui.add(smoothing.setup("smoothing", 37, 0, 100, 256,20 ));
    
    fingerX = fingerY = 0; 
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0,0,0);
    
    //threshold = ofMap(mouseX, 0,ofGetWidth(), 0,255);
    
    cam.update();
	if(cam.isFrameNew()) {
        
        unsigned char* cameraPixels = cam.getPixels();
        int nChans = 3;  // assume camera pixel format is OF_PIXELS_RGB

        for (int y=0; y<camh; y++){
            for (int x=0; x<camw; x++){
                
                int srcIndex = (y*camw + x)*nChans;
                int rIndex = srcIndex  ;
                int gIndex = srcIndex+1;
                int bIndex = srcIndex+2;
                
                unsigned char pixR = cameraPixels[rIndex];
                unsigned char pixG = cameraPixels[gIndex];
                unsigned char pixB = cameraPixels[bIndex];
                
                int dr = pixR - myOrangeColor.r;
                int dg = pixG - myOrangeColor.g;
                int db = pixB - myOrangeColor.b;
                
                int dstIndex = y*camw + x;
                float colorDist = sqrt(dr*dr + dg*dg + db*db); // Pythagoras
                if (colorDist < threshold){
                    foundOrangePixels[dstIndex] = 255;
                } else {
                    foundOrangePixels[dstIndex] = 0;
                }
            }
            foundOrangeImage.setFromPixels(foundOrangePixels, camw, camh, OF_IMAGE_GRAYSCALE);
        }
    
       
        contourFinder.setThreshold(threshold);
        contourFinder.findContours(foundOrangeImage);
        
        vector<ofPolyline> polys = contourFinder.getPolylines();
        for (int i=0; i<polys.size(); i++){
   
            ofPolyline aBlobContourPolyline = contourFinder.getPolyline(i);
            aBlobContourPolyline.simplify();
            filteredPolyline = aBlobContourPolyline.getResampledBySpacing(3.0);
            filteredPolyline = filteredPolyline.getSmoothed(smoothing);
            
            int nPoints = filteredPolyline.size();
            int indexOfSharpest = 0;
            float maxAngle = -99999;
            for (int p=0; p<nPoints; p++){
                float angleAtP = filteredPolyline.getAngleAtIndex(p);
                if (angleAtP > maxAngle){
                    maxAngle = angleAtP;
                    indexOfSharpest = p;
                }
            }
            ofPoint sharpestPoint = filteredPolyline[indexOfSharpest];
            fingerX = sharpestPoint.x;
            fingerY = sharpestPoint.y;
            
        }
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofColor::white);
    cam.draw(0,0,camw,camh);
    
    foundOrangeImage.draw(camw,0,camw,camh);

    vector<ofPolyline> polys = contourFinder.getPolylines();
    if (polys.size() == 1){
        ofSetLineWidth(2);
        ofSetColor(0,222,222);
        contourFinder.getPolyline(0).draw();
        ofSetColor(0,255,0);
        filteredPolyline.draw();
    }
    
    ofEnableAlphaBlending();
    ofSetColor (255,255,0, 100);
    ofEllipse(fingerX, fingerY, 60,60);
    
    ofFill();
    ofSetColor(myOrangeColor);
    ofRect(0,camh,100,100);
    
    ofSetColor(255,255,255);
    float val = (float)threshold;
    ofDrawBitmapString( ofToString(val) , 20,camh+20);
    
    gui.draw();
    
    
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    myOrangeColor = cam.getPixelsRef().getColor(x, y);
}













//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
