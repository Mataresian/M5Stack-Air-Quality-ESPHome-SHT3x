#include "esphome.h"
#include "Microfire_SHT3x.h"

class SHT3x : public PollingComponent {
 public:
  Microfire_SHT3x sht3x;
  Sensor *temperature_sensor = new Sensor();
  Sensor *humidity_sensor = new Sensor();
  Sensor *vpd_sensor = new Sensor();
  Sensor *dew_point_sensor = new Sensor();

  // To prevent self-heating, the datasheet warns to do
  // maximum two measurements per second at 12-bit accuracy.
  // Stay on the safe side by polling every five seconds,
  // because the calls to vpd() and dew_point() also measure
  // the temperature.
  SHT20() : PollingComponent(5000) { }

  void setup() override {
    if(!sht3x.begin()) {
      ESP_LOGE("SHT3x", "Sensor is not connected");
    }
  }

  void update() override {
    float temperature = sht3x.temperature();
    temperature_sensor->publish_state(temperature);

    int humidity = sht3x.humidity();
    humidity_sensor->publish_state(humidity);

    int vpd = sht3x.vpd();
    vpd_sensor->publish_state(vpd);

    int dew_point = sht3x.dew_point();
    dew_point_sensor->publish_state(dew_point);

  }
};
