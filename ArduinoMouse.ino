
//https://www.arduino.cc/en/Reference/MouseMove
//https://www.sparkfun.com/tutorials/272

//Pins Joystick
const int pinJoyX = 2; // analog
const int pinJoyY = 3; // analog
const int pinJoyB = 6; // digital
float joyX, joyY, joyB;
float mScroll=0.0;
int leftB, rightB;

//pins Mouse
const int pinLeftB=4;
const int pinRightB=5;
int previousLeftB=HIGH;
int previousRightB=HIGH;
float speedMouse=.2;//1=100% 0.0=0%
int scrollSpeed=70;//milliseconds to delay


void setup()
{
  // make the SEL line an input
  pinMode(pinJoyB,INPUT);
  pinMode(pinRightB,INPUT);
  pinMode(pinLeftB,INPUT);
  
  // turn on the pull-up resistor for the SEL line (see http://arduino.cc/en/Tutorial/DigitalPins)
  digitalWrite(pinJoyB,HIGH);
  digitalWrite(pinLeftB,HIGH);
  digitalWrite(pinRightB,HIGH);

  // set up serial port for output
  Serial.begin(9600);
  Mouse.begin();

}

void loop() 
{   
  normalizeJoystick();
  readButtons(); 
  
  Mouse.move(joyX, joyY, mScroll);
  delay(20);
}  


void normalizeJoystick(){
  joyX = (analogRead(pinJoyX)-512)/10; 
  joyY = (analogRead(pinJoyY)-512)/10;

  if (joyX>-10 && joyX<10){ joyX=0;}
  else{ joyX=joyX*speedMouse;  }
  if (joyY>-10 && joyY<10){ joyY=0;}
  else{joyY=-joyY*speedMouse;}
  joyB = digitalRead(pinJoyB);
  if(joyB==HIGH){
    mScroll=-joyY*speedMouse; 
    joyY=0;
    joyX=0;
    delay(scrollSpeed);
  }
  else{
    mScroll=0;
  }
  
}

void readButtons(){ 
  
  leftB = digitalRead(pinLeftB); 
  rightB = digitalRead(pinRightB);

  if (leftB==HIGH && previousLeftB!=leftB){
    previousLeftB=leftB;
    Mouse.press(MOUSE_LEFT);
  }
  if (leftB==LOW && previousLeftB!=leftB){
    previousLeftB=leftB;
    Mouse.release(MOUSE_LEFT);
  }
  if (rightB==HIGH && previousRightB!=rightB){
    previousRightB=rightB;
    Mouse.press(MOUSE_RIGHT);
  }
  if (rightB==LOW && previousRightB!=rightB){
    previousRightB=rightB;
    Mouse.release(MOUSE_RIGHT);
  }
}

