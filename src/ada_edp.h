#pragma once

#include "Adafruit_ThinkInk.h"

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include "esphome/components/sensor/sensor.h"



namespace esphome {
namespace ada_edp {

class ADAEDPComponent : public PollingComponent{

 public:
  ADAEDPComponent(sensor::Sensor *temperature, sensor::Sensor *humidity, sensor::Sensor *pressure) : PollingComponent(120000){ 
    this->temperature_sensor_ = temperature;
    this->humidity_sensor_ = humidity;
    this->pressure_sensor_ = pressure;
  }
  
  void setup() override;
  void update() override;
  void dump_config() override;


  //void set_string(char* str);
  float get_setup_priority() const override { return setup_priority::LATE; }
  
 protected:
  sensor::Sensor *temperature_sensor_;
  sensor::Sensor *humidity_sensor_;
  sensor::Sensor *pressure_sensor_;

};

}  // namespace ada_edp
}  // namespace esphome
