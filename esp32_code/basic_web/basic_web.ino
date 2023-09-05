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
AutoConnectConfig Config("penguin", "penguinpenguin");
////// AutoConect Init ////////


////// AutoConect Config API Page ////////
AutoConnectAux aux("/penguin_api", "Penguin API");
ACText(header, "API Settings");
ACText(caption, "Penguin API Settings Page");
////// AutoConect Config API Page ////////


////// Setting looping for checking API ///////
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();
// TWO minute check
// unsigned long period = 120000;  // two minutes
// unsigned long period = 60000;  // one minutes
unsigned long period = 30000;  // 30 seconds
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
uint32_t LED_HEALTH_COLOR = LED_GREEN;
uint32_t LED_COLOR = LED_BLACK;
////// NeoPixel Defaults ///////////


////// Global Variables ///////////
DynamicJsonDocument docTest(5120);
JsonArray testResponse = docTest.to<JsonArray>();
DynamicJsonDocument doc(5120);
JsonArray apiResponse = doc.to<JsonArray>();
////// Global Variables ///////////


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
        <h2>Penguin API Settings</h2>
        <p>
            Please make sure you have gone to Github and setup you API and know your settings. URL can be found here: <a href="https://github.com/shotah/penguin/tree/main#penguin" target="_blank"> Penguin Readme</a>. Fill in the fields below and submit to
            enable penguin.
        </p>
        </br>
        <div>
            <form action="/">
                <label for="apikeyfield">API KEY: Required</label>
                <input type="text" id="apikeyfield" name="apikey" placeholder="619b9d50..." value="{{APIKEY}}" required>
                <label for="fromuseridfield">From User ID: Required</label>
                <input type="text" id="fromuseridfield" name="fromuserid" placeholder="USER1..." value="{{FROMUSERID}}" required>
                <label for="touseridfield">To User ID: Required</label>
                <input type="text" id="touseridfield" name="touserid" placeholder="USER2..." value="{{TOUSERID}}" required>
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
    return fromUserId;
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
    return toUserId;
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
  String connectionURL = String(server_address + getFromUsertId() + "?key=" + getApiKey());
  Serial.printf("Using URL API: %s\n", &connectionURL[0]);
  return connectionURL;
}
String postConnectionUrl() {
  String server_address = "http://mc.bldhosting.com:3000/";
  //// TODO: get button presses
  String connectionURL = String(server_address + getToUsertId() + "?key=" + getApiKey() + "&presses=2");
  Serial.printf("Using URL API: %s\n", &connectionURL[0]);
  return connectionURL;
}
/////// API URL Details /////


////// WRITE API Settings to SPIFFS ////////
String writeApiSettings(PageArgument& args) {
  if (args.hasArg("apikey")) {
    preferences.putString("apikey", args.arg("apikey"));
  }
  if (args.hasArg("fromuserid")) {
    preferences.putString("fromuserid", args.arg("fromuserid"));
  }
  if (args.hasArg("touserid")) {
    preferences.putString("touserid", args.arg("touserid"));
  }
  delay(10);
  return "<p>";
}
////// WRITE API Settings to SPIFFS ////////


////// Building page and inserting data //////
PageElement ROOT_ELM(FPSTR(rootHtml), { { "APIKEY", getAPiKeyArgs },
                                        { "FROMUSERID", getFromUsertIdArgs },
                                        { "TOUSERID", getToUsertIdArgs },
                                        { "WRITESETTINGS", writeApiSettings } });
PageBuilder ROOT("/", { ROOT_ELM });
////// Building page and inserting data //////


///// Main call to API to get response data /////
JsonArray GetAPIResponse() {
  // init clients:
  WiFiClient wifi_client;
  HTTPClient http_client;

  // setup client:
  http_client.begin(wifi_client, getResponseUrl().c_str());
  int response_code = http_client.GET();
  Serial.printf("[HTTP] GET... code: %d\n", response_code);
  if (response_code == HTTP_CODE_OK) {
    // StaticJsonDocument<80> filter;
    // JsonObject filter_ledPattern = filter["ledPattern"].createNestedObject();
    // filter_ledPattern["ledPattern"] = true;
      
    DynamicJsonDocument doc(10240);
    // DeserializationError error = deserializeJson(doc, wifi_client, DeserializationOption::Filter(filter));
    DeserializationError error = deserializeJson(doc, wifi_client);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
    }
    http_client.end();
    // Pretty print JSON response
    // serializeJsonPretty(doc, Serial);
    return doc["ledPattern"];
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http_client.errorToString(response_code).c_str());
  }
  return testResponse;
}
///// Main call to API to get response data /////

uint32_t HEALTH_COLOR() {
  LED_COLOR = (LED_COLOR == LED_HEALTH_COLOR) ? LED_BLACK : LED_HEALTH_COLOR;
  return LED_COLOR;
}

void ShowOnbaordPixel() {
  onboard_pixel.clear();
  onboard_pixel.setPixelColor(0, HEALTH_COLOR());
  onboard_pixel.setBrightness(LED_BRIGHTNESS);
  onboard_pixel.show();
}

void ShowLEDPixels() {
  pixels.clear();
  int32_t currentPixel = 0;
  // serializeJsonPretty(apiResponse, Serial);
  for(int row=0; row <= 7; row++) {
    Serial.printf("\nCurrent Row: %s\n", String(row));
    serializeJson(apiResponse[row], Serial);
    for(int led=0; led <= 7; led++) {
      Serial.printf("\nCurrent LED: %s\n", String(row));
      serializeJson(apiResponse[row][led], Serial);
      // pixels.setPixelColor(currentPixel, pixels.Color(apiResponse[row][led]));
      // Serial.printf("Setting Pixel: %s\n", String(currentPixel));
      // Serial.printf("First RGB: %s\n", apiResponse[row][led][0]);
      // apiResponse.get(0).get(0);
      // serializeJsonPretty(apiResponse[row][led], Serial);
      pixels.setPixelColor(currentPixel, pixels.Color(
        apiResponse[row][led][0].as<uint8_t>(),
        apiResponse[row][led][1].as<uint8_t>(),
        apiResponse[row][led][2].as<uint8_t>())
      );
      currentPixel++;
    }
  }
  pixels.setPixelColor(64, pixels.Color(127,255,0));
  pixels.setBrightness(LED_BRIGHTNESS);
  pixels.show();
}

void CheckForResponse() {
  apiResponse = GetAPIResponse();
  // serializeJson(apiResponse[0], Serial);
}

void SetDefaultVars() {
  JsonArray testledPattern = testResponse.createNestedArray();
  for(int row=0; row <= 7; row++) {
    JsonArray rowTest = testledPattern.createNestedArray();
    for(int led=0; led <= 7; led++) {
      JsonArray ledTest = rowTest.createNestedArray();
      ledTest.add(255);
      ledTest.add(0);
      ledTest.add(0);
    };
  };
  JsonArray ledPattern = apiResponse.createNestedArray();
  for(int row=0; row <= 7; row++) {
    JsonArray rowPattern = ledPattern.createNestedArray();
    for(int led=0; led <= 7; led++) {
      JsonArray ledPattern = rowPattern.createNestedArray();
      ledPattern.add(255);
      ledPattern.add(0);
      ledPattern.add(0);
    };
  };

}

////// Use to clear wifi creds //////
void deleteAllCredentials() {
  AutoConnectCredential credential;
  station_config_t config;
  uint8_t ent = credential.entries();

  while (ent--) {
    int8_t zero = 0;
    credential.load(zero, &config);
    credential.del((const char*)&config.ssid[0]);
  }
}
////// Use to clear wifi creds //////

//// MAIN LOOP: ////
int counter = 0;
void loop() {
  portal.handleClient();
  currentMillis = millis();

  // API call over defined period.
  if (currentMillis - previousMillis >= period) {
    CheckForResponse();
    ShowOnbaordPixel();
    ShowLEDPixels();
    previousMillis = currentMillis;
  }
}
//// MAIN LOOP: ////


//// MAIN SETUP: ////
void setup() {
  // DEBUG: used to clear credentials:
  // deleteAllCredentials();
  Serial.begin(115200);
  Serial.println();
  SetDefaultVars();
  preferences.begin("apiSettings", false);

  ROOT.insert(Server);
  Config.title = "Penguin";
  portal.config(Config);
  if (portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }

  // Init ONBOARD_LED Strip of Pixels
  onboard_pixel.begin();
  onboard_pixel.show();
  ShowOnbaordPixel();
  // Init LED Strip of Pixels
  pixels.begin();
  pixels.show();
  // do an initial call and show the output:
  CheckForResponse();
  ShowLEDPixels();
}
//// MAIN SETUP: ////
