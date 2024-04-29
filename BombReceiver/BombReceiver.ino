#include <WiFi.h>

const char index_html[] PROGMEM = R"rawliteral(
HTTP/1.1 200 OK
Content-Type: text/html; charset=UTF-8

<!DOCTYPE html>
<html>
<head>
<script>
setInterval(() => {
  let xhttp = new XMLHttpRequest();
  xhttp.timeout = 2000;
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      let inputChecked, outputStateM;
      //console.log(this);
      let response = JSON.parse(this.responseText);
      let d = new Date();

      document.getElementById("error").textContent = "";
      document.getElementById("data").innerHTML = `Doorbell: ${response.doorbell ? "ON" : "OFF"}
    }
  };
  xhttp.addEventListener('timeout', () => document.getElementById("error").textContent = "Lost connection to server.");
  xhttp.open("GET", "/state", true);
  xhttp.send();
}, 750);
</script>
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
.switch { position: relative;  display: inline-block;  width: 60px;  height: 34px;}
.switch input { opacity: 0;  width: 0;  height: 0;}
.slider {  position: absolute;  cursor: pointer;  top: 0;  left: 0;  right: 0;  bottom: 0;  background-color: #ccc;  -webkit-transition: .4s;  transition: .4s;}
.slider:before {  position: absolute;  content: "";  height: 26px;  width: 26px;  left: 4px;  bottom: 4px;  background-color: white;  -webkit-transition: .4s;  transition: .4s;}
input:checked + .slider { background-color: #2196F3;}
input:focus + .slider {  box-shadow: 0 0 1px #2196F3;}
input:checked + .slider:before { -webkit-transform: translateX(26px);  -ms-transform: translateX(26px);  transform: translateX(26px);}
.slider.round {  border-radius: 34px;}
.slider.round:before {  border-radius: 50%;}
.centerDiv { display:flex;justify-content:center;align-items:center; }
#data { text-align:center; }
#error { text-align: center; color: #D8000C; background-color: #FFD2D2; font-size: 25px; }
</style>
<title>Doorbell Bomb</title>
</head>
<body>
<div class="h-100 p-5 text-white bg-dark"> <h2>Doorbell Bomb</h2></div>
</br>
<p id="error"></p>
<div id="content" class="ms-3">
</br>
<a href="/" class="btn btn-primary mt-2">Refresh</a>
</div>
</br></br>
<p id="data" class="centerDiv fs-4">Doorbell: %doorbellplaceholder%</p>
</br></br>
</br></br>
</body>
</html>
)rawliteral";

// WiFi Router Login - change these to your router settings
const char* ssid = "HWDSB-GUEST";
const char* password = "Education";

String request;

const int doorbellPin = 33;
bool doorbellOn = false;

int timeout = 0;

// Create the ESP Web Server on port 80
WiFiServer WebServer(80);
// Web Client
WiFiClient client;

void setup() {
  Serial.begin(115200);

  //setup pin modes
  pinMode(doorbellPin, OUTPUT);

  // Connect to WiFi network
  Serial.println();
  // WiFi.disconnect();
  WiFi.hostname("Doorbell Receiver");
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");

  // Start the Web Server
  WebServer.begin();
  Serial.println("Web Server started");

  // Print the IP address
  Serial.print("You can connect to the bomb at this URL: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
}

String format() {
  String stringified = String(index_html);

  stringified.replace("%doorbellplaceholder%", doorbellOn ? "ON" : "OFF");
  return stringified;
}

void loop() {
  // Check if a user has connected
  client = WebServer.available();
  if (!client)  //restart loop
    return;

  // Wait until the user sends some data
  Serial.println("New User");
  while (!client.available()) {
    delay(1);
    timeout++;
    if (timeout > 3000) {
      Serial.println("INFINITE LOOP BREAK!");
      break;
    }
  }
  timeout = 0;

  // Read the first line of the request
  request = client.readStringUntil('\n');
  Serial.println(request);
  client.flush();

  // Process the request:

  if (request.indexOf("/state") != -1) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json; charset=UTF-8");
    client.println();
    client.print("{\n");
    client.print("\"doorbell\": ");
    client.print(doorbellOn ? "true" : "false");
    client.print("\n}");
    return;
  } else if (request.indexOf("/on") != -1) {
    doorbellOn = true;
    digitalWrite(doorbellPin, true);
    return;
  } else if (request.indexOf("/off") != -1) {
    doorbellOn = false;
    digitalWrite(doorbellPin, false);
    return;
  }

  // Return the response
  client.println(format());
  Serial.println("------------------------------------");
}
