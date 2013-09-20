
int ledPin = 9;

int dits = 500;
int dah;

void setup()
{
  pinMode(ledPin, OUTPUT);
  dah = 3*dits;
}

void loop()
{
//W
  dit(1);
  dit(0);
  dahs(1);
  dit(0);
  dahs(1);
  
//Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }
 
 //H
   dit(1);
   dit(0);
   dit(1);
   dit(0);
   dit(1);
   dit(0);
   dit(1);
 
 //Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }
 
 //A
 dit(1);
 dit(0);
 dahs(1);
 
 //Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }
  
 //T
   dahs(1);
   
 //Next word
  for(int i = 0; i < 7; i++)
  {
    dit(0);
  }
  
   //H
   dit(1);
   dit(0);
   dit(1);
   dit(0);
   dit(1);
   dit(0);
   dit(1);
   
//Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }
   
   //A
   dit(1);
   dit(0);
   dahs(1);
   
 //Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }
   
    //T
   dahs(1);
 
  //Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }
 
    //H
   dit(1);
   dit(0);
   dit(1);
   dit(0);
   dit(1);
   dit(0);
   dit(1);
   
  //Next word
  for(int i = 0; i < 7; i++)
  {
    dit(0);
  }
  
  //G
  dahs(1);
  dit(0);
  dahs(1);
  dit(0);
  dit(1);
  
 //Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }
  
 //O
  dahs(1);
  dit(0);
  dahs(1);
  dit(0);
  dahs(1);
  
 //Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }
  
 //D
 dahs(1);
 dit(0);
 dit(1);
 dit(0);
 dit(1);
 
//Next word
  for(int i = 0; i < 7; i++)
  {
    dit(0);
  }

//W
  dit(1);
  dit(0);
  dahs(1);
  dit(0);
  dahs(1);

//Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }
  
//R
  dit(1);
  dit(0);
  dahs(1);
  dit(0);
  dit(1);
  
//Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }

//O
 dahs(1);
 dit(0);
 dahs(1);
 dit(0);
 dahs(1);

//Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  } 
  
//U
  dit(1);
  dit(0);
  dit(1);
  dit(0);
  dahs(1);
  
 //Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }
  
//G
  dahs(1);
  dit(0);
  dahs(1);
  dit(0);
  dit(1);
  
//Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }
  
//H
  dit(1);
  dit(0);
  dit(1);
  dit(0);
  dit(1);
  dit(0);
  dit(1);
  
 //Next letter
  for(int i = 0; i < 3; i++)
  {
    dit(0);
  }
  
//T
  dahs(1);
}

void dit(int dig)
{
  if(dig == 1)
  {
    digitalWrite(ledPin, HIGH);
    delay(dits);
    digitalWrite(ledPin, LOW);
  }
  
  if(dig == 0)
  {
    delay(dits);
  }
}

void dahs(int dig)
{
  if(dig == 1)
  {
    digitalWrite(ledPin, HIGH);
    delay(dah);
    digitalWrite(ledPin, LOW);
  }
  
  if(dig ==0)
  {
    delay(dah);
  }
}
