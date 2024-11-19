#include <Arduino.h>
#include <LiquidCrystal.h>

// Define the pins connected to the LCD
const int rs = 12;
const int enable = 11;
const int d4 = 10;
const int d5 = 9;
const int d6 = 8;
const int d7 = 7;

// Create an instance of the LiquidCrystal library
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

// The text to scroll
String text1 = "kirubel";
String id1 = "00040/12";

String text2 = "mastewal";
String id2 = "00020/12";

String text3 = "dagim";
String id3 = "makuanint";

String text4 = "getnet";
String id4 = "makuanint";

String text5 = "zekarial";
String id5 = "makuanint";

String text6 = "halemariam";
String id6 = "makuanint";

String text7 = "makuanint";
String id7 = "makuanint";

// The current scroll position
int scrollPos = 0;

void scroller(String text, String id){
    // Scroll the text one position
  if (scrollPos > 16) {
    // if (scrollPos >= text.length()) {
    scrollPos = 0;
  }
  while (scrollPos <= 16) {

  // Clear the LCD
  lcd.clear();

  // Print the text, starting at the current scroll position
  lcd.setCursor(scrollPos, 0);
  lcd.print(text);
  lcd.setCursor(scrollPos, 1);
  lcd.print(id);

  // Delay for a millisecond
  delay(100);

  scrollPos++;
  }

}

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
}

void loop() {
  scroller(text1, id1);
  scroller(text2, id2);
  scroller(text3, id3);
  scroller(text4, id4);
  scroller(text5, id5);
  scroller(text6, id6);
  scroller(text7, id7);
}
