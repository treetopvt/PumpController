#include "application.h"
#include <vector>
// #include <algorithm>

class Relay{
  private:
    int _address;
    int _state = 0;
    long _lastOn = 0;
    String _name = "";
  public:
    Relay(int address, String name, long lastOn){
      _address = address;
      _name = name;
      _lastOn = lastOn;
      pinMode(address, OUTPUT);
    }
    String Name() { return _name; }
    int Address() { return _address; }
    long LastOn() { return _lastOn; }
    bool IsOn() { return _state == HIGH; }
    void TurnOn(void){
      _state = HIGH;
      Serial.print(_address);
      Serial.println(" TURN ON");
      digitalWrite(_address, _state);
      _lastOn = millis();//update last on
    }
    void UpdateState(){
      if(_state == HIGH){
        _lastOn = millis();
      }
    }
    void TurnOff(void){
      _state = LOW;
      Serial.print(_address);
      Serial.println(" TURN OFF");
      digitalWrite(_address, _state);
    }
};

class RelayHandler
{
      private:
        // int redLed = D4;
        // int blueLed = D7;
        // int led_state1 = 0;
        // int led_state2 = 0;
        // Timer *tp;
        // ClickButton* redButton;
        // ClickButton* blueButton;
        // void handleTimer (void);
        // void handleButtonClick (int clicks, int outPin);
        std::vector<Relay*> _relays;
        void initializeRelays(std::vector<int> relayAddresses);
        Relay* findRelayByName(String name);
        Relay* findRelayByAddress(int address);

        Timer *statusTimer;
        void handleTimer (void);
      public:
        RelayHandler();
        RelayHandler(long minTimeOff);
        ~RelayHandler();

        long CycleOffTimeMS = 6000; //will need to probably be 5min (30000) in production
        void Initialize(std::vector<int> relayAddresses);
        int ChangeRelayState(String relayName, bool turnOn);
        int ChangeRelayState(int relayNum, bool turnOn);
        bool AddRelay(int relayAddress, String name, bool turnOn);
        // void start (void);
        // void stop (int s);
};
