/*
 * RetroDevicePia6821.h
 *
 *  Created on: 13 apr. 2020
 *      Author: Windows
 */

#ifndef RETRODEVICEPIA6821_H_
#define RETRODEVICEPIA6821_H_

#include <avr/pgmspace.h>
#include "pins2_arduino.h"
#include <DIO2.h>

#include "RetroSystemBoard.h"

////////////////////////////////////////////////////////////////////
// 6821 Peripheral
// emulate just enough so keyboard/display works thru serial port.
////////////////////////////////////////////////////////////////////
//

#define KBD   0xd010
#define KBDCR 0xd011
#define DSP   0xd012
#define DSPCR 0xd013

class RetroDevicePia6821  {

  public:
	const word _baseAddr;
	const word _lastAddr;

	byte regKBD;
	byte regKBDDIR;    // Dir register when KBDCR.bit2 == 0
	byte regKBDCR;
	byte regDSP;
	byte regDSPDIR;    // Dir register when DSPCR.bit2 == 0
	byte regDSPCR;

	RetroDevicePia6821(const word baseAddr, const word lastAddr)
		:  _baseAddr(baseAddr), _lastAddr(lastAddr) {
		init();
    }


	void init()
	{
	  regKBD    = 0x00;
	  regKBDDIR = 0x00;
	  regKBDCR  = 0x00;
	  regDSP    = 0x00;
	  regDSPDIR = 0x00;
	  regDSPCR  = 0x00;
	}

	__attribute__((always_inline))
	inline byte readByte(word busAddr)
	{
	  // KBD?
	  if (busAddr == KBD) {
		  if (regKBDCR & 0x02) {
			  // KBD register
			  byte kbdData = regKBD;
			  // clear IRQA bit upon read
			  regKBDCR = regKBDCR & 0x7F;
			  return kbdData;
		  }
		  return regKBDDIR;
	  }

	  // KBDCR?
	  if (busAddr == KBDCR)
	  {
		  // KBDCR register
		  return regKBDCR;
	  }

	  // DSP?
	  if (busAddr == DSP)
	  {
		if (regDSPCR & 0x02) {
			// DSP register
			byte data = regDSP;
			// clear IRQA bit upon read
			regDSPCR = regDSPCR & 0x7F;
			return data;
		}
		return regDSPDIR;
	  }

	  // DSPCR?
	  if (busAddr == DSPCR) {
		// DSPCR register
		return regDSPCR;
	  }

	  return 0;
	}


	__attribute__((always_inline))
	inline void writeByte(word busAddr, byte busData) {

	  // KBD?
	  if (busAddr == KBD) {
		  if (regKBDCR & 0x02) {
			  // KBD register
			  regKBD = busData;
			  return;
		  }
		  regKBDDIR = busData;
	  	  return;
	  }

	  // KBDCR?
	  if (busAddr == KBDCR) {
		  // KBDCR register
		  regKBDCR = busData & 0X7F;
	  	  return;
	  }

	  // DSP?
	  if (busAddr == DSP) {
		  if (regDSPCR & 0x02) {
			  // DSP register
			  if (busData == 0x8D) {
				  // send CR / LF
				  Serial.write("\r\n");
				  return;
			  }

			  Serial.write(regDSP = busData & 0x7F);
			  return;
		  }

		  regDSPDIR = busData;
	  	  return;
	  }

	  // DSPCR?
	  if (busAddr == DSPCR) {
		  // DSPCR register
		  regDSPCR = busData;
	  	  return;
	  }
	}

	inline __attribute__((always_inline))
	void fetchFromSerialPort() {
		// read serial byte only if we can set 6821 interrupt
	    if ((regKBDCR & 0x80) == 0x00) {
	      // stop interrupts while changing 6821 guts
	      cli();
	      // 6821 portA is available
	      // apple1 expects upper case
	      int ch = toupper( Serial.read() );
	      // apple1 expects bit 7 set for incoming characters
	      regKBD = ch | 0x80;
	      // set 6821 interrupt
	      regKBDCR = regKBDCR | 0x80;
	      sei();
	    }
	}


    __attribute__((always_inline))
    inline byte isDeviceAddress(word busAddr) {
		return ((busAddr >= _baseAddr) && (busAddr <= _lastAddr));
    }

    __attribute__((always_inline))
    inline void transferDataByte(word busAddr) {
    	if (RetroSystemBoard::isCpuDataFetchCycle()) {
    		RetroSystemBoard::supplyDataToCpu(readByte(busAddr));
    	} else {
    		writeByte(busAddr, RetroSystemBoard::fetchDataFromCpu());
    	}
    }

};



#endif /* RETRODEVICEPIA6821_H_ */
