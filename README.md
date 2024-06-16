# my-esp32-display-oled

It can be used to display multiple alerts of your choice. In my case, I've been using it to show WhatsApp notifications and the currently playing track on Spotify.

## See in action
[![Watch the video](https://img.youtube.com/vi/Qm0B8_kE16A/default.jpg)](https://youtu.be/Qm0B8_kE16A)

It depends from the Tasker application for Android, that reads the notification from both applications and make a GET request to the esp32 with the message! That's it!

## Dependencies
- ssd1306 library: https://github.com/squix78/esp8266-oled-ssd1306. You can install it from Arduino IDE, search for ssd1306 by thing pulse.

## References
- https://www.hackster.io/johnnyfrx/esp32-with-integrated-oled-wemos-lolin-getting-started-07ac5d
