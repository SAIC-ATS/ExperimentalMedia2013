
const int num=2;
int redLED[num] = {9, 3};
int greenLED[num] = {10, 5};
int blueLED[num] = {11,6};
int arrayR[num] ={0,0};
int arrayG[num] = {0,0};
int arrayB[num] = {0,0};

int  RVal, GVal, BVal;
int lampNumber = 1;


void setup() {
  Serial.begin(9600);
 for(int i =0; i < num-1; i++){
  pinMode(redLED[i], OUTPUT);
  pinMode(greenLED[i], OUTPUT);
  pinMode(blueLED[i], OUTPUT);
 }      
}

void loop(){
  if (Serial.available()>4) { 
    char val = Serial.read();
    if(val == 'S'){
      int messageNumber = Serial.read();
      if(messageNumber == lampNumber){
        RVal = Serial.read();
        GVal = Serial.read();
        BVal = Serial.read();
      }
    }
  }
  
  for (int i =0; i<num-1 ; i++ ){
    arrayR[i] = arrayR[i+1];
    arrayG[i] = arrayG[i+1];
    arrayB[i] = arrayB[i+1];
  }
  arrayR[num-1] = RVal;
  arrayG[num-1] = GVal;
  arrayB[num-1] = BVal;
  
  for (int i =0; i < num; i ++){
  analogWrite(redLED[i],arrayR[i]);
  analogWrite(greenLED[i], arrayG[i]);
  analogWrite(blueLED[i], arrayB[i]);
  }
}

