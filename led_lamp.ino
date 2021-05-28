#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 
#include <Adafruit_NeoPixel.h>

#define PIN 13
#define NUM_LEDS 32

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

void handleRoot();              // function prototypes for HTTP handlers

String red_color = "0";
String green_color = "0";
String blue_color = "0";

const char hellostr[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta charset="UTF-8">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 1.7rem;}
    p {font-size: 1.1rem;}
    body {margin:0px auto; padding-bottom: 15px;}
    .slider_red { -webkit-appearance: none; width: 75%; margin: 14px; height: 25px; background: #ff4d4d;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider_red::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}
    .slider_red::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; } 

    .slider_green { -webkit-appearance: none;width: 75%;  margin: 14px; height: 25px; background: #4dff4d;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider_green::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}
    .slider_green::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; } 

    .slider_blue { -webkit-appearance: none;width: 75%;  margin: 14px; height: 25px; background: #4d4dff;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider_blue::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}
    .slider_blue::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; } 
  </style>
</head>
<body>

<h2>Light settings</h2>

<p>Domyślnie wszystkie kolory wyłączone, przesuń aby zmieszać kolory.</p>

<p id="slider_red"></p>
<p id="slider_green"></p>
<p id="slider_blue"></p>

<script>
  var queryString = window.location.search;
  var urlParams = new URLSearchParams(queryString);
  if (urlParams.has('red_value')) {
    red_value = urlParams.get('red_value');
  }
  else {
    red_value = '0'
  }
  
  if (urlParams.has('green_value')) {
    green_value = urlParams.get('green_value');
  }
  else {
    green_value = '0'
  }
  
  if (urlParams.has('blue_value')) {
    blue_value = urlParams.get('blue_value');
  }
  else {
    blue_value = '0'
  }
  
  var slider_red = '<input type="range" onchange="updateColors(this)" id="RedSlider" min="0" max="255" value="' + red_value + '" step="1" class="slider_red">'
  var slider_green = '<input type="range" onchange="updateColors(this)" id="GreenSlider" min="0" max="255" value="' + green_value + '" step="1" class="slider_green">'
  var slider_blue = '<input type="range" onchange="updateColors(this)" id="BlueSlider" min="0" max="255" value="' + blue_value + '" step="1" class="slider_blue">'

  document.getElementById("slider_red").innerHTML = slider_red;
  document.getElementById("slider_green").innerHTML = slider_green;
  document.getElementById("slider_blue").innerHTML = slider_blue;

  function updateColors(element) {
    var redValue = document.getElementById("RedSlider").value;
    var greenValue = document.getElementById("GreenSlider").value;
    var blueValue = document.getElementById("BlueSlider").value;
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/?red_value=" + redValue + "&green_value=" + greenValue + "&blue_value=" + blueValue, true);
    xhr.send();
  }
</script>

</body>
</html>

)=====";


void setup() 
{         
      strip.begin();
      strip.show();
      WiFiManager wifiManager;
      Serial.begin(9600);
      //wifiManager.resetSettings();
      wifiManager.autoConnect("AutoConnectAP");
      
      Serial.println("Connected.");

      server.on("/", HTTP_GET, handleRoot);
      //server.on("/", HTTP_POST, handlePostData);
      server.begin();                            // Actually start the server
      Serial.println("HTTP server started");
}
 
void loop() 
{      
    server.handleClient();                     // Listen for HTTP requests from clients
}

void handleRoot() { 
  red_color = server.arg("red_value");
  green_color = server.arg("green_value");
  blue_color = server.arg("blue_value");
  if (red_color == "") {
    red_color = "0";
  }
  if (green_color == "") {
    green_color = "0";
  }
  if (blue_color == "") {
    blue_color = "0";
  }
  Serial.print("GET -> red:" + red_color);
  Serial.print(" green:" + green_color);
  Serial.println(" blue:" + blue_color);
  for (int i = 0; i <= NUM_LEDS; i++) {
      strip.setPixelColor(i, red_color.toInt(), green_color.toInt(), blue_color.toInt());
  }
  strip.show();
  server.send(200, "text/html", hellostr);
}
