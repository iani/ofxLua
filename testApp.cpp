/*
 * Copyright (c) 2011 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 */
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
    scriptID = 0;
    
	current_msg_string = 0;
    scriptDirectory = "scripts/graphicsExample.lua";
    
	core.setup();
}

//--------------------------------------------------------------
void testApp::update() {
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}
    
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message
		if(m.getAddress() == "test"){
            cout << "ok" << endl;
		}
		if(m.getAddress() == "addScript"){
            //core.scripts.pop_back();
            core.scripts.push_back(m.getArgAsString(0));
            scriptID++;
            core.runScript(scriptID);
            //core.scripts.push_back("scripts/graphicsExample.lua");
            cout << m.getArgAsString(0) << endl;
		}
		if(m.getAddress() == "updateScript"){
            core.reloadScript();
		}
	}

	core.update();
}

//--------------------------------------------------------------
void testApp::draw() {
	core.draw();
}

//--------------------------------------------------------------
void testApp::exit() {
	core.exit();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	core.keyPressed(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
	core.mouseMoved(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
	core.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	core.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
	core.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {}
