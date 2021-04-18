#define SAHA

#include <Arduino.h>
#include "TR.BIDS.libs.h"
#include "SpdDrive.h"

bool isNonAS = false;
int bidsVersion = 202;
BIDS bids = BIDS(&Serial);
SpdDrive Board = SpdDrive();

void Assert() {
  Serial.println("Assert");
  while(1) delay(1000);
}

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
  Serial.println("serial connected");
  bidsVersion = bids.CmdSenderI("TRV" + bidsVersion);
  delay(1000);

  if (!bids.AddAutoSend('E', 1, SpeedChanged)) Assert();
  if (!bids.AddAutoSend('P', 135, orpChanged)) Assert();
  if (!bids.AddAutoSend('P', 100, dispChanged)) Assert();
  if (!bids.AddAutoSend('P', 132, atcGChanged)) Assert();
  if (!bids.AddAutoSend('P', 131, atcRChanged)) Assert();
  if (!bids.AddAutoSend('P', 101, atcXChanged)) Assert();
  if (!bids.AddAutoSend('P', 134, atcPChanged)) Assert();
  if (!bids.AddAutoSend('P', 133, atcNoticeChanged)) Assert();
  if (!bids.AddAutoSend('P', 161, backLightChanged)) Assert();
  if (!bids.AddAutoSend('d', 1, doorChanged)) Assert();
  if (!bids.AddAutoSend('P', 44, atsChanged)) Assert();
  if (!bids.AddAutoSend('P', 42, ats15Changed)) Assert();
  if (!bids.AddAutoSend('P', 43, ats60Changed)) Assert();
}

void loop()
{
  isNonAS = false;
  if (!bids.ASDataCheck(&isNonAS) && isNonAS) {
    while (true) Assert();
  }
}
