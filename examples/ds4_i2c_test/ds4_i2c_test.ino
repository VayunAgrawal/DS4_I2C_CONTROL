/*
   I2C Test harness for USB Host PS4 Bluetooth controller
   http://www.hobbytronics.co.uk/usb-host/ps3-ps4-controller-bluetooth
   
   Steve Smith 2017, based on Hobbytronics ps4_hex_tank example.

   Connections:
   5V on host controller --> 5V on Arduino
   0V on host controller --> GND on Arduino
   SDA on host controller --> pin A4 (SDA) on Arduino
   SCL on host controller --> pin A5 (SCL) on Arduino
   non-latching SPST push switch between 0V and SS pin on host controller to enable bluetooth pairing mode (blue LED flashes faster)

   NB: in order for the host controller to work in I2C mode, it is necessary to turn off SERIAL mode on the USB host controller board.
   This needs to be done via a direct UART (Rx/Tx) connection to the board via the Arduino, which can be set up as follows:

   Temporary connections to turn off Serial mode on host controller:
   5V on host controller --> 5V on Arduino
   0V on host controller --> GND on Arduino
   TX on host controller --> TX-> on Arduino
   RX on host controller --> ->RX on Arduino
   RESET pin on Arduino --> GND on Arduino (this is to bypass the Arduino's internal UART chip so we're talking directly to the host controller)

   Instructions to turn off Serial mode on the host controller:
   - Remove the bluetooth dongle from the host controller
   - Open up the Serial Monitor in the Arduino IDE and set the line mode to "Carriage return" and the baud rate to whatever rate the Arduino was using (recommend 115200).
   - Enter the command HELP in the command line and click Send. 
   - You should see a report of the current settings of the host controller board (if HELP doesn't work, try ? instead) - by default, Serial mode is ON.
   - Enter the command SERIAL OFF and click Send.
   - Then type HELP or ? again and you should see that the SERIAL mode is now OFF.
   - Now turn everything off, reinsert the bluetooth dongle into the host controller and reconnect as per the normal connections shown above.

*/

#include <DS4_I2C_CONTROL.h>

unsigned long time;
uint32_t baudRate = 115200;
uint8_t read_interval = 20;
DS4_I2C_CONTROL ds4 = DS4_I2C_CONTROL(0x29);

void setup()  {
  Serial.begin(baudRate);
  time = 0;
  ds4.begin();
}

void loop()  {

  if (millis() > time)
  {
    time = millis() + read_interval;
    ds4.get_ps4();
    if (ds4.ps4_ok)
    {
      showStatus();
    }
  }
}

void showStatus()
{
  Serial.println((String)"PS4 left joystick value is x: " + ds4.l_joystick_x + " y: " + ds4.l_joystick_y);
  Serial.println((String)"PS4 right joystick value is x: " + ds4.r_joystick_x + " y: " + ds4.r_joystick_y);
  Serial.println((String)"PS4 R1 button is:  " + ds4.button_r1);
  Serial.println((String)"PS4 R2 button is:  " + ds4.button_r2);  
}




