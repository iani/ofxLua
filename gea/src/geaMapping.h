//
//  geaMapping.h
//  gea
//
//  Created by Aris Bezas on 2/8/14.
//
//

#ifndef __gea__geaMapping__
#define __gea__geaMapping__

#include <iostream>

#endif /* defined(__gea__geaMapping__) */
#ifndef _GAMUZAMAPPING
#define _GAMUZAMAPPING

#define MAPPING_FILE	"/Users/ari/Tools/openFrameworks/repository/openFrameworks/addons/ofxLua/gea/bin/data/xml/projection/mapping.xml"
// EXTERNAL TEXT EDITOR COMUNICATION
#define GAMUZA_CONSOLE_LOG              0
#define GAMUZA_CONSOLE_ERROR            1



#include "matrixAreas.h"

class ofxGeaMapping {
    
public:

    // from gamuzaMain
    
    // MAPPING --> gamuzaMapping.h
    int                     res;
    int                     realRes;
    bool                    saveMappingSettings;
    bool                    drawGrid=true;

    matrixAreas             finalTextureMapping;
    int                     totalMappingPoints;
    int                     actualMappingPoint;
    bool                    manualEditMappingPoint;
    bool                    activateMouseMapping;
    


    // SCREENS settings
    int                     projectionScreenW;
    int                     projectionScreenH;
    float					INVprojectionScreenW;
    float					INVprojectionScreenH;
    
    // MAPPING settings
    int                     gridRes;
    int                     fboNumSamples;


    // AUTOMATION settings
    bool					autoPilot;
    int                     autoPilotScreen;
    bool					autoLoadScript;
    bool					autoLoadMapping;
    string					autoScriptFile;
    string					autoMappingFile;


    //////////////////////////////////////////////
    // FBO --> gamuzaFBO.h
    ofFbo					drawingFbo;
    ofFbo                   gamuzaFbo;
//    ofxFastFboReader        pixelsReader;
    ofPixels                gamuzaPixels;
    ofShader				shaderColorCorrection;
    ofImage                 tempFrame;
    
    float                   fboDrawingW;
    float                   fboDrawingH;
    float                   fboDrawingPosX;
    float                   fboDrawingPosY;
    
    char					shaderName[64];
    float					fbo_gammaCorrection;
    float					fbo_brightness;
    float					fbo_saturation;
    float					fbo_contrast;
    float					fbo_filmBleach;
    float					fbo_techniColor;
    float					fbo_whiteDiffusion;
    float					fbo_exposure;
    float					fbo_diffusion;
    //////////////////////////////////////////////


    void setupMapping();
    void updateMapping();
    void drawMapping();
    void resetMappingPoints();
    void loadMappingPoints();
    void saveMappingPoints();
    void toggleDrawGrid();
    bool switchMouseKeyControl();
    void manualPointEditON();
    void manualPointEditOFF();
    void northMappingPoint();
    void southMappingPoint();
    void eastMappingPoint();
    void westMappingPoint();
    void applyHomography();
    void applyGridMesh(int xCalib, int yCalib, int w, int h);

};
#endif
