#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(3);

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	bool flag = true;
	auto x = 0;

	for (int radius = 50; radius <= 300; radius += 100) {

		int deg_start = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -360, 360);

		for (int deg = deg_start; deg < deg_start + 360; deg += 1) {

			ofPushMatrix();
			ofRotate(deg);

			auto base_location = glm::vec2(x, radius);
			auto target_location = glm::vec2(x, radius + 80);
			auto distance = target_location - base_location;
			auto len = glm::length(distance);
			auto noise_seed = ofRandom(1000);

			vector<glm::vec2> vertices;
			for (int d = 0; d <= len; d++) {

				auto location = base_location + glm::normalize(distance) * d;

				auto gap = abs(len * 0.5 - d);
				auto power = gap < len * 0.35 ? 1 : ofMap(gap, len * 0.35, len * 0.5, 1, 0);

				auto noise_x = ofMap(ofNoise(noise_seed, location.x * 0.05, location.y * 0.015 + ofGetFrameNum() * 0.05), 0, 1, -10, 10);
				location += glm::vec2(noise_x * power, 0);

				vertices.push_back(location);
			}

			ofColor color;
			color.setHsb(ofMap(deg, deg_start, deg_start + 360, 0, 255), 200, 255);

			ofSetColor(color);

			ofNoFill();
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape();

			ofFill();
			ofDrawCircle(vertices.front(), 2);
			ofDrawCircle(vertices.back(), 2);

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}