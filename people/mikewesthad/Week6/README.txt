This project requires all three pieces of software to run: Arduino, openFrameworks and Unity.

Arduino controls the LEDs and detects whether or not an LED is connected.
Unity contains the virtual world with virtual LEDs which can be switched on and off.
openFrameworks stitches the two together by communicating over serial with arduino and via OSC with Unity.

The Unity scene that needs to be run is called Flood.  Ignore the others...

References for the sounds used are in Unity/Flood/Assets/Sounds/References.txt

More description here:
http://mikewesthad.wordpress.com/2013/10/07/experimental-media-flood-or-arduino-and-unity/