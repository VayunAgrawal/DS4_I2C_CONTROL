# DS4_I2C_CONTROL
PS4 Dualshock I2C USB Host Controller library for Arduino microcontrollers.

This is a library for the Hobbytronics USB Host Controller board pre-programmed for the PS4 Dualshock Controller
   http://www.hobbytronics.co.uk/usb-host/ps3-ps4-controller-bluetooth
   
SEMU Consulting 2017, based on the Hobbytronics ps4_hex_tank example.

## Connections:
   * 5V on host controller --> 5V on Arduino
   * 0V on host controller --> GND on Arduino
   * SDA on host controller --> pin A4 (SDA) on normal Arduino (SDA1 on Arduino Due)
   * SCL on host controller --> pin A5 (SCL) on normal Arduino (SCL1 on Arduino Due)
   * non-latching SPST push switch between 0V and SS pin on host controller to enable bluetooth pairing mode (blue LED flashes faster)

NB: in order for the host controller to work in I2C mode, it is necessary to turn off SERIAL mode on the USB host controller board.
This needs to be done via a direct UART (Rx/Tx) connection to the board via the Arduino, which can be set up as follows:

## Temporary connections to turn off Serial mode on host controller:
   * 5V on host controller --> 5V on Arduino
   * 0V on host controller --> GND on Arduino
   * TX on host controller --> TX-> on Arduino
   * RX on host controller --> ->RX on Arduino
   * RESET pin on Arduino --> GND on Arduino (this is to bypass the Arduino's internal UART chip so we're talking directly to the host controller)

## Instructions to turn off Serial mode on the host controller:
   1. Remove the bluetooth dongle from the host controller
   2. Open up the Serial Monitor in the Arduino IDE and set the line mode to "Carriage return" and the baud rate to whatever rate the Arduino was using (recommend 115200).
   3. Enter the command HELP in the command line and click Send. 
   4. You should see a report of the current settings of the host controller board (if HELP doesn't work, try ? instead) - by default, Serial mode is ON.
   5. Enter the command SERIAL OFF and click Send.
   6. Then type HELP or ? again and you should see that the SERIAL mode is now OFF.
   7. Now turn everything off, reinsert the bluetooth dongle into the host controller and reconnect as per the normal connections shown above.

<!-- START COMPATIBILITY TABLE -->

## Compatibility

MCU                | Tested Works | Doesn't Work | Not Tested  | Notes
------------------ | :----------: | :----------: | :---------: | -----
Atmega328 @ 16MHz  |      X       |             |            | 
Atmega328 @ 12MHz  |      X       |             |            | 
Atmega32u4 @ 16MHz |      X       |             |            | 
Atmega32u4 @ 8MHz  |      X       |             |            | 
ESP8266            |      X       |             |            | 
Atmega2560 @ 16MHz |      X       |             |            | 
ATSAM3X8E          |      X       |             |            | Use SDA1/SCL1
ATSAM21D           |      X       |             |            | 
ATtiny85 @ 16MHz   |      X       |             |            | 
ATtiny85 @ 8MHz    |      X       |             |            | 
Intel Curie @ 32MHz |             |             |     X       | 
STM32F2            |             |             |     X       | 

  * ATmega328 @ 16MHz : Arduino UNO, Adafruit Pro Trinket 5V, Adafruit Metro 328, Adafruit Metro Mini
  * ATmega328 @ 12MHz : Adafruit Pro Trinket 3V
  * ATmega32u4 @ 16MHz : Arduino Leonardo, Arduino Micro, Arduino Yun, Teensy 2.0
  * ATmega32u4 @ 8MHz : Adafruit Flora, Bluefruit Micro
  * ESP8266 : Adafruit Huzzah
  * ATmega2560 @ 16MHz : Arduino Mega
  * ATSAM3X8E : Arduino Due
  * ATSAM21D : Arduino Zero, M0 Pro
  * ATtiny85 @ 16MHz : Adafruit Trinket 5V
  * ATtiny85 @ 8MHz : Adafruit Gemma, Arduino Gemma, Adafruit Trinket 3V

<!-- END COMPATIBILITY TABLE -->
