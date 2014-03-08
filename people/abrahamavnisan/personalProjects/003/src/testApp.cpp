#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    font.loadFont("Verdana.ttf", 5, true, true, true, .01);
    
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground( 10, 10, 10);
    
    ofxLoadCamera(camera, "ofEasyCamSettings");
    enableEasyCam = false;
    displayStats = true;
    
    world.setup();
	world.enableGrabbing();
	world.enableDebugDraw();
  	world.setCamera(&camera);
    
    ofVec3f gravity = ofVec3f(0,0,0);
    world.setGravity(gravity);

    sphere = new ofxBulletSphere();
	sphere->create(world.world, ofVec3f(0, 0, 0), 1.0, 2.5);
	sphere->add();
    
    // set world bounds (taken from ofXBulletEventsExample)
    ofVec3f startLoc;
	ofPoint dimens;
	boundsWidth = 75.;
	float hwidth = boundsWidth*.5;
	float depth = .1;
	float hdepth = depth*.5;
    
	for(int i = 0; i < 6; i++) {
		bounds.push_back( new ofxBulletBox() );
		if(i == 0) { // ground //
			startLoc.set( 0., hwidth+hdepth, 0. );
			dimens.set(boundsWidth, depth, boundsWidth);
		} else if (i == 1) { // back wall //
			startLoc.set(0, 0, hwidth+hdepth);
			dimens.set(boundsWidth, boundsWidth, depth);
		} else if (i == 2) { // right wall //
			startLoc.set(hwidth+hdepth, 0, 0.);
			dimens.set(depth, boundsWidth, boundsWidth);
		} else if (i == 3) { // left wall //
			startLoc.set(-hwidth-hdepth, 0, 0.);
			dimens.set(depth, boundsWidth, boundsWidth);
		} else if (i == 4) { // ceiling //
			startLoc.set(0, -hwidth-hdepth, 0.);
			dimens.set(boundsWidth, depth, boundsWidth);
		} else if (i == 5) { // front wall //
			startLoc.set(0, 0, -hwidth-hdepth);
			dimens.set(boundsWidth, boundsWidth, depth);
		}
        
		bounds[i]->create( world.world, startLoc, 0., dimens.x, dimens.y, dimens.z );
		bounds[i]->setProperties(1., .1); // restitution, friction
		bounds[i]->add();
        
	}
    

}

//--------------------------------------------------------------
void testApp::update(){
    if (enableEasyCam)
    {
        camera.enableMouseInput();
        world.disableGrabbing();
    }
    else
    {
        camera.disableMouseInput();
        world.enableGrabbing();
    }
	world.update();

}

//--------------------------------------------------------------
void testApp::draw(){
    glEnable( GL_DEPTH_TEST );

    string myString = "oh boy";
    float stringWidth = font.stringWidth(myString);
    float stringHeight = font.stringHeight(myString);
    
    camera.begin();
    
    ofSetLineWidth(1.f);
    ofSetColor(255, 0, 200);
	world.drawDebug();
    
    ofSetColor(225, 225, 225);
	//sphere->draw(); // don't need to draw sphere since we can see where it is in debug mode
    
    ofPushMatrix();
    ofVec3f position;
    position = sphere->getPosition();
    ofTranslate(position.x, position.y, position.z);

//    // Method 1 (this hardly works at all)
//    ofVec3f axis = sphere->getRotationAxis();
//    float angle = sphere->getRotationAngle();

    // Method 2 (this works but isn't smooth and I'm not sure why)
    ofQuaternion rotationQuat;
    rotationQuat = sphere->getRotationQuat();
    ofVec3f axis;
    float angle;
    rotationQuat.getRotate(angle, axis);
    
    ofRotate(angle, axis.x, axis.y, axis.z);
    
    font.drawStringAsShapes(myString, 0-stringWidth/2, 0-stringHeight/2);
  
    ofPopMatrix();
    
    camera.end();

    if (displayStats)
    {
        std::string infoString = makeInfoString(axis, angle);
        ofDrawBitmapStringHighlight(infoString, 20, 20);
    }
}

//------------------------------------------------------------------------------
std::string testApp::makeInfoString(ofVec3f axis, float angle)
{
    if (displayStats)
    {
        std::stringstream ss;
        
        int width = 25;
        
        ss << std::setw(width) << "-SHORTCUTS- " << std::endl; // new line
        ss << std::setw(width) << "Display stats: " << "d" << std::endl;
        ss << std::endl;
        ss << std::setw(width) << "Save camera: " << "s" << std::endl;
        ss << std::setw(width) << "Load camera: " << "l" << std::endl;
        ss << std::setw(width) << "Reset camera: " << "r" << std::endl;
        ss << std::setw(width) << "Enable EasyCam: " << "c" << std::endl;
        ss << std::endl;
        ss << std::setw(width) << "Apply X torque : " << "X" << std::endl;
        ss << std::setw(width) << "Apply Y torque : " << "Y" << std::endl;
        ss << std::setw(width) << "Apply Z torque : " << "Z" << std::endl;
        ss << std::endl;
        ss << std::setw(width) << "-INFO- " << std::endl;
        ss << std::setw(width) << "Framerate: " << ofGetFrameRate() << std::endl;
        ss << std::setw(width) << "Rotation Angle" << angle << std::endl;
        ss << std::setw(width) << "Axis X" << axis.x << std::endl;
        ss << std::setw(width) << "Axis Y" << axis.y << std::endl;
        ss << std::setw(width) << "Axis Z" << axis.z << std::endl;
        
        return ss.str();
    }
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch(key) {
		case 'F':
		case 'f':
			ofToggleFullscreen();
			break;
        case 's':
            ofxSaveCamera(camera, "ofEasyCamSettings");
            break;
        case 'r':
            camera.reset();
            camera.setLensOffset(ofVec2f());
            camera.setForceAspectRatio(false);
            break;
        case 'l':
            ofxLoadCamera(camera, "ofEasyCamSettings");
            break;
        case 'c':
            enableEasyCam = !enableEasyCam;
            break;
        case 'd':
            displayStats = !displayStats;
            break;
        case 'X':
            sphere->applyTorque(50., 0., 0.);
            break;
        case 'Y':
            sphere->applyTorque(0., 50., 0.);
            break;
        case 'Z':
            sphere->applyTorque(0., 0., 50.);
            break;

    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
