// #include "Adafruit_GFX.h"
// #include "Adafruit_LEDBackpack.h"
// #include "Adafruit_SSD1306.h"

#include "OneWire.h"
#include "spark-dallas-temperature.h"

//#include "clickButton.h"
#include "leds.h"
#include "ButtonListener.h"
#include "DisplayManager.h"
//#include "RelayHandler.h"
#include <vector>

Leds l1 (D7, 3000, 0);
ButtonListener bListener(D6, D5);
std::vector<int> relayAddr = {D7, A1};
RelayHandler rHandler(2000);//2 second min relay off time
DisplayManager* _display = new DisplayManager();

// Adafruit_7segment matrix = Adafruit_7segment();
//
// #define OLED_RESET D4
// Adafruit_SSD1306 display(OLED_RESET);
//
// #if (SSD1306_LCDHEIGHT != 64)
// #error("Height incorrect, please fix Adafruit_SSD1306.h!");
// #endif

double tempC = 0.0;
double tempF = 0.0;
int brightness = 15;
int tempSensorPin = D2;

//bool _useOLED = false;

OneWire oneWire(tempSensorPin);
DallasTemperature sensors(&oneWire);

int setBrightness(String bright){
  Serial.print(bright);
  brightness = bright.toInt();
  //matrix.setBrightness(brightness);
  return 0;
}

bool _inDemo = false;

int showDemo(String args){
  //display.display(); // show splashscreen
 // delay(2000);
 if(!_inDemo){
   _inDemo = true;
    // display.clearDisplay();   // clears the screen and buffer
    //
    // display.setTextSize(2);           // from 1-9 sensible actually can be bigger but useless
    // display.setTextColor(BLACK, WHITE); // 'inverted' text
    // display.setCursor(0,30);       // 128,64 pixels
    // display.clearDisplay();
    // display.println("Hello OLED");
    // display.display();
    // delay(4000);
    //
    //
    // display.setTextSize(1);
    // display.setTextColor(WHITE,BLACK); // Normal text
    // display.setCursor(0,0);
    // display.clearDisplay();
    // display.println("size 1");
    // display.println("size 1, line 2");
    // display.display();
    // delay(4000);
    //
    //
    // display.clearDisplay();
    // display.println("size 2");
    // display.display();
    // delay(1000);
    //
    //
    // display.setTextSize(3);
    // display.clearDisplay();
    // display.setCursor(50,4);
    // display.println("size 3");
    // display.display();
    // delay(1000);
    //
    //
    // display.setTextSize(9);
    // display.setCursor(0,0);
    // display.clearDisplay();
    // display.println("9");
    // display.display();
    // delay(2000);
    //
    //
    // display.setTextSize(1);
    // display.setCursor(0,0);
    // display.clearDisplay();
    // display.println("Good Bye");
    // display.display();
    // delay(2000);
    //
    // display.clearDisplay();
    // display.display();
     _inDemo = false;
     delay(500);
  }
}
void showTemp(double tempToShow, int tempNum) {
  // tempNum++;
  // Serial.print(tempNum);
  // Serial.println(tempToShow);
  // if(tempNum == 1){
  //   double tmpTemp = tempToShow*10.0;
  //   int32_t scaledTemp =  (int32_t)tmpTemp; // 724 means 72.4
  //   Serial.println(scaledTemp);
  //   // if (scaledTemp<0) {
  //   //     matrix.writeDigitRaw(0,0x40); // minus sign
  //   // } else {
  //   //     matrix.writeDigitRaw(0,0);
  //   // }
  //   if(scaledTemp>1000){
  //       matrix.writeDigitNum(0,(scaledTemp/1000)%10);
  //   }else{
  //     matrix.writeDigitRaw(0,0);
  //   }
  //
  //   if (scaledTemp<100) {
  //       matrix.writeDigitRaw(0,0);
  //   } else {
  //       matrix.writeDigitNum(1,(scaledTemp/100)%10);
  //   }
  //   matrix.writeDigitNum(3,(scaledTemp/10)%10, true);
  //   //matrix.writeDigitRaw(3,0x80); //degree dot
  //   matrix.writeDigitNum(4,(scaledTemp%10));
  //   matrix.writeDisplay();
  //}
//write to oled
    //display.clearDisplay();   // clears the screen and
    int vertPos = 16;
    if(tempNum != 1){
      vertPos = (tempNum + 1) * 11 + 1;
    }
//     display.setCursor(0, vertPos);
//     display.setTextSize(2);           // from 1-9 sensible actually can be bigger but useless
// //    display.setTextColor(BLACK, WHITE); // 'inverted' text
// //    display.setCursor(0,30);       // 128,64 pixels
//     String newStr = String::format("%d %.2f F",tempNum, tempToShow);
//     //String newStr = String(tempF, DEC) + String(' F');
//     //String tmp = String("TEST MSG");
//     display.println(newStr.c_str());
//     display.display();
//     //delay(1500);

}
void drawHeader(){
  // display.setTextColor(WHITE, BLACK); // VERY IMPORTANT TO DISPLAY ANYTHING!
  // display.setCursor(0,0);       // 128,64 pixels
  // display.drawCircle(6,6,6,WHITE);
  // display.setCursor(16,0);
  // display.setTextSize(2);
  // display.print("A PUMP B");
  // display.setCursor(78,1);
  // //display.print("PUMP 2");
  // display.drawCircle(120,6,6,WHITE);
}

