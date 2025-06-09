#include "sx127x.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sx127x {

static const char *TAG = "sx127x";

void SX127xComponent::setup() {
    ESP_LOGI(TAG, "Inicializando SX127x...");
    
    // Inicializar SPI
    this->spi_setup();

    // Configurar pines
    pinMode(this->cs_pin_, OUTPUT);
    pinMode(this->reset_pin_, OUTPUT);
    pinMode(this->dio0_pin_, INPUT);

    // Reset del módulo LoRa
    digitalWrite(this->reset_pin_, LOW);
    delay(10);
    digitalWrite(this->reset_pin_, HIGH);
    delay(10);

    // Inicializar LoRa
    if (!LoRa.begin(this->frequency_)) {
        ESP_LOGE(TAG, "Error al iniciar LoRa");
        this->mark_failed();
        return;
    }

    LoRa.setTxPower(this->tx_power_);
    LoRa.setSyncWord(this->sync_word_);
    
    ESP_LOGI(TAG, "SX127x inicializado correctamente");
}

void SX127xComponent::loop() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        ESP_LOGI(TAG, "Paquete recibido");
        String receivedData = "";
        while (LoRa.available()) {
            receivedData += (char)LoRa.read();
        }
        ESP_LOGI(TAG, "Datos recibidos: %s", receivedData.c_str());

        // Publicar el mensaje recibido en ESPHome
        this->publish_state(receivedData.c_str());
    }
}

void SX127xComponent::send_lora_packet(const std::string &message) {
    ESP_LOGI(TAG, "Enviando paquete LoRa: %s", message.c_str());
    LoRa.beginPacket();
    LoRa.print(message.c_str());
    LoRa.endPacket();
}

}  // namespace sx127x
}  // namespace esphome
