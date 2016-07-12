#include "RelayHandler.h"

void RelayHandler::initializeRelays(std::vector<int> relayAddresses){
  // for (unsigned int i = 0; i < relayList.size(); i++ ) {
  //   Serial.printf(relayList[i]);
  // }
  for (auto &r : relayAddresses) // access by reference to avoid copying
    {
      char str[40];
      sprintf (str, "Relay Addr: %d", r);
      Serial.println(str);
      //build relay struct
      //get any eeprom information about relay (when it was last on namely!)
      _relays.push_back(new Relay(r, "Named", 0));
    }
}

Relay* RelayHandler::findRelayByName(String name){
  for (int i = 0; i<_relays.size();i++)
  {
    String rName = _relays[i]->Name();
      if(rName == name)
      {
          //"i" is the index of your Vector.
          return _relays[i];
      }
  }
}
Relay* RelayHandler::findRelayByAddress(int address){
  for (int i = 0; i<_relays.size();i++)
  {
      if(_relays[i]->Address() == address)
      {
          //"i" is the index of your Vector.
          return _relays[i];
      }
  }
}

int RelayHandler::ChangeRelayState(String relayName, bool turnOn){
  Serial.print(relayName);
  Serial.println(" ,Relay state changed");
}
int RelayHandler::ChangeRelayState(int relayNum, bool turnOn){
  Relay *r = findRelayByAddress(relayNum);
  if(r == NULL){
    return -1;
  }
  long now = (long)millis();
  if(turnOn){
    long lastOn = r->LastOn();
    Serial.print(lastOn);
    Serial.print(", ");
    Serial.print(CycleOffTimeMS);
    Serial.print(", ");
    Serial.println(now);
    if(lastOn != 0 && (lastOn + CycleOffTimeMS > now)){
      Serial.print(r->Address());
      Serial.println(": cannot be turned on due to minimum times");
      return -1; //not enough time has ellapsed
    }else{
      //minimum time ellapsed since on
      r->TurnOn();
      Serial.print(relayNum);
      Serial.println(": Relay turned on");
    }
  }else{
    r->TurnOff();
    Serial.print(relayNum);
    Serial.println(": Relay turned off");
  }

}

void RelayHandler::handleTimer (void){
  //update the status of all relays and write to eeprom
  for (auto &r : _relays) // access by reference to avoid copying
    {
      r->UpdateState();
    }
}

RelayHandler::RelayHandler(){
  int listeningRate = 5;
  statusTimer = new Timer (listeningRate, &RelayHandler::handleTimer, *this);
}
RelayHandler::RelayHandler(long minTimeOff):RelayHandler(){
  CycleOffTimeMS = minTimeOff;
}

void RelayHandler::Initialize(std::vector<int> relayAddresses){
  Serial.println("In Relay Handler Initializer");
  initializeRelays(relayAddresses);
  statusTimer->start ();
}

bool RelayHandler::AddRelay(int relayAddress, String name, bool turnOn){

}

RelayHandler::~RelayHandler(){

}
