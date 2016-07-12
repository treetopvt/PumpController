#include "leds.h"
#include "application.h"

void
Leds::blink ()
{
        char ststr[40];
        led_state = !led_state;
        sprintf (ststr, "New state: %d", led_state);
        digitalWrite (p, led_state);
}

void
Leds::changePeriod (int t)
{
        tp->changePeriod (t);
}

void
Leds::start ()
{
        tp->start ();
}

void
Leds::stop (int s)
{
        tp->stop ();
        digitalWrite (p, s);
        led_state = s;
}
Leds::Leds (int pin, int rate, int state)
{
        led_state = state;
        p = pin;
        pinMode (pin, OUTPUT);
        digitalWrite (p, led_state);
        r = rate;
        tp = new Timer (rate, &Leds::blink, *this);
}
