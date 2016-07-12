#include "DisplayManager.h"

  DisplayManager::DisplayManager(){

  }
  // DisplayManager::DisplayManager(int availableTempSensors){
  //
  // }
  DisplayManager::~DisplayManager(){

  }

  void DisplayManager::Initialize(){
    Serial.println("Initializing Displays");
    _matrix.begin(0x70);
    _matrix.setBrightness(13);

    _display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
    _display.display(); // show splashscreen
    delay(500);
    //_display.clearDisplay();   // clears the screen and buffer
    drawHeader();
    Serial.println("FINISHED Initializing Displays");
  }
  int DisplayManager::UpdatePumpState(String relayName, bool isOn){

  }
  int DisplayManager::UpdatePumpState(int relayNum, bool isOn){

  }

  void DisplayManager::drawHeader(){
    Serial.println("Drawing Header");
    _display.clearDisplay();
    _display.setTextColor(WHITE, BLACK); // VERY IMPORTANT TO DISPLAY ANYTHING!
    _display.setCursor(0,0);       // 128,64 pixels
    _display.drawCircle(6,6,6,WHITE);
    _display.setCursor(16,0);
    _display.setTextSize(2);
    _display.print("A PUMP B");
    _display.setCursor(78,1);
    //display.print("PUMP 2");
    _display.drawCircle(120,6,6,WHITE);
    _display.display();
    Serial.println("FINISHED Drawing Header");
  }

  void DisplayManager::update7Segement(double tempF){
    double tmpTemp = tempF*10.0;
    int32_t scaledTemp =  (int32_t)tmpTemp; // 724 means 72.4
    Serial.println(scaledTemp);
    // if (scaledTemp<0) {
    //     matrix.writeDigitRaw(0,0x40); // minus sign
    // } else {
    //     matrix.writeDigitRaw(0,0);
    // }
    if(scaledTemp>1000){
        _matrix.writeDigitNum(0,(scaledTemp/1000)%10);
    }else{
      _matrix.writeDigitRaw(0,0);
    }

    if (scaledTemp<100) {
        _matrix.writeDigitRaw(0,0);
    } else {
        _matrix.writeDigitNum(1,(scaledTemp/100)%10);
    }
    _matrix.writeDigitNum(3,(scaledTemp/10)%10, true);
    //_matrix.writeDigitRaw(3,0x80); //degree dot
    _matrix.writeDigitNum(4,(scaledTemp%10));
    _matrix.writeDisplay();
  }
  void DisplayManager::updateOLEDTemp(int lineNum, double tempF){
    //display.clearDisplay();   // clears the screen and
    //need to find the correct temp/relay combo and figure out line num
      int vertPos = 16;
      int tempNum = lineNum;
      if(tempNum != 1){
        vertPos = (tempNum + 1) * 11 + 1;
      }
      _display.setCursor(0, vertPos);
      _display.setTextSize(2);           // from 1-9 sensible actually can be bigger but useless
  //    display.setTextColor(BLACK, WHITE); // 'inverted' text
  //    display.setCursor(0,30);       // 128,64 pixels
      //String newStr = String::format("%d %.2f F",sensorId, tempF);
      String newStr = String::format("%d %.2f F",lineNum, tempF);
      //String newStr = String(tempF, DEC) + String(' F');
      //String tmp = String("TEST MSG");
      _display.println(newStr.c_str());
      _display.display();
      //delay(1500);
  }

  void DisplayManager::UpdateTemperature(int sensorId, double tempF){
  //  tempNum++;
    Serial.print(sensorId);
    Serial.println(tempF);
    if(sensorId == 1){
      update7Segement(tempF);
    }

    //update temp mapping
    _tempMap[sensorId] = tempF;
    //write to oled
    int lineNum = 0;
    updateOLEDTemp(lineNum, tempF);
  }
