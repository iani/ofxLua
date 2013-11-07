//
//  ofxOscLua.cpp
//  ofxLuaExample
//
//  Created by Aris Bezas on 5/7/13.
//
//

#include "ofxOscLua.h"

void ofxOscLua::setup(){
	cout << "Lua script listening for osc messages on port " << PORT2 << "\n";
	receiver.setup(PORT2);
	current_msg_string = 0;
}

//--------------------------------------------------------------
void ofxOscLua::update(){
	for(int i = 0; i < NUM_MSG_STRINGS2; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}
	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        for (int i=0; i < oscResponder.size(); i++) {
            if(m.getAddress() == oscResponder[i]){
                oscRespoderValue[i] = m.getArgAsFloat(0);
                cout << m.getArgAsFloat(0) << endl;
            }
        }
    }
}

float ofxOscLua::var(string varName) {
//    for (int i=0; i < oscResponder.size(); i++) {
//        if (varName == oscResponder[i]) {
//            return oscRespoderValue[i];
//        }
//    }
}
void ofxOscLua::resp(string respName) {
    oscResponder.push_back(respName);
//    for (int i=0; i < oscResponder.size(); i++) {
//        if (respName != oscResponder[i]) {
//            oscResponder.push_back(respName);
//            cout << "add" << endl;
//        }
//    }
}
