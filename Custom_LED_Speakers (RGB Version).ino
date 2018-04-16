#define aref_voltage 3.3 // tie 3.3V to ARef

// Right Subwoofer, clockwise, begins in upper right corner
#define Right1R 3
#define Right1G 4
#define Right1B 5

#define Right2R 6
#define Right2G 7
#define Right2B 8

#define Right3R 9
#define Right3G 10
#define Right3B 11

#define Right4R 12
#define Right4G 13
#define Right4B 14

// Left Subwoofer, clockwise, begins in upper right corner
#define Left1R 15
#define Left1G 16
#define Left1B 17

#define Left1R 18
#define Left1G 19
#define Left1B 20

#define Left1R 21
#define Left1G 22
#define Left1B 23

#define Left1R 24
#define Left1G 25
#define Left1B 26

#define ModeSwitch 28 // Button for switching profile

#define TempSensor A1 // Temperature sensor for the amplifiers

#define FanRegulator 29 // Manual regulator for the fans
#define FanSpeed A3     // connect the fans here

#define Mic A0 //Input from the microphone

int SoundIntensity; // Variable to hold the intensity of the analog sound signal

// Variables for the button
int buttonPushCounter = 0; // Counter for the number of button presses
int buttonState = 0;       // Current state of the button
int lastButtonState = 0;   // Previous state of the button

// Variables for the temp sensor and fans
int currentTemp;    // Stores the current temperature
int manualFanSpeed; // Holds the reading from the fanregulator

int LeftRandom; // Holds random numbers for the left / right speaker
int RightRandom;

unsigned long previousMillis = 0; // time since last run of the code

// constants won't change:
const long interval = 1000; // interval at which to do TempCheck (milliseconds)

byte pins[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26}; // the pins to of the LEDs

String readString; //main captured String
// These ints help parse the incomming info
byte ind1; 
byte ind2;
int ind3;
int ind4;
int ind5;
int ind6; 
int ind7;
int ind8;
int ind9;
int ind10;
int ind11; 
int ind12;
int ind13;
int ind14;
int ind15;
int ind16; 
int ind17;
int ind18;
int ind19;
int ind20;
int ind21; 
int ind22;
int ind23;
int ind24;
int ind25;

// Every set of strings are for 1 of the four LEDs on the Subwoofers
String Right1Rr = "";
String Right1Gr = "";
String Right1Br = "";

String Right2Rr = "";
String Right2Gr = "";
String Right2Br = "";

String Right3Rr = "";
String Right3Gr = "";
String Right3Br = "";

String Right4Rr = "";
String Right4Gr = "";
String Right4Br = "";

String Left1Rr = "";
String Left1Gr = "";
String Left1Br = "";

String Left2Rr = "";
String Left2Gr = "";
String Left2Br = "";

String Left3Rr = "";
String Left3Gr = "";
String Left3Br = "";

String Left4Rr = "";
String Left4Gr = "";
String Left4Br = "";

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

void massDigitalWrite()
{
  for (int i = 0; i < sizeof(pins); i++)
  {
    digitalWrite(pins[i], LOW); //declaring them as outputs
  }
}

/* void DimEffect()
{
  for (int i = 0; i < sizeof(pins); i++)
  {
    analogWrite(pins[i], duty_cycle); //declaring them as outputs
  }
}*/

void Bluetooth()
{
  if (Serial.available())
  {
    char c = Serial.read(); //gets one byte from serial buffer
    if (c == '*')
    {
      //do stuff

      ind1 = readString.indexOf(',');
      FanSpeedr = readString.substring(0, ind1);
      ind2 = readString.indexOf(',', ind1 + 1);
      // Parsing info for Right side LEDs
      Right1Rr = readString.substring(ind1 + 1, ind2 + 1);
      ind3 = readString.indexOf(',', ind2 + 1);
      Right1Gr = readString.substring(ind2 + 1, ind3 + 1);
      ind4 = readString.indexOf(',', ind3 + 1);
      Right1Br = readString.substring(ind3 + 1, ind4 + 1);
      ind5 = readString.indexOf(',', ind4 + 1);

      Right2Rr = readString.substring(ind4 + 1, ind5 + 1);
      ind6 = readString.indexOf(',', ind5 + 1);
      Right2Gr = readString.substring(ind5 + 1, ind6 + 1);
      ind7 = readString.indexOf(',', ind6 + 1);
      Right2Br = readString.substring(ind6 + 1, ind7 + 1);
      ind8 = readString.indexOf(',', ind7 + 1);

      Right3Rr = readString.substring(ind7 + 1, ind8 + 1);
      ind9 = readString.indexOf(',', ind8 + 1);
      Right3Gr = readString.substring(ind8 + 1, ind9 + 1);
      ind10 = readString.indexOf(',', ind9 + 1);
      Right3Br = readString.substring(ind9 + 1, ind10 + 1);
      ind11 = readString.indexOf(',', ind10 + 1);

      Right4Rr = readString.substring(ind10 + 1, ind11 + 1);
      ind12 = readString.indexOf(',', ind11 + 1);
      Right4Gr = readString.substring(ind11 + 1, ind12 + 1);
      ind13 = readString.indexOf(',', ind12 + 1);
      Right4Br = readString.substring(ind12 + 1, ind12 + 1);
      // Parsing info for Left side LEDs
      ind14 = readString.indexOf(',', ind12 + 1);
      Left1Rr = readString.substring(ind12 + 1, ind13 + 1);
      ind15 = readString.indexOf(',', ind13 + 1);
      Left1Gr = readString.substring(ind13 + 1, ind14 + 1);
      ind16 = readString.indexOf(',', ind14 + 1);
      Left1Br = readString.substring(ind14 + 1, ind15 + 1);

      ind17 = readString.indexOf(',', ind15 + 1);
      Left2Rr = readString.substring(ind15 + 1, ind16 + 1);
      ind18 = readString.indexOf(',', ind16 + 1);
      Left2Gr = readString.substring(ind16 + 1, ind17 + 1);
      ind19 = readString.indexOf(',', ind17 + 1);
      Left2Br = readString.substring(ind17 + 1, ind18 + 1);

      ind20 = readString.indexOf(',', ind18 + 1);
      Left3Rr = readString.substring(ind18 + 1, ind19 + 1);
      ind21 = readString.indexOf(',', ind19 + 1);
      Left3Gr = readString.substring(ind19 + 1, ind20 + 1);
      ind22 = readString.indexOf(',', ind20 + 1);
      Left3Br = readString.substring(ind20 + 1, ind21 + 1);

      ind23 = readString.indexOf(',', ind21 + 1);
      Left4Rr = readString.substring(ind21 + 1, ind22 + 1);
      ind24 = readString.indexOf(',', ind22 + 1);
      Left4Gr = readString.substring(ind22 + 1, ind23 + 1);
      ind25 = readString.indexOf(',', ind23 + 1);
      Left4Br = readString.substring(ind23 + 1, ind24 + 1);

      // Parses the strings of data to Integers
      int fanr = round(FanSpeedr.toInt());
      int Right1Rr = round(Right1R.toInt());
      int Right1Gr = round(Right1G.toInt());
      int Right1Br = round(Right1B.toInt());

      int Right2Rr = round(Right1R.toInt());
      int Right2Gr = round(Right1G.toInt());
      int Right2Br = round(Right1B.toInt());

      int Right3Rr = round(Right1R.toInt());
      int Right3Gr = round(Right1G.toInt());
      int Right3Br = round(Right1B.toInt());

      int Right4Rr = round(Right1R.toInt());
      int Right4Gr = round(Right1G.toInt());
      int Right4Br = round(Right1B.toInt());

      int Left1Rr = round(Right1R.toInt());
      int Left1Gr = round(Right1R.toInt());
      int Left1Br = round(Right1R.toInt());

      int Left2Rr = round(Right1R.toInt());
      int Left2Gr = round(Right1R.toInt());
      int Left2Br = round(Right1R.toInt());

      int Left3Rr = round(Right1R.toInt());
      int Left3Gr = round(Right1R.toInt());
      int Left3Br = round(Right1R.toInt());

      int Left4Rr = round(Right1R.toInt());
      int Left4Gr = round(Right1R.toInt());
      int Left4Br = round(Right1R.toInt());

      Serial.println(Right1Br);

      readString = ""; //clears variables for new input
      FanSpeed = "";

      Right1Rr = "";
      Right1Gr = "";
      Right1Br = "";

      Right2Rr = "";
      Right2Gr = "";
      Right2Br = "";

      Right3Rr = "";
      Right3Gr = "";
      Right3Br = "";

      Right4Rr = "";
      Right4Gr = "";
      Right4Br = "";

      Left1Rr = "";
      Left1Gr = "";
      Left1Br = "";

      Left2Rr = "";
      Left2Gr = "";
      Left2Br = "";

      Left3Rr = "";
      Left3Gr = "";
      Left3Br = "";

      Left4Rr = "";
      Left4Gr = "";
      Left4Br = "";
    }
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

void TempCheck()
{
  // call this to check the temps and control the fans,
  //comment this part out if you dont have a temp sensor - fan control setup.

  // checks if the manual override regulator has been used. If not, this code runs (automatic fan control)
  manualFanSpeed = analogRead(FanRegulator); // reads the setting of the fan regulator and stores it in manualFanSpeed

  if (manualFanSpeed = 0)
  {
    currentTemp = analogRead(TempSensor); // values range from 0 -1023

    // converting that reading to voltage, which is based off the reference voltage
    float voltage = currentTemp * aref_voltage;
    voltage /= 1024.0;

    //converting from 10 mv per degree wit 500 mV offset to degrees ((volatge - 500mV) times 100)
    float temperatureC = (voltage - 0.5) * 100;

    if (temperatureC >= 19)
    { //turns of the fans at 19 degress Celsius or below
      analogWrite(FanSpeed, 0);
    }
    else if (temperatureC >= 20)
    { // fans at 5% at 20c or under
      analogWrite(FanSpeed, 50);
    }
    else if (temperatureC >= 25)
    { // ~20% fanspeed at 25c
      analogWrite(FanSpeed, 250);
    }
    else if (temperatureC >= 30)
    { // 40% fanspeed at 30c
      analogWrite(FanSpeed, 400);
    }
    else if (temperatureC >= 35)
    { // 60% fanspeed at 35c
      analogWrite(FanSpeed, 600);
    }
    else if (temperatureC >= 45)
    { // 80% fanspeed at 40c
      analogWrite(FanSpeed, 800);
    }
    else if (temperatureC >= 50)
    { //fans at full speed at 50 degress Celsius
      analogWrite(FanSpeed, 1023);
    }
  }
}

void ButtonCheck() // call this to check the button states
{
  buttonState = digitalRead(ModeSwitch); // This part checks the button and counts how many times the button has been pushed

  if (buttonState != lastButtonState)
  { // compare the buttonState to its previous state

    if (buttonState == HIGH)
    {                      // if the state has changed, increment the counter
      buttonPushCounter++; // if the current state is HIGH then the button went from off to on
    }
    if (buttonPushCounter = 5)
    {
      buttonPushCounter = 0;
    }
  }

  lastButtonState = buttonState; // save the current state as the last state, for next time through the loop
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval || data == "CHECKS OFF")
  {
    // save the last time the code ran
    previousMillis = currentMillis;

    TempCheck();

    if (data == "DISABLE BUTTON")
    {
      ButtonCheck();
    }
  }

  // this checks the value of buttonPushCounter and selects the appropriate effect
  if (buttonPushCounter = 1 || data == "LIGHT FLASH") // || means or, and we are gonna have to figure out a way to send commands from the app
  {
    FlashingSound();
  }
  if (buttonPushCounter = 2 || data == "LIGHT SPIN")
  {
    SpinEffect();
  }
  if (buttonPushCounter = 3 || data == "LIGHT RANDOM")
  {
    RandomEffect();
  }
  /* if (buttonPushCounter = 4 || data == 5); {
    //place new effect here
    }*/
}
