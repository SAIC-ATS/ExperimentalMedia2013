
float ditLength;
float dotLength;

//A:('.-')
//B:('-...'),
//C:('-.-.'),
//D:('-..'),
//E: ('.'),      
//F: ('..-.'),
//G: ('--.'),    
//H: ('....'),   
//I: ('..'),
//J: ('.---'),  
//K: ('-.-'),   
//L: ('.-..'),
//M: ('--'),    
//N: ('-.'),     
//O: ('---'),
//P: ('.--.'), 
//Q: ('--.-'),  
//R: ('.-.'),
//S: ('...'),   
//T: ('-'),    
//U: ('..-'),
//V: ('...-'),  
//W: ('.--'), 
//X: ('-..-'),
//Y: ('-.--'), 
//Z: ('--..'), 
//0: ('-----'),  
//1: ('.----'),  
//2: ('..---'),
//3: ('...--'),  
//4: ('....-'),  
//5: ('.....'),
//6: ('-....'),  
//7: ('--...'),  
//8: ('---..'),
//9: ('----.')

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(convertCharToUpper('a'));
  Serial.println(convertCharToUpper('m'));
  Serial.println(convertCharToUpper('0'));
  Serial.println(convertCharacterToMorse('A'));
  Serial.println(convertCharacterToMorse('A'));
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}


int convertCharacterToMorse(char c) {
  c = convertCharToUpper(c);
  
  // Upper Case Letters A-Z
  if (c >= 65 and c <= 90) {
    
  }
  
  return int(c);
}


// Given a char, c, return the uppercase version (if c is alphabetical)
char convertCharToUpper(char c) {
  // Lower Case Letters a-z are 97-122
  if (c >= 97 && c <= 122) {
    c -= 32; 
  }
  return c;
}



