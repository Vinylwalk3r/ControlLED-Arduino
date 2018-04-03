// Right Subwoofer, clockwise, begins in upper right corner
#define Right1 3
#define Right2 4 
#define Right3 5
#define Right4 6 

// Left Subwoofer, clockwise, begins in upper right corner
#define Left1 7 
#define Left2 8
#define Left3 9 
#define Left4 10 

// All the extra light, will be renamed if installed
#define Extra1 11 
#define Extra2 12


#define Mic A0 //Input from the microphone

int SoundIntensity; //the variable to hold the intensity of the analog sound signal

void setup() 
{
  Serial.begin(9600);
  
  pinMode(Mic, INPUT);

  //Right SBW
  pinMode(Right1, OUTPUT);
  pinMode(Right2, OUTPUT);
  pinMode(Right3, OUTPUT);
  pinMode(Right4, OUTPUT);
  // Left SBW
  pinMode(Left1, OUTPUT);
  pinMode(Left2, OUTPUT);
  pinMode(Left3, OUTPUT);
  pinMode(Left4, OUTPUT);
}

void loop() 
{

 if (=true)
 {
  SoundIntensity = analogRead(Mic);  //reads the sound signal and saves it as a number between 0 and 1023

  // Makes all the LEDs flash with the music. Adjust the number with * for better precision
  analogWrite(Right1, SoundIntensity *15);  //assigns the pin the value of variable "SoundIntensity";
  analogWrite(Right2, SoundIntensity *15);
  analogWrite(Right3, SoundIntensity *15);
  analogWrite(Right4, SoundIntensity *15);
  analogWrite(Left1, SoundIntensity *15);
  analogWrite(Left2, SoundIntensity *15);
  analogWrite(Left3, SoundIntensity *15);
  analogWrite(Left4, SoundIntensity *15); 
  }
 
  else if (=true)
  {
  digitalWrite(Right1, HIGH);
  digitalWrite(Right2, HIGH;
  digitalWrite(Right3, HIGH);
  
  digitalWrite(Right1, LOW;
  digitalWrite(Right4, HIGH);
  digitalWrite(Right2, LOW);
  
  digitalWrite(Right1, HIGH);
  digitalWrite(Right3, LOW;
  digitalWrite(Right2, HIGH);
  
  digitalWrite(Right4, HIGH;
  digitalWrite(Right3, LOW);
  digitalWrite(Right2, HIGH;
  
  digitalWrite(Right1, HIGH);
  digitalWrite(Right2, HIGH;
  }
 
  else if (=true)
  {
  
  }
  else 
  {
  
}
  
 
  
}
