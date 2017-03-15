#include "Desert.hpp"
ofImage cactus;
//------------------------------------------------------------------
Desert::Desert(){
    pos.x=0;
    pos.y=100;
    
    cactus.load("image/cactus.png");
}

//------------------------------------------------------------------
void Desert::growth(){
    
    // if(ofGetMousePressed()){
    
    weight = 0.002;
    pos.y -= pos.y*weight;
    
    // }

}


//------------------------------------------------------------------
void Desert::draw(){
    cactus.draw(pos.x, pos.y, ofGetWidth(), ofGetHeight());
    
    //ofDrawRectangle(pos.x,pos.y,50,800);
    
}


