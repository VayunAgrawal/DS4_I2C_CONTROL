/*
  USB Host PS4 Dualshock Controller
  I2C interface 
*/

#include <DS4_I2C_CONTROL.h>
#include <Wire.h>
#if defined(ARDUINO_SAM_DUE)
 #define WIRE Wire1
#else
 #define WIRE Wire
#endif

#define IC2_LENGTH 14

DS4_I2C_CONTROL::DS4_I2C_CONTROL(uint8_t address) {
  _i2caddr = address;
  _i2clength = IC2_LENGTH;
  ps4_ok = false;
}

void DS4_I2C_CONTROL::begin(void) {
 WIRE.begin();
}

void DS4_I2C_CONTROL::get_ps4()
{
  // Get data from PS4 DualShock Controller via I2C
  // We only want single byte values (0 to 255)

  unsigned char i2c_index=0; 
  WIRE.beginTransmission(_i2caddr);  // transmit to device
  WIRE.write(0);                        // Start receiving data from register 0
  WIRE.endTransmission();               // end transmission
  
  WIRE.requestFrom(_i2caddr, _i2clength);    // request PS4_I2C_LEN bytes from PS4 
  while(WIRE.available())
  { 
    ps4_ic2[i2c_index++] = WIRE.read();          // receive a byte and increment index     
  }  

  decode_ps4();                         // Decode PS4 data
}

// Decode PS4 Data and move to struct
void DS4_I2C_CONTROL::decode_ps4(void){

   ps4_ok = false;
  
   l_joystick_x = ps4_ic2[0];
   l_joystick_y = ps4_ic2[1];
   r_joystick_x = ps4_ic2[2];
   r_joystick_y = ps4_ic2[3];
   accel_x      = ps4_ic2[4];
   accel_y      = ps4_ic2[5]; 
   l2           = ps4_ic2[6]; 
   r2           = ps4_ic2[7]; 
             
   if(((ps4_ic2[8]&0x0F)==5) || ((ps4_ic2[8]&0x0F)==6) || ((ps4_ic2[8]&0x0F)==7)) button_left=1;  else button_left=0;	//W
   if(((ps4_ic2[8]&0x0F)==3) || ((ps4_ic2[8]&0x0F)==4) || ((ps4_ic2[8]&0x0F)==5)) button_down=1;  else button_down=0;	//S
   if(((ps4_ic2[8]&0x0F)==1) || ((ps4_ic2[8]&0x0F)==2) || ((ps4_ic2[8]&0x0F)==3)) button_right=1; else button_right=0;	//E
   if(((ps4_ic2[8]&0x0F)==0) || ((ps4_ic2[8]&0x0F)==1) || ((ps4_ic2[8]&0x0F)==7)) button_up=1;    else button_up=0;	//N
   button_square  =((ps4_ic2[8]&0b00010000)>>4); // SQUARE
   button_x       =((ps4_ic2[8]&0b00100000)>>5); // X
   button_circle  =((ps4_ic2[8]&0b01000000)>>6); // CIRCLE
   button_triangle=((ps4_ic2[8]&0b10000000)>>7); // TRIANGLE

   button_l1     =((ps4_ic2[9]&0b00000001));    // L1
   button_r1     =((ps4_ic2[9]&0b00000010)>>1); // R1
   button_l2     =((ps4_ic2[9]&0b00000100)>>2); // L2
   button_r2     =((ps4_ic2[9]&0b00001000)>>3); // R2
   button_share  =((ps4_ic2[9]&0b00010000)>>4); // SHARE
   button_options=((ps4_ic2[9]&0b00100000)>>5); // OPTIONS
   button_l3     =((ps4_ic2[9]&0b01000000)>>6); // L3
   button_r3     =((ps4_ic2[9]&0b10000000)>>7); // R3

   button_ps4    =((ps4_ic2[10]&0b00000001));    // PS4
   button_tpad   =((ps4_ic2[10]&0b00000010)>>1); // TPAD
                
   tpad_x        =ps4_ic2[11]; 
   tpad_y        =ps4_ic2[12];      
   battery       =ps4_ic2[13];

   ps4_ok = true;
}

