//
//  ofxOscLua.h
//  ofxLuaExample
//
//  Created by Aris Bezas on 5/7/13.
//
//

#ifndef __ofxLuaExample__ofxOscLua__
#define __ofxLuaExample__ofxOscLua__

#include <iostream>
#include "ofMain.h"
#include "ofxOsc.h"

#define PORT2 46100
#define NUM_MSG_STRINGS2 20


class ofxOscLua {
    
public: 
    void	setup();
    void	update();
    float   var(string varName);
    void    resp(string respName);
    
    string temp;
    vector<string> oscResponder;
    vector<float> oscRespoderValue;
    ofxOscReceiver receiver;
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS2];
    float timers[NUM_MSG_STRINGS2];
};

#endif /* defined(__ofxLuaExample__ofxOscLua__) */
