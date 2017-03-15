#include "demoParticle.hpp"

//------------------------------------------------------------------
demoParticle::demoParticle(){
    
}

//------------------------------------------------------------------
void demoParticle::setMode(particleMode newMode){
    mode = newMode;
    
}


//------------------------------------------------------------------
void demoParticle::setup(){
    uniqueVal = ofRandom(-20000, 20000);
    
    pos.x = ofRandomWidth();
    pos.y = ofRandomHeight();
    
    vel.x = 0.01;
    vel.y = fabs(vel.y) * 3.0;
    
    frc   = ofPoint(0,0);
    
    scale = ofRandom(20, 40);
    
    
    drag  = ofRandom(0.97, 0.99);

    
}

//------------------------------------------------------------------
void demoParticle::update(){
    
    float fakeWindX = ofSignedNoise(pos.x , pos.y , ofGetElapsedTimef() );
    
    frc.x = fakeWindX * 0.25;
    frc.y = ofSignedNoise(uniqueVal, pos.x , ofGetElapsedTimef()) *0.01 +0.3;
    
    vel += frc * 0.1;
    
    //we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
    if( pos.y + vel.y > ofGetHeight() ){
        pos.y -= ofGetHeight();
    }
    //}
    
    pos += vel;
    
    
    //3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN
    //we could also pass in bounds to check - or alternatively do this at the ofApp level
    if( pos.x > ofGetWidth() ){
        pos.x = ofGetWidth();
        vel.x *= -1.0;
    }else if( pos.x < 0 ){
        pos.x = 0;
        vel.x *= -1.0;
    }
    if( pos.y > ofGetHeight() ){
        pos.y = ofGetHeight();
        vel.y *= -1.0;
    }
    else if( pos.y < 0 ){
        pos.y = 0;
        vel.y *= -1.0;
    }

    
}

//------------------------------------------------------------------
void demoParticle::draw(){
    
    if(pos.x>=ofGetWidth()/2-50 && pos.x<ofGetWidth()){
        ofSetColor(255,255,255,150);
        ofDrawLine(pos.x, pos.y, pos.x, pos.y+scale);
    }
    
}
