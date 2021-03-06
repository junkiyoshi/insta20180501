#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(39);
	ofSetWindowTitle("Insta");

	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 230, true, true);
	this->fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->fbo.begin();

	ofSetColor(0);
	string word_1 = "500";
	this->font.drawString(word_1, ofGetWidth() / 2 - this->font.stringWidth(word_1) / 2, ofGetHeight() / 2);
	string word_2 = "days";
	this->font.drawString(word_2, ofGetWidth() / 2 - this->font.stringWidth(word_2) / 2, ofGetHeight() / 2 + this->font.stringHeight(word_1));

	this->fbo.end();
	this->fbo.readToPixels(this->pix);
}

//--------------------------------------------------------------
void ofApp::draw() {

	//this->fbo.draw(0, 0);

	while (circles.size() < 1500) {

		int x = ofRandom(ofGetWidth());
		int y = ofRandom(ofGetHeight());

		ofColor pix_color = this->pix.getColor(x, y);
		if (pix_color != ofColor(0)) {

			continue;
		}

		ofColor color;
		color.setHsb(ofRandom(255), 239, 239);
		ofPoint point = ofPoint(x, y);
		float radius = ofRandom(2, 20);

		bool flag = true;
		for (int i = 0; i < circles.size(); i++) {

			if (point.distance(get<1>(circles[i])) < get<2>(circles[i]) + radius) {

				flag = false;
				break;
			}
		}

		if (flag) {

			circles.push_back(make_tuple(color, point, radius));
		}
	}

	for (int circles_index = 0; circles_index < circles.size(); circles_index++) {

		ofColor color = get<0>(circles[circles_index]);
		ofPoint point = get<1>(circles[circles_index]);
		float radius = get<2>(circles[circles_index]);

		this->draw_shapes(point, radius, color);
	}

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::draw_shapes(ofPoint point, float radius, ofColor color) {

	ofPushMatrix();
	ofTranslate(point);

	ofSetColor(color);
	int type = ofRandom(4);
	switch (type) {
	case 0:
		this->draw_circle(radius, color);
		break;
	case 1:
		this->draw_star(radius, color);
		break;
	case 2:
		this->draw_rectangle(radius, color);
		break;
	case 3:
		this->draw_triangle(radius, color);
		break;
	}

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::draw_circle(float radius, ofColor color) {

	if (ofRandom(1) < 0.2) {

		ofNoFill();
		ofDrawCircle(ofPoint(0, 0), radius);

		ofFill();
		ofSetColor(color);
		float tmp_deg = ofRandom(360);
		ofPoint point = ofPoint(radius * 0.6 * cos((tmp_deg + ofGetFrameNum()) * DEG_TO_RAD), radius * 0.6 * sin((tmp_deg + ofGetFrameNum()) * DEG_TO_RAD));
		ofDrawCircle(point, radius * 0.3);

	}
	else {

		ofFill();
		ofDrawCircle(ofPoint(0, 0), radius);

		ofSetColor(39);
		float tmp_deg = ofRandom(360);
		ofPoint point = ofPoint(radius * 0.6 * cos((tmp_deg + ofGetFrameNum()) * DEG_TO_RAD), radius * 0.6 * sin((tmp_deg + ofGetFrameNum()) * DEG_TO_RAD));
		ofDrawCircle(point, radius * 0.3);
	}
}

//--------------------------------------------------------------
void ofApp::draw_star(float radius, ofColor color) {

	ofRandom(1) < 0.2 ? ofNoFill() : ofFill();
	ofRotate(ofRandom(360));
	radius = ofMap(ofNoise(ofRandom(1) + ofGetFrameNum() * 0.05), 0, 1, radius * 0.5, radius);

	ofBeginShape();
	for (int deg = 0; deg < 360; deg += 30) {

		if (deg % 60 == 0) {

			ofVertex(radius * 0.5 * cos(deg * DEG_TO_RAD), radius * 0.5 * sin(deg * DEG_TO_RAD));
		}
		else {

			ofVertex(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		}
	}
	ofEndShape(true);
}

//--------------------------------------------------------------
void ofApp::draw_rectangle(float radius, ofColor color) {

	ofRandom(1) < 0.2 ? ofNoFill() : ofFill();
	ofRotate(ofRandom(360));

	ofColor tmp_color;
	tmp_color.setHsb((int)(ofRandom(255) + ofGetFrameNum()) % 255, 239, 239);
	ofSetColor(tmp_color);

	ofDrawRectangle(ofPoint(), radius, radius);
}

//--------------------------------------------------------------
void ofApp::draw_triangle(float radius, ofColor color) {

	ofRandom(1) < 0.2 ? ofNoFill() : ofFill();
	ofRotate(ofRandom(360) + ofGetFrameNum());

	ofBeginShape();
	for (int deg = 0; deg < 360; deg += 120) {

		ofVertex(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
	}
	ofEndShape(true);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}