#include <WiFi.h>
#include "SSD1306.h"

SSD1306  screen(0x3c, 5, 4);
WiFiServer espServer(80);

String request;
boolean currentLineIsBlank = true;
const int MAX_COLUMNS = 128;
const char* ssid = "X";
const char* password = "X";
unsigned long millisTimer = 0;
boolean blockDevice = false;

void setup()
{
  millisTimer = millis();
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  String myLocalIP = WiFi.localIP().toString();
  Serial.println("CONNECTED");
  Serial.print("IP=");
  Serial.println(myLocalIP);

  espServer.begin();

  screen.init();
  screen.setFont(ArialMT_Plain_16);

  screen.clear();
  screen.drawStringMaxWidth(0, 0, MAX_COLUMNS, "My IP: " + myLocalIP);
  screen.display();
}

void loop()
{
  String message = handleRequest();

  //For some reason, Android Tasker, sends "Calendar syncing"
  //when there is no event, from time to time.
  if (message.length() > 0
      && blockDevice
      && message != "Calendar syncing")
  {
    int await_time = 9;
    int seconds = 59;
    while (await_time >= 0)
    {
      unsigned long difference = (millis() - millisTimer);
      if (difference == 500) {
        screen.clear();
        screen.display();
      }

      if (difference == 1000) {
        screen.clear();
        screen.setFont(ArialMT_Plain_16);
        screen.drawStringMaxWidth(0, 0, MAX_COLUMNS, message + " " + String(await_time) + ":" + String(seconds));
        screen.display();
      }

      if (difference > 1000) {
        millisTimer = millis();

        seconds = seconds - 1;
        if (seconds == 0)
        {
          await_time = await_time - 1;
          seconds = 59;
        }
      }
    }

    screen.clear();
    screen.setFont(ArialMT_Plain_16);
    screen.drawStringMaxWidth(0, 0, MAX_COLUMNS, message);
    screen.display();
  }
  else if  (message.length() > 0
            && !blockDevice
            && message != "Calendar syncing") {
    screen.clear();
    screen.setFont(ArialMT_Plain_16);
    screen.drawStringMaxWidth(0, 0, MAX_COLUMNS, message);
    screen.display();
  }
}

String handleRequest()
{
  String returnMessage = "";
  WiFiClient client = espServer.available();
  while (client.connected())
  {
    if (client.available())
    {
      char c = client.read();
      request += c;
      if (c == '\n' && currentLineIsBlank)
      {
        if (request.indexOf("/timer?text=") != -1)
        {
          blockDevice = true;
          int equal = request.indexOf("=");
          int protocol = request.indexOf("HTTP");

          Serial.println(request.substring(equal + 1, protocol - 1));
          String message = request.substring(equal + 1, protocol - 1);
          message.replace("%20", " ");

          //that's a big and silly workaround, please use an elegant solution!
          message.replace("%C3%81", "Á");
          message.replace("%C3%89", "É");
          message.replace("%C3%8D", "Í");
          message.replace("%C3%93", "Ó");
          message.replace("%C3%9A", "Ú");
          message.replace("%C3%A1", "á");
          message.replace("%C3%A9", "é");
          message.replace("%C3%AA", "ê");
          message.replace("%C3%AD", "í");
          message.replace("%C3%B3", "ó");
          message.replace("%C3%BA", "ú");
          message.replace("%C3%A0", "à");
          message.replace("%C3%A8", "è");
          message.replace("%C3%AC", "ì");
          message.replace("%C3%B2", "ò");
          message.replace("%C3%B9", "ù");
          message.replace("%C3%80", "À");
          message.replace("%C3%88", "È");
          message.replace("%C3%8C", "Ì");
          message.replace("%C3%92", "Ò");
          message.replace("%C3%99", "Ù");
          message.replace("%C3%87", "Ç");
          message.replace("%C3%A7", "ç");
          message.replace("%C3%83", "Ã");
          message.replace("%C3%95", "Õ");
          message.replace("%C3%A3", "ã");
          message.replace("%C3%B5", "õ");

          message.replace("%AA", "");
          message.replace("%22", "");
          message.replace("%E2", "");
          message.replace("%80", "");
          message.replace("%8E", "");
          message.replace("%AC", "");
          message.trim();
          returnMessage = message;
        }

        if (request.indexOf("/message?text=") != -1)
        {
          blockDevice = false;
          int equal = request.indexOf("=");
          int protocol = request.indexOf("HTTP");

          Serial.println(request.substring(equal + 1, protocol - 1));
          String message = request.substring(equal + 1, protocol - 1);
          message.replace("%20", " ");

          //that's a big and silly workaround, please use an elegant solution!
          message.replace("%C3%81", "Á");
          message.replace("%C3%89", "É");
          message.replace("%C3%8D", "Í");
          message.replace("%C3%93", "Ó");
          message.replace("%C3%9A", "Ú");
          message.replace("%C3%A1", "á");
          message.replace("%C3%A9", "é");
          message.replace("%C3%AA", "ê");
          message.replace("%C3%AD", "í");
          message.replace("%C3%B3", "ó");
          message.replace("%C3%BA", "ú");
          message.replace("%C3%A0", "à");
          message.replace("%C3%A8", "è");
          message.replace("%C3%AC", "ì");
          message.replace("%C3%B2", "ò");
          message.replace("%C3%B9", "ù");
          message.replace("%C3%80", "À");
          message.replace("%C3%88", "È");
          message.replace("%C3%8C", "Ì");
          message.replace("%C3%92", "Ò");
          message.replace("%C3%99", "Ù");
          message.replace("%C3%87", "Ç");
          message.replace("%C3%A7", "ç");
          message.replace("%C3%83", "Ã");
          message.replace("%C3%95", "Õ");
          message.replace("%C3%A3", "ã");
          message.replace("%C3%B5", "õ");

          message.replace("%AA", "");
          message.replace("%22", "");
          message.replace("%E2", "");
          message.replace("%80", "");
          message.replace("%8E", "");
          message.replace("%AC", "");
          message.trim();
          returnMessage = message;
        }

        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println(); //  IMPORTANT
        break;
      }

      if (c == '\n')
      {
        currentLineIsBlank = true;
      }
      else if (c != '\r')
      {
        currentLineIsBlank = false;
      }
    }
  }

  delay(25);
  request = "";
  client.stop();
  return returnMessage;
}
