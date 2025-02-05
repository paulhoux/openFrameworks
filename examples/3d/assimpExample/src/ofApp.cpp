#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(50, 0);

	ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.

	bAnimate = false;
	bAnimateMouse = false;
	animationPosition = 0;

	model.load("astroBoy_walk.dae", false);
	model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
	model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	model.playAllAnimations();
	if(!bAnimate) {
		model.setPausedForAllAnimations(true);
	}

	bHelpText = true;

}

//--------------------------------------------------------------
void ofApp::update(){
	model.update();

	if(bAnimateMouse) {
		model.setPositionForAllAnimations(animationPosition);
	}

	mesh = model.getCurrentAnimatedMesh(0);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	ofEnableDepthTest();
#ifndef TARGET_PROGRAMMABLE_GL
	glShadeModel(GL_SMOOTH); //some model / light stuff
#endif
	light.enable();
	ofEnableSeparateSpecularLight();

	ofPushMatrix();
	ofTranslate(model.getPosition().x+100, model.getPosition().y, 0);
	ofRotateDeg(-mouseX, 0, 1, 0);
	ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
	model.drawFaces();
	ofPopMatrix();
#ifndef TARGET_PROGRAMMABLE_GL
	glEnable(GL_NORMALIZE);
#endif
	ofPushMatrix();
	ofTranslate(model.getPosition().x-300, model.getPosition().y, 0);
	ofRotateDeg(-mouseX, 0, 1, 0);
	ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);

	ofxAssimpMeshHelper & meshHelper = model.getMeshHelper(0);

	ofMultMatrix(model.getModelMatrix());
	ofMultMatrix(meshHelper.matrix);

	ofMaterial & material = meshHelper.material;
	if(meshHelper.hasTexture()){
		meshHelper.getTextureRef().bind();
	}
	material.begin();
	mesh.drawWireframe();
	material.end();
	if(meshHelper.hasTexture()){
		meshHelper.getTextureRef().unbind();
	}
	ofPopMatrix();

	ofDisableDepthTest();
	light.disable();
	ofDisableLighting();
	ofDisableSeparateSpecularLight();

	if(bHelpText){
	ofSetColor(255, 255, 255 );
	stringstream ss;
	ss << "FPS: " << ofToString(ofGetFrameRate(),0) <<endl<<endl;
	ss <<"(keys 1-5): load models"<<endl;
	ss << "num of animations in this model: " + ofToString(model.getAnimationCount());
	ss <<endl <<"(Spacebar): toggle animation"<<endl;
	ss <<"(LEFT MOUSE BUTTON DRAG in y-axis): control animation."<<endl;
	ss <<"(h): toggle help."<<endl;
	ofDrawBitmapString(ss.str().c_str(), 20, 20);

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	glm::vec3 modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75, 0);
	switch (key) {
		case '1':
			model.load("astroBoy_walk.dae");
			model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
			ofEnableSeparateSpecularLight();
			break;
		case '2':
			model.load("TurbochiFromXSI.dae");
			model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
			ofEnableSeparateSpecularLight();
			break;
		case '3':
			model.load("dwarf.x");
			model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
			ofDisableSeparateSpecularLight();
			break;
		case '4':
			model.load("monster-animated-character-X.X");
			model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
			model.setRotation(0, -90, 0, 0, 1);
			ofDisableSeparateSpecularLight();
			break;
		case '5':
			model.load("squirrel/NewSquirrel.3ds");
			model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
			ofDisableSeparateSpecularLight();
			break;
		case ' ':
			bAnimate = !bAnimate;
			break;
		case 'h':
			bHelpText = !bHelpText;
			break;
		default:
			break;
	}

	mesh = model.getMesh(0);

	model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	model.playAllAnimations();
	if(!bAnimate) {
		model.setPausedForAllAnimations(true);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	//
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	// scrub through aninations manually.
	animationPosition = y / (float)ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	// pause all animations, so we can scrub through them manually.
	model.setPausedForAllAnimations(true);
	animationPosition = y / (float)ofGetHeight();
	bAnimateMouse = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	// unpause animations when finished scrubbing.
	if(bAnimate) {
		model.setPausedForAllAnimations(false);
	}
	bAnimateMouse = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

