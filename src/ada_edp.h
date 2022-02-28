#pragma once

#include "Adafruit_ThinkInk.h"

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"



namespace esphome {
namespace ada_edp {

class ADAEDPComponent : public PollingComponent{

 public:
  ADAEDPComponent() : PollingComponent(120000){ }
  
  void setup() override;
  void update() override;
  void dump_config() override;


  //void set_string(char* str);
  float get_setup_priority() const override { return setup_priority::LATE; }
 



};

}  // namespace ada_edp
}  // namespace esphome
