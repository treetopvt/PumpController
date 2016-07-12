#include "application.h"
class Leds
{
      private:
        int led_state;
        int r;
        int p;
        Timer *tp;
        void blink (void);
      public:
          Leds (int pin, int rate, int state);
        void changePeriod (int t);
        void start (void);
        void stop (int s);
};
