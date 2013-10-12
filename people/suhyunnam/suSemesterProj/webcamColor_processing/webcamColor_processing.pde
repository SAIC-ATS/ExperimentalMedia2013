/*next
1.migrate to oF
2. Serial communication with Arduino
3.Run on Raspberry PI
4. Live feed from PI
*/
import processing.video.*;
import processing.serial.Serial;
int num = 16;

Serial myPort;

float avR,avG,avB;
//float totalR,totalG,totalB;
float[] arrayR = new float[num];
float totalG;
float[] arrayG = new float[num];;
float totalB;
float[] arrayB = new float[num];;

int cellSize = 20;
int cols, rows;
Capture video;

void setup() {
  size(1280, 480);
  frameRate(30);
  cols = width / cellSize;
  rows = height / cellSize;
  colorMode(RGB, 255, 255, 255, 100);
  video = new Capture(this, width, height);
  video.start();  
  
println(Serial.list());
String portName = Serial.list()[0];
myPort = new Serial(this, portName, 9600);
frameRate(10);

}


void draw() { 
  background(255);
  if (video.available()) {
    video.read();
    video.loadPixels();
       float totalR = 0;
       float totalG = 0;
       float totalB = 0;
    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
   
        int x = i*cellSize;
        int y = j*cellSize;
        int loc = x + y*video.width; // Reversing x to mirror the image
      
        float r = red(video.pixels[loc]);
        float g = green(video.pixels[loc]);
        float b = blue(video.pixels[loc]);

        totalR +=  red(video.pixels[loc]);
        avR = totalR/(cols*rows);
        
        totalG +=  green(video.pixels[loc]);
        avG = totalG/(cols*rows);
        
        totalB +=  blue(video.pixels[loc]);
        avB = totalB/(cols*rows);
      }
    }
  }
  pushMatrix();
  scale(-1,1);
  image(video,-640,0,640,480);
  noStroke();
  popMatrix();

 //migrate to arduino from here
  for (int i =0; i<num-1 ; i++ ){
    arrayR[i] = arrayR[i+1];
    arrayG[i] = arrayG[i+1];
    arrayB[i] = arrayB[i+1];
  }
  arrayR[num-1] = avR;
  arrayG[num-1] = avG;
  arrayB[num-1] = avB;
  
  for (int i =0; i < num; i ++){
  fill(arrayR[i],arrayG[i],arrayB[i]);
  rect(640 + i*40,0,40,480);
 
}
//to here!!!
sendSerialData();
  //println("R: " + avR + "G : " + avG+ "B : " + avB);
}
void sendSerialData() {
//for (int i = 0; i < lamps.size(); i++) {
myPort.write('S');
myPort.write(1);
myPort.write(int(avR));
myPort.write(int(avG));
myPort.write(int(avB));

//}
}
