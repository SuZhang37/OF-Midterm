#pragma once
#include "ofMain.h"

enum particleMode{
    
    PARTICLE_1,
    
    
};

class demoParticle{
    
public:
    demoParticle();
    
    void setMode(particleMode newMode);
    void update();
    void draw();
    void setup();
    
    ofPoint pos;
    ofPoint vel;
    ofPoint frc;
    
    float drag;
    float uniqueVal;
    float scale;
    
    particleMode mode;
    ofSoundPlayer player_rain;
};
