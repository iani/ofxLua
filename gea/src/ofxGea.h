//
//  ofxGea.h
//  gea
//
//  Created by Aris Bezas on 2/3/14.
//
//

#ifndef __gea__ofxGea__
#define __gea__ofxGea__

#pragma once
#include "ofxOsc.h"
#define HOST "localhost"
#define LuaReceiverPort 46100
#define NUM_MSG_STRINGS 20

#include <iostream>
class ofxGea{
public:
	
    void setup();
    void update();
        
};
#endif /* defined(__gea__ofxGea__) */
