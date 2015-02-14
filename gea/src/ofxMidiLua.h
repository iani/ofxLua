//
//  ofxMidiLua.h
//  ofxLuaExample
//
//  Created by Aris Bezas on 4/22/13.
//
//

#ifndef __ofxLuaExample__ofxMidiLua__
#define __ofxLuaExample__ofxMidiLua__

#include <iostream>
#include "ofMain.h"
#include "ofxMidi.h"

class ofxMidiLua : public ofBaseApp, public ofxMidiListener {
    
public:
    void			setup();
    void			update();
    void			init(int midiID, float initialVallue);
    int             num(int midiID);
    float           map(int midiID, float min, float max, float x0);
    
	void newMidiMessage(ofxMidiMessage& eventArgs);
	
	
	ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;
    int tempMidiValue[200];
    float x0;
    
	
};

#endif /* defined(__ofxLuaExample__ofxMidiLua__) */
