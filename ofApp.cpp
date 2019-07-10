#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(150, 3);
	this->triangles = ico_sphere.getMesh().getUniqueFaces();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	for (auto& triangle : this->triangles) {

		auto avg = glm::vec3(triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto param = (int)(ofRandom(750) + ofGetFrameNum()) % 500;
		auto alpha = 0;
		if (param > 350) {

			alpha = ofMap(param, 350, 500, 0, 255);
		}
		else if (param < 150) {

			alpha = ofMap(param, 0, 150, 255, 0);
		}

		ofPushMatrix();
		ofTranslate(avg);
	
		vector<glm::vec3> vertices;
		for (int j = 0; j < 3; j++) {

			glm::vec3 location = glm::vec3(triangle.getVertex(j).x, triangle.getVertex(j).y, triangle.getVertex(j).z) - avg;

			vertices.push_back(location);
		}

		if (alpha > 0) {

			ofFill();
			ofSetColor(39, alpha);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(239, alpha);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}