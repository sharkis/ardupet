#include "Monster.h"
#include <Sprites.h>
#include <Arduboy2.h>
Arduboy2 arduboy;
BeepPin1 beep;
Monster monster1;
Monster monster2;

void setup() {
  arduboy.begin();
  Serial.begin(9600);
  arduboy.clear();
  beep.begin();
  arduboy.setFrameRate(30);
  monster1 = genMonster();

  monster2 = genMonster();
}

const uint8_t PROGMEM charlie[] = {B11110000, B10011000, B11000100, B00111110, B00000011, B00000001, B01011001, B11000001, B01011001, B00000001, B00000011, B00111110, B11000100, B10011000, B11110000,
                                    0x00,0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x01,0x00,0x00,0x00};

void loop() {
  arduboy.pollButtons();
  beep.timer();
  if (arduboy.justPressed(UP_BUTTON)) {
    monster1 = genMonster();
  }
  if (arduboy.justPressed(DOWN_BUTTON)) {
    monster2 = genMonster();
  }
  if (arduboy.justPressed(A_BUTTON)) {
    int monster1dmg = random(20) + monster1.atk > monster2.def ? random(6) : 0;
    int monster2dmg = random(20) + monster2.atk > monster1.def ? random(6) : 0;
    if (monster1.hp > 0 && monster2.hp > 0) {
      monster1.hp = monster1.hp - (monster1dmg > 0 ? monster1dmg : 0);
      monster2.hp = monster2.hp - (monster2dmg > 0 ? monster2dmg : 0);
    }
    if (monster1.hp <= 0 || monster2.hp <= 0) {
      beep.tone(beep.freq(440), 15);
    }
  }
  arduboy.clear();
  printInfo(monster1, monster2);
  arduboy.display();
}

void printInfo(Monster monster1, Monster monster2) {

  if (monster1.hp <= 0) {
    arduboy.setCursor(0, 32);
    arduboy.print("DEAD");
  }
  if (monster2.hp <= 0) {
    arduboy.setCursor(64, 32);
    arduboy.print("DEAD");
  }
  arduboy.setCursor(0, 0);
  arduboy.print("ATK ");
  arduboy.println(monster1.atk);
  arduboy.print("DEF ");
  arduboy.println(monster1.def);
  arduboy.print("HP  ");
  arduboy.println(monster1.hp);
  arduboy.print("LV  ");
  arduboy.println(monster1.level);
  
  arduboy.drawBitmap(0, 40, charlie, 15, 10, WHITE);
  arduboy.setCursor(64, 0);
  arduboy.print("ATK ");
  arduboy.println(monster2.atk);
  arduboy.setCursor(64, 8);
  arduboy.print("DEF ");
  arduboy.println(monster2.def);
  arduboy.setCursor(64, 16);
  arduboy.print("HP  ");
  arduboy.println(monster2.hp);
  arduboy.setCursor(64, 24);
  arduboy.print("LV  ");
  arduboy.println(monster2.level);
  for (int i = 0; i < 16; i++) {
    for (int k = 0; k < 8; k++) {
      arduboy.drawPixel(64 + k, 40 + i, monster2.img[2 * i] >> k & 0x01);
      arduboy.drawPixel(k + 72, 40 + i, monster2.img[(2 * i + 1)] >> k & 0x01);
    }
  }
  
}

Monster genMonster() {
  Monster newMonster;
  newMonster.atk = random(10);
  newMonster.def = random(10);
  newMonster.hp = 10;
  newMonster.level = 1;
  for (int i = 0; i < 32; i++) {
    byte line = (byte)random(255);
    Serial.println(line, BIN);
    newMonster.img[i] = line;
  }
  return newMonster;
}
