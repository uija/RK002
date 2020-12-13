#include <RK002.h>

#define MAXCHANNEL 11
 
RK002_DECLARE_INFO("Channel Ignorer","jkirchheimer@gmail.com ","1.0","ccd6aa34-84a8-484b-bfec-5987c3cf36dc")

boolean checkChannel( byte channel) {
  return channel <= MAXCHANNEL;
}

boolean RK002_onNoteOff(byte channel, byte key, byte velocity) {
  return checkChannel( channel);
}
boolean RK002_onNoteOn(byte channel, byte key, byte velocity) {
  return checkChannel( channel);
}
boolean RK002_onPolyPressure(byte channel, byte key, byte value) {
  return checkChannel( channel);
}
boolean RK002_onControlChange(byte channel, byte nr, byte value) {
  return checkChannel( channel);
}
boolean RK002_onProgramChange(byte channel, byte nr) {
  return checkChannel( channel);
}
boolean RK002_onChannelPressure(byte channel, byte val) {
  return checkChannel( channel);
}
boolean RK002_onPitchBend(byte channel, int val) {
  return checkChannel( channel);
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
