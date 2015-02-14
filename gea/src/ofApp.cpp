/*
 * Copyright (c) 2012 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 * Modified my Aris Bezas <igoumeninja@gmail.com>
 */

#include "ofApp.h"

//ofApp* getApp() {return (ofApp*) ofGetAppPtr();}
//--------------------------------------------------------------

void ofApp::setup() {
    
    //******************//
    //****** GEA *******//
    ofSetCircleResolution(5);
    ofSetBackgroundAuto(false);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
	
	cout << "listening for osc messages on port " << LuaReceiverPort << "\n";
	receiver.setup(12345);
	luaSender.setup(HOST, 46101);
    scriptID = 0;
    
	current_msg_string = 0;
    
	ofSetVerticalSync(true);
	ofSetLogLevel("ofxLua", OF_LOG_VERBOSE);
    
    scripts.push_back("/Users/ari/Tools/openFrameworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-lua-scripts/startup.lua");
	currentScript = 0;

    //****** SHADERS *******//
    #ifdef TARGET_OPENGLES
    shader.load(
                "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.vert",
                "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.frag");

    #else
        if(ofGetGLProgrammableRenderer()){
            shader.load(
                        "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.vert",
                        "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.frag");
        }else{
            shader.load(
                        "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.vert",
                        "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.frag");
        }
    #endif
    
    doShader = true;	
    
    //******************//
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
    
    onsetBool = false;
    
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
        
        //Shaders
        if(m.getAddress() == "updateShaders"){
            //test load shader
#ifdef TARGET_OPENGLES
            shader.load(
                        "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.vert",
                        "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.frag");
            
#else
            if(ofGetGLProgrammableRenderer()){
                shader.load(
                            "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.vert",
                            "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.frag");
            }else{
                shader.load(
                            "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/ab.vert",
                            "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/ab.frag");
            }
#endif
        }
        if(m.getAddress() == "doShader") {doShader = !doShader;}
		// Machine Listening
		if(m.getAddress() == "/amp"){
            amplitude = m.getArgAsFloat(0);
            //cout << amplitude << endl;
        }
		if(m.getAddress() == "/freq"){
            frequency = m.getArgAsFloat(0);
            //cout << m.getArgAsFloat(0)  << endl;
        }
		if(m.getAddress() == "/onset"){
            onsetBool = true;
        }
        if(m.getAddress() == "/note"){
            midiNote = m.getArgAsFloat(0);
            cout << m.getArgAsFloat(0) << endl;
        }

    }
    //******************//
    
	// call the script's update() function
	lua.scriptUpdate();
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    
//    ofSetColor(0,0,0,10);
//    ofRect(0, 0, ofGetWidth(), ofGetHeight());
//    cam.begin();
//    cam.orbit(200*(1+sin(ofGetFrameNum()*0.001)),200*(1+sin(ofGetFrameNum()*0.001)), 100*(1+sin(ofGetFrameNum()*0.01)));
    //****** SHADERS *******//
    if( doShader ){
        shader.begin();
        //we want to pass in some varrying values to animate our type / color
        shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
        shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );

        lua.scriptDraw();
        shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
        
        shader.end();
    }   else {
        lua.scriptDraw();
    }
    
    
//    cam.end();
 
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
		case 'f':
            if(ofGetWindowMode() == 0){
                ofSetFullscreen(true);
                ofBackground(0, 0, 0);
            }else{
                ofSetFullscreen(false);
                ofBackground(0, 0, 0);
            }
			break;
         
        case 'b':
            ofBackground(0, 0, 0);
            break;

        case 'r':
			reloadScript();
			break;
		case 'm':
            ofHideCursor();
			break;
		case 'M':
            ofShowCursor();
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
    if( key == 's' ){
        doShader = !doShader;
    }
    if( key == 'p' ){
        //test load shader
#ifdef TARGET_OPENGLES
        shader.load(
                    "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.vert",
                    "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.frag");
        
#else
        if(ofGetGLProgrammableRenderer()){
            shader.load(
                        "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.vert",
                        "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/noise.frag");
        }else{
            shader.load(
                        "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/ab.vert",
                        "/Users/ari/Tools/openframeworks/of_v0.8.4_osx_release/addons/ofxLua/gea/bin/data/scripts/my-shaders/of-example/ab.frag");
        }
#endif
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
    amplitude = ofRandom(200,400);
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
	// exit, reinit the lua state, anofSetCircleResolution()d reload the current script
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
float ofApp::freq() {
    return frequency;
}
bool ofApp::onset() {
    return onsetBool;
}
float ofApp::note() {
    return midiNote;
}


