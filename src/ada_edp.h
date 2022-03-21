#pragma once

#include "Adafruit_ThinkInk.h"

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/homeassistant/time/homeassistant_time.h"



namespace esphome {
namespace ada_edp {

class ADAEDPComponent : public PollingComponent, public sensor::Sensor{

 public:
  ADAEDPComponent(sensor::Sensor *temperature, sensor::Sensor *humidity, sensor::Sensor *pressure, binary_sensor::BinarySensor *hastatus) : PollingComponent(180000){ 
    this->temperature_sensor_ = temperature;
    this->humidity_sensor_ = humidity;
    this->pressure_sensor_ = pressure;
    this->ha_status_binary_sensor_ = hastatus;
  }
  
  void setup() override;
  void update() override;
  void dump_config() override;
  void set_time(homeassistant::HomeassistantTime *esptime){this->esptime_ = esptime;}


  //void set_string(char* str);
  float get_setup_priority() const override { return setup_priority::LATE; }
  
 protected:
  sensor::Sensor *temperature_sensor_;
  sensor::Sensor *humidity_sensor_;
  sensor::Sensor *pressure_sensor_;
  binary_sensor::BinarySensor *ha_status_binary_sensor_;
  homeassistant::HomeassistantTime *esptime_;
};

}  // namespace ada_edp
}  // namespace esphome
