#define SAHA

#include <Arduino.h>
#include "TR.BIDS.libs.h"
#include "SpdDrive.h"

bool isNonAS = false;
BIDS bids = BIDS(&Serial);
SpdDrive Board = SpdDrive();

void SpeedChanged(int valI, double valF) {
  Board.setPWM1duty(valF / 120);
}
void orpChanged(int valI, double valF) {
  Board.setPWM2duty((valI * 10) / 120);
}
void dispChanged(int valI, double valF) {
  Board.setAtcIndicators(valI);
}
void atcGChanged(int valI, double valF) {
  Board.setAtcG(valI);
}
void atcRChanged(int valI, double valF) {
  Board.setAtcR(valI);
}
void atcXChanged(int valI, double valF) {
  Board.setAtcX(valI);
}
void atcPChanged(int valI, double valF) {
  Board.setAtcP(valI);
}
void atcNoticeChanged(int valI, double valF) {
  Board.setAtcNotice(valI);
}
void backLightChanged(int valI, double valF) {
  Board.setBackLight(valI);
}
void doorChanged(int valI, double valF) {
  Board.setDoor(valI);
}
void atsChanged(int valI, double valF) {
  Board.setAts(valI);
}
void ats15Changed(int valI, double valF) {
  Board.setAts15(valI);
}
void ats60Changed(int valI, double valF) {
  Board.setAts60(valI);
}

void setup() {
  Board.begin();
  Serial.begin(115200);
  while (!Serial);
  if (!bids.AddAutoSend('E', 1, SpeedChanged)) assert();
  if (!bids.AddAutoSend('P', 135, orpChanged)) assert();
  if (!bids.AddAutoSend('P', 100, dispChanged)) assert();
  if (!bids.AddAutoSend('P', 132, atcGChanged)) assert();
  if (!bids.AddAutoSend('P', 131, atcRChanged)) assert();
  if (!bids.AddAutoSend('P', 101, atcXChanged)) assert();
  if (!bids.AddAutoSend('P', 134, atcPChanged)) assert();
  if (!bids.AddAutoSend('P', 133, atcNoticeChanged)) assert();
  if (!bids.AddAutoSend('P', 161, backLightChanged)) assert();
  if (!bids.AddAutoSend('d', 1, doorChanged)) assert();
  if (!bids.AddAutoSend('P', 44, atsChanged)) assert();
  if (!bids.AddAutoSend('P', 42, ats15Changed)) assert();
  if (!bids.AddAutoSend('P', 43, ats60Changed)) assert();
}

void loop()
{
  isNonAS = false;
  if (!bids.ASDataCheck(&isNonAS) && isNonAS) {
    while (true) assert();
  }
}
