#include "ada_edp.h"

namespace esphome {
namespace ada_edp {

#define EPD_DC      26 // can be any pin, but required!
#define EPD_CS      27  // can be any pin, but required!
#define EPD_BUSY    16  // can set to -1 to not use a pin (will wait a fixed delay)
#define SRAM_CS     25  // can set to -1 to not use a pin (uses a lot of RAM!)
#define EPD_RESET   13  // can set to -1 and share with chip Reset (can't deep sleep)
#define EPD_MOSI   23
#define EPD_MISO   19
#define EPD_CLK   18

static const char *const TAG = "ada_epd";

  ThinkInk_154_Tricolor_Z90 displayEPD(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
  //ThinkInk_154_Tricolor_Z90 displayEDP(EPD_MOSI, EPD_CLK, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_MISO, EPD_BUSY);

  void ADAEDPComponent::setup() {
    Serial.begin(115200);
    while (!Serial) { delay(10); }
    Serial.println("AC Temp Monitor Boot");
    displayEPD.begin(THINKINK_TRICOLOR);
  };

  void ADAEDPComponent::dump_config(){
    Serial.println("dump");      
  };


  
  uint16_t counter = 0;

  void ADAEDPComponent::update(){
    
    std::time_t result = std::time(nullptr);
    time::ESPTime esptime;
    esptime.from_epoch_local(result);
    uint8_t month = esptime.day_of_month;
    
    
    Serial.println("Update Called");
    
    displayEPD.setRotation(0);
    displayEPD.clearBuffer();
    
     displayEPD.setTextSize(2);
     displayEPD.setCursor(5,5);
     displayEPD.setTextColor(EPD_BLACK);
    // displayEPD.print(std::ctime(&result)); 

    // displayEPD.setTextSize(2);
    // displayEPD.setTextColor(EPD_RED);
    // displayEPD.setCursor(5, 100);
    // displayEPD.printf ("Loops: ");
    // displayEPD.print(counter);
    //displayEPD.printf("Time: %02i:%02i", esptime.hour, esptime.minute);

    displayEPD.setCursor(5,40);

    displayEPD.printf("Date: %02i/%02i", esptime.day_of_month, esptime.month);

    displayEPD.setCursor(5,75);

    displayEPD.printf("Temperature: %.2fC", float(this->temperature_sensor_->state));

    displayEPD.setCursor(5,110);

    displayEPD.printf("Humidity: %.2f%%", float(this->humidity_sensor_->state));

    displayEPD.setCursor(5,140);

    displayEPD.printf("Loops: %i", counter);







    displayEPD.display(false);
 

    counter++;
  };



}  // namespace ada_edp
}  // namespace esphome
