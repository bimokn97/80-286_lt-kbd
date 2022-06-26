#include <Keyboard.h>
#include <SPI.h>
#include <Arduino.h>
#include <inttypes.h>

const uint8_t SS589 = PA1
const uint8_t LS589 =  PA2


/* PA10 - PA12 used for USB */
const uint8_t rowsPin[] = { PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15 };
const int rowCount = sizeof(rowsPin) / sizeof(rowsPin[0]);
//uint16_t rowData[] = { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100};
//const int rowCount = sizeof(rowData) / sizeof(rowData[0]);

/*
     this data is configure 74hc595 pin on binary
     i set all hc595 pin high, and selected pin to low
     because it used 2 hc595, so i use 16 bit data on it
*/
//const uint8_t colsPin[] = {PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PA9, PA8, PB15 };
//const int colCount = sizeof(colsPin) / sizeof(colsPin[0]);
uint16_t colData[] = { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x200, 0x0400 };
const int colCount = sizeof(colData) / sizeof(colData[0]);

/*
   This data contain all preconfigured keys

  String keys[8][11] = {
  {"Escape", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10"},
  {"`", "1", "2", "3", "4", "5", "6", "8", "0", "-", "Numlock"},
  {"TAB", "q", "w", "e", "r", "y", "7", "9", "[", "=", "ScrollLock"},
  {"Capslock", "a", "s", "f", "t", "u", "i", "p", "|", "}", "PrintScreen"},
  {"LShift", "z", "d", "g", "h", "k", "o", "'", "UArrow", "Enter", "PauseBreak"},
  {"LCtrl", "x", "c", "n", "j", "l", ";", "RShift", "DArrow", "PgDown", "Home"},
  {"LAlt", "Insert", "v", "Space", "m", ".", "XX", "RCtrl", "XX", "End", "BackSpace"},
  {"Delete", "XX", "b", "RAlt", ",", "/", "XX", "LArrow", "XX", "RArrow", "PgUp"},
  };
*/

/* and this is key in ascii
   https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
*/
byte keys[rowCount][colCount] = {
  {0xB1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB},
  {0x7E, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x38, 0x30, 0x2D, 0xDB},
  {0xB3, 0x71, 0x77, 0x65, 0x72, 0x79, 0x37, 0x39, 0x5B, 0x3D, 0xCF},
  {0xC1, 0x61, 0x73, 0x66, 0x74, 0x75, 0x69, 0x70, 0x5C, 0x5D, 0xCE},
  {0x81, 0x7A, 0x64, 0x67, 0x68, 0x6B, 0x6F, 0x27, 0xDA, 0xB0, 0xD0},
  {0x80, 0x78, 0x63, 0x6E, 0x6A, 0x6C, 0x3B, 0x85, 0xD9, 0xD6, 0xD2},
  {0x82, 0xD1, 0x76, 0x20, 0x6D, 0x2E, 0x00, 0x84, 0x00, 0xD5, 0xB2},
  {0xD4, 0x00, 0x62, 0x86, 0x2C, 0x2F, 0x00, 0xD8, 0x00, 0xD7, 0xD3},
};

bool keysState[rowCount][colCount];
bool keysPrevState[rowCount][colCount];
uint32_t keyslastDebounce[rowCount][colCount];
uint16_t debounceDelay = 50;

String str;
int col = 0, row = 0;
uint16_t data;
String state[] = {"release", "pressed"};
uint16_t* spi_buffer;


namespace myKbd {
void begin() {
  pinMode(SS595, OUTPUT);
  digitalWrite(SS595, HIGH);

  // initialize keyboard pin
  for (auto pin : rowsPin) {
    pinMode(pin, INPUT_PULLUP);
    /* no longger used, move to hc595
      for (col = 0; col < colCount; col++) {
      //set column pin to output and set to high
      pinMode(colsPin[col], OUTPUT);
      digitalWrite(colsPin[col], HIGH);

      // set all keystate and pre state to 1
      keysState[row][col] = 1;
      keysPrevState[rowCount][colCount] = 1 ;
      //}
    */
  }
}

void keyReads() {
  int col = 0, row = 0;
  /*
    set hc595 pinout using spi
    spi_buff = 0xF7FF; 1111111111101111
  */

  //scan each column
  for (col = 0; col < colCount; col++) {
    //set col high
    //digitalWrite(colsPin[col], LOW);

    //send 16 bit spi
    data = ~colData[col];
    digitalWrite(SS595, LOW);
    *spi_buffer = SPI.transfer16(data);
    digitalWrite(SS595, HIGH);

    // scan each row
    for (row = 0; row < rowCount; row++) {
      //read keyboard row
      keysState[row][col] = !digitalRead(rowsPin[row]);

      /* inverting register and shift to right */
      //spi_buff = ~spi_buff;
      //spi_buff = spi_buff << 1;
      //spi_buff = ~spi_buff;

      //set col high /* used only if using mcu io */
      //digitalWrite(colsPin[col], HIGH);
    }
  }
}

void keyProccess() {
  int col = 0, row = 0;
  for (col = 0; col < colCount; col++) {
    for (row = 0; row < rowCount; row++) {
      // if keyboard pressed internal led on
      if (keysState[row][col]) {
        digitalWrite(LED_BUILTIN, LOW);
      }

      //if ((millis() - keyslastDebounce[row][col]) > debounceDelay) {
      if (keysState[row][col] != keysPrevState[row][col]) {

        //#ifdef KEYBOARD_h
        if ( keysState[row][col] ) {
          Keyboard.press(keys[row][col]);
        } else {
          Keyboard.release(keys[row][col]);
        }
        //#endif
#ifdef SERIAL_H
        Serial.printf("Row|Col: [%02d][%02d] | Ascii key: 0x%02X | State: %s | Time; %03d ms \r \n", row, col, keys[row][col], state[keysState[row][col]].c_str(), millis() -  keyslastDebounce[row][col]);
#endif
      }

      if (keysState[row][col] != keysPrevState[row][col]) {
        keyslastDebounce[row][col] = millis();
      }

      keysPrevState[row][col] = keysState[row][col];
    }
  }

}
}

char h_str[3];
char m_str[3];

long lastTime = 0;
long s = 0;
long m = 0;
long h = 0;
bool sec;

void setup() {
  // initialize the LED pin as an output:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(PB10, OUTPUT);
  digitalWrite(PB10, LOW);

  pinMode(USER_BTN, INPUT_PULLUP);

  pinMode(SSEEPROM, OUTPUT);
  digitalWrite(SSEEPROM, HIGH);

  //SPI.setClockDivider(SPI_CLOCK_DIV16);

  myKbd::begin();

  SPI.begin();

  //#ifdef KEYBOARD_h
  Keyboard.begin();
  //#endif

#ifdef SERIAL_H
  Serial.begin(115200);
  Serial.println("Started kbd");
#endif
}


void loop() {
  myKbd::keyReads();
  myKbd::keyProccess();
  digitalWrite(SS595, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);

}
