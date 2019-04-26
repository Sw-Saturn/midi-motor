#include <MIDI.h>
#include <Stepper.h>
#include<avr/io.h>

#define PWMpin 10

float duty = 0.14;

MIDI_CREATE_DEFAULT_INSTANCE();

void motorTone(int freq) {
  OCR1A = (unsigned int)(1000000 / freq);
  OCR1B = (unsigned int)(1000000 / freq * duty);
}

int m2t[127] = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  11,
  19,
  27,
  35,
  43,
  51,
  59,
  67,
  75,
  83,
  91,
  99,
  107,
  115,
  123, //NOTE_B2
  131, //NOTE_C3
  139, //NOTE_CS3
  147, //NOTE_D3
  156, //NOTE_DS3
  165, //NOTE_E3
  175, //NOTE_F3
  185, //NOTE_FS3
  196, //NOTE_G3
  208, //NOTE_GS3
  220, //NOTE_A3
  233, //NOTE_AS3
  247, //NOTE_B3
  262, //NOTE_C4
  277, //NOTE_CS4
  294, //NOTE_D4
  311, //NOTE_DS4
  330, //NOTE_E4
  349, //NOTE_F4
  370, //NOTE_FS4
  392, //NOTE_G4
  415, //NOTE_GS4
  440, //NOTE_A4
  466, //NOTE_AS4
  494, //NOTE_B4
  523, //NOTE_C5
  554, //NOTE_CS5
  587, //NOTE_D5
  622, //NOTE_DS5
  659, //NOTE_E5
  698, //NOTE_F5
  740, //NOTE_FS5
  784, //NOTE_G5
  831, //NOTE_GS5
  880, //NOTE_A5
  932, //NOTE_AS5
  988, //NOTE_B5
  1047, //NOTE_C6
  1109, //NOTE_CS6
  1175, //NOTE_D6
  1245, //NOTE_DS6
  1319, //NOTE_E6
  1397, //NOTE_F6
  1480, //NOTE_FS6
  1568, //NOTE_G6
  1661, //NOTE_GS6
  1760, //NOTE_A6
  1865, //NOTE_AS6
  1976, //NOTE_B6
  2093, //NOTE_C7
  2217, //NOTE_CS7
  2349, //NOTE_D7
  2489, //NOTE_DS7
  2637, //NOTE_E7
  2794, //NOTE_F7
  2960, //NOTE_FS7
  3136, //NOTE_G7
  3322, //NOTE_GS7
  3520, //NOTE_A7
  3729, //NOTE_AS7
  3951, //NOTE_B7
  4186, //NOTE_C8
  4435, //NOTE_CS8
  4699, //NOTE_D8
  4978 //NOTE_DS8
};

int vol = 4;
int tone1Interval = 0;
int note;

void handleNoteOn(byte channel, byte pitch, byte velocity){
  if (channel == 1) {
    duty=0.14;
    motorTone(m2t[pitch]);
  }
  tone1Interval = MIDI.getData1();
  digitalWrite(8, HIGH);
}

void handleNoteOff(byte channel, byte pitch, byte velocity){
  if (channel == 1) {
    tone1Interval = 0;
    duty=0;
    motorTone(m2t[pitch]);
    digitalWrite(8, LOW);
  }
}

void setup() {
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin();
  pinMode(PWMpin, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  TCCR1A = 0b00100001;
  TCCR1B = 0b00010010;
  MIDI.read();
}
