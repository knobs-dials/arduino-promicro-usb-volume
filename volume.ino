/*  USB volume knob with mute made from a 
 *  - Arduino Pro Micro 
 *  - HW-040 encoder
 *  
 *  Third-party libraries 
 *  -  HID-Project
 *  -  BasicEncoder
 *  
 *  Can repeat vol+ and vol- presses to go up/down faster, 
 *    because the encoder is fairly coarse (30 is jumps) so is effectively a physical rate limit.
 *  
 *  By default also presses vol- more than vol+,
 *    so that a "crap volume down" panic response works better,
 *    and turning up is a little more precise
 */
#include <BasicEncoder.h>
#include <TimerOne.h>
#include <HID-Project.h>

char up_nudges    = 3,  down_nudges = 5;
int  button_state = 0;  // state to avoid repeat presses, to ignore bounce on release, and to rate limit a little in the process

BasicEncoder encoder( 14, 10 );      // the pins I happen to use

void timer_service() {
  encoder.service();
}

void setup() {
  pinMode( 10, INPUT_PULLUP );
  pinMode( 14, INPUT_PULLUP );
  pinMode( 16, INPUT_PULLUP );
  Consumer.begin();                  // https://github.com/NicoHood/HID/wiki/Consumer-API
  Timer1.initialize( 1000 );         // 1kHz servicing the encoder
  Timer1.attachInterrupt( timer_service );
}


void loop() {
  int encoder_change = encoder.get_count();
  if (encoder_change != 0) {
    if (encoder_change>0) {
      for (char t=up_nudges; t; t--) {
        Consumer.press(MEDIA_VOLUME_UP);
        Consumer.release(MEDIA_VOLUME_UP);
      }
    }
    if (encoder_change<0) {
      for (char t=down_nudges; t; t--) {
        Consumer.press(MEDIA_VOLUME_DOWN);
        Consumer.release(MEDIA_VOLUME_DOWN);
      }
    }
    encoder.reset();
  }

  char button = !digitalRead(16);
  if (button) {
    if (button_state == 0) {
      button_state = 1000;
      Consumer.press(MEDIA_VOLUME_MUTE);
      Consumer.release(MEDIA_VOLUME_MUTE);
    } // else we're still ignoring it
  } else { // button == 0
    if (button_state > 0)
      button_state--;
  }
  
}
