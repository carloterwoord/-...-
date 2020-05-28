#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    // Arduino setup
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    //Set Baud
    int baud = 9600;
    
    //Arduino port + baud
    serial.setup("tty.usbserial-143220", baud);
    
    //Camera setup
    camera.setup(640, 320);
    
    color.allocate(camera.getWidth(), camera.getHeight());
    gray.allocate(camera.getWidth(), camera.getHeight());
    
    //Haar setup
    haar.setup("haarcascade_frontalface.xml");
    haar.setScaleHaar(1.8);
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //Font
    font.load("Apercu.otf", 18);
    
    //UI Circle size
    circleCenterX = ofGetWidth()/2;
    circleCenterY = ofGetHeight()/2;
    circleRadius = 100;
    
    //Application text
    text = "Please take a seat in front of the screen.";
    text_2 = "Breath in.. breath out..";
    
    //Timer
    time = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    //Check if Arduino sends serial messages.
    if (serial.available() < 0) {
        sensorValue = "Arduino Error";
    }
    else {
        //Check serial messages.
        while (serial.available() > 0) {
            byteData = serial.readByte();
        }
    }
    
    //Update Camera
    camera.update();
    
    //Capture face from webcam
    if (camera.isFrameNew()){
        color.setFromPixels(camera.getPixels());
        gray = color;
        haar.findHaarObjects(gray);
        
        time++;
        // Face detection
        if (haar.findHaarObjects(gray) == true && time >= 50) {
            if (ofGetFrameNum()%45 == 0) {
                value++;
                serial.writeByte('a');
                if (value > 360) {
                    value = 0;
                    serial.writeByte('b');
                }
            }
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw Camera + Detection frame
    //    color.draw(0, 0);
    //
    //    for (int i = 0; i < haar.blobs.size(); i++) {
    //        ofSetColor(255);
    //        ofNoFill();
    //        ofDrawRectangle(haar.blobs[i].boundingRect);
    //    }
    
    // Face detection states
    if (haar.findHaarObjects(gray) == false) {
        time = 0;
        ofSetColor(ofMap(abs(sin(ofGetElapsedTimef())),0,1,0,255,true));
        font.drawString(text, ofGetWidth()/2 - font.stringWidth(text)/2, ofGetHeight()/2 - 200);
    } else {
        if (haar.findHaarObjects(gray) == true) {
        ofSetColor(ofMap(abs(sin(ofGetElapsedTimef())),0,1,0,255,true));
        font.drawString(text_2, ofGetWidth()/2 - font.stringWidth(text_2)/2, ofGetHeight()/2 - 200);
        }
    }
    ofSetColor(255);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    myKnob(value);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //Debug - hardware comunication
    switch (key) {
        case 'a':
            value++;
            serial.writeByte('a');
            cout << "Moved one step" << endl;;
            break;
        case 'b':
            serial.writeByte('b');
            cout << "Clean sweep" << endl;;
            break;
        case 'c':
            serial.writeByte('c');
            cout << "Clean sweep reversed" << endl;;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
// UI - Circle
void ofApp::myCircle(){
    ofSetCircleResolution(100);
    ofNoFill();
    ofSetLineWidth(4);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2 - 110, 0);
    ofDrawLine(100, ofGetHeight()/2, 0, ofGetHeight()/2);
    ofPopMatrix();
    ofDrawCircle(circleCenterX, circleCenterY, circleRadius);
}

//--------------------------------------------------------------
// UI - Knob
void ofApp::myKnob(int x){
    ofScale(1.5);
    ofRotateDeg(x);
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    myCircle();
    ofPopMatrix();
}
