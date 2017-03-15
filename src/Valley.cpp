
#include "Valley.hpp"
ofImage lily;

//------------------------------------------------------------------
Valley::Valley(){
    pos.x=0;
    pos.y=150;
    dist = pos.x;
    lily.load("image/lily.png");
}

//------------------------------------------------------------------
void Valley::growth(){
    
    
    // if(ofGetMousePressed()){
    
    weight = .005;
    pos.y -= (dist + pos.y)*weight;
    // }
    
    
}

//------------------------------------------------------------------
void Valley::draw(){
    
    lily.draw(pos.x,pos.y,ofGetWidth(),ofGetHeight());
    
    //ofDrawRectangle(pos.x,pos.y,50,800);
    
}


