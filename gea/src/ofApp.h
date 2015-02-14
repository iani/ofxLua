#pragma once

#include "ofMain.h"
#include "ofxLua.h"

//******************//
//****** GEA *******//
#include "ofxOsc.h"
#include "ofxGea.h"
#define HOST "localhost"
#define NUM_MSG_STRINGS 20
//******************//

#include "ofxLuaBindings.h"	// the OF api -> lua binding

class ofApp : public ofBaseApp, ofxLuaListener {
    
public:
    
    // main
    void setup();
    void update();
    void draw();
    void exit();
    
    // input
    void keyPressed(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    // ofxLua error callback
    void errorReceived(string& msg);
    
    // a bunch of api tests
    //void runTests();
    
    // script control
    void reloadScript();
    void nextScript();
    void prevScript();
    
    ofxLua lua;
    vector<string> scripts;
    int currentScript;
    
    //******************//
    //****** GEA *******//

    void runScript(int scriptID);

    ofxOscReceiver receiver;
    ofxOscSender	luaSender;
    
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    string scriptDirectory;
    int scriptID;
    
    float mlab[100];
    float amp();
    float amplitude;
    float freq();
    float frequency;
    bool onset();
    bool onsetBool;
    
    //******************//
    //****** Other *****//
    
    float midiNote;
    float note();
    ofCamera cam;
    
    
    //****** Shaders ****//
    //*******************//
    ofShader shader;
    bool doShader;
};

