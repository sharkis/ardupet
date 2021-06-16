#include <Arduboy2.h>
#include "Monster.h"
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
  /*
  byte strhp = 0xf8;
  byte hp = 0x8;
  byte maxhplevel = 0xf1;
  byte level = 0x1;
  // 0xf8f1 63729
  unsigned int password = strhp << 8 | maxhplevel;
  */
  arduboy.pollButtons();
  if(arduboy.justPressed(UP_BUTTON)){
    monster1 = genMonster();
  }
  if(arduboy.justPressed(DOWN_BUTTON)){
    monster2 = genMonster();
  }
   if(arduboy.justPressed(A_BUTTON)){
    int monster1dmg = (monster2.atk - monster1.def);
    int monster2dmg = (monster1.atk - monster2.def);
    if(monster1.hp>0 && monster2.hp>0){
    monster1.hp = monster1.hp -( monster1dmg > 0 ? monster1dmg : 0);
    monster2.hp = monster2.hp -( monster2dmg > 0 ? monster2dmg : 0);  
    }
  }
  arduboy.clear();
  if(monster1.hp <=0){
    arduboy.setCursor(0,32);
    arduboy.print("DEAD");
  }
  if(monster2.hp <=0){
    arduboy.setCursor(64,32);
    arduboy.print("DEAD");
  }
  arduboy.setCursor(0, 0);
  arduboy.print("atk");
  arduboy.println(monster1.atk);
  arduboy.print("def");
  arduboy.println(monster1.def);
  arduboy.print("hp");
  arduboy.println(monster1.hp);
  arduboy.print("level");
  arduboy.println(monster1.level);
  arduboy.setCursor(64, 0);
  arduboy.print("atk");
  arduboy.println(monster2.atk);
  arduboy.setCursor(64, 8);
  arduboy.print("def");
  arduboy.println(monster2.def);
  arduboy.setCursor(64, 16);
  arduboy.print("hp");
  arduboy.println(monster2.hp);
  arduboy.setCursor(64, 24);
  arduboy.print("level");
  arduboy.println(monster2.level);
  arduboy.display();
}

Monster genMonster(){
  Monster newMonster;
  newMonster.atk = random(10);
  newMonster.def = random(10);
  newMonster.hp = 10;
  newMonster.level=1;
  return newMonster;
}
