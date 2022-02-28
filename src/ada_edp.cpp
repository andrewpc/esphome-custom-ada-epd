#include "ada_edp.h"
#include <ctime>
#include "esphome/components/time/real_time_clock.h"

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
    time::ESPTime esptime = esptime.from_epoch_local(result);
    
    Serial.println("Update Called");

    
    displayEPD.setCursor(5,5);
    displayEPD.setTextColor(EPD_BLACK);
    displayEPD.clearBuffer();

    if (esptime.year > 1970) {

      displayEPD.setTextSize(6);
      displayEPD.setRotation(0);
      displayEPD.clearBuffer();
      
      displayEPD.setTextSize(6);
      displayEPD.setCursor(5,5);
      displayEPD.setTextColor(EPD_BLACK);


      displayEPD.printf("%.2f°C", float(this->temperature_sensor_->state));

      displayEPD.setTextSize(3);
      displayEPD.setCursor(5,80);
      displayEPD.printf("Humidity: %.2f%%", float(this->humidity_sensor_->state));

      displayEPD.setCursor(5,170);

      displayEPD.printf("Last Updated: %02i/%02i/%02i %02i:%02i", esptime.day_of_month, esptime.month, esptime.year, esptime.hour, esptime.minute);

    }
    else{
      displayEPD.setTextSize(4);
      displayEPD.printf("Waiting for connection...")
    }



    displayEPD.display(false);
 

    counter++;
  };



}  // namespace ada_edp
}  // namespace esphome
