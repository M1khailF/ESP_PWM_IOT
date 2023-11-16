#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "ESP32_PWM.h"

const char* ssid     = "ESP32_PWM";
const char* password = "listentome";

IPAddress local_ip(192, 168, 2, 1);
IPAddress gateway(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);

AsyncWebServer server(9999);

int getPWM[] = {0, 0, 0, 0, 0};
String result = "";

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Определение обработчиков маршрутов HTTP
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    String html = "<html><body>";

    html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    html += "<link rel=\"icon\" href=\"data:,\">";
    html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
    html += "button { background-color: #4CAF50; border: none; color: white; padding: 16px 20px;text-decoration: none; font-size: 30px;white-space: nowrap;margin: 10px 10px; cursor: pointer;}";
    html += "pos1 {position: relative;top: 0px; left: 60px;}";
    html += "pos2 {position: relative;top: -86px; left: 50px;}";
    html += "input {width: 220px;height: 10px;}";
    html += "h2{font-size: 25px;color:rgb(128, 128, 128);}";
    html += "body {touch-action: none;-ms-content-zooming: none;-ms-user-select: none;-webkit-tap-highlight-color: rgba(0, 0, 0, 0);}";
    html += "</style></head>";

    html += "<h1 style=\"text-align:center\">ESP32-PWM</h1>";

    html += "<h2><p>PWM1: <output id='PWM1'>" + String(getPWM[0]) + "</output></p><input type='range' id=\"rangePWM1\" min='0' max='100' value='" + String(getPWM[0]) + "' step = '1' oninput='updateSliderValuePWM1(this.value);PWM1.value = this.value'>";
    html += "<script>function updateSliderValuePWM1(value){var xhttp=new XMLHttpRequest();xhttp.open(\"GET\",\"/PWM1?value=\"+value,true);xhttp.send();}</script>";

    html += "<p>PWM2: <output id='PWM2'>" + String(getPWM[1]) + "</output></p><input type='range' id=\"rangePWM2\" min='0' max='100' value='" + String(getPWM[1]) + "' step = '1' oninput='updateSliderValuePWM2(this.value);PWM2.value = this.value'>";
    html += "<script>function updateSliderValuePWM2(value){var xhttp=new XMLHttpRequest();xhttp.open(\"GET\",\"/PWM2?value=\"+value,true);xhttp.send();}</script>";

    html += "<p>PWM3: <output id='PWM3'>" + String(getPWM[2]) + "</output></p><input type='range' id=\"rangePWM3\" min='0' max='100' value='" + String(getPWM[2]) + "' step = '1' oninput='updateSliderValuePWM3(this.value);PWM3.value = this.value'>";
    html += "<script>function updateSliderValuePWM3(value){var xhttp=new XMLHttpRequest();xhttp.open(\"GET\",\"/PWM3?value=\"+value,true);xhttp.send();}</script>";


    html += "<p>PWM4: <output id='PWM4'>" + String(getPWM[3]) + "</output></p><input type='range'id=\"rangePWM4\" min='0' max='100' value='" + String(getPWM[3]) + "' step = '1' oninput='updateSliderValuePWM4(this.value);PWM4.value = this.value'>";
    html += "<script>function updateSliderValuePWM4(value){var xhttp=new XMLHttpRequest();xhttp.open(\"GET\",\"/PWM4?value=\"+value,true);xhttp.send();}</script>";


    html += "<p>General value: <output id='PWM5'>" + String(getPWM[4]) + "</output></p><input type='range' min='0' max='100' value='" + String(getPWM[4]) + "' step = '1' oninput='updateSliderValuePWM5(this.value);PWM5.value = this.value;PWM1.value = this.value;PWM2.value = this.value;PWM3.value = this.value;PWM4.value = this.value'></h2>";
    html += "<script>function updateSliderValuePWM5(value){var xhttp=new XMLHttpRequest();xhttp.open(\"GET\",\"/PWM5?value=\"+value,true);xhttp.send(); rangePWM1.value = value; rangePWM2.value = value; rangePWM3.value = value; rangePWM4.value = value}";
    html += "function updateSliders(){var xhttp=new XMLHttpRequest();xhttp.open(\"GET\",\"/\",true);xhttp.send();}</script>";

    html += "</body></html>";

    request->send(200, "text/html", html);
  });

  server.on("/PWM1", HTTP_GET, [](AsyncWebServerRequest * request) {
    String value = request->getParam("value")->value();
    getPWM[0] = value.toFloat();
    request->send(200, "text/plain", "OK");
  });

  server.on("/PWM2", HTTP_GET, [](AsyncWebServerRequest * request) {
    String value = request->getParam("value")->value();
    getPWM[1] = value.toFloat();
    request->send(200, "text/plain", "OK");
  });

  server.on("/PWM3", HTTP_GET, [](AsyncWebServerRequest * request) {
    String value = request->getParam("value")->value();
    getPWM[2] = value.toFloat();
    request->send(200, "text/plain", "OK");
  });

  server.on("/PWM4", HTTP_GET, [](AsyncWebServerRequest * request) {
    String value = request->getParam("value")->value();
    getPWM[3] = value.toFloat();
    request->send(200, "text/plain", "OK");
  });

  server.on("/PWM5", HTTP_GET, [](AsyncWebServerRequest * request) {
    String value = request->getParam("value")->value();
    getPWM[4] = value.toFloat();

    for (int i = 0; i <= 3; i++) {
      getPWM[i] = getPWM[4];
    }
    request->send(200, "text/plain", "OK");
  });

  // Запуск сервера
  server.begin();
}

void loop() {
  //  Serial.print(map(getPWM[0], 0, 100, 1000, 2000));
  //  Serial.print(',');
  //  Serial.print(map(getPWM[1], 0, 100, 1000, 2000));
  //  Serial.print(',');
  //  Serial.print(map(getPWM[2], 0, 100, 1000, 2000));
  //  Serial.print(',');
  //  Serial.print(map(getPWM[3], 0, 100, 1000, 2000));
  //  Serial.print(',');
  //  Serial.println(map(getPWM[4], 0, 100, 1000, 2000));

  String msg = "";

  for (int i = 0; i < sizeof(getPWM) / sizeof(getPWM[0]); i++) {
    if (i != sizeof(getPWM) / sizeof(getPWM[0]) - 1){
      result += String(getPWM[i]) + ":";
    }
    else{
      result += String(getPWM[i]) + "#";
    }
  }

//  char charArray[result.length() + 1];
//  result.toCharArray(charArray, sizeof(charArray));

  for (int i = 0; i < result.length(); i++)
  {
    Serial2.write(result[i]);   // Push each char 1 by 1 on each loop pass
  }
  Serial.println(result);
  result = "";

  delay(10);
}
