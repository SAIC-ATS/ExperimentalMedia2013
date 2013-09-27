#include "testApp.h"


//------------------------------------------------------------------------------
void testApp::setup()
{
    // you must use your own port number here!
    // to find your port number on mac/linux/windows
    // % ls -la /dev/tty.*
    serial.setup("/dev/tty.usbmodem1421",9600);
    
    // initialize the pot1Value = 0
    pot1Value = -1;
    pot2Value = -1;
    
    verdana30.loadFont("verdana.ttf", 75, true, true);
	verdana30.setLineHeight(34.0f);
	verdana30.setLetterSpacing(1.035);
    
    ofBuffer bufferText = ofBufferFromFile("byte.txt");
    
    int i = 0;
    
    while(bufferText.isLastLine() == false) {
        
        // move on to the next line
        string line = bufferText.getNextLine();
        
        // copy the line to draw later
        // make sure its not a empty line
        if(line.empty() == false) {
            byteLines.push_back(line);
        }
        
        // print out the line
        cout << line << endl;
        cout << "line number is " << i << endl;
        i++;
    }
}

//------------------------------------------------------------------------------
void testApp::update()
{
    
    // We read as many bytes as we can
    
    while(serial.available() > 0)
    {
        // Read a single byte
        char myByte = serial.readByte(); // a "char" is just like a byte
        
        // If our byte is an \r that means that we don't want to add it to
        // our buffer to later turn it into a number, but we instead want to
        // just want to ignore it.
        if(myByte == '\r') {
            // nothing -- we are waiting for the \n
        }
        // if it is not \r then we check to see if it is an \n
        else if(myByte == '\n')
        {
            // if it IS an \n then we know the buffer is full and can be
            // converted into our int pot1Value for processing.
            
            serialInput = ofSplitString(buffer, ",");
            pot1Value = ofToInt(serialInput[0]);
            pot2Value = ofToInt(serialInput[1]);
            
            
            // we then clear our buffer so that we can start adding the next
            // incoming bytes that will form our next number.
            buffer.clear();
        }
        else
        {
            buffer += myByte;
        }
    }

    
    
    

}

//------------------------------------------------------------------------------
void testApp::draw()
{
    // since our pot value ranges from 0-1024, we need to map it onto a range
    // from 0-255 (which is what we use for colors).  We can use ofMap to do
    // this.  Please see the ofMap documentation to learn about the parameters.
    
    if (pot1Value==-1) {
        lineOut = ofMap(mouseX, 0, 1024, 0, 255, TRUE);
        yColor = ofMap(mouseY, 0, 768, 0, 255, TRUE);
    }
    else {
        lineOut = ofMap(pot1Value,0,1024,0,255);
        yColor = ofMap(pot2Value,0,1024,0,255);
    }
    
    int backgroundColor = 0-yColor;
    
    // now we set our pot value to control the background of our screen.
    
    ofBackground(backgroundColor);

    float stringWidth = verdana30.stringWidth(byteLines[lineOut]);
    float stringHeight = verdana30.stringHeight(byteLines[lineOut]);
    ofSetColor(yColor);
    verdana30.drawString(byteLines[lineOut], ((ofGetWindowWidth()/2)-(stringWidth/2)), ((ofGetWindowHeight()/2)-(stringHeight/2)));
        
}

//------------------------------------------------------------------------------
void testApp::keyPressed(int key)
{
}

//------------------------------------------------------------------------------
void testApp::keyReleased(int key)
{
}

//------------------------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//------------------------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
}

//------------------------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{
}

//------------------------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{
}