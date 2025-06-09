import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
from esphome.const import CONF_ID

DEPENDENCIES = ["spi"]
AUTO_LOAD = ["sensor", "text_sensor"]

sx127x_ns = cg.esphome_ns.namespace("sx127x")
SX127xComponent = sx127x_ns.class_("SX127xComponent", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SX127xComponent),
    cv.Required("cs_pin"): cv.pin,
    cv.Required("reset_pin"): cv.pin,
    cv.Required("dio0_pin"): cv.pin,
    cv.Required("frequency"): cv.frequency,
    cv.Optional("tx_power", default=20): cv.int_range(2, 20),
    cv.Optional("sync_word", default=0x12): cv.hex_uint8_t,
}).extend(cv.COMPONENT_SCHEMA).extend(spi.spi_device_schema())

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)

    cg.add(var.set_cs_pin(config["cs_pin"]))
    cg.add(var.set_reset_pin(config["reset_pin"]))
    cg.add(var.set_dio0_pin(config["dio0_pin"]))
    cg.add(var.set_frequency(config["frequency"]))
    cg.add(var.set_tx_power(config["tx_power"]))
    cg.add(var.set_sync_word(config["sync_word"]))
