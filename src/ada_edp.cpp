#include "ada_edp.h"
#include "AvenirNextLTPro_Regular32pt7b.h"
#include "AvenirNextLTPro_Regular16pt7b.h"
#include "AvenirNextLTPro_Regular14pt7b.h"
#include <ctime>


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
    Serial.println("dump_config");      
  };


  
  uint16_t counter = 0;
  float lastTemp = 0;
  int lastHumidity = 0;
  int lastPressure = 0;
  bool screenUpdate = false;

  void ADAEDPComponent::update(){
    
    Serial.printf("Last Temp: %f", lastTemp); 
    Serial.printf("Current Temp: %f", float(this->temperature_sensor_->state)); 
    Serial.printf("Last Humidity: %i", lastHumidity); 
    Serial.printf("Current Humidity: %i", int(this->humidity_sensor_->state)); 
    Serial.printf("Last Pressure: %i", lastPressure); 
    Serial.printf("Current Pressure: %i", int(this->pressure_sensor_->state)); 

    if (lastTemp != float(this->temperature_sensor_->state) || 
      lastHumidity != int(this->humidity_sensor_->state) ||
      lastPressure != int(this->pressure_sensor_->state) )
    {
      Serial.println("*********************"); 
      Serial.println("At least one sensor value has changed - screen update needed"); 
      Serial.println("*********************"); 
      
      screenUpdate = true;
      
      lastTemp = float(this->temperature_sensor_->state);
      lastHumidity != int(this->humidity_sensor_->state);
      lastPressure != int(this->pressure_sensor_->state);
    }


    //std::time_t result = std::time(nullptr);
    //time::ESPTime esptime = esptime.from_epoch_local(result);


    displayEPD.setCursor(5,5);
    displayEPD.setTextColor(EPD_BLACK);
    displayEPD.setRotation(2);
    
    displayEPD.clearBuffer();

    displayEPD.setFont(&AvenirNextLTPro_Regular32pt7b);
    displayEPD.setTextSize(1);
    displayEPD.setCursor(2,50);
    displayEPD.setTextColor(EPD_BLACK);


    displayEPD.printf("%.1f", float(this->temperature_sensor_->state));
    
    displayEPD.setFont(&AvenirNextLTPro_Regular14pt7b);
    displayEPD.setTextSize(1);
    displayEPD.setCursor(displayEPD.getCursorX(), displayEPD.getCursorY()-34);
    displayEPD.print("o");
    displayEPD.setFont(&AvenirNextLTPro_Regular16pt7b);
    displayEPD.setCursor(displayEPD.getCursorX(), displayEPD.getCursorY()+10);
    displayEPD.print("C");


    displayEPD.setFont(&AvenirNextLTPro_Regular32pt7b);
    displayEPD.setTextSize(1);
    displayEPD.setCursor(2,110);
    displayEPD.printf("%.1f", float(this->humidity_sensor_->state));
    displayEPD.setCursor(displayEPD.getCursorX(), displayEPD.getCursorY()-24);
    displayEPD.setFont(&AvenirNextLTPro_Regular16pt7b);
    displayEPD.print("%RH");
    
    displayEPD.setCursor(2,150);
    displayEPD.setFont(&AvenirNextLTPro_Regular16pt7b);
    displayEPD.printf("%.0f hPa", float(this->pressure_sensor_->state));

    displayEPD.setFont();
    displayEPD.setTextSize(2);
    displayEPD.setCursor(6,163);
    displayEPD.printf("%s", ha_status_binary_sensor_->state ? "HA Connected" : "Local Only");
    
    if (this->ha_status_binary_sensor_->state && this->esptime_ != NULL) {

      displayEPD.setTextSize(1);
      displayEPD.setCursor(6,185);
      displayEPD.printf("Last Updated: %02i/%02i/%02i %02i:%02i", esptime_.day_of_month, esptime_.month, esptime_.year, esptime_.hour, esptime_.minute);

    }

    if (screenUpdate){ 
      displayEPD.display(false);
    }
  
    screenUpdate = false;
    counter++;
  };



}  // namespace ada_edp
}  // namespace esphome
