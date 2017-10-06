/*
  USB Host PS4 Dualshock Controller
  I2C interface
*/

//#define DEBUG 1

#ifndef _DS4_I2C_CONTROL_H
#define _DS4_I2C_CONTROL_H
#include "Arduino.h"

#define IC2_LENGTH 14

class DS4_I2C_CONTROL {
  public:
    DS4_I2C_CONTROL(uint8_t address = 0x41);
    void begin(void);
    void get_ps4();
    bool ps4_ok;

    unsigned char  l_joystick_x;
    unsigned char  l_joystick_y;
    unsigned char  r_joystick_x;
    unsigned char  r_joystick_y;
    unsigned char  accel_x;
    unsigned char  accel_y;
    unsigned char  l2;
    unsigned char  r2;

    unsigned char  button_left;
    unsigned char  button_down;
    unsigned char  button_right;
    unsigned char  button_up;
    unsigned char  button_square;
    unsigned char  button_x;
    unsigned char  button_circle;
    unsigned char  button_triangle;

    unsigned char  button_l1;
    unsigned char  button_r1;
    unsigned char  button_l2;
    unsigned char  button_r2;
    unsigned char  button_share;
    unsigned char  button_options;
    unsigned char  button_l3;
    unsigned char  button_r3;

    unsigned char  button_ps4;
    unsigned char  button_tpad;

    unsigned char  tpad_x;
    unsigned char  tpad_y;
    unsigned char  battery;

  private:
    uint8_t _i2caddr;
	uint8_t _i2clength;
	unsigned char ps4_ic2[IC2_LENGTH];
    void decode_ps4(void);

};

#endif

