#include "Monster.h"
#include <Arduboy2.h>
Arduboy2 arduboy;
Monster monster1;
Monster monster2;

void setup() {
  arduboy.begin();
  arduboy.clear();
  monster1 = genMonster();
  monster2 = genMonster();
}

void loop() {
  arduboy.pollButtons();
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
}

Monster genMonster() {
  Monster newMonster;
  newMonster.atk = random(10);
  newMonster.def = random(10);
  newMonster.hp = 10;
  newMonster.level = 1;
  return newMonster;
}
