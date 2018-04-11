#define aref_voltage 3.3 // tie 3.3V to ARef

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

#define ModeSwitch 12 // Button for switching profile

#define TempSensor A1 // Temperature sensor for the amplifiers

#define FanRegulator 2 // Manual regulator for the fans
#define FanSpeed A3 // connect the fans here

#define Mic A0 //Input from the microphone

int SoundIntensity; // Variable to hold the intensity of the analog sound signal

// Variables for the button
int buttonPushCounter = 0;   // Counter for the number of button presses
int buttonState = 0;         // Current state of the button
int lastButtonState = 0;     // Previous state of the button

// Variables for the temp sensor and fans
int currentTemp; // Stores the current temperature
int manualFanSpeed; // Holds the reading from the fanregulator

int LeftRandom; // Holds random numbers for the left / right speaker
int RightRandom;

unsigned long previousMillis = 0; // time since last run of the code

// constants won't change:
const long interval = 1000; // interval at which to do TempCheck (milliseconds)

byte pins[] = {3, 4, 5, 6, 7, 8, 9, 10}; // the pins to change in massDigitalWrite

int data; // the data from the phone via serial bluetooth
int phoneFanSpeed; // the fan speed from the phone

void setup()
{
  Serial.begin(9600); // Serial used for bluetooth

  // If you want to set the aref to something other than 5v
  analogReference(EXTERNAL);

  pinMode(ModeSwitch, INPUT);
  pinMode(TempSensor, INPUT);
  pinMode(FanRegulator, INPUT);
  pinMode(Mic, INPUT);

  pinMode(FanSpeed, OUTPUT);

  //Right & Left SB
  for (int i = 0; i < sizeof(pins); i++)
  {
    pinMode(pins[i], OUTPUT); //makes all LED pins outputs
  }
}

void massDigitalWrite() {
  for (int i = 0; i < sizeof(pins); i++)
  {
    digitalWrite(pins[i], LOW); //declaring them as outputs
  }
}

void FlashingSound() // flashes the LEDs in beat with the music
{
  //reads the sound signal and saves it as a number between 0 and 1023
  SoundIntensity = analogRead(Mic);

  // Makes all the LEDs flash with the music. Adjust the number with * for better precision
for (int i = 0; i < sizeof(pins); i++)
 {
   digitalWrite(pins[i], SoundIntensity * 15); //assigns the pin the value of variable "SoundIntensity";
 }
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

void RandomEffect() // Lights the LEDs in a random sequense
{
  LeftRandom = random(4);
  RightRandom = random(4);

  massDigitalWrite();

  if (LeftRandom = 1) {
    digitalWrite(Left1, HIGH);
  }
  if (LeftRandom = 2) {
    digitalWrite(Left2, HIGH);
  }
  if (LeftRandom = 3) {
    digitalWrite(Left3, HIGH);
  }
  if (LeftRandom = 4) {
    digitalWrite(Left4, HIGH);
  }
  if (RightRandom = 1) {
    digitalWrite(Right1, HIGH);
  }
  if (RightRandom = 2) {
    digitalWrite(Right2, HIGH);
  }
  if (RightRandom = 2) {
    digitalWrite(Right2, HIGH);
  }
  if (RightRandom = 3) {
    digitalWrite(Right3, HIGH);
  }
  if (RightRandom = 4) {
    digitalWrite(Right4, HIGH);
  }
}

void TempCheck() {
  // call this to check the temps and control the fans,
  //comment this part out if you dont have a temp sensor - fan control setup.

  // checks if the manual override regulator has been used. If not, this code runs (automatic fan control)
  manualFanSpeed = analogRead(FanRegulator); // reads the setting of the fan regulator and stores it in manualFanSpeed

  if (manualFanSpeed = 0) {
    currentTemp = analogRead(TempSensor); // values range from 0 -1023

    // converting that reading to voltage, which is based off the reference voltage
    float voltage = currentTemp * aref_voltage;
    voltage /= 1024.0;

    //converting from 10 mv per degree wit 500 mV offset to degrees ((volatge - 500mV) times 100)
    float temperatureC = (voltage - 0.5) * 100 ;

    if (temperatureC >= 19) { //turns of the fans at 19 degress Celsius or below
      analogWrite(FanSpeed, 0);
    }
    else if (temperatureC >= 20) { // fans at 5% at 20c or under
      analogWrite(FanSpeed, 50);
    }
    else if (temperatureC >= 25) { // ~20% fanspeed at 25c
      analogWrite(FanSpeed, 250);
    }
    else if (temperatureC >= 30) { // 40% fanspeed at 30c
      analogWrite(FanSpeed, 400);
    }
    else if (temperatureC >= 35) { // 60% fanspeed at 35c
      analogWrite(FanSpeed, 600);
    }
    else if (temperatureC >= 45) { // 80% fanspeed at 40c
      analogWrite(FanSpeed, 800);
    }
    else if (temperatureC >= 50) { //fans at full speed at 50 degress Celsius
      analogWrite(FanSpeed, 1023);
    }
  }
  if (manualFanSpeed > 1) { // if the manual override regulator has been moved, this code runs (manual fan control)
    analogWrite(FanSpeed, manualFanSpeed); // assigns the values of manualFanSpeed to the fans
  }
  else {
    analogWrite(FanSpeed, phoneFanSpeed);
  }
}

void ButtonCheck() // call this to check the button states
{
  buttonState = digitalRead(ModeSwitch); // This part checks the button and counts how many times the button has been pushed

  if (buttonState != lastButtonState) { // compare the buttonState to its previous state

    if (buttonState == HIGH) {  // if the state has changed, increment the counter
      buttonPushCounter++;  // if the current state is HIGH then the button went from off to on
    }
    if (buttonPushCounter = 5)
    {
      buttonPushCounter = 0;
    }
  }

  lastButtonState = buttonState;   // save the current state as the last state, for next time through the loop
}


void loop()
{
  unsigned long currentMillis = millis();

  if (Serial.available() > 0) // Send data only when you receive data:
  {
    data = Serial.read();  //Read the incoming data & store into data
    Serial.print(data);  //Print Value inside data in Serial monitor
    Serial.print("\n");
  }

  if (currentMillis - previousMillisTemp >= interval || data == 1) {
    // save the last time the code ran
    previousMillisTemp = currentMillis;

    TempCheck();
    ButtonCheck();
  }

  // this checks the value of buttonPushCounter and selects the appropriate effect
  if (buttonPushCounter = 1 || data == 2) { // || means or, and we are gonna have to figure out a way to send commands from the app
    FlashingSound;
  }
  if (buttonPushCounter = 2 || data == 3) {
    SpinEffect;
  }
  if (buttonPushCounter = 3 || data == 4) {
    RandomEffect();
  }
  /* if (buttonPushCounter = 4 || data == 5); {
    //place new effect here
    }*/
}
