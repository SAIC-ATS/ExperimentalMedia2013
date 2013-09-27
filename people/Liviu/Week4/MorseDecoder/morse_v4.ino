  int ledPin = 13;
  int timeUnit = 100;
  int dotDuration = timeUnit;
  int dashDuration = dotDuration*3;
  int letterSpacer = dashDuration;
  int wordSpaceDuration = dashDuration*3;
  String textLine="SOME TEXT";

   
    // Methods
  void dot() {
    digitalWrite(ledPin, HIGH);
    delay(dotDuration);
    digitalWrite(ledPin, LOW);
    delay(dotDuration);
  }
  void dash() {
    digitalWrite(ledPin, HIGH);
    delay(dashDuration);
    digitalWrite(ledPin, LOW);
    delay(dotDuration);
  }
  void letterSpace() {
    delay(letterSpacer);
  }
  void wordSpace() {
    delay(wordSpaceDuration);
  }
 
void A(){ 
  dot(); 
  dash();                 
  letterSpace();
}
void B(){ 
  dash(); 
  dot(); 
  dot(); 
  dot();   
  letterSpace();
} 
void C(){ 
  dash(); 
  dot(); 
  dash(); 
  dot();  
  letterSpace();
} 
void D(){ 
  dash(); 
  dot(); 
  dot();          
  letterSpace();
}
void E(){ 
  dot();                         
  letterSpace();
}
void f(){ 
  dot(); 
  dot(); 
  dash(); 
  dot();   
  letterSpace();
}
void G(){ 
  dash(); 
  dash(); 
  dot();         
  letterSpace();
}
void H(){ 
  dot(); 
  dot(); 
  dot(); 
  dot(); 
  letterSpace();
}
void I(){ 
  dot(); 
  dot();                  
  letterSpace();
}
void J(){ 
  dot(); 
  dash(); 
  dash(); 
  dash(); 
  letterSpace();
}  
void K(){ 
  dash(); 
  dot(); 
  dash();         
  letterSpace();
}
void L(){ 
  dot(); 
  dash(); 
  dot(); 
  dot();   
  letterSpace();
} 
void M(){ 
  dash(); 
  dash();                
  letterSpace();
}
void N(){ 
  dash(); 
  dot();                 
  letterSpace();
}
void O(){ 
  dash(); 
  dash(); 
  dash();        
  letterSpace();
}
void P(){ 
  dot(); 
  dash(); 
  dash(); 
  dot();  
  letterSpace();
} 
void Q(){ 
  dash(); 
  dash(); 
  dot(); 
  dash(); 
  letterSpace();
}  
void R(){ 
  dot(); 
  dash(); 
  dot();          
  letterSpace();
}
void S(){ 
  dot(); 
  dot(); 
  dot();           
  letterSpace();
}
void T(){ 
  dash();                        
  letterSpace();
}
void U(){ 
  dot(); 
  dot(); 
  dash();          
  letterSpace();
}
void V(){ 
  dot(); 
  dot(); 
  dot(); 
  dash();   
  letterSpace();
}
void W(){ 
  dot(); 
  dash(); 
  dash();         
  letterSpace();
}
void X(){ 
  dash(); 
  dot(); 
  dot(); 
  dash();  
  letterSpace();
}
void Y(){ 
  dash(); 
  dot(); 
  dash(); 
  dash(); 
  letterSpace();
} 
void Z(){ 
  dash(); 
  dash(); 
  dot(); 
  dot();  
  letterSpace();
}

void setup() {
  pinMode(ledPin, OUTPUT);}
  
 
void loop (){

for (int i=0; i<textLine.length(); i++){
   
  // Get the current character
    char c = textLine[i];
    
    
    
    if (c == 'A'|| c == 'a'){     
    A();
      }
      if (c == 'B'|| c == 'b'){     
    B();
      }
      if (c == 'D'|| c == 'd'){     
    D();
      }
    if (c == 'E'|| c == 'e'){     
    E();
      }
    if (c == 'F'|| c == 'f'){     
    f();
      }
   if (c == 'G'|| c == 'g')
 {G();}
   
   if (c == 'H'|| c == 'h'){     
    H();
      }
      
      if (c == 'I'|| c == 'i'){     
    I();
      }
       if (c == 'J'|| c == 'j'){     
    J();
      }
          if (c == 'K'|| c == 'k'){     
    K();
      }
      if (c == 'L'|| c == 'l'){     
    L();
      }
      if (c == 'M'|| c == 'm'){     
    M();
      }
       if (c == 'N'|| c == 'n'){     
    N();
      }
      if (c == 'O'|| c == 'o'){     
    O();
      }
      if (c == 'P'|| c == 'p'){     
    P();
      }
      if (c == 'Q'|| c == 'q'){     
    Q();
      }
       if (c == 'R'|| c == 'r'){     
    R();
      }
      if (c == 'S'|| c == 's'){     
    S();
      }
      if (c == 'T'|| c == 't'){     
    T();
      }
      if (c == 'U'|| c == 'u'){     
    U();
      }
      if (c == 'V'|| c == 'v'){     
    V();
      }
      if (c == 'W'|| c == 'w'){     
    W();
      }
      if (c == 'X'|| c == 'x'){     
    X();
      }
      if (c == 'Y'|| c == 'y'){     
    Y();
      }
       if (c == 'Z'|| c == 'z'){     
    Z();
      }
}}


 



