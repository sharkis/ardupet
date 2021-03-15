#include <Arduboy2.h>
Arduboy2 arduboy;

void setup() {
arduboy.begin();
arduboy.clear();
}

void loop() {
arduboy.clear();
arduboy.setCursor(0,0);
arduboy.print("ardupet");
arduboy.display();
}
