# my-esp32-display-oled

It can be used to display N alerts that you want, in my case I've using to display Whatsapp alerts and the track that is playing on Spotify.
![image](https://user-images.githubusercontent.com/5191469/145686447-ada90158-8a96-493e-9ac1-0905391214d1.png)

It depends from the Tasker application for Android, that reads the notification from both applications and make a GET request to the esp32 with the message! That's it!

## Dependencies
- ssd1306 library: https://github.com/squix78/esp8266-oled-ssd1306. You can install it from Arduino IDE, search for ssd1306 by thing pulse.

## References
- https://www.hackster.io/johnnyfrx/esp32-with-integrated-oled-wemos-lolin-getting-started-07ac5d