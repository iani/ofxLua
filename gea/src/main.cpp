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
#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofAppGlutWindow window;
    
    #ifdef TARGET_OPENGLES
        ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
    #endif
	ofSetupOpenGL(&window, 280, 124, OF_WINDOW);
//    ofSetupOpenGL(1024,500, OF_WINDOW);			// <-------- setup the GL context

    

//	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
//	ofSetupOpenGL(&window, 1280, 1024, OF_WINDOW);
    //ofSetupOpenGL(&window, 1280, 960, OF_FULLSCREEN);
	//ofSetupOpenGL(&window, 1024, 768, OF_FULLSCREEN);
	//ofSetupOpenGL(&window, 1460, 960, OF_WINDOW);
	//ofSetWindowPosition(1440,0);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