void updatePumpStatusDisplay(int pumpNum, bool pumpOn){
  // int xPos = -1;
  // switch (pumpNum) {
  //   case 1:
  //     xPos = 6;
  //     break;
  //   case 2:
  //     xPos = 120;
  //     break;
  //   default:
  //     return;
  // }
  // if(pumpOn){
  //   display.fillCircle(xPos,6,6,WHITE);
  // }else{
  //   display.fillCircle(xPos,6,6,BLACK);
  //   display.drawCircle(xPos,6,6,WHITE);
  // }
}

int changePumpState(int pumpNum, bool desiredOn){
  //find pump address in memory based on pump number

  //set it to correct state and record start time in eeprom

  //update display if successful, otherwise return -1
  updatePumpStatusDisplay(pumpNum, desiredOn);
  return 0;
}
int changePumpStateRemotely(String args){
    char com = args.charAt(0);
    int rslt = -1;
    int rslt2 = -1;
    bool desiredOn = false;
    int pumpNum = -1;
    char char1 = '0';
    //A to activate, D to deactivate, R to turn everything off,
    //W to write current status to serial
    switch(com){
      case 'A':
      case 'D':
        desiredOn = false;
        if(com == 'A'){
          desiredOn = true;
        }
        //get which pump to change
        pumpNum = args.charAt(1) - '0';//minus 48 to get int value
        //Serial.println(char1);
        char1 = args.charAt(2);
        Serial.println(pumpNum);
        rslt = changePumpState(pumpNum, desiredOn);
        if(char1 !='0'){
          pumpNum = char1 - '0';
          rslt2 = changePumpState(pumpNum, desiredOn);
          if (rslt < 0 || rslt2 < 0){
            return -1;
          }
        }else{
          return rslt;
        }

      break;
      case 'R':
        //reset
        rslt = changePumpState(1, false);
        rslt2 = changePumpState(2, false);
        if (rslt < 0 || rslt2 < 0){
          return -1;
        }
      break;
      case 'W':
        //write the current state of each pump to the serial stream
      break;
    }
    return 0;
}

bool _isInitialized = false;
bool _startInitialization = false;
bool initDisplays(bool forceInit = false){

  if(_isInitialized && !forceInit){
    return true;
  }else if(_startInitialization){
    return false;
  }
    _startInitialization = true;
    // display.clearDisplay();   // clears the screen and buffer
    // matrix.writeDigitRaw(0,0);
    // matrix.writeDigitRaw(1,0);
    // matrix.writeDigitRaw(2,0);
    // matrix.writeDigitRaw(3,0);
    // matrix.writeDigitRaw(4,0);
    // matrix.writeDisplay();
    //
    // Serial.println("initializing oled");
    // display.clearDisplay();   // clears the screen and buffer
    //
    // display.setTextSize(1);           // from 1-9 sensible actually can be bigger but useless
    // display.setTextColor(WHITE, BLACK); // VERY IMPORTANT TO DISPLAY ANYTHING!
    // display.setCursor(5,30);       // 128,64 pixels
    // display.clearDisplay();
    // display.println("Initializing");
    // display.display();
    // delay(500);
    // Serial.println("finished init oled");
    // sensors.requestTemperatures();
    // display.clearDisplay();   // clears the screen and buffer
    // drawHeader();
    _isInitialized = true;
    return true;
}

void setup() {
  Serial.begin(57600); // for debug. Has to be first in the code, or the USB-RS232 driver doesn't start
  //pinMode(D6, INPUT);
  //pinMode(blueButtonPIN, INPUT);
  //last = millis();

  // matrix.begin(0x70);
  // matrix.setBrightness(brightness);
  //
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // display.display(); // show splashscreen
  // delay(500);
  // display.clearDisplay();   // clears the screen and buffer
  //
  //
  //l1.start ();
  rHandler.Initialize(relayAddr);

  _display->Initialize();

  bListener.start(rHandler);


  sensors.begin();
  Particle.variable("tempc", tempC);
  Particle.variable("tempf", tempF);
  Particle.function("setbright", setBrightness);
  Particle.function("showDemo", showDemo);
  Particle.function("pumpState", changePumpStateRemotely);
}

void loop() {
  // int min = 02;
  // int hour = 7;
  // matrix.print(hour * 100 + min, DEC);
  //Serial.println("TEST");
  //colon = ! colon;
  // matrix.drawColon(colon);
  // matrix.writeDisplay
  // while(!initDisplays()){
  //
  // }

  sensors.requestTemperatures();
  int sensorCount = sensors.getDeviceCount();

  for(int i=0; i<sensorCount; i++) {
  //  Serial.println(i);
    double tempCheck = sensors.getTempCByIndex(i);
    if ( tempCheck > -50 && tempCheck < 50) // might want to guard against a spurious high value as well
    {
        tempC = tempCheck;
        tempF = tempC * 9.0 / 5.0 + 32.0;
        // EXAMPLE USAGE
        String newStr = String::format("%f F",tempF);
        String tempName = String::format("%i Therm", i);
        //char* publishString;
        //sprintf(publishString,"%f F",tempF);
        //Serial.println(tempF);
        Particle.publish(tempName, newStr);
        //write to LED
        showTemp(tempF, i);
        // matrix.writeDisplay();
    }
  }
   delay(1000);
}
