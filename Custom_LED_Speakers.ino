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

// The button for switching profile
#define ModeSwitch 12 

#define Mic A0 //Input from the microphone

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

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

void FlashingSound() // flashes the LEDs in beat with the music
{
  //reads the sound signal and saves it as a number between 0 and 1023
  SoundIntensity = analogRead(Mic);  

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

void SpinEffect() //creates a infinte loopable spin effect
{
  digitalWrite(Right4, HIGH);
  digitalWrite(Left4, HIGH);
  digitalWrite(Right2, LOW);
  digitalWrite(Left2, LOW);
  
  digitalWrite(Right1, HIGH);
  digitalWrite(Left1, HIGH);
  digitalWrite(Right3, LOW);
  digitalWrite(Left3, LOW);
  
  digitalWrite(Right2, HIGH);
  digitalWrite(Left2, HIGH);
  digitalWrite(Right4, LOW);
  digitalWrite(Left4, LOW);
  
  digitalWrite(Right3, HIGH);
  digitalWrite(Left3, HIGH);
  digitalWrite(Right1, LOW);
  digitalWrite(Left1, LOW);
  
  digitalWrite(Right4, HIGH);
  digitalWrite(Left4, HIGH);
  digitalWrite(Right2, LOW);
  digitalWrite(Left2, LOW);
}

void loop() 
{

  
  buttonState = digitalRead(ModeSwitch); // This part checks the button and counts how many times the button has been pushed
 
    if (buttonState != lastButtonState) { // compare the buttonState to its previous state
      
      if (buttonState == HIGH) {  // if the state has changed, increment the counter
        buttonPushCounter++;  // if the current state is HIGH then the button went from off to on
      } 
      
      else {
      // if the current state is LOW then the button went from on to off:
      }
    
      delay(50); // Delay a little bit to avoid bouncing

    if (buttonPushCounter = 5)
    {
    buttonPushCounter = 0
    }
  }
lastButtonState = buttonState;   // save the current state as the last state, for next time through the loop

// this checks the value of buttonPushCounter and selects the appropriate effect
for (buttonPushCounter = 1) {
  FlashingSound();
}
for (buttonPushCounter = 2) {
  SpinEffect();
}
for (buttonPushCounter = 3) {
  //place new effect here
}
for (buttonPushCounter = 4) {
  //place new effect here
}

 
 
  
}