
#include <ESP32Encoder.h>
#include "esp_task_wdt.h"

// Обработчик прерываний
static IRAM_ATTR void enc_cb(void* arg) {
  ESP32Encoder* enc = (ESP32Encoder*) arg;
  // static bool leds = false;
  // digitalWrite(LED_BUILTIN, (int)leds);
  // leds = !leds;
}

extern bool loopTaskWDTEnabled;
extern TaskHandle_t loopTaskHandle;

ESP32Encoder encoder(true, enc_cb);
//Adafruit_SSD1306 display(128, 32, &Wire);

static const char* LOG_TAG = "main";

void setup(){
  loopTaskWDTEnabled = true;
  //pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  // Encoder A and B pins connected with 1K series resistor to pins 4 and 5, common pin to ground.
  //         |- A   --- 1K --- pin 4
  //  >=[enc]|- GND
  //         |- B   --- 1K --- pin 5
  
  // Enable the weak pull down resistors
	//ESP32Encoder::useInternalWeakPullResistors = puType::down;
	// Enable the weak pull up resistors
  ESP32Encoder::useInternalWeakPullResistors = puType::up;
  encoder.attachSingleEdge(2, 4);
  encoder.clearCount();
  encoder.setFilter(1023);

  // if (! display.begin(SSD1306_SWITCHCAPVCC, 0x3c))
  // {
  //   for (;;) {
  //     Serial.println("display init failed");
  //   }
  // }
  // display.cp437(true);
  // display.clearDisplay();
  // display.setTextSize(2);
  // display.setTextColor(WHITE);
  // display.setCursor(0,0);
  // display.display();
  // esp_log_level_set("*", ESP_LOG_DEBUG);
  // esp_log_level_set("main", ESP_LOG_DEBUG);
  // esp_log_level_set("ESP32Encoder", ESP_LOG_DEBUG);
  esp_task_wdt_add(loopTaskHandle);
}

void loop(){

  // display.clearDisplay();
  // display.setCursor(0,0);
  // display.printf("E: %lld\n", encoder.getCount());
  // display.display();
  Serial.printf("Enc count: %d\n", encoder.getCount());
  delay(500);
  
}
