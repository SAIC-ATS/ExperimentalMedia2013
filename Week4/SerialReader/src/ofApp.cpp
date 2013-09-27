#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    // you must use your own port number here!
    // to find your port number on mac/linux/windows
    // % ls -la /dev/tty.*
    serial.setup("/dev/tty.usbmodem1421",9600);

    // initialize the potValue = 0
    potValue = 0;
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    // When we use Serial.println(value); in Arduino, the "println" sends the
    // number as ASCII values followed by the \r\n characters.
    //
    // So, when we want to read in our data, we want to accumulate our
    // characters one by one until we see an \r\n which means that that little
    // "package" of ASCII characters representing the potentiometer value is
    // complete.
    //
    // Once the "package" is complete, we can then use 'ofToInt' to convert the
    // string representation in our buffer to an actual number that we can use
    // to control things.

    // We read as many bytes as we can
    while(serial.available() > 0)
    {
        // Read a single byte
        char myByte = serial.readByte(); // a "char" is just like a byte
        //cout << "myByte is " << myByte << endl;
        
        // If our byte is an \r that means that we don't want to add it to
        // our buffer to later turn it into a number, but we instead want to
        // just want to ignore it.
        
        if(myByte == '\\r') {
            //cout << "myByte == '\r'!" << endl;
            // nothing -- we are waiting for the \n
        }
        // if it is not \r then we check to see if it is an \n
        else if(myByte == '\n')
        {
            // if it IS an \n then we know the buffer is full and can be
            // converted into our int potValue for processing.

            potValue = ofToInt(buffer);


            // we then clear our buffer so that we can start adding the next
            // incoming bytes that will form our next number.
            buffer.clear();
        }
        else
        {
            // if it is not an \r and it is not an \n, then it must be part
            // of our number.  So we use the += operator to append it to our
            // string.

            // buffer += myByte is the same as saying

            // buffer = buffer + myByte

            // when we "add" two strings together remember that they aren't
            // summed like numbers, but are concatenated.

            // So if buffer == "Hello World" and myByte == "!", the following
            // statement buffer += myByte; would set buffer == "Hello World!"

            buffer += myByte;
        }
    }
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    // since our pot value ranges from 0-1024, we need to map it onto a range
    // from 0-255 (which is what we use for colors).  We can use ofMap to do
    // this.  Please see the ofMap documentation to learn about the parameters.

    int backgroundColor = ofMap(potValue,0,1024,0,255);

    // now we set our pot value to control the background of our screen.

    ofBackground(backgroundColor);

    // we might also want to see the current value printed to the console
    cout << potValue << endl;


}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//------------------------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//------------------------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//------------------------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
