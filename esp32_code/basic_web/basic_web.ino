#include <Preferences.h>
#include <StreamUtils.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebServer.h>
#include <PageBuilder.h>
#include <AutoConnect.h>
#include <Adafruit_NeoPixel.h>


/////// Preferences Settings ///////
Preferences preferences;
/////// Preferences Settings ///////


/////// AVR Power Control module /////////
#ifdef __AVR__
#include <avr/power.h>
#endif
/////// AVR Power Control module /////////


////// AutoConect Init ////////
WebServer Server;
AutoConnect portal(Server);
AutoConnectConfig Config("penguin", "penguin!@#");
////// AutoConect Init ////////


////// AutoConect Config API Page ////////
AutoConnectAux aux("/penguin_api", "penguin API");
ACText(header, "API settings");
ACText(caption, "Please go to Weather Unlocked and setup your API account and Ski Resort settings. URL: https://developer.weatherunlocked.com/skiresort");
////// AutoConect Config API Page ////////


////// Setting looping for checking API ///////
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();
unsigned long period = 120000;  // two minutes
////// Setting looping for checking API ///////


////// Declaring NeoPixel variables. ///////////
// PIN out to control the LEDs
// ESP32-s2:
// #define ONBOARD_LED_PIN 18
// ESP32-s3:
#define ONBOARD_LED_PIN 38
#define ONBOARD_LED_COUNT 1
Adafruit_NeoPixel onboard_pixel(ONBOARD_LED_COUNT, ONBOARD_LED_PIN, NEO_GRB + NEO_KHZ800);
// PIN out to control the LEDs
#define LED_PIN 17
// How many LEDs we have connected
#define LED_COUNT 74
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
////// Declaring NeoPixel variables. ///////////


////// NeoPixel Colors ///////////
const uint32_t LED_RED = pixels.Color(255, 0, 0);
const uint32_t LED_GREEN = pixels.Color(0, 255, 0);
const uint32_t LED_BLUE = pixels.Color(0, 0, 255);
const uint32_t LED_PURPLE = pixels.Color(153, 0, 153);
const uint32_t LED_WHITE = pixels.Color(255, 255, 255);
const uint32_t LED_BROWN = pixels.Color(139, 69, 19);
const uint32_t LED_YELLOW = pixels.Color(255, 255, 0);
const uint32_t LED_GRAY = pixels.Color(143, 188, 143);
const uint32_t LED_BLACK = pixels.Color(0, 0, 0);
////// NeoPixel Colors ///////////


////// NeoPixel Defaults ///////////
uint32_t LED_BRIGHTNESS = 50;         // 1-100
uint32_t LED_BRIGHTNESS_OFF = 0;      // 1-100
uint32_t LED_HEALTH_BRIGHTNESS = 50;  // 1-100
uint32_t LED_HEALTH_COLOR = LED_BLUE;
uint32_t LED_GROUND_COLOR = LED_GREEN;
uint32_t LED_COLOR = LED_BLACK;
////// NeoPixel Defaults ///////////


////// Defining Snow, Visibility, and Rain  //////////
uint16_t inches_of_snow = 0;
uint16_t inches_of_rain = 0;
uint16_t miles_of_visibility = 0;
////// Defining Snow, Visibility, and Rain  //////////


////// Root webpage to enable people to change API data  //////////
static const char rootHtml[] PROGMEM = R"(
    <!DOCTYPE html>
    <html>
    <head>
        <meta charset="UTF=8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
    </head>
    <style type="text/css">
      input[type=text],
      select {
          width: 100%;
          padding: 12px 20px;
          margin: 8px 0;
          display: inline-block;
          border: 1px solid #ccc;
          border-radius: 4px;
          box-sizing: border-box;
      }
      input[type=submit] {
          width: 100%;
          background-color: #4CAF50;
          color: white;
          padding: 14px 20px;
          margin: 8px 0;
          border: none;
          border-radius: 4px;
          cursor: pointer;
      }
      input[type=submit]:hover {
          background-color: #45a049;
      }
      input:required {
          border-color: #800000;
          border-width: 3px;
      }
      input:required:invalid {
          border-color: #c00000;
      }
      div {
          border-radius: 5px;
          background-color: #f2f2f2;
          padding: 20px;
      }
    </style>
    <body>
        <h2>penguin API Settings</h2>
        <p>
            Please make sure you have gone to Github and setup you API and know your settings. URL can be found here: <a href="https://github.com/shotah/penguin/tree/main#penguin" target="_blank"> Penguin Readme</a>. Fill in the fields below and submit to
            enable penguin.
        </p>
        </br>
        <div>
            <form action="/">
                <label for="apikey">API KEY: Required</label>
                <input type="text" id="apikey" name="apikey" placeholder="619b9d50..." value="{{APIKEY}}" required>
                <label for="fromuserid">From User ID: Required</label>
                <input type="text" id="fromuserid" name="fromuserid" placeholder="USER1..." value="{{FROMUSERID}}" required>
                <label for="touserid">To User ID: Required</label>
                <input type="text" id="touserid" name="touserid" placeholder="USER2..." value="{{TOUSERID}}" required>
                <input type="submit" class="button" value="Submit">
                {{WRITESETTINGS}}
        </div>
    </body>
    </html>
)";
////// Root webpage to enable people to change API data  //////////


///// GET api Settings //////
String getApiKey() {
  try {
    String apiKey = preferences.getString("apikey", "");
    Serial.printf("getApiKey: %s\n", &apiKey[0]);
    return apiKey;
  } catch (const std::exception& e) {
    Serial.printf("getApiKey error: %s\n", e.what());
    return "<p>";
  }
}
String getAPiKeyArgs(PageArgument& args) {
  return getApiKey();
}
String getFromUsertId() {
  try {
    String fromUserId = preferences.getString("fromuserid", "");
    Serial.printf("getFromUsertId: %s\n", &fromUserId[0]);
    return resortId;
  } catch (const std::exception& e) {
    Serial.printf("getFromUsertId error: %s\n", e.what());
    return "<p>";
  }
}
String getFromUsertIdArgs(PageArgument& args) {
  return getFromUsertId();
}
String getToUsertId() {
  try {
    String toUserId = preferences.getString("touserid", "");
    Serial.printf("getToUsertId: %s\n", &toUserId[0]);
    return resortId;
  } catch (const std::exception& e) {
    Serial.printf("getToUsertId error: %s\n", e.what());
    return "<p>";
  }
}
String getToUsertIdArgs(PageArgument& args) {
  return getToUsertId();
}
///// GET api Settings //////


/////// API URL Details /////
String getResponseUrl() {
  String server_address = "http://mc.bldhosting.com:3000/";
  String connectionURL = String(server_address + getFromUsertId() "&key=" + getApiKey());
  Serial.printf("Using URL API: %s\n", &connectionURL[0]);
  return connectionURL;
}
String postConnectionUrl() {
  String server_address = "http://mc.bldhosting.com:3000/";
  //// TODO: get button presses
  String connectionURL = String(server_address + getToUsertId() + "&key=" + getApiKey()) + "&presses=2");
  Serial.printf("Using URL API: %s\n", &connectionURL[0]);
  return connectionURL;
}
/////// API URL Details /////


////// WRITE API Settings to SPIFFS ////////
String writeApiSettings(PageArgument& args) {
  if (args.hasArg("apikey")) {
    preferences.putString("apikey", args.arg("apikey"));
  }
  if (args.hasArg("fromUserid")) {
    preferences.putString("fromUserid", args.arg("fromUserid"));
  }
  if (args.hasArg("toUserid")) {
    preferences.putString("toUserid", args.arg("toUserid"));
  }
  delay(10);
  return "<p>";
}
////// WRITE API Settings to SPIFFS ////////


////// Building page and inserting data //////
PageElement ROOT_ELM(FPSTR(rootHtml), { { "APPKEY", getAPiKeyArgs },
                                        { "FROMUSERID", getFromUsertIdArgs },
                                        { "TOUSERID", getToUsertIdArgs },
                                        { "WRITESETTINGS", writeApiSettings } });
PageBuilder ROOT("/", { ROOT_ELM });
////// Building page and inserting data //////


