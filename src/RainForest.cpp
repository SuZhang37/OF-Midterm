#include "RainForest.hpp"

ofImage bananaTree;


//------------------------------------------------------------------
RainForest::RainForest(){

    pos.x=0;
    pos.y=150;
    bananaTree.load("image/bananaTree.png");

    
}


//------------------------------------------------------------------
void RainForest::growth(){
    


    //if(ofGetMousePressed()){
    
        weight = .004;
        pos.y -= (dist + pos.y)*weight;
    //}
    
    
    
}


//------------------------------------------------------------------
void RainForest::draw(){

bananaTree.draw(pos.x, pos.y, ofGetWidth(), ofGetHeight());
    
    
    
}


//------------------------------------------------------------------
void RainForest::keyPressed(int key){

    }

//------------------------------------------------------------------
void RainForest::mousePressed(int x, int y, int button){
    
}
