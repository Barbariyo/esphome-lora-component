#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"
#include <LoRa.h>

namespace esphome {
namespace sx127x {

class SX127xComponent : public Component, public spi::SPIDevice {
 public:
  void setup() override;
  void loop() override;

  void set_cs_pin(GPIOPin *cs_pin) { this->cs_pin_ = cs_pin; }
  void set_reset_pin(GPIOPin *reset_pin) { this->reset_pin_ = reset_pin; }
  void set_dio0_pin(GPIOPin *dio0_pin) { this->dio0_pin_ = dio0_pin; }
  void set_frequency(float frequency) { this->frequency_ = frequency; }
  void set_tx_power(uint8_t tx_power) { this->tx_power_ = tx_power; }
  void set_sync_word(uint8_t sync_word) { this->sync_word_ = sync_word; }

  void send_lora_packet(const std::string &message);

 protected:
  GPIOPin *cs_pin_;
  GPIOPin *reset_pin_;
  GPIOPin *dio0_pin_;
  float frequency_;
  uint8_t tx_power_;
  uint8_t sync_word_;
};

}  // namespace sx127x
}  // namespace esphome
