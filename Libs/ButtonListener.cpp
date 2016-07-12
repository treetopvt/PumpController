#include "ButtonListener.h"
#include "application.h"
//#include "clickButton.h"


void ButtonListener::handleButtonClick (int clicks, int outPin){
  bool writeState = false;
  int outState = 0;
  switch(clicks){
    case 1:
      //switch led state
      writeState = true;
      if(outPin == redLed){
        outState = !led_state1;
      }else if(outPin == blueLed) {
        outState = !led_state2;
      }
      //digitalWrite (D7, led_state);
      break;
    case 2:
      //turn on no matter what
      writeState = true;
      outState = 1;
      //digitalWrite (D7, led_state);
      break;
    case -1:
      //turn OFF no matter what
      writeState = true;
      outState = 0;
      break;
  }
  if(writeState){
    //digitalWrite (outPin, outState);
    int result = _rHandler->ChangeRelayState(outPin, outState);
    if(result != -1){
      if(outPin == redLed){
        led_state1 = outState;
      }else if(outPin == blueLed){
        led_state2 = outState;
      }
    }
  }
}


void ButtonListener::handleTimer ()
{
  char ststr[40];
  //led_state = !led_state;
  //sprintf (ststr, "New state: %d", led_state);
  //digitalWrite (p, led_state);
  redButton->Update();
  int clicks = redButton->clicks;
  handleButtonClick(clicks, redLed);
  blueButton->Update();
  clicks = blueButton->clicks;
  handleButtonClick(clicks, blueLed);
}

// void ButtonListener::start ()
// {
//         tp->start ();
// }
void ButtonListener::start (RelayHandler &rHandler)
{
  _rHandler = &rHandler;
  tp->start ();
}
void ButtonListener::stop (int s)
{
  tp->stop ();
  //led_state = s;
}
ButtonListener::ButtonListener(int redButtonPin, int blueButtonPin)
{
    int listeningRate = 5;

    pinMode(blueLed, OUTPUT);
    pinMode(redLed, OUTPUT);
    digitalWrite (redLed, led_state1); //turn off led
    digitalWrite (blueLed, led_state1); //turn off led
    pinMode(redButtonPin, INPUT);
    pinMode(blueButtonPin, INPUT);
    redButton = new ClickButton(redButtonPin, HIGH);
    redButton->debounceTime   = 20;   // Debounce timer in ms
    redButton->multiclickTime = 250;  // Time limit for multi clicks
    redButton->longClickTime  = 1000; // time until "held-down clicks" register

    blueButton = new ClickButton(blueButtonPin, HIGH);
    blueButton->debounceTime   = 20;   // Debounce timer in ms
    blueButton->multiclickTime = 250;  // Time limit for multi clicks
    blueButton->longClickTime  = 1000; // time until "held-down clicks" register

    tp = new Timer (listeningRate, &ButtonListener::handleTimer, *this);
}
