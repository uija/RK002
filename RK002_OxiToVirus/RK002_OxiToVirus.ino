#include <RK002.h>

//RK002_DECLARE_INFO("OXI Multi to Virus Mapping","jkirchheimer@gmail.com","1.0","c6bc7044-d987-11ec-9d64-0242ac120002")

byte virus_min_channel = 8;
byte virus_max_channel = 14;
byte rhythm_min_channel = 0;
byte rhythm_max_channel = 7;
byte rhythm_pg_channel = 15;
byte program_change_note = 120;
byte bank_select_note = 119;
byte bank_select_cc = 0;
byte cc_note = 118;

byte current_target_cc[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

boolean RK002_onNoteOn(byte channel, byte key, byte velocity) {
  // channels outside our range function normally
  if( channel < virus_min_channel || channel > virus_max_channel) {
    return true;
  }
  
  if( key == program_change_note) {       // handle program changes
    RK002_sendProgramChange( channel, velocity-1);
    return false;
  } else if( key == bank_select_note) {   // handle bank select
    RK002_sendControlChange( channel, bank_select_cc, velocity-1);
    return false;
  } else if( key == cc_note) {            // set CC number
    current_target_cc[0] = velocity;
    return false;
  }
  // let all the other notes play
  return true;
}
boolean RK002_onNoteOff(byte channel, byte key, byte velocity) {
  if( channel < virus_min_channel || channel > virus_max_channel) {
    return true;
  }
  if( key == program_change_note || key == bank_select_note || key == cc_note) {
    return false;
  }
  return true;
}
boolean RK002_onProgramChange(byte channel, byte nr) {
  if( channel >= virus_min_channel && channel <= virus_max_channel) {
    // block all program changes because we do it via a note
    return false;
  }
  if( channel >= rhythm_min_channel && channel <= rhythm_max_channel) {
    // rhythm wants it on #16. As Oxi is sending multiple, lets, lets only listen to #1
    if( channel == rhythm_min_channel) {
      RK002_sendProgramChange( rhythm_pg_channel, nr);
    }
    return false;
  }
  return true;
}
boolean RK002_onControlChange(byte channel, byte nr, byte value) {
  // if outside range or we dont want to overwrite it, continue
  if( channel < virus_min_channel || channel > virus_max_channel || current_target_cc[channel] == 0) {
    return true;
  }
  RK002_sendControlChange( channel, current_target_cc[channel], value);
  return false;
}

void setup() {
  //
}

void loop() {
  //
}
