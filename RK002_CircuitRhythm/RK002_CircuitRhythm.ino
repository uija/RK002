#include <RK002.h>

#define DEFAULT_CHANNEL 1
#define DEFAULT_NOTE 48

//RK002_DECLARE_INFO("Circuit Rhythm Channel Splitter","jkirchheimer@gmail.com","1.0","bf8bf7f7-3a8d-44d4-b2ca-f124faae1bda")
RK002_DECLARE_PARAM(CHANNEL,1,1,16,DEFAULT_CHANNEL)
RK002_DECLARE_PARAM(NOTE,1,0,127,DEFAULT_NOTE)

uint8_t listening_channel = DEFAULT_CHANNEL;
uint8_t note = DEFAULT_NOTE;

void load_params() {
  uint8_t c = RK002_paramGet( CHANNEL);
  if( c > 0 && c < 17) {
    listening_channel = c-1;
  } else {
    listening_channel = DEFAULT_CHANNEL-1;  
  }

  c = RK002_paramGet( NOTE);
  if( c >= 0 && c <= 127) {
    note = c;
  } else {
    note = DEFAULT_NOTE;  
  }
}

byte getRhythmCCforSequencerCC( byte sequencerCC) {
  switch( sequencerCC) {
    case 1:
      return 8; // Sample Choice
    case 2:
      return 21; // Pitch
    case 3:
      return 17; // Number of slices
    case 4:
      return 16; // slice
    case 5:
      return 24; // Slope
    case 6:
      return 25; // Distortion
    case 7:
      return 26; // HPF
    case 8:
      return 27; // LPF
    case 9:
      return 29; // Level
    case 10:
      return 30; // Pan
    case 11:
      return 31; // Reverb Send
    case 12:
      return 32; // DelaySend
    default:
      return 127;
  }
}
void RK002_onParamChange( unsigned param_nr, int param_val) {
  if( param_nr == CHANNEL) {
    listening_channel = param_val;
  } else if( param_nr == NOTE) {
    note = param_val;
  }
}

boolean RK002_onNoteOff( byte channel, byte key, byte velocity) {
  if( channel != listening_channel) {
    return false;
  }
  while( key >= 8) {
    key -= 8;
  }
  RK002_sendNoteOff( key, note, velocity); 
  return false;
}
boolean RK002_onNoteOn(byte channel, byte key, byte velocity) {
  if( channel != listening_channel) {
    return false;
  }
  while( key >= 8) {
    key -= 8;
  }
  RK002_sendNoteOn( key, note, velocity); 
  return false;
}
boolean RK002_onControlChange( byte channel, byte nr, byte value) {
  static int number_of_ccs = 12;
  if( channel != listening_channel) {
    return false;
  }
  byte cc = 127;
  byte ch = 0;
  for( uint8_t i = 0; i < 8; ++i) {
    if( nr < (i+1 * number_of_ccs + 1)) {
      cc = nr - i*number_of_ccs;
      ch = i;
      break;
    }
  }
  cc = getRhythmCCforSequencerCC( cc);
  if( ch > 7) {
    return false;
  }
  if( cc == 127) {
    return false;
  }
  RK002_sendControlChange( ch, cc, value);
  return false;
}
boolean RK002_onProgramChange(byte channel, byte nr) {
  if( channel != listening_channel) {
    return false;
  }
  RK002_sendProgramChange( 16, nr);
  return false;  
}
void setup() {
  load_params();
}

void loop() {

}
