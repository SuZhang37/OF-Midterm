
#ifndef Desert_hpp
#define Desert_hpp

#include <ofMain.h>

class Desert{
public:
    Desert();
    void draw();
    void growth();
    void Image();
    void keyPressed(int key);

    ofPoint pos;
    int dist = 100;
    float weight;
    
};

#endif /* Desert_hpp */
