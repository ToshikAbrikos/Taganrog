#include <WiFi.h> // библиотека для WiFi сервера
#include <WebServer.h>
#include <Wire.h>
// #include <AsyncTCP.h>  // Добавьте библиотеку AsyncTCP
// #include <ESPAsyncWebServer.h>
#include <LiquidCrystal.h> // библиотека с дисплеем

// Задаём выходы пинов для матрицы из фоторезисторовы
const int PIN_A1_PHOTO_SENSOR = 2;
const int PIN_A2_PHOTO_SENSOR = 4;
const int PIN_A3_PHOTO_SENSOR = 15;
const int PIN_B1_PHOTO_SENSOR = 32;
const int PIN_B2_PHOTO_SENSOR = 33;
const int PIN_B3_PHOTO_SENSOR = 34;
const int PIN_C1_PHOTO_SENSOR = 35;
const int PIN_C2_PHOTO_SENSOR = 36;
const int PIN_C3_PHOTO_SENSOR = 39;

// Настройки Wi-Fi
const char* ssid = "Seven";
const char* password = "monblan07";

const int serverPort = 80;
WebServer server(serverPort);

// Static IP configuration
IPAddress staticIP(192, 168, 1, 184); // Set your desired static IP address
IPAddress gateway(192, 168, 1, 1);   // Set your router's IP address
IPAddress subnet(255, 255, 255, 0);  // Set your subnet mask

// Инициализируем переменные для предыдущих значений, снятых с фоторезисторов матрицы
int val_A1_old = 0;
int val_A2_old = 0;
int val_A3_old = 0;
int val_B1_old = 0;
int val_B2_old = 0;
int val_B3_old = 0;
int val_C1_old = 0;
int val_C2_old = 0;
int val_C3_old = 0;

// Инициализируем переменные для свежих значений, снятых с фоторезисторов матрицы
int val_A1 = 0;
int val_A2 = 0;
int val_A3 = 0;
int val_B1 = 0;
int val_B2 = 0;
int val_B3 = 0;
int val_C1 = 0;
int val_C2 = 0;
int val_C3 = 0;

// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal My_LCD(13, 12, 14, 27, 26, 25);
 
void setup()
{
  Serial.begin(115200);
  Serial.print(WiFi.localIP());

  WiFi.config(staticIP, gateway, subnet);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Подключение к Wi-Fi...");
  }
  Serial.println("Подключено к Wi-Fi!");

  My_LCD.begin(16, 2);
  My_LCD.clear();

  server.on("/", HTTP_GET, []() {
    String html = "<html><head><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js'></script>";
    html += "<script>";
    html += "function updateData() {";
    html += "$.ajax({";
    html += "url: '/data',";
    html += "method: 'GET',";
    html += "success: function(data) {";
    html += "$('#data-container').html(data);";
    html += "}";
    html += "});";
    html += "}";
    html += "setInterval(updateData, 2000);";
    html += "</script></head><body>";
    html += "<div id='data-container'></div>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/data", HTTP_GET, []() {
    String response = "A1: " + String(val_A1) + "<br>";
    response += "A2: " + String(val_A2) + "<br>";
    response += "A3: " + String(val_A3) + "<br>";
    response += "B1: " + String(val_B1) + "<br>";
    response += "B2: " + String(val_B2) + "<br>";
    response += "B3: " + String(val_B3) + "<br>";
    response += "C1: " + String(val_C1) + "<br>";
    response += "C2: " + String(val_C2) + "<br>";
    response += "C3: " + String(val_C3) + "<br>";

    server.send(200, "text/html", response);
  });

  server.begin();
  Serial.println("Сервер начал работу");

}
 
void loop()
{
  My_LCD.clear();

  val_A1 = analogRead(PIN_A1_PHOTO_SENSOR);
  val_A2 = analogRead(PIN_A2_PHOTO_SENSOR);
  val_A3 = analogRead(PIN_A3_PHOTO_SENSOR);
  val_B1 = analogRead(PIN_B1_PHOTO_SENSOR);
  val_B2 = analogRead(PIN_B2_PHOTO_SENSOR);
  val_B3 = analogRead(PIN_B3_PHOTO_SENSOR);
  val_C1 = analogRead(PIN_C1_PHOTO_SENSOR);
  val_C2 = analogRead(PIN_C2_PHOTO_SENSOR);
  val_C3 = analogRead(PIN_C3_PHOTO_SENSOR);

  if ((abs(val_B2 - val_B2_old) < 100) && (val_B2 > 400)) {
    char good[] = "good!!!";
    Serial.println(good);
    My_LCD.clear();
    My_LCD.print(good);
  }
  else if ((abs(val_A1 - val_A1_old) < 100) && (val_A1 > 400)) {
    char text[] = "A1";
    Serial.println(text);
    My_LCD.clear();
    My_LCD.print(text);
  }
  else if (((abs(val_A2 - val_A2_old) < 100) && (val_A2 > 400))) {
    char text[] = "A2";
    Serial.println(text);
    My_LCD.clear();
    My_LCD.print(text);
  }
  else if (((abs(val_A3 - val_A3_old) < 100) && (val_A3 > 400))) {
    char text[] = "A3";
    Serial.println(text);
    My_LCD.clear();
    My_LCD.print(text);
  }
  else if (((abs(val_B1 - val_B1_old) < 100) && (val_B1 > 400))) {
    char text[] = "B1";
    Serial.println(text);
    My_LCD.clear();
    My_LCD.print(text);
  }
  else if (((abs(val_B3 - val_B3_old) < 100) && (val_B3 > 400))) {
    char text[] = "B3";
    Serial.println(text);
    My_LCD.clear();
    My_LCD.print(text);
  }
  else if (((abs(val_C1 - val_C1_old) < 100) && (val_C1 > 400))) {
    char text[] = "C1";
    Serial.println(text);
    My_LCD.clear();
    My_LCD.print(text);
  }
  else if (((abs(val_C2 - val_C2_old) < 100) && (val_C2 > 400))) {
    char text[] = "C2";
    Serial.println(text);
    My_LCD.clear();
    My_LCD.print(text);
  }
  else if (((abs(val_C3 - val_C3_old) < 100) && (val_C3 > 400))) {
    char text[] = "C3";
    Serial.println(text);
    My_LCD.clear();
    My_LCD.print(text);
  }

  val_A1_old = val_A1;
  val_A2_old = val_A2;
  val_A3_old = val_A3;
  val_B1_old = val_B1;
  val_B2_old = val_B2;
  val_B3_old = val_B3;
  val_C1_old = val_C1;
  val_C2_old = val_C2;
  val_C3_old = val_C3;

  // Serial.println(val_A1);
  // Serial.println(val_A2);
  // Serial.println(val_A3);
  // Serial.println(val_B1);
  // Serial.println(val_B2);
  // Serial.println(val_B3);
  // Serial.println(val_C1);
  // Serial.println(val_C2);
  // Serial.println(val_C3);
  // Serial.println();

  delay (4500);
}