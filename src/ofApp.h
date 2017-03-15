#pragma once


#include "ofMain.h"
#include "RainForest.hpp"
#include "Desert.hpp"
#include "Valley.hpp"
#include "demoParticle.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void urlResponse(ofHttpResponse & response);
    void urlResponse2(ofHttpResponse & response2);

    ofSerial serial;
    RainForest myRainForest;
    Desert myDesert;
    Valley myValley;
    ofTrueTypeFont Thin, Med, Light;
    
  
    particleMode currentMode;
    vector <demoParticle> p;
    
    ofSoundPlayer player_rain;
    ofSoundPlayer player_rainforest;
    ofSoundPlayer player_valley;
    ofSoundPlayer player_desert;
		
};
