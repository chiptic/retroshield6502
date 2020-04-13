////////////////////////////////////////////////////////////////////
// RetroShield 6502 for Arduino Mega
// Apple I
//
// 2019/01/28
// Version 0.1

// The MIT License (MIT)

// Copyright (c) 2019 Erturk Kocalar, 8Bitforce.com

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//


#include <avr/pgmspace.h>
//#include "pins2_arduino.h"
#include <DIO2.h>

////////////////////////////////////////////////////////////////////
// include the library code for LCD shield:
////////////////////////////////////////////////////////////////////

#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

#include "RetroSystemBoard.h"
#include "RetroDevicePia6821.h"

////////////////////////////////////////////////////////////////////
// Configuration
////////////////////////////////////////////////////////////////////


// MEMORY LAYOUT
// - Apple 1 BASIC requires 4KB min, so adjust when SPI_RAM not used.

// 6K MEMORY
//#define RAM_START   0x0000
//#define RAM_END     0x17FF

// ROMs (Monitor + Basic + ACI)
//#define ROM_START   0xFF00
//#define ROM_END     0xFFFF


// Woz Monitor Code, based 0xFF00 to 0xFFFF
extern "C" PROGMEM const unsigned char code_rom_apple1_woz_mon[];

// Define device address for Woz Monitor ROM
static constexpr DeviceAddressDef monitorRomAddressDef(code_rom_apple1_woz_mon, 0xFF00, 0xFFFF);

// EHBASIC Code, based 0xE000 to 0xEFFF
extern "C" PROGMEM const unsigned char code_rom_apple1_basic[];

// Define device address for BASIC ROM
static constexpr DeviceAddressDef basicRomAddressDef(code_rom_apple1_basic, 0xE000, 0xEFFF);

// Statically allocate RAM
byte memory1[6144];

// Define device address for RAM
static constexpr DeviceAddressDef ramAddressDef(memory1, 0x0000, 0x1FFF);



RetroDevicePia6821 pia6821(KBD, DSPCR);



class SystemBoard : public RetroSystemBoard {

public:

	static void init() {

		// Initialize processor GPIO's
		initCpuDeviceAdapter();

		pia6821.init();

		resetCpu();
	};

	static void resetCpu() {

	  // Reset processor for 25 cycles
	  assertReset();
	  for(int i=0; i<25; i++) {
		  SystemBoard::clockTick();
	  }
	  releaseReset();
	};


	 __attribute__((always_inline))
     static inline void clockTick() {

		// Start data access phase
		startCpuDataAccessPhase();

		// Read bus address supplied by CPU
		register word busAddr = RetroSystemBoard::readCpuBusAddress();

	    if (isAddressOfBottomDevice(ramAddressDef, busAddr)) {
	    	transferMemoryDataByte(ramAddressDef, busAddr);

	    } else if (isAddressOfTopDevice(monitorRomAddressDef, busAddr)) {
	    	transferProgramDataByte(monitorRomAddressDef, busAddr);

	    } else if (isAddressOfDevice(basicRomAddressDef, busAddr)) {
	    	transferProgramDataByte(basicRomAddressDef, busAddr);

		} else if (busAddr >= KBD && busAddr <= DSPCR) {
			pia6821.transferDataByte(busAddr);
		}

		// Finish data access phase and start next cycle
	    finishCpuDataAccessPhase();
	}

};

SystemBoard systemBoard;

////////////////////////////////////////////////////////////////////
// Processor Control Loop
////////////////////////////////////////////////////////////////////
// This is where the action is.
// it reads processor control signals and acts accordingly.
//


////////////////////////////////////////////////////////////////////
// Serial Event
////////////////////////////////////////////////////////////////////

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
inline __attribute__((always_inline))
void serialEvent0()
{
  if (Serial.available()) {
	pia6821.fetchFromSerialPort();
  }
  return;
}


