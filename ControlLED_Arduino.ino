#include <SoftwareSerial.h>

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

#define Left2R 18
#define Left2G 19
#define Left2B 20

#define Left3R 21
#define Left3G 22
#define Left3B 23

#define Left4R 24
#define Left4G 25
#define Left4B 26

#define ModeSwitch 28 // Button for switching profile

#define TempSensor A2 // Temperature sensor for the amplifiers

#define FanRegulator 29 // Manual regulator for the fans
#define FanSpeed A3     // connect the fans here

#define Mic A1 //Input from the microphone

SoftwareSerial mySerial(30, 31);

byte SoundIntensity; // Variable to hold the intensity of the analog sound signal

// Variables for the button
byte buttonPushCounter = 0; // Counter for the number of button presses
byte buttonState = 0;       // Current state of the button
byte lastButtonState = 0;   // Previous state of the button

// Variables for the temp sensor and fans
int currentTemp;    // Stores the current temperature
int manualFanSpeed; // Holds the reading from the fanregulator

byte LeftRandom; // Holds random numbers for the left / right speaker
byte RightRandom;
byte LightRandom;

unsigned long previousMillis = 0; // time since last run of the code

// constants won't change:
const long interval = 1000; // interval at which to do TempCheck (milliseconds)

String string;
char command;

byte pins[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26}; // the pins to of the LEDs
byte Redpins[] = {3, 6, 9, 12, 15, 18, 21, 24};                                                          //Red pins
byte Greenpins[] = {4, 7, 10, 13, 16, 19, 22, 25};                                                       //Green pins
byte Bluepins[] = {5, 8, 11, 14, 17, 20, 23, 26};                                                        // Blue pins

// A byte value which will be either 0, 127 or 255 depending
// on if Red, Green o Blue LED should light up
byte R1;
byte R2;
byte R3;
byte R4;
byte L1;
byte L2;
byte L3;
byte L4;

byte EffectChoise; // Stores the choice of effect command

void setup()
{
  Serial.begin(57600); // Serial used for bluetooth
  // The data rate for the SoftwareSerial port needs to
  // match the data rate for your bluetooth board.
  mySerial.begin(9600);

  // If you want to set the aref to something other than 5v
  analogReference(EXTERNAL);

  pinMode(ModeSwitch, INPUT);
  pinMode(TempSensor, INPUT);
  pinMode(FanRegulator, INPUT);
  pinMode(Mic, INPUT);

  pinMode(FanSpeed, OUTPUT);

  //make Right & Left SB pins outputs
  for (int i = 0; i < sizeof(pins); i++)
  {
    pinMode(pins[i], OUTPUT); //makes all LED pins outputs
  }
}

void massDigitalWrite()
{
  for (int i = 0; i < sizeof(pins); i++)
  {
    digitalWrite(pins[i], LOW); //turns off all LEDs
  }
}

