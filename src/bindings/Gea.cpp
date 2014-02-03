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
                .def("test", (void(ofxGea::*)()) &ofxGea::test)

    ;
    
}
} // namespace