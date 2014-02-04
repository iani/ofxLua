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
#include "ofxLua.h"

//#include <luabind/operator.hpp>

namespace bindings {

luabind::scope registerGea() {

    using namespace luabind;

    return
        
            ///////////////////////////////
            /// \section geaOSC.h
            
            class_<ofxGea>("gea")
                .def(constructor<>())
                
//                .def("test", &test)
                .def("setup", (void(ofxGea::*)()) &ofxGea::setup)
                .def("update", (void(ofxGea::*)()) &ofxGea::update)
                .def("test", (void(ofxGea::*)()) &ofxGea::test)
                .def("takis", (int(ofxGea::*)()) &ofxGea::takis),
    
            class_<ofApp>("app")
                .def(constructor<>())
                .def("test", (void(ofApp::*)()) &ofApp::test)
                .def("amp", (float(ofApp::*)()) &ofApp::amp)

    ;
    
}
} // namespace