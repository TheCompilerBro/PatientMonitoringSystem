#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>
#include <WiFiManager.h>  // WiFiManager by tzapu

// ---- Firebase RTDB URL ----
String basePath = "https://patient-monitoring-syste-dd78b-default-rtdb.firebaseio.com/alerts.json";

// ---- Sensor Pins ----
#define LM35_PIN 39
#define FLEX_PIN 33
#define X_PIN 34
#define Y_PIN 35
#define Z_PIN 32
#define LED_PIN 25

// ---- Thresholds ----
float TEMP_ALERT = 38.5;
int FLEX_ALERT = 170;
int FALL_THR = 350;

// ---- Last Values ----
String lastFlex = "--";
String lastFall = "--";
String lastTemp = "--";
String lastMsg  = "--";
String lastTime = "--";

int lastX = 0, lastY = 0, lastZ = 0;

// ---- Time ----
void initTime() {
  configTime(19800, 0, "pool.ntp.org", "time.nist.gov");
  while (time(nullptr) < 100000) {
    delay(100);
  }
}

String timestamp() {
  time_t now = time(nullptr);
  struct tm* t = localtime(&now);
  char buffer[30];
  sprintf(buffer, "%02d-%02d-%04d %02d:%02d:%02d",
          t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
          t->tm_hour, t->tm_min, t->tm_sec);
  return String(buffer);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // ------------------- WiFiManager -------------------
  WiFiManager wm;

  if (!wm.autoConnect("ESP32-Setup", "12345678")) {
    Serial.println("❌ WiFi Failed. Rebooting...");
    delay(2000);
    ESP.restart();
  }

  Serial.println("✅ WiFi Connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  initTime();
}

void loop() {

  // ---------------- TEMP ----------------
  float raw = analogRead(LM35_PIN);
  float voltage = raw * (3.3 / 4095.0);
  float tempC = (voltage / 1.8) * 100.0;
  String tempStatus = (tempC > TEMP_ALERT) ? "HIGH" : "NORMAL";

  // ---------------- FLEX ----------------
  int flex = analogRead(FLEX_PIN);
  String flexStatus = (flex > FLEX_ALERT) ? "YES" : "NO";

  // ---------------- ADXL ----------------
  int x = analogRead(X_PIN);
  int y = analogRead(Y_PIN);
  int z = analogRead(Z_PIN);

  int dx = abs(x - lastX);
  int dy = abs(y - lastY);
  int dz = abs(z - lastZ);

  lastX = x;
  lastY = y;
  lastZ = z;

  String fallStatus = (dx > FALL_THR || dy > FALL_THR || dz > FALL_THR) ? "YES" : "NO";

  // ---------------- LED ----------------
  if (flexStatus == "YES" || fallStatus == "YES" || tempStatus == "HIGH") {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  // ---------------- MESSAGE ----------------
  String msg = "none";
  if (tempStatus == "HIGH") msg = "HIGH TEMPERATURE — NEED HELP";
  if (flexStatus == "YES") msg = "GIVE SOME FOOD";
  if (fallStatus == "YES") msg = "FALL DETECTED — NEED HELP";

  // ---------------- TIME ----------------
  String timeNow = timestamp();

  // ---------------- SEND ONLY WHEN CHANGED ----------------
  if (flexStatus != lastFlex ||
      fallStatus != lastFall ||
      tempStatus != lastTemp ||
      msg != lastMsg ||
      timeNow != lastTime)
  {
    lastFlex = flexStatus;
    lastFall = fallStatus;
    lastTemp = tempStatus;
    lastMsg  = msg;
    lastTime = timeNow;

    // ---- JSON ----
    String json = "{\"flex\":\"" + flexStatus +
                  "\",\"fall\":\"" + fallStatus +
                  "\",\"temperature\":\"" + tempStatus +
                  "\",\"time\":\"" + timeNow +
                  "\",\"message\":\"" + msg + "\"}";

    HTTPClient http;
    http.begin(basePath);
    http.addHeader("Content-Type", "application/json");

    int code = http.PUT(json);

    Serial.printf("\nSENT (HTTP %d): %s\n", code, json.c_str());

    http.end();
  }

  delay(20);
}