void Bluetooth()
{
  // if there's a new command reset the string
  if (mySerial.available())
  {
    string = "";
  }

  // Construct the command string fetching the bytes, sent by Android, one by one.
  while (mySerial.available())
  {
    command = ((byte)mySerial.read()); // Reads the serial port and adds the data to the byte "command"

    if (command == ':') // Stops if a ":" is encounted
    {
      break;
    }
    else
    {
      string += command; // Puts the recived commands into string commands
    }
  }

  Serial.println(string); // Print on the Monitor latest command recieved

  // Checks if a effect change command has been sent
  if (string == "FlashEffect") // Command for Flash effect
  {
    EffectChoise = 1;
  }
  else if (string == "SpinEffect") // Command for Spin effect
  {
    EffectChoise = 2;
  }
  else if (string == "RandomEffect") //Command for Random effect
  {
    EffectChoise = 3;
  }

  // Right LEDs
  if (string == "R1R HIGH") //Right1 Red LED
  {
    R1 = 0; // 0 = Red
  }
  else if (string == "R1G HIGH")
  {
    R1 = 127; // 127 = Green
  }
  else if (string == "R1B HIGH")
  {
    R1 = 255; //255 = Blue
  }

  if (string == "R2R HIGH")
  {
    R2 = 0;
  }
  else if (string == "R2G HIGH")
  {
    R2 = 127;
  }
  else if (string == "R2B HIGH")
  {
    R2 = 255;
  }

  if (string == "R3R HIGH")
  {
    R3 = 0;
  }
  else if (string == "R3G HIGH")
  {
    R3 = 127;
  }
  else if (string == "R3B HIGH")
  {
    R3 = 255;
  }

  if (string == "R4R HIGH")
  {
    R4 = 0;
  }
  else if (string == "R4G HIGH")
  {
    R4 = 127;
  }
  else if (string == "R4B HIGH")
  {
    R4 = 255;
  }

  // Left LEDs
  if (string == "L1R HIGH")
  {
    L1 = 0;
  }
  else if (string == "L1G HIGH")
  {
    L1 = 127;
  }
  else if (string == "L1B HIGH")
  {
    L1 = 255;
  }

  if (string == "L2R HIGH")
  {
    L2 = 0;
  }
  else if (string == "L2G HIGH")
  {
    L2 = 127;
  }
  else if (string == "L2B HIGH")
  {
    L2 = 255;
  }

  if (string == "L3R HIGH")
  {
    L3 = 0;
  }
  else if (string == "L3G HIGH")
  {
    L3 = 127;
  }
  else if (string == "L3B HIGH")
  {
    L3 = 255;
  }

  if (string == "R4R HIGH")
  {
    L4 = 0;
  }
  else if (string == "R4G HIGH")
  {
    L4 = 127;
  }
  else if (string == "R4B HIGH")
  {
    L4 = 255;
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

void SpinEffect() //creates a infinte loopable spin effect
{
  if (R4 = 0)
  {
    digitalWrite(Right4R, HIGH);
  }
  else if (R4 = 127)
  {
    digitalWrite(Right4G, HIGH);
  }
  else
  {
    digitalWrite(Right4B, HIGH);
  }

  if (L4 = 0)
  {
    digitalWrite(Left4R, HIGH);
  }
  else if (L4 = 127)
  {
    digitalWrite(Left4G, HIGH);
  }
  else
  {
    digitalWrite(Left4B, HIGH);
  }

  digitalWrite(Right2R, LOW);
  digitalWrite(Right2G, LOW);
  digitalWrite(Right2B, LOW);

  digitalWrite(Left2R, LOW);
  digitalWrite(Left2G, LOW);
  digitalWrite(Left2B, LOW);
  if (R4 = 0)
  {
    digitalWrite(Right1R, HIGH);
  }
  else if (R4 = 127)
  {
    digitalWrite(Right1G, HIGH);
  }
  else
  {
    digitalWrite(Right1B, HIGH);
  }

  if (L1 = 0)
  {
    digitalWrite(Left1R, HIGH);
  }
  else if (L1 = 127)
  {
    digitalWrite(Left1G, HIGH);
  }
  else
  {
    digitalWrite(Left1B, HIGH);
  }

  digitalWrite(Right3R, LOW);
  digitalWrite(Right3G, LOW);
  digitalWrite(Right3B, LOW);

  digitalWrite(Left3R, LOW);
  digitalWrite(Left3G, LOW);
  digitalWrite(Left3B, LOW);

  if (R2 = 0)
  {
    digitalWrite(Right2R, HIGH);
  }
  else if (R2 = 127)
  {
    digitalWrite(Right2G, HIGH);
  }
  else
  {
    digitalWrite(Right2B, HIGH);
  }

  if (L2 = 0)
  {
    digitalWrite(Left2R, HIGH);
  }
  else if (L2 = 127)
  {
    digitalWrite(Left2G, HIGH);
  }
  else
  {
    digitalWrite(Left2B, HIGH);
  }

  digitalWrite(Right4R, LOW);
  digitalWrite(Right4G, LOW);
  digitalWrite(Right4B, LOW);

  digitalWrite(Left4R, LOW);
  digitalWrite(Left4G, LOW);
  digitalWrite(Left4B, LOW);
  if (R3 = 0)
  {
    digitalWrite(Right3R, HIGH);
  }
  else if (R3 = 127)
  {
    digitalWrite(Right3G, HIGH);
  }
  else
  {
    digitalWrite(Right3B, HIGH);
  }

  if (L3 = 0)
  {
    digitalWrite(Left3R, HIGH);
  }
  else if (L3 = 127)
  {
    digitalWrite(Left3G, HIGH);
  }
  else
  {
    digitalWrite(Left3B, HIGH);
  }

  digitalWrite(Right1R, LOW);
  digitalWrite(Right1G, LOW);
  digitalWrite(Right1B, LOW);

  digitalWrite(Left1R, LOW);
  digitalWrite(Left1G, LOW);
  digitalWrite(Left1B, LOW);
  if (R4 = 0)
  {
    digitalWrite(Right4R, HIGH);
  }
  else if (R4 = 127)
  {
    digitalWrite(Right4G, HIGH);
  }
  else
  {
    digitalWrite(Right4B, HIGH);
  }
  if (L4 = 0)
  {
    digitalWrite(Left4R, HIGH);
  }
  else if (L4 = 127)
  {
    digitalWrite(Left4G, HIGH);
  }
  else
  {
    digitalWrite(Left4B, HIGH);
  }

  digitalWrite(Right2R, LOW);
  digitalWrite(Right2G, LOW);
  digitalWrite(Right2B, LOW);

  digitalWrite(Left2R, LOW);
  digitalWrite(Left2G, LOW);
  digitalWrite(Left2B, LOW);
}

void FlashingSound() // flashes the LEDs in beat with the music
{
  byte RandomColor;

  //reads the sound signal and saves it as a number between 0 and 1023
  SoundIntensity = analogRead(Mic);

  // Makes all the LEDs flash with the music. Adjust the number with * for better precision
  for (int i = 0; i < sizeof(pins); i++)
  {
    RandomColor = random(3);

    if (RandomColor == 1) //Makes a specific color flash each time
    {
      digitalWrite(Redpins[i], SoundIntensity * 15); //assigns the pin the value of variable "SoundIntensity";
    }
    if (RandomColor == 2)
    {
      digitalWrite(Greenpins[i], SoundIntensity * 15);
    }
    if (RandomColor == 3)
    {
      digitalWrite(Bluepins[i], SoundIntensity * 15);
    }
  }
}

void RandomEffect() // Lights the LEDs in a random sequense
{
  //Creates 3 byte values and generates random values
  LeftRandom = random(4);
  RightRandom = random(4);
  LightRandom = random(3);

  massDigitalWrite(); // Släcker alla lamporna
  unsigned long currentMillis = millis();

  if ((currentMillis - previousMillis) >= interval)
  {
    if (LeftRandom = 1)
    {
      if (LightRandom == 1)
      {
        digitalWrite(Left1R, LightRandom);
      }
      else if (LightRandom == 2)
      {
        digitalWrite(Left1G, LightRandom);
      }
      else
      {
        digitalWrite(Left1B, LightRandom);
      }
    }
    if (LeftRandom = 2)
    {
      if (LightRandom == 1)
      {
        digitalWrite(Left2R, LightRandom);
      }
      else if (LightRandom == 2)
      {
        digitalWrite(Left2G, LightRandom);
      }
      else
      {
        digitalWrite(Left2B, LightRandom);
      }
    }
    if (LeftRandom = 3)
    {
      if (LightRandom == 1)
      {
        digitalWrite(Left3R, LightRandom);
      }
      else if (LightRandom == 2)
      {
        digitalWrite(Left3G, LightRandom);
      }
      else
      {
        digitalWrite(Left3B, LightRandom);
      }
    }
    if (LeftRandom = 4)
    {
      if (LightRandom == 1)
      {
        digitalWrite(Left4R, LightRandom);
      }
      else if (LightRandom == 2)
      {
        digitalWrite(Left4G, LightRandom);
      }
      else
      {
        digitalWrite(Left4B, LightRandom);
      }
    }
  }
  if ((currentMillis - previousMillis) >= interval)
  {
    if (RightRandom = 1)
    {
      if (LightRandom == 1)
      {
        digitalWrite(Right1R, LightRandom);
      }
      else if (LightRandom == 2)
      {
        digitalWrite(Right1G, LightRandom);
      }
      else
      {
        digitalWrite(Right1B, LightRandom);
      }
    }

    if (RightRandom = 2)
    {
      if (LightRandom == 1)
      {
        digitalWrite(Right2R, LightRandom);
      }
      else if (LightRandom == 2)
      {
        digitalWrite(Right2G, LightRandom);
      }
      else
      {
        digitalWrite(Right2B, LightRandom);
      }
    }

    if (RightRandom = 3)
    {
      if (LightRandom == 1)
      {
        digitalWrite(Right3R, LightRandom);
      }
      else if (LightRandom == 2)
      {
        digitalWrite(Right3G, LightRandom);
      }
      else
      {
        digitalWrite(Right3B, LightRandom);
      }
    }

    if (RightRandom = 4)
    {
      if (LightRandom == 1)
      {
        digitalWrite(Right4R, LightRandom);
      }
      else if (LightRandom == 2)
      {
        digitalWrite(Right4G, LightRandom);
      }
      else
      {
        digitalWrite(Right4B, LightRandom);
      }
    }
  }
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // save the last time the code ran
    previousMillis = currentMillis;

    TempCheck();
  }
  Bluetooth(); //Checks the bluetooth connection

  // Checks which effect is choosen and runs it
  if (EffectChoise = 1)
  {
    FlashingSound();
  }
  else if (EffectChoise = 2)
  {
    SpinEffect();
  }
  else
  {
    RandomEffect();
  }
}