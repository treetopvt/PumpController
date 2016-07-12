#include "application.h"
#include <map>

#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_SSD1306.h"

#define OLED_RESET D4
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

class DisplayManager
{
      private:
        std::map<int, double> _tempMap;

        Adafruit_7segment _matrix = Adafruit_7segment();
        Adafruit_SSD1306 _display = Adafruit_SSD1306(OLED_RESET);


        // void initializeRelays(std::vector<int> relayAddresses);
        // Relay* findRelayByName(String name);
        // Relay* findRelayByAddress(int address);
        //
        // Timer *statusTimer;
        // void handleTimer (void);
        void update7Segement(double tempF);
        void updateOLEDTemp(int lineNum, double tempF);
        void drawHeader();
      public:
        DisplayManager();
        ~DisplayManager();

        void Initialize();
        int UpdatePumpState(String relayName, bool isOn);
        int UpdatePumpState(int relayNum, bool isOn);

        void UpdateTemperature(int sensorId, double tempF);
};
