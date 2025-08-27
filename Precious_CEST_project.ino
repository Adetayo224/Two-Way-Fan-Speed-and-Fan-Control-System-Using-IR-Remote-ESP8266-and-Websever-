#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// WiFi credentials
const char* ssid = "Samfred";
const char* password = "samfred224";

// IR setup
const uint16_t RECV_PIN = D6;
IRrecv irrecv(RECV_PIN);
decode_results results;

// Relay pins
const int relay1 = D5;  // Low speed
const int relay2 = D7;  // Medium speed
const int relay3 = D8;  // High speed

// IR button values
#define BTN_LOW     0xFFA25D
#define BTN_MEDIUM  0xFF629D
#define BTN_HIGH    0xFFE21D
#define BTN_OFF     0xFF22DD

// Web server
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start IR receiver

  // Relay pins as output
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);

  // All relays OFF at start
  turnOffAll();

  // WiFi setup
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.println(WiFi.localIP());

  // Web server routes
  server.on("/", []() {
    server.send(200, "text/html", getPage("Welcome! Fan Control Ready"));
  });
  server.on("/low", []() { activateRelay(relay1); server.send(200, "text/html", getPage("Low Fan Speed ON")); });
  server.on("/medium", []() { activateRelay(relay2); server.send(200, "text/html", getPage("Medium Fan Speed ON")); });
  server.on("/high", []() { activateRelay(relay3); server.send(200, "text/html", getPage("High Fan Speed ON")); });
  server.on("/off", []() { turnOffAll(); server.send(200, "text/html", getPage("All Fan Speeds OFF")); });

  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient();

  if (irrecv.decode(&results)) {
    Serial.println(resultToHexidecimal(&results));

    switch (results.value) {
      case BTN_LOW: activateRelay(relay1); break;
      case BTN_MEDIUM: activateRelay(relay2); break;
      case BTN_HIGH: activateRelay(relay3); break;
      case BTN_OFF: turnOffAll(); break;
    }
    irrecv.resume();  // Receive the next value
  }
}

void activateRelay(int relayPin) {
  // Turn off all first
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);

  // Turn on selected relay
  digitalWrite(relayPin, HIGH);
}

void turnOffAll() {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
}

String getPage(String message) {
  String page = "<html><body><h1>Fan Control</h1>";
  page += "<p>Status: " + message + "</p>";
  page += "<a href=\"/low\"><button>Low Speed</button></a>";
  page += "<a href=\"/medium\"><button>Medium Speed</button></a>";
  page += "<a href=\"/high\"><button>High Speed</button></a>";
  page += "<a href=\"/off\"><button>OFF</button></a>";
  page += "</body></html>";
