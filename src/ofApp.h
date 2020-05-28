#pragma once

#include "ofMain.h"
#include "ofxCvHaarFinder.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();
        void keyPressed(int key);
    
    //Floats
    float time;
    
    float circleCenterX;
    float circleCenterY;
    float circleRadius;

    float value;
    float sendValue;
    
    //Serial Comunication
    ofSerial serial;
    string sensorValue;
    int byteData;
    string msg;

    //UI Functions
    void myCircle();
    void myKnob(int x);
    
    //Font
    ofTrueTypeFont font;
    
    //OpenCV + Webcam + HaarFinder
    ofVideoGrabber camera;
    ofxCvColorImage color;
    ofxCvGrayscaleImage gray;
    ofxCvHaarFinder haar;

    //Application text
    string text;
    string text_2;
};
