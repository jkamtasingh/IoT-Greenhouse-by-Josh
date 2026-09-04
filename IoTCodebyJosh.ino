#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <time.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

const char* ssid = "YOUR WIFI SSID";
const char* password = "YOUR WIFI PASSWORD";

#define API_KEY "YOUR API KEY"
#define DATABASE_URL "YOUR DATABASE URL"

FirebaseData fbdo;
FirebaseData fbdoSchedule;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
unsigned long checkCommandPrevMillis = 0;
unsigned long checkSchedulePrevMillis = 0;
bool signupOK = false;


const int soilPin = 34;   
const int relayPin = 13;  

int moisture;
int thres = 3200; 

String lastTriggeredTime = "";

unsigned long logHistoryPrevMillis = 0;
const unsigned long historyInterval = 5UL * 60UL * 1000UL;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  pinMode(soilPin, INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected: " + WiFi.localIP().toString());

   configTime(-5 * 3600, 3600, "pool.ntp.org", "time.nist.gov");
  Serial.println("Syncing time...");
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Time synced!");
  Serial.println(&timeinfo, "Current time: %A, %B %d %Y %H:%M:%S");

 
   
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase sign-up OK");
    signupOK = true;
  } else {
    Serial.printf("Firebase sign-up failed: %s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}
  void dispense() {
    Serial.println("Dispensing Water");
    digitalWrite(relayPin, LOW);
    delay(3000);
    digitalWrite(relayPin, HIGH);
  }

  void checkSchedule() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return;

    char currentTime[6];
    strftime(currentTime, sizeof(currentTime), "%H:%M", &timeinfo);
  String nowStr = String(currentTime);

  Serial.println("Current time check: " + nowStr);

  if (Firebase.RTDB.getJSON(&fbdoSchedule, "/greenhouse/schedule")) {
    FirebaseJson *json = fbdoSchedule.jsonObjectPtr();
    size_t count = json->iteratorBegin();
    String key, value;
    int type;

    for (size_t i = 0; i < count; i++) {
      json->iteratorGet(i, type, key, value);
     
      FirebaseJson entry;
      entry.setJsonData(value);
      FirebaseJsonData result;
      entry.get(result, "time");
      String schedTime = result.stringValue;

      if (schedTime == nowStr && lastTriggeredTime != nowStr) {
        dispense();
        lastTriggeredTime = nowStr;
      }
    }
    json->iteratorEnd();
  }
  }

  void logMoistureHistory() {
    time_t now;
    time(&now);
    String path = "/greenhouse/history/" + String ((unsigned long) now);
    Firebase.RTDB.setInt(&fbdo, path.c_str(), moisture);
  }

void loop() {
  moisture = analogRead(soilPin);
  Serial.println(moisture);
  if (moisture > thres) 
  {
    digitalWrite(relayPin, LOW); 
  }
  else 
  {
    digitalWrite(relayPin, HIGH); 
  }

    
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 2000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    if (Firebase.RTDB.setInt(&fbdo, "/greenhouse/moisture", moisture)) {
      Serial.println("Moisture sent: " + String(moisture));
    } else {
      Serial.println("Failed: " + fbdo.errorReason());
    }

    bool pumpOn = (moisture > thres);
    Firebase.RTDB.setBool(&fbdo, "/greenhouse/pumpStatus", pumpOn);
  }

  
  if (Firebase.ready() && signupOK && (millis() - checkCommandPrevMillis > 1000)) {
    checkCommandPrevMillis = millis();

    if (Firebase.RTDB.getBool(&fbdo, "/greenhouse/manualDispense")) {
      if (fbdo.boolData()) {
        Serial.println("Manual dispense triggered!");
        digitalWrite(relayPin, LOW);
        delay(3000); 
        digitalWrite(relayPin, HIGH);

       
        Firebase.RTDB.setBool(&fbdo, "/greenhouse/manualDispense", false);
      }
    }
  }

   if (Firebase.ready() && signupOK && (millis() - checkSchedulePrevMillis > 20000)) {
    checkSchedulePrevMillis = millis();
    checkSchedule();
  }

  if (Firebase.ready() && signupOK && (millis() - logHistoryPrevMillis > historyInterval || logHistoryPrevMillis == 0)) { 
    logHistoryPrevMillis = millis();
    logMoistureHistory();
  }

  delay(400);
}