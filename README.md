# LTM driven Artificial Horizon
When you fly FPV with an Cockpit-Camera you might wan’t some eyecandy on the dashboard of your
plane. With this project I use a Generic NodeMCU ESP8266 or ESP32C3 to display an artificial horizon on 
a 0.96“ SSD1306 OLED display. Both components together need only a 5V power supply with low current.
 
LTMReader Class is based on parts of ltm_telemetry_reader from Paweł Spychalski. (originaly found 
at https://github.com/DzikuVx/ltm_telemetry_reader).

You will find a detailed HowTo in the Documentation folder, the Artificial-Horizon and the 
Artificial-Horizon-ESP32C3 folder contain the complete Arduino sketch for each development board.