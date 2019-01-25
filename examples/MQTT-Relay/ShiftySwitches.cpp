#include "ShiftySwitches.h"

ShiftySwitches::ShiftySwitches(bool defaultStatus, int _data, int _clock, int _latch){
  _dataPin = _data;
  _clockPin = _clock;
  _latchPin = _latch;
  
  // Initialize shift register
  _shifty.setBitCount(MAX_SWITCHES);
  _shifty.setPins(_dataPin, _clockPin, _latchPin);
  for(int i = 0; i < MAX_SWITCHES; i++){
    _statuses[i] = defaultStatus;
    _shifty.writeBit(i, (_toggleWriteBit ? !defaultStatus : defaultStatus));
  }
}

/* Public methods*/
// Turn on switch
bool ShiftySwitches::turnOn(String id){
  int _switchIndex = getIndexOfSwitch(id);
  if(_switchIndex != -1){
    _statuses[_switchIndex] = true;
    _shifty.writeBit(_switchIndex, (_toggleWriteBit ? LOW : HIGH));
    return true;
  }
  return false;
}

// Turn of switch
bool ShiftySwitches::turnOff(String id){
  int _switchIndex = getIndexOfSwitch(id);
  if(_switchIndex != -1){
    _statuses[_switchIndex] = false;
    _shifty.writeBit(_switchIndex, (_toggleWriteBit ? HIGH : LOW));
    return true;
  }
  return false;
}

bool ShiftySwitches::toggle(String id){
  int _switchIndex = getIndexOfSwitch(id);
  if(_switchIndex != -1){
    bool _status = _statuses[_switchIndex] = !_statuses[_switchIndex];
    _shifty.writeBit(_switchIndex, (_toggleWriteBit ? !_status : _status));
    return true;
  }
  return false;
}

void ShiftySwitches::turnAllOn(){
  _shifty.batchWriteBegin();
  for(int i = 0; i < MAX_SWITCHES; i++){
    _statuses[i] = true;
    _shifty.writeBit(i, (_toggleWriteBit ? LOW : HIGH));
  }
  _shifty.batchWriteEnd();
}

void ShiftySwitches::turnAllOff(){
    _shifty.batchWriteBegin();
  for(int i = 0; i < MAX_SWITCHES; i++){
    _statuses[i] = false;
    _shifty.writeBit(i, (_toggleWriteBit ? HIGH : LOW));
  }
  _shifty.batchWriteEnd();
}

void ShiftySwitches::toggleAll(){
  _shifty.batchWriteBegin();
  for(int i = 0; i < MAX_SWITCHES; i++){
    bool _status = _statuses[i] = !_statuses[i];
    _shifty.writeBit(i, (_toggleWriteBit ? !_status : _status));
  }
  _shifty.batchWriteEnd();
}

// Add shitch id
bool ShiftySwitches::add(String id, int index){
  if (index >= 0 && index < MAX_SWITCHES){
    _switches[index] = id;
    return true;
  }
  return false;
}

/* Private methods*/
int ShiftySwitches::getIndexOfSwitch(String id){
  for(int i = 0; i < MAX_SWITCHES; i++){
    if(_switches[i] == id) {
      return i;
    }
  }
  return -1;
}