/*
byte lastButton;
char seconds = 0;
char minutes = 0;
uint32_t  wait1Sec, wait250mSec;
int walkingLed = 0;
int potValue = 0;


void scrollText(String text, int speed) {
  String seg4;

  text = "   " + text + "  ";

  for (unsigned int p=0; p < text.length(); p++) {
      seg4 = text.substring(p, (p+4));
      MFS.write(seg4.c_str());
      delay(speed);
  }

} // scrollText();


void animateDisplay() {
  Serial.println("All LED's ON");
  MFS.writeLeds(LED_ALL, ON);

  scrollText("Retroshield 6502", 200);

  Serial.println("All LED's OFF");
  MFS.writeLeds(LED_ALL, OFF);
  delay(50);
  Serial.println("LED 1 ON");
  MFS.writeLeds(LED_1, ON);
  delay(50);
  Serial.println("LED 2 ON");
  MFS.writeLeds(LED_2, ON);
  delay(50);
  Serial.println("LED 3 ON");
  MFS.writeLeds(LED_3, ON);
  delay(50);
  Serial.println("LED 4 ON");
  MFS.writeLeds(LED_4, ON);
  delay(50);
  Serial.println("LED 1 OFF");
  MFS.writeLeds(LED_1, OFF);
  delay(50);
  Serial.println("LED 2 OFF");
  MFS.writeLeds(LED_2, OFF);
  delay(50);
  Serial.println("LED 3 OFF");
  MFS.writeLeds(LED_3, OFF);
  delay(100);

  Serial.println("All LED's OFF");
  MFS.writeLeds(LED_ALL, OFF);

} // animateDisplay()



class LedInterface {

	public:
	void portOut(byte index, byte pinMask, byte pinBits) {
		if (index > 0) {
			return;
		}
		byte ledsOff = (~pinBits) & (pinMask & LED_ALL);
		MFS.writeLeds(ledsOff, OFF);
		byte ledsOn = pinBits  & (pinMask & LED_ALL);
		MFS.writeLeds(ledsOn, ON);
	}

};
*/

////////////////////////////////////////////////////////////////////
// Setup
////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);

/*
  // put your setup code here, to run once:
   Timer1.initialize();
   MFS.initialize(&Timer1); // initialize multi-function shield library
   MFS.write(0);


   //animateDisplay();
   //MFS.write(0);

   //MFS.writeLeds(LED_1, ON);

   LedInterface ledInterface;
   ledInterface.portOut(0, 0x0f, 0x0A);
   Serial.println("LEDs 0xA");
   delay(1000);
   ledInterface.portOut(0, 0x0f, 0x05);
   Serial.println("LEDs 0x5");
   delay(1000);
   ledInterface.portOut(0, 0x0f, 0x0F);
   Serial.println("LEDs 0xF");
   delay(1000);
   ledInterface.portOut(0, 0x0f, 0x00);
   Serial.println("LEDs 0x0");
   delay(1000);
*/
  // Retroshield

  Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");
  Serial.println("\n");
  Serial.println("Configuration:");
  Serial.println("==============");
  //Serial.print("SRAM Size:  "); Serial.print(RAM_END - RAM_START + 1, DEC); Serial.println(" Bytes");
  //Serial.print("SRAM_START: 0x"); Serial.println(RAM_START, HEX);
  //Serial.print("SRAM_END:   0x"); Serial.println(RAM_END, HEX);
  Serial.println("");
  Serial.println("=======================================================");
  Serial.println("> WOZ Monitor by Steve Wozniak in FF00-FFFF");
  Serial.println("=======================================================");
  Serial.println("Notes/examples to use monitor:");
  Serial.println("Enter FF00.FFFF to dump memory from FF00 to EFFF");
  Serial.println("=======================================================");

  SystemBoard::init();

  Serial.println("\n");
}


////////////////////////////////////////////////////////////////////
// Loop()
////////////////////////////////////////////////////////////////////

void loop()
{
  // Loop forever
  for(;;)
  {
    serialEvent0();
    SystemBoard::clockTick();
  }
}

