
#ifndef RainForest_hpp
#define RainForest_hpp

#include <ofMain.h>
#include "ofxVectorGraphics.h"

class RainForest{
public:
    RainForest();
    void setup();
    void draw();
    void growth();
    void Image();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

    
    ofSerial serial;
    ofPoint pos;
    int dist = 100;
    float weight;

    bool day;
    ofxVectorGraphics output;
    float y1;
    float w1;
    
};

#endif /* RainForest_hpp */
