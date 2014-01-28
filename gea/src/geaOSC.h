//
//  geaOSC.h
//  gea
//
//  Created by Aris Bezas on 1/28/14.
//
//

#ifndef gea_geaOSC_h
#define gea_geaOSC_h

/// \section C++ Binding

/// bind C++ functions and objects to lua
/// this allows lua scripts to call C++ entities
///
/// see the luabind docs for syntax:
///  http://www.rasterbar.com/products/luabind/docs.html
///
///
///	create a static bind function in your class which contains the
///	luabind definitions:
///
///
///
/// your class bind function will be called automatically when using the
/// ofxLua bind function:
///
/// lua.bind<ofWrapper>();
///
///	see bindings/ofxLuaBindings.h for a much more detailed example

//--------------------------------------------------------------
void gamuzaMain::checkNetConnection(){
    
    char temp_message[512];
    
    connectionTest.Create();
    connectionUP = connectionTest.Connect("127.0.0.1", 13969);
    
    connectionTest.Close();
    
    if(connectionUP){
        sprintf(temp_message," OSC Connection UP & RUNNING");
    }else{
        sprintf(temp_message," OSC Connection DOWN");
        
    }
    sendGALog(temp_message);
    
}

//--------------------------------------------------------------
void gamuzaMain::setupOSC(){
    
	char temp_message[512];
    currentErrorLog = "";
    currentLog      = "";
    
    oscReceivingValues = new vector<string>[GA_OSC_MAX_SENDING_VARIABLES];
    
	sender.setup(host_number.c_str(),atoi(host_port.c_str()));
    receiver.setup(atoi(server_port.c_str()));
    
    sprintf(temp_message,"  - receiving at port %s",server_port.c_str());
    sendGALog(temp_message);
    sprintf(temp_message,"  - sending at host:port %s:%s",host_number.c_str(),host_port.c_str());
    sendGALog(temp_message);
    sendGALog(" ");
	
}

//--------------------------------------------------------------
void gamuzaMain::updateOSC(){
	
	char osc_name[256];
    
    ////////////////////////////////////////////
	// send custom data
	if(oscSendingLabels.size() > 0){
        for(int i=0;i<oscSendingLabels.size();i++){
            if(oscSendingActive[i] == true){
                osc_message.clear();
                sprintf(osc_name,"%s",oscSendingLabels[i].c_str());
                osc_message.setAddress(osc_name);
                if(oscSendingTypes[i] == OFXOSC_TYPE_INT32){
                    osc_message.addIntArg(ofToInt(oscSendingValues[i]));
                }else if(oscSendingTypes[i] == OFXOSC_TYPE_FLOAT){
                    osc_message.addFloatArg(ofToFloat(oscSendingValues[i]));
                }else if(oscSendingTypes[i] == OFXOSC_TYPE_STRING){
                    osc_message.addStringArg(oscSendingValues[i]);
                }
                sender.sendMessage(osc_message);
            }
        }
    }
	////////////////////////////////////////////
    
    ////////////////////////////////////////////
	// receive custom data
    receiveOSC();
    ////////////////////////////////////////////
}

//--------------------------------------------------------------
void gamuzaMain::receiveOSC(){
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
		received_message.clear();
		receiver.getNextMessage(&received_message);
        
        for(int i=0;i<oscReceivingLabels.size();i++){
            for(int a=0;a<received_message.getNumArgs();a++){
                if(received_message.getAddress() == oscReceivingLabels[i]){
                    if(received_message.getArgType(0) == OFXOSC_TYPE_INT32){
                        oscReceivingValues[i][a] = ofToString(received_message.getArgAsInt32(0));
                    }else if(received_message.getArgType(0) == OFXOSC_TYPE_FLOAT){
                        oscReceivingValues[i][a] = ofToString(received_message.getArgAsFloat(0));
                    }else if(received_message.getArgType(0) == OFXOSC_TYPE_STRING){
                        oscReceivingValues[i][a] = received_message.getArgAsString(0);
                    }
                }
            }
        }
    }
    
}

//--------------------------------------------------------------
void gamuzaMain::resetIncomingOSC(){
    if(oscReceivingLabels.size() > 0){
        oscReceivingLabels.clear();
    }
    for(int i=0;i<oscReceivingLabels.size();i++){
        if(oscReceivingValues[i].size() > 0){
            oscReceivingValues[i].clear();
        }
    }
}

//--------------------------------------------------------------
void gamuzaMain::resetOutgoingOSC(){
    if(oscSendingLabels.size() > 0){
        oscSendingLabels.clear();
    }
    if(oscSendingValues.size() > 0){
        oscSendingValues.clear();
    }
    if(oscSendingTypes.size() > 0){
        oscSendingTypes.clear();
    }
    if(oscSendingActive.size() > 0){
        oscSendingActive.clear();
    }
}

//--------------------------------------------------------------
void gamuzaMain::sendBuffer(){
	
	////////////////////////////////////////////
	// send OSC data bundle
	sender.sendBundle(osc_bundle);
	////////////////////////////////////////////
	
}

//--------------------------------------------------------------
void gamuzaMain::cleanBuffer(){
	
	////////////////////////////////////////////
	// clean OSC buffer
	osc_bundle.clear();
	osc_message.clear();
	////////////////////////////////////////////
	
}


#endif
