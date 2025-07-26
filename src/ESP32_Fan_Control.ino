#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

// Define GPIO pins for relays
// Adjust these based on your ESP32 board and relay module connections
const int RELAY_OFF_PIN = 25; // Example: GPIO25 for Fan OFF
const int RELAY_1_PIN = 26;   // Example: GPIO26 for Speed 1
const int RELAY_2_PIN = 27;   // Example: GPIO27 for Speed 2
const int RELAY_3_PIN = 32;   // Example: GPIO32 for Speed 3

int currentFanState = 0; // 0:OFF, 1:Speed1, 2:Speed2, 3:Speed3

// HTML for the web interface
const char* HTML_CONTENT = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Fan Control</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin: 50px; background-color: #f0f0f0; }
        .container { background-color: #fff; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); display: inline-block; }
        h1 { color: #333; }
        .button {
            display: block;
            width: 150px;
            padding: 15px;
            margin: 10px auto;
            font-size: 18px;
            cursor: pointer;
            border: none;
            border-radius: 5px;
            color: white;
            background-color: #007bff;
            transition: background-color 0.3s ease;
        }
        .button.off { background-color: #dc3545; }
        .button.speed { background-color: #28a745; }
        .button:hover { opacity: 0.9; }
        .status { margin-top: 20px; font-size: 1.2em; color: #555; }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 Fan Control</h1>
        <p class="status">Current Status: <span id="fanStatus">Unknown</span></p>
        <button class="button off" onclick="sendCmd('off')">Fan OFF</button>
        <button class="button speed" onclick="sendCmd('speed1')">Speed 1</button>
        <button class="button speed" onclick="sendCmd('speed2')">Speed 2</button>
        <button class="button speed" onclick="sendCmd('speed3')">Speed 3</button>
    </div>

    <script>
        function sendCmd(cmd) {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/" + cmd, true);
            xhr.send();
            xhr.onload = function() {
                if (xhr.status == 200) {
                    updateStatus(cmd);
                } else {
                    document.getElementById("fanStatus").innerText = "Error sending command!";
                }
            };
        }

        function updateStatus(cmd) {
            let statusText = "OFF";
            switch(cmd) {
                case 'off': statusText = "OFF"; break;
                case 'speed1': statusText = "Speed 1"; break;
                case 'speed2': statusText = "Speed 2"; break;
                case 'speed3': statusText = "Speed 3"; break;
                default: statusText = "Unknown"; break;
            }
            document.getElementById("fanStatus").innerText = statusText;
        }

        function fetchStatus() {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/status", true);
            xhr.onload = function() {
                if (xhr.status == 200) {
                    let state = parseInt(xhr.responseText);
                    let cmd = 'off';
                    switch(state) {
                        case 1: cmd = 'speed1'; break;
                        case 2: cmd = 'speed2'; break;
                        case 3: cmd = 'speed3'; break;
                    }
                    updateStatus(cmd);
                }
            };
            xhr.send();
        }

        // Fetch initial status when the page loads
        window.onload = fetchStatus;
    </script>
</body>
</html>
)rawliteral";

void setFanState(int state) {
  // Turn off all relays first to ensure only one is active
  digitalWrite(RELAY_OFF_PIN, HIGH); // Assuming HIGH means relay OFF (normally open)
  digitalWrite(RELAY_1_PIN, HIGH);
  digitalWrite(RELAY_2_PIN, HIGH);
  digitalWrite(RELAY_3_PIN, HIGH);

  // Activate the desired relay
  switch (state) {
    case 0: // OFF
      digitalWrite(RELAY_OFF_PIN, LOW); // Activate OFF relay
      break;
    case 1: // Speed 1
      digitalWrite(RELAY_1_PIN, LOW);
      break;
    case 2: // Speed 2
      digitalWrite(RELAY_2_PIN, LOW);
      break;
    case 3: // Speed 3
      digitalWrite(RELAY_3_PIN, LOW);
      break;
    default:
      // Should not happen
      break;
  }
  currentFanState = state;
}

void handleRoot() {
  server.send(200, "text/html", HTML_CONTENT);
}

void handleOff() {
  setFanState(0);
  server.send(200, "text/plain", "Fan OFF");
}

void handleSpeed1() {
  setFanState(1);
  server.send(200, "text/plain", "Speed 1 ON");
}

void handleSpeed2() {
  setFanState(2);
  server.send(200, "text/plain", "Speed 2 ON");
}

void handleSpeed3() {
  setFanState(3);
  server.send(200, "text/plain", "Speed 3 ON");
}

void handleStatus() {
  server.send(200, "text/plain", String(currentFanState));
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // Initialize relay pins as outputs
  pinMode(RELAY_OFF_PIN, OUTPUT);
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(RELAY_3_PIN, OUTPUT);

  // Ensure all relays are off initially
  setFanState(0); // Set to OFF state

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up web server routes
  server.on("/", handleRoot);
  server.on("/off", handleOff);
  server.on("/speed1", handleSpeed1);
  server.on("/speed2", handleSpeed2);
  server.on("/speed3", handleSpeed3);
  server.on("/status", handleStatus);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
