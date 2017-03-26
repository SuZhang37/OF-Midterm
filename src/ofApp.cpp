#include "ofApp.h"
#include "ofxJSON.h"

ofxJSONElement json;	// JSON reader
ofColor dayFade;	// an alpha box we draw over the landscape to simulate night
int dfAlpha;		// dayfade opacity

int byteData;
bool color;
bool BLUE = false;
bool YELLOW = false;



#define ONE_HRS  3600
#define SIX_HRS 21600

ofImage landscape;
ofImage Info;
ofImage Sunshine;
ofImage start;

bool rianforest_load = false;
bool valley_load = false;
bool desert_load = false;


int curTime = 1487358400;
int sunrise = 1487343485;
int sunset =  1487382729;


double temperature;
double humidity;
double windSpeed;



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    serial.setup("/dev/cu.usbmodem1421", 9600);
    
    start.load("image/start.jpg");
    
    ofEnableAlphaBlending();
    ofBackground(255,255,255);
    
    ofRegisterURLNotification(this);
    cout << "starting\n";
    
    ofSetFrameRate(30);

    
    dfAlpha = ofMap(curTime, sunset - ONE_HRS, sunset + ONE_HRS, 0, 230, true);
    
    Thin.load("helveticaneue/HelveticaNeue Thin.ttf", 14);
    Med.load("helveticaneue/HelveticaNeue Medium.ttf", 14);
    Light.load("helveticaneue/HelveticaNeue Light.ttf", 14);
   
    
    int num = 500;
    p.assign(num, demoParticle());
    currentMode == PARTICLE_1;
    
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].setup();
        
    }
    player_rain.load("sound/rain.wav");
    player_rainforest.load("sound/rainforest.wav");
    player_valley.load("sound/valley.mp3");
    player_desert.load("sound/desert.wav");

}

//--------------------------------------------------------------

void ofApp::urlResponse(ofHttpResponse & response){
    if(response.status==200 ){
        cout << response.request.name << endl;
        cout << response.data.getText() << endl;
        
        if (json.parse(response.data.getText())) {  // parse url returns T/F
            sunrise = json["daily"]["data"][0]["sunriseTime"].asInt();
            sunset = json["daily"]["data"][0]["sunsetTime"].asInt();
            curTime = json["currently"]["time"].asInt();
            temperature = json["currently"]["temperature"].asInt();
            humidity = json["currently"]["humidity"].asInt();
            windSpeed = json["currently"]["windSpeed"].asInt();

            
            cout << "Set sunrise epoch to: " << sunrise << endl;
            cout << "Set sunset epoch to : " << sunset << endl;
            cout << "Set curtime epoch to: " << curTime << endl;
            cout << "Set temperature epoch to: " << temperature << endl;
            cout << "Set humidity epoch to: " << humidity << endl;
            cout << "Set windSpeed epoch to: " << windSpeed << endl;
            
        } else {
            cout << "Parsing Failed." << endl;
        }
    }else{
        cout << response.status << " " << response.error << endl;
    }
}

//--------------------------------------------------------------


void ofApp::update(){
    Sunshine.load("image/sunshine.png");
    
    if(serial.available()<0){
        color = false;
        
    } else {
    
    while (serial.available() > 0) {
        color = true;
        byteData = serial.readByte();
        
        if (byteData == 2) {
            BLUE = true;
            
        }
        
        if (byteData == 3) {
            YELLOW = true;
        }
        
        if (byteData == 1){
            BLUE = false;
            YELLOW = false;
        
       }
        
    }
    }
    
    if(rianforest_load == true){
        landscape.load("image/rainforest.jpg");
        Info.load("image/rainforest02.png");
        
  
        if(BLUE==true){
            for(unsigned int i = 0; i < p.size(); i++){
                p[i].setMode(currentMode);
                p[i].setup();
                //p[i].update();
            }
           
        }
        
        if(YELLOW == true){

            myRainForest.growth();
        }
        
    }
    
    /////////////////////////////////////////////////////
    
    if(valley_load == true){
        
        
        landscape.load("image/valley.jpg");
        Info.load("image/valley02.png");
        
        if(BLUE==true){
            
            for(unsigned int i = 0; i < p.size(); i++){
                p[i].setMode(currentMode);
                p[i].setup();
                //p[i].update();
            }
        }
        
        if(YELLOW == true) {
            myValley.growth();
        }
    }
    
    /////////////////////////////////////////////////////
    
    if(desert_load == true){
        landscape.load("image/desert.jpg");
        Info.load("image/desert02.png");

        if(YELLOW == true){
          myDesert.growth();
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    ofTranslate(ofGetWindowWidth()/2,ofGetWindowHeight()/2);
    ofSetColor(255);
    start.draw(-ofGetWindowWidth()/2, -ofGetWindowHeight()/2);
    ofPopMatrix();
    
    landscape.draw(0, 0, ofGetWidth(), ofGetHeight());
    Info.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    if(YELLOW == true){
        Sunshine.draw(0,0,ofGetWidth(), ofGetHeight()/*,100+((int)(counter * 5.0f) % 255)*/);
    }

    
    dfAlpha = ofMap(curTime, sunset - ONE_HRS, sunset + ONE_HRS, 0, 180, true); // set dayFade alpha with clamping
    dayFade = ofColor(33, 38, 58, dfAlpha);  // midnight blue / grey
    ofSetColor(dayFade);
    ofDrawRectangle(582,0,ofGetWidth()-582,ofGetHeight());

    if(BLUE==true){
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].draw();
        
    }
    }
   
    if (rianforest_load == true ||valley_load == true||desert_load == true ){
    
    ofSetColor(84,98,35);
    
        Med.drawString("Temperature: " + ofToString(temperature)+" F", ofGetWidth()*0.11, ofGetHeight()*0.45);
        Med.drawString("Humidity: " + ofToString(humidity), ofGetWidth()*0.11, ofGetHeight()*0.48);
        Med.drawString("Wind Speed: " + ofToString(windSpeed)+" mph", ofGetWidth()*0.11, ofGetHeight()*0.51);

    ofSetColor(255);
        
}
    

    if(color == false){
        cout << "erro" << endl;
    }
    
    if(color == true){
        cout << "connect" << endl;
    }
    
    if(BLUE == true){
        cout << "blue" << endl;
    }
    
    if(YELLOW == true){
        cout << "yellow" << endl;
    }
    
    
    
    if(rianforest_load == true){
    myRainForest.draw();
    }
    
    if(desert_load == true){
    myDesert.draw();
    }
    
    if(valley_load == true){
    myValley.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == '3') {    // sync time with json weather data
        // Amazon Rriver LAT/LONG == -1.262592, -61.627218
        string url = "https://api.darksky.net/forecast/3c129f037d51b067be69ece2598e1edf/-1.262592, -61.627218";
        ofLoadURLAsync(url, "async_req");
        rianforest_load = true;
        desert_load = false;
        valley_load = false;
        
        player_rainforest.play();
        player_rainforest.setLoop(true);
        player_valley.stop();
        player_desert.stop();
        
        
    }
    
    if (key == '4') {    // sync time with json weather data
        // Guangxi LAT/LONG == 22.106114, 108.256814
        string url = "https://api.darksky.net/forecast/3c129f037d51b067be69ece2598e1edf/22.106114, 108.256814";
        ofLoadURLAsync(url, "async_req");
        valley_load = true;
        rianforest_load = false;
        desert_load = false;
        
        player_valley.play();
        player_valley.setLoop(true);
        player_rainforest.stop();
        player_desert.stop();
        
    }
    
    if (key == '5') {    // sync time with json weather data
        // Arabian Desert LAT/LONG == 21.078323, 48.688841
        string url = "https://api.darksky.net/forecast/3c129f037d51b067be69ece2598e1edf/21.078323, 48.688841";
        ofLoadURLAsync(url, "async_req");
        desert_load = true;
        rianforest_load = false;
        valley_load = false;
        
        player_desert.play();
        player_desert.setLoop(true);
        player_valley.stop();
        player_rainforest.stop();
    }
    
    if (key == '1')
        curTime -= 600;  // minus 10 min
    if (key == '2')
        curTime += 600;  // add 10 min
    
    if (curTime < sunrise)  // impose early limit
        curTime = sunrise;
    
    if (curTime > sunset + SIX_HRS)  // impose late limit
        curTime = sunset + SIX_HRS;
    
    cout << "Current epoch time is: " << curTime << endl;
    
    if(key == 'r'){
        BLUE = true;
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'r'){
        BLUE = false;
        
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    YELLOW = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    YELLOW = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
