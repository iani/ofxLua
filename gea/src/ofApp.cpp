/*
 * Copyright (c) 2012 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 */
#include "ofApp.h"


//--------------------------------------------------------------

void ofApp::test() {
    cout << "sdfgdsgsdggsd" << endl;
}

void ofApp::setup() {
    
    //******************//
    //****** GEA *******//
    //gea.setup();
    ofSetBackgroundAuto(false);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
	
	cout << "listening for osc messages on port " << LuaReceiverPort << "\n";
	receiver.setup(LuaReceiverPort);
	luaSender.setup(HOST, 46101);
    scriptID = 0;
    
	current_msg_string = 0;

    
    
	ofSetVerticalSync(true);
	ofSetLogLevel("ofxLua", OF_LOG_VERBOSE);
    
    scripts.push_back("/Users/ari/Tools/openFrameworks/repository/of_v0.8.0_osx_release/addons/ofxLua/ofGea_140116/src/lua-scripts/00-empty.lua");
	currentScript = 0;

    //******************//

	
    // init the lua state
	lua.init(true);
	
	// listen to error events
	lua.addListener(this);
	
	// run some api tests
	//runTests();
	
	// reinit the lua state, clears test data in state
	lua.init(true); // true because we want to stop on an error
	
	// bind the OF api to the lua state
	lua.bind<ofxLuaBindings>();
	
	// run a script
	lua.doScript(scripts[currentScript]);
	
	// call the script's setup() function
	lua.scriptSetup();
}

//--------------------------------------------------------------
void ofApp::update() {
    
    //******************//
    //****** GEA *******//
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
        
        // GEA SCRIPT READING
		if(m.getAddress() == "addScript"){
            scripts.push_back(m.getArgAsString(0));
            scriptID++;
            runScript(scriptID);
            cout << m.getArgAsString(0) << endl;
		}
		if(m.getAddress() == "updateScript"){
            reloadScript();
		}
        
		// Machine Listening
		if(m.getAddress() == "mlab"){
            if (m.getArgAsString(0) == "amp") {
                amplitude = m.getArgAsFloat(1);
            }

		}
		if(m.getAddress() == "test"){
            reloadScript();
            cout << "ok" << endl;
		}
	}
    //******************//
    
	// call the script's update() function
	lua.scriptUpdate();
}

//--------------------------------------------------------------
void ofApp::draw() {
	// call the script's draw() function
	lua.scriptDraw();
}

//--------------------------------------------------------------
void ofApp::exit() {
	// call the script's exit() function
	lua.scriptExit();
	
	// clear the lua state
	lua.clear();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	switch(key) {
            
		case 'r':
			reloadScript();
			break;
            
		case OF_KEY_LEFT:
			prevScript();
			break;
			
		case OF_KEY_RIGHT:
			nextScript();
			break;
			
		case ' ':
			lua.doString("print(\"this is a lua string saying you hit the space bar!\")");
			break;
	}
	
	lua.scriptKeyPressed(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	lua.scriptMouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	lua.scriptMouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	lua.scriptMousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	lua.scriptMouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::errorReceived(string& msg) {
	ofLogNotice() << "got a script error: " << msg;
}

//--------------------------------------------------------------
void ofApp::reloadScript() {
	// exit, reinit the lua state, and reload the current script
	lua.scriptExit();
	lua.init(true);
	lua.bind<ofxLuaBindings>(); // rebind
	lua.doScript(scripts[currentScript]);
	lua.scriptSetup();
}

void ofApp::nextScript() {
	currentScript++;
	if(currentScript > scripts.size()-1)
		currentScript = 0;
	reloadScript();
}

void ofApp::prevScript() {
	currentScript--;
	if(currentScript < 0)
		currentScript = scripts.size()-1;
	reloadScript();
}

//******************//
//****** GEA *******//
void ofApp::runScript(int scriptID) {
    currentScript++;
	lua.scriptExit();
	lua.init();
    lua.bind<ofxLuaBindings>();
	lua.doScript(scripts[scriptID]);
	lua.scriptSetup();
}
//******************//


float ofApp::amp() {
    return amplitude;
}
