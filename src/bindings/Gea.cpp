/*
 * Copyright (c) 2014 Aris Bezas <aribezas@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/igoumninja/ofxLua branch gea for documentation
 *
 */
#include "ofApp.h"
#include "ofxGea.h"
#include "ofxMidiLua.h"
#include "ofxLua.h"

// get global app pointer and cast type to your custom ofApp
ofApp* getApp() {return (ofApp*) ofGetAppPtr();}

namespace bindings {

luabind::scope registerGea() {

    using namespace luabind;

    return
        
            ///////////////////////////////
            /// \section geaOSC.h
    
            class_<ofxGea>("gea")
                .def(constructor<>())
                .def("setup", (void(ofxGea::*)()) &ofxGea::setup)
                .def("update", (void(ofxGea::*)()) &ofxGea::update),
                //.def("amp", (float(ofxGea::*)()) &ofxGea::amp),

            class_<ofxMidiLua>("midi")
                .def(constructor<>())
                .def("setup", (void(ofxMidiLua::*)()) &ofxMidiLua::setup)
                .def("update", (void(ofxMidiLua::*)()) &ofxMidiLua::update)
                .def("init", (void(ofxMidiLua::*)(int, float)) &ofxMidiLua::init)
                .def("map", (float(ofxMidiLua::*)(int, float, float, float)) &ofxMidiLua::map),
    
    
            def("getApp", &getApp),
    
            class_<ofApp>("app")
                .def(constructor<>())
                .def("amp", &ofApp::amp)
                .property("amp", &ofApp::amp) // readonly property
                .def("freq", &ofApp::freq)
                .property("freq", &ofApp::freq) // readonly property
                .def("note", &ofApp::note)
                .property("note", &ofApp::note) // readonly property
                .def("onset", &ofApp::onset)
                .property("onset", &ofApp::onset) // readonly property

    ;
    
}
} // namespace