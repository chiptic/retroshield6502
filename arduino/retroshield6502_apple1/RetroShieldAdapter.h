/*
 * RetroSystemBoard.h
 *
 *  Created on: 13 apr. 2020
 */

#ifndef RETROSHIELDADAPTER_H_
#define RETROSHIELDADAPTER_H_

#include <avr/pgmspace.h>
#include <DIO2.h>

/**
 *  The CPU is connected to the 36 pins connector at the shorter end of the Mega 2650 board.
 *  These pins are the Arduino Digital Pins 22 to 53 (together with 2 pins VCC and 2 pins GND)
 *  The Arduino connector pins are allocated to AVR Mega 2650 ports PA, PB, PC, PD, PG and PL.
 *
 *  -- Address bus low byte pins on PA --
 *  22 : PA0		A0		(cpu out)
 *  23 : PA1		A1		(cpu out)
 *  24 : PA2		A2		(cpu out)
 *  25 : PA3		A3		(cpu out)
 *  26 : PA4		A4		(cpu out)
 *  27 : PA5		A5		(cpu out)
 *  28 : PA6		A6		(cpu out)
 *  29 : PA7		A7		(cpu out)
 *  -- Address bus high byte pins on PC --
 *  30 : PC7 		A15		(cpu out)
 *  31 : PC6		A14		(cpu out)
 *  32 : PC5		A13		(cpu out)
 *  33 : PC4		A12		(cpu out)
 *  34 : PC3		A11		(cpu out)
 *  35 : PC2		A10		(cpu out)
 *  36 : PC1		A9		(cpu out)
 *  37 : PC0		A8		(cpu out)
 *  -- Control bus pins on PD --
 *  38 : PD7		RESET	(cpu in)
 *  -- Control bus pins on PG --
 *  39 : PG2
 *  40 : PG1		WR		(cpu out)
 *  41 : PG0
 *  -- Data bus pins on PL ---
 *  42 : PL7		D7		(bidir)
 *  43 : PL6		D6		(bidir)
 *  44 : PL5		D5		(bidir)
 *  45 : PL4		D4		(bidir)
 *  46 : PL3		D3		(bidir)
 *  47 : PL2		D2		(bidir)
 *  48 : PL1		D1		(bidir)
 *  49 : PL0		D0		(bidir)
 *  -- Control bus pins on PB --
 *  50 : PB3		INT		(cpu in)
 *  51 : PB2		NMI 	(cpu in)
 *  52 : PB1		CLOCK	(cpu in)
 *  53 : PB0
 *
 *  The AVR ports all have a port data direction register DDRx,
 *  a port data input register PINx and port data output register PORTx.
 *  This CPU device interface class manipulates the Arduino AVR ports.
 */

class RetroShieldAdapter {

public:


	__attribute__((always_inline))
	static inline void driveClockPinHigh() {
		// CPU clock input connected to port PB pin 2 for 6809, 6502 & Z80.
		// Fast routine to drive clock signal high; faster than digitalWrite
		// required to meet >100kHz clock freq for 6809e.
		// 6502 & z80 do not have this requirement.
		PORTB = PORTB | PB2;
	}

	__attribute__((always_inline))
	static inline void driveClockPinLow() {
		// CPU clock input connected to port PB pin 2 for 6809, 6502 & Z80.
		// Fast routine to drive clock signal low; faster than digitalWrite
		// required to meet >100kHz clock freq for 6809e.
		// 6502 & z80 do not have this requirement.
		PORTB = PORTB & (~PB2);
	}

	// CPU addressbus is connected to ports PC and PA for 6809, 6502 & Z80.
	__attribute__((always_inline))
	static inline word readCpuBusAddress() {
		// Read address from ports on CPU address bus
		return (word) (PINC << 8 | PINA);
	}

	__attribute__((always_inline))
	static inline byte readCpuReadWritePinState() {
		// CPU R/W or WR output connected to port PG pin 2 for 6809, 6502 & Z80.
		// Read R/W pin state supplied by CPU
		return (PING & PING2);
	}

	// CPU databus is connected to port PL for 6809, 6502 & Z80.
	__attribute__((always_inline))
	static inline byte fetchDataFromCpu() {
		// ensure DATA port is output from CPU
		setDataBusPortAsInput();

		// Fetch value coming CPU
		return PINL;
	}

	// CPU databus is connected to port PL for 6809, 6502 & Z80.
	__attribute__((always_inline))
	static inline void supplyDataToCpu(byte val) {
		// change DATA port to output to CPU
		setDataBusPortAsOutput();

		// Supply value going to CPU
		PORTL = val;
	}



protected:

	constexpr static const uint8_t 	HDR_PIN_22_PA0 = 	22;
	constexpr static const uint8_t 	HDR_PIN_23_PA1 = 	23;
	constexpr static const uint8_t 	HDR_PIN_24_PA2 = 	24;
	constexpr static const uint8_t 	HDR_PIN_25_PA3 = 	25;
	constexpr static const uint8_t 	HDR_PIN_26_PA4 = 	26;
	constexpr static const uint8_t 	HDR_PIN_27_PA5 = 	27;
	constexpr static const uint8_t 	HDR_PIN_28_PA6 = 	28;
	constexpr static const uint8_t 	HDR_PIN_29_PA7 = 	29;

	constexpr static const uint8_t 	HDR_PIN_30_PC7 = 	30;
	constexpr static const uint8_t 	HDR_PIN_31_PC6 = 	31;
	constexpr static const uint8_t 	HDR_PIN_32_PC5 = 	32;
	constexpr static const uint8_t 	HDR_PIN_33_PC4 = 	33;
	constexpr static const uint8_t 	HDR_PIN_34_PC3 = 	34;
	constexpr static const uint8_t 	HDR_PIN_35_PC2 = 	35;
	constexpr static const uint8_t 	HDR_PIN_36_PC1 = 	36;
	constexpr static const uint8_t 	HDR_PIN_37_PC0 = 	37;

	constexpr static const uint8_t 	HDR_PIN_38_PD7 = 	38;
	constexpr static const uint8_t 	HDR_PIN_39_PG2 = 	39;
	constexpr static const uint8_t 	HDR_PIN_40_PG1 = 	40;
	constexpr static const uint8_t 	HDR_PIN_41_PG0 = 	41;

	constexpr static const uint8_t 	HDR_PIN_42_PL7 = 	42;
	constexpr static const uint8_t 	HDR_PIN_43_PL6 = 	43;
	constexpr static const uint8_t 	HDR_PIN_44_PL5 = 	44;
	constexpr static const uint8_t 	HDR_PIN_45_PL4 = 	45;
	constexpr static const uint8_t 	HDR_PIN_46_PL3 = 	46;
	constexpr static const uint8_t 	HDR_PIN_47_PL2 = 	47;
	constexpr static const uint8_t 	HDR_PIN_48_PL1 = 	48;
	constexpr static const uint8_t 	HDR_PIN_49_PL0 = 	49;

	constexpr static const uint8_t 	HDR_PIN_50_PB3 = 	50;
	constexpr static const uint8_t 	HDR_PIN_51_PB2 = 	51;
	constexpr static const uint8_t 	HDR_PIN_52_PB1 = 	52;
	constexpr static const uint8_t 	HDR_PIN_53_PB0 = 	53;


	constexpr static const byte PORT_DATADIR_INPUT = 0x00;
	constexpr static const byte PORT_DATADIR_OUTPUT = 0xFF;


	__attribute__((always_inline))
	inline static void setDataBusDataDirectionPort(byte val) {
		// Set data direction for port L on CPU data bus
		DDRL = val; // Data direction for Arduino port L
	}

	__attribute__((always_inline))
	inline static void setAddressBusDataDirectionPorts(byte val) {
		// Set data direction for ports on CPU address bus low
		DDRC = val; // Data direction for Arduino port C
		DDRA = val; // Data direction for Arduino port A
	}

	__attribute__((always_inline))
	inline static void setDataBusPortAsInput() {
		setDataBusDataDirectionPort(PORT_DATADIR_INPUT);
	}

	__attribute__((always_inline))
	inline static void setDataBusPortAsOutput() {
		setDataBusDataDirectionPort(PORT_DATADIR_OUTPUT);
	}


	__attribute__((always_inline))
	inline static void setAddressBusPortsAsInput() {
		setAddressBusDataDirectionPorts(PORT_DATADIR_INPUT);
	}

};


#endif /* RETROSHIELDADAPTER_H_ */
