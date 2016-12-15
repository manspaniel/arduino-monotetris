#ifndef IO_H
#define IO_H

#include <Adafruit_SharpMem.h>

// Display Type
typedef Adafruit_SharpMem Display;

// Display Pins
#define SCK 10
#define MOSI 11
#define SS 13

// Display Colors
#define BLACK 0
#define WHITE 1

// Init display..
static Display display(SCK, MOSI, SS);

// Buttons
#define BUTTON_L 14
#define BUTTON_R 15
#define BUTTON_A 16
#define BUTTON_B 17

// Display stuff
Display * getMainDisplay();

void initButtons();
bool isButtonDown(int button);

#endif