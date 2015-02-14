//
//  ofxMidiLua.cpp
//  ofxLuaExample
//
//  Created by Aris Bezas on 4/22/13.
//
//

#include "ofxMidiLua.h"
void ofxMidiLua::setup() {
    
    for (int i=0; i<200; i++) {
        tempMidiValue[i]=-10;
    }
    // print input ports to console
	midiIn.listPorts(); // via instance
	//ofxMidiIn::listPorts(); // via static as well
	
	// open port by number (you may need to change this)
	midiIn.openPort(0);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input");	// open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add testApp as a listener
	midiIn.addListener(this);
    midiMessage.value=0;
	
	// print received messages to the console
	//midiIn.setVerbose(true);
}
void ofxMidiLua::init(int midiID, float initValue) {
    tempMidiValue[midiID]=initValue;
}

void ofxMidiLua::update() {
    tempMidiValue[midiMessage.control] = midiMessage.value;
}
int ofxMidiLua::num(int midiID) {
    return tempMidiValue[midiID];
}
float ofxMidiLua::map(int midiID, float min, float max, float x0) {
    //cout << ofMap(tempMidiValue[midiID], 0, 127, min, max) << endl;
    if(tempMidiValue[midiID] == -10) {
        cout << "NULL" << endl;
        return x0;
    } else {
        return ofMap(tempMidiValue[midiID], 0, 127, min, max);
    }
}

//float ofxMidiLua::map(int midiID, float min, float max, float x0) {
//    //cout << ofMap(tempMidiValue[midiID], 0, 127, min, max) << endl;
//
//    return ofMap(tempMidiValue[midiID], 0, 127, min, max);
//}

void ofxMidiLua::newMidiMessage(ofxMidiMessage& msg) {
	midiMessage = msg;
}
