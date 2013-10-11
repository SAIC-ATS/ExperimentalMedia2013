#include "testApp.h"


//------------------------------------------------------------------------------
void testApp::setup()
{
    // you must use your own port lineNumber here!
    // to find your port lineNumber on mac/linux/windows
    // % ls -la /dev/tty.*
    ofSetFrameRate(30);
    serial.setup("/dev/tty.usbmodem1411",9600);
    
    verdana30.loadFont("verdana.ttf", 75, true, true, true);
    verdanaNumber.loadFont("verdana.ttf",45,true,true,true);
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
        // our buffer to later turn it into a lineNumber, but we instead want to
        // just want to ignore it.
        
        // if it is not \r then we check to see if it is an \n
        if(myByte == '\n')
        {
            // if it IS an \n then we know the buffer is full and can be
            // converted into our int pot1Value for processing.
            
            serialInput = ofSplitString(buffer, ",");
            
            // we then clear our buffer so that we can start adding the next
            // incoming bytes that will form our next lineNumber.
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
    
    // create a boolean so that oF knows whether to listen to push buttons or the mouse control
    // in order to set linout and LEDs
    
    
    
//    CGPoint point;
//    point.x = 500;
//    point.y = ofGetMouseY();
//    CGWarpMouseCursorPosition(point);
    
    int lineOut = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255, TRUE);
    yColor = ofMap(mouseY, 0, ofGetHeight(), 0, 255, TRUE);
    
    int backgroundColor = 0-yColor;
    
    ofBackground(backgroundColor);
    
    //unsigned char lineNumber = (unsigned char)lineOut;       // lineNumber to be converted to a string
    string myResult;          // string which will contain the result
    ostringstream convert;   // stream used for the conversion
    convert << lineOut;      // insert the textual representation of 'lineNumber' in the characters in the stream
    myResult = convert.str(); // set 'Result' to the contents of the stream

    float stringWidth = verdana30.stringWidth(byteLines[lineOut]);
    float string2Width = verdana30.stringWidth(myResult);
    float stringHeight = verdana30.stringHeight(byteLines[lineOut]);
    ofSetColor(yColor);
    verdana30.drawString(byteLines[lineOut], ((ofGetWindowWidth()/2)-(stringWidth/2)), ((ofGetWindowHeight()/2)-(stringHeight/2)));
    verdanaNumber.drawString(myResult, ((ofGetWindowWidth()/2)-(string2Width/2)), (ofGetWindowHeight())-50);
    
    //int test = 14;
    int step = lineOut;
    int i = 0;
    while (step >= 1)
    {
        stepArray[i] = step%2;
        step = floor(step/2);
            //cout << "step array index " << i << " is equal to " << stepArray[i] << endl;
        i++;
    }
    cout << "i is equal to " << i << endl;
    //re-initialize the binArray
    std::fill_n(binArray, 8, 0);
    //because stepArray lists our binary number backwards, we have to reverse it here
    int j = (i-8)*-1;
        //cout << "int j is " << j << endl;
    i = i -1;
    for (j; j<8; j++)
    {
        binArray[j] = stepArray[i];
        i--;
    }
    
    for (int x = 0; x<8; x++)
    {
        cout << "lineout is " << lineOut << endl;
        cout << "digit number " << x << " in bin number is " << binArray[x] << endl;
        serial.writeByte(binArray[x]);
    }
    serial.writeByte(255);
    
    
}

//------------------------------------------------------------------------------
void testApp::keyPressed(int key)
{
    if (key=='f')
    {
        ofToggleFullscreen();
    }
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