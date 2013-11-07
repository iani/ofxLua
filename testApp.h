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
#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#include "AppCore.h"

#define PORT 46100
#define NUM_MSG_STRINGS 20

/// a desktop os app wrapper
class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		
		AppCore core;
        ofxOscReceiver receiver;
    
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
        string scriptDirectory;
        int scriptID;
    
};
