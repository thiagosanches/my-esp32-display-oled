#include <WiFi.h>
#include "SSD1306.h"

SSD1306  screen(0x3c, 5, 4);
WiFiServer espServer(80);

String request;
boolean currentLineIsBlank = true;
const int MAX_COLUMNS = 128;
const char* ssid = "X";
const char* password = "Y";

void setup()
{
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
  screen.drawStringMaxWidth(0, 0, MAX_COLUMNS, "My IP is: " + myLocalIP);
  screen.display();
}

void loop()
{
  delay(200);
  handleRequest();
}

void handleRequest()
{
  WiFiClient client = espServer.available();
  while (client.connected())
  {
    if (client.available())
    {
      char c = client.read();
      request += c;
      if (c == '\n' && currentLineIsBlank)
      {
        if (request.indexOf("/message?text=") != -1)
        {
          int equal = request.indexOf("=");
          int protocol = request.indexOf("HTTP");

          Serial.println(request.substring(equal + 1, protocol - 1));
          String message = request.substring(equal + 1, protocol - 1);
          message.replace("%20", " ");
          message.replace("%22", "");

          //that's a big and silly workaround, please use an elegant solution!
          message.replace("%C3%81", "Á");
          message.replace("%C3%89", "É");
          message.replace("%C3%8D", "Í");
          message.replace("%C3%93", "Ó");
          message.replace("%C3%9A", "Ú");
          message.replace("%C3%A1", "á");
          message.replace("%C3%A9", "é");
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
          message.trim();

          screen.clear();

          for (int j = 0; j < 64; j++)
          {
            screen.clear();
            screen.drawStringMaxWidth(0, j + 5, MAX_COLUMNS, message);
            screen.display();
          }

          for (int j = 64; j >= 0; j--)
          {
            screen.clear();
            screen.drawStringMaxWidth(0, j - 5, MAX_COLUMNS, message);
            screen.display();
          }

          screen.clear();
          screen.drawStringMaxWidth(0, 0, MAX_COLUMNS, message);
          screen.display();
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
}