///// Main call to API to get weather data /////
JsonObject GetAPIResponse() {
  // init clients:
  WiFiClient wifi_client;
  HTTPClient http_client;

  // setup client:
  http_client.begin(wifi_client, getResponseUrl().c_str());
  int response_code = http_client.GET();
  Serial.printf("[HTTP] GET... code: %d\n", response_code);
  if (response_code == HTTP_CODE_OK) {
    StaticJsonDocument<80> filter;
    JsonObject filter_forecast_0 = filter["forecast"].createNestedObject();
    filter_forecast_0["vis_mi"] = true;
    filter_forecast_0["snow_in"] = true;
    filter_forecast_0["rain_in"] = true;

    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, wifi_client, DeserializationOption::Filter(filter));
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
    }
    http_client.end();
    return doc["forecast"][0];
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http_client.errorToString(response_code).c_str());
  }

  JsonObject blank_forcast = {};
  blank_forcast["vis_mi"] = 0;
  blank_forcast["snow_in"] = 0;
  blank_forcast["rain_in"] = 0;
  return blank_forcast;
}
///// Main call to API to get weather data /////


///// calls get forcast and sets the values  /////
void SetForecastValues() {
  JsonObject forecast = GetAPIResponse();
  Serial.println(forecast);
  if (forecast["vis_mi"] > 0) { miles_of_visibility = ((int)forecast["vis_mi"]) + 1; }
  if (forecast["snow_in"] > 0) { inches_of_snow = (((int)forecast["snow_in"]) + 1) / 2; }
  if (forecast["rain_in"] > 0) { inches_of_rain = ((int)forecast["rain_in"]) + 1; }
}
///// calls get forcast and sets the values  /////


uint32_t SKY_COLOR() {
  if (inches_of_rain > 1) {
    return LED_PURPLE;
  }
  return LED_BLUE;
}

uint32_t SUN_COLOR() {
  if (miles_of_visibility <= 2) {
    return LED_PURPLE;
  } else if (miles_of_visibility <= 5) {
    return LED_GRAY;
  }
  return LED_YELLOW;
}

uint32_t GROUND_COLOR() {
  LED_GROUND_COLOR = (LED_GROUND_COLOR == LED_GREEN) ? LED_BLUE : LED_GREEN;
  return LED_GROUND_COLOR;
}

uint32_t HEALTH_COLOR() {
  LED_COLOR = (LED_COLOR == LED_HEALTH_COLOR) ? LED_BLACK : LED_HEALTH_COLOR;
  return LED_COLOR;
}

void ShowOnbaordPixel() {
  onboard_pixel.clear();
  onboard_pixel.setPixelColor(0, HEALTH_COLOR());
  onboard_pixel.setBrightness(LED_HEALTH_BRIGHTNESS);
  onboard_pixel.show();
}

void ShowLEDPixels() {
  pixels.clear();
  pixels.setPixelColor(0, GROUND_COLOR());
  for (uint16_t LED = 1; LED < LED_COUNT - 1; LED++) {
    if (LED <= inches_of_snow) {
      pixels.setPixelColor(LED, LED_WHITE);
    } else {
      pixels.setPixelColor(LED, SKY_COLOR());
    }
  }
  // Setting the sun weather:
  pixels.setPixelColor(LED_COUNT - 1, SUN_COLOR());
  pixels.setBrightness(LED_BRIGHTNESS);
  pixels.show();
}

//// MAIN LOOP: ////
int counter = 0;
void loop() {
  portal.handleClient();
  currentMillis = millis();

  if (currentMillis - previousMillis >= period) {
    SetForecastValues();
    previousMillis = currentMillis;
  }

  ShowOnbaordPixel();
  ShowLEDPixels();
  delay(1000);
}
//// MAIN LOOP: ////


//// MAIN SETUP: ////
void setup() {
  delay(1000);  // for stable the module.
  Serial.begin(115200);
  Serial.println();
  preferences.begin("apiSettings", false);

  ROOT.insert(Server);
  Config.title = "penguin";
  portal.config(Config);
  if (portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }

  // Init ONBOARD_LED Strip of Pixels
  onboard_pixel.begin();
  onboard_pixel.show();
  // Init LED Strip of Pixels
  pixels.begin();
  pixels.show();
}
//// MAIN SETUP: ////
