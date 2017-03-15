

#ifndef Valley_hpp
#define Valley_hpp

#include <ofMain.h>

class Valley{
public:
    Valley();
    void draw();
    void growth();
    void Image();
    void keyPressed(int key);
    
    ofPoint pos;
    int dist = 100;
    float weight;
};

#endif /* Valley_hpp */
