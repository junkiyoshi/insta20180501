#pragma once
#include "ofMain.h"
#include "ofxTrueTypeFontUC/src/ofxTrueTypeFontUC.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	ofFbo fbo;
	ofPixels pix;
	ofxTrueTypeFontUC font;
	vector<tuple<ofColor, ofPoint, float>> circles;

	void draw_shapes(ofPoint point, float radius, ofColor color);

	void draw_circle(float radius, ofColor color);
	void draw_star(float radius, ofColor color);
	void draw_rectangle(float radius, ofColor color);
	void draw_triangle(float radius, ofColor color);
};