#ifndef ShiftySwitches_h
#define ShiftySwitches_h

#include <Shifty.h>

#define MAX_SWITCHES  8

class ShiftySwitches{
private:
  Shifty _shifty;
  
  int _dataPin, _latchPin, _clockPin;
  String _switches[MAX_SWITCHES];
  bool _statuses[MAX_SWITCHES];
  bool _toggleWriteBit = true;

  int getIndexOfSwitch(String);
public:
  /* Construct */
  ShiftySwitches(bool defaultStatus = false, int _data = 13, int _clock = 14, int _latch = 12);

  /* Basic Functions */
  bool turnOn(String);
  bool turnOff(String);
  bool toggle(String);

  void turnAllOn();
  void turnAllOff();
  void toggleAll();

  /* Class Based Functions */
  // Add Siwtches with relative id
  bool add(String, int);
};

#endif
