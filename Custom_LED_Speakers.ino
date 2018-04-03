#define LedOutput 3 //The sound to the Subwoofer

#define SoundInput A0 //Signal to the lights to blink

int SoundIntensity; //the variable to hold the intensity of the analog sound signal

void setup() 
{
  Serial.begin(9600);
  
  pinMode(SoundInput, INPUT);
  
  pinMode(LedOutput, OUTPUT);
 
}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  SoundIntensity = analogRead(SoundInput);  //reads the sound signal and saves it as a number between 0 and 1023
  
  analogWrite(LedOutput, SoundIntensity *15);  //assigns the output pin "LedOutput" the value of variable "SoundIntensity";
  
  
}
