#include "application.h"
#include "clickButton.h"
#include "RelayHandler.h"

class ButtonListener
{
      private:
        int redLed = D4;
        int blueLed = D7;
        int led_state1 = 0;
        int led_state2 = 0;
        Timer *tp;
        RelayHandler* _rHandler;
        ClickButton* redButton;
        ClickButton* blueButton;
        void handleTimer (void);
        void handleButtonClick (int clicks, int outPin);
      public:
        ButtonListener (int redButtonPin, int blueButtonPin);
        // void start (void);
        void start (RelayHandler &rHandler);
        void stop (int s);
};
