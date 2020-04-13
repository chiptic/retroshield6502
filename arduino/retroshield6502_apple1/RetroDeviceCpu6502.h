/*
 * RetroShieldCpu6502.h
 *
 *  Created on: 13 apr. 2020
 *      Author: Windows
 */

#ifndef RETROSHIELDCPU6502_H_
#define RETROSHIELDCPU6502_H_


#include <avr/pgmspace.h>
#include "pins2_arduino.h"
#include <DIO2.h>

#include "RetroShieldAdapter.h"

/**
 *  The CPU is connected to the 36 pins connector at the shorter end of the Mega 2650 board.
 *  These pins are the Arduino Digital Pins 22 to 53 (together with 2 pins VCC and 2 pins GND)
 *  The Arduino connector pins are allocated to AVR Mega 2650 ports PA, PB, PC, PD, PG and PL
 *  and connected to the 6502 CPU as follows:
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
 *  38 : PD7		RESET_N	(cpu in)
 *  -- Control bus pins on PG --
 *  39 : PG2		RDY		(cpu in)
 *  40 : PG1		RW_N	(cpu out)
 *  41 : PG0		SO_N	(cpu in)
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
 *  50 : PB3		IRQ_N	(cpu in)
 *  51 : PB2		NMI_N 	(cpu in)
 *  52 : PB1		PHI0	(cpu in)
 *  53 : PB0		Q, not connected for 6502
 *
 *  The 6502 pins PHI1 (OUT), PHI2 (OUT), SYNC are not connected.
 *  For the WD65S02 the pins VP_N (OUT), ML_N (OUT), BE are not connected.
 *
 *  To read the address presented by the CPU use ports PINC and PINA.
 *  To read data from or write data to the CPU use port PINL and PORTL.
 *  To reset the CPU use output pin PD7 and keep low for 25 clock cycles.
 *  To find out if CPU wants to read or write use input pin PG1.
 *  To cycle the CPU clock use output pin PB1.
 *
 *  The AVR ports all have a port data direction register DDRx,
 *  a port data input register PINx and port data output register PORTx.
 *  This CPU device interface class manipulates the Arduino AVR ports.
 *
 *
 *  65C02 HW CONSTRAINTS
 * 	1- RESET_N must be asserted at least 2 clock cycles.
 *	2- CLK can not be low more than 5 microseconds.  Can be high indefinitely.
 *
 */

class RetroDeviceCpu6502 : public RetroShieldAdapter {

public:

	__attribute__((always_inline))
	static inline void openCpuDataAccessPhase() {
		// Start data access phase for CPU
		driveClockPinHigh();   // Phi0 goes high
	}

	__attribute__((always_inline))
	static inline void closeCpuDataAccessPhase() {
		// end data access phase and start next cycle
		driveClockPinLow();    // Phi0 goes low

		// natural delay for DATA Hold time (t_HR)
		// ensure DATA port is output from CPU
		setDataBusPortAsInput();
	}

	__attribute__((always_inline))
	static inline byte isCpuDataFetchCycle() {
		// Read R/W pin state supplied by CPU
		return readCpuReadWritePinState();
	}



	static void initCpuDevicePorts()	{
		// Set data direction registers
		setDataBusDataDirectionPort(PORT_DATADIR_INPUT);
		setAddressBusDataDirectionPorts(PORT_DATADIR_INPUT);

		// Set data direction for pins
		pinMode(MPU_OUTP_RW_N,   INPUT);
		pinMode(MPU_INP_RST_N, 	 OUTPUT);
		pinMode(MPU_INP_RDY,     OUTPUT);
		pinMode(MPU_INP_SO_N,    OUTPUT);
		pinMode(MPU_INP_IRQ_N,   OUTPUT);
		pinMode(MPU_INP_NMI_N,   OUTPUT);
		pinMode(MPU_INP_PHI0,    OUTPUT);
		pinMode(MPU_INP_GPIO,    OUTPUT);

		assertReset();
		digitalWrite(MPU_INP_PHI0, LOW);
		digitalWrite(MPU_INP_GPIO, HIGH);
	}


	static void assertReset()
	{
	  // Drive RESET conditions
	  digitalWrite(MPU_INP_RST_N, LOW);
	  digitalWrite(MPU_INP_IRQ_N, HIGH);
	  digitalWrite(MPU_INP_NMI_N, HIGH);
	  digitalWrite(MPU_INP_RDY, HIGH);
	  digitalWrite(MPU_INP_SO_N, HIGH);
	}

	static void releaseReset()
	{
	  // Drive RESET conditions
	  digitalWrite(MPU_INP_RST_N, HIGH);
	}


	static void driveResetPin(uint8_t val) {
		  digitalWrite(MPU_INP_RST_N, val);
	}

	static void driveInterruptRequestPin(uint8_t val) {
		  digitalWrite(MPU_INP_IRQ_N, val);
	}

	static void driveNonMaskableInterruptPin(uint8_t val) {
		  digitalWrite(MPU_INP_NMI_N, val);
	}

	static void driveReadyPin(uint8_t val) {
		  digitalWrite(MPU_INP_RDY, val);
	}

	static void driveSetOverflowPin(uint8_t val) {
		  digitalWrite(MPU_INP_SO_N, val);
	}

protected:

	constexpr static const uint8_t 	MPU_INP_RST_N 	= HDR_PIN_38_PD7;
	constexpr static const uint8_t 	MPU_INP_RDY     = HDR_PIN_39_PG2;
	constexpr static const uint8_t 	MPU_OUTP_RW_N   = HDR_PIN_40_PG1;
	constexpr static const uint8_t 	MPU_INP_SO_N    = HDR_PIN_41_PG0;

	constexpr static const uint8_t 	MPU_INP_IRQ_N   = HDR_PIN_50_PB3;
	constexpr static const uint8_t 	MPU_INP_NMI_N   = HDR_PIN_51_PB2;
	constexpr static const uint8_t 	MPU_INP_PHI0    = HDR_PIN_52_PB1;
	constexpr static const uint8_t 	MPU_INP_GPIO    = HDR_PIN_53_PB0;

};





#endif /* RETROSHIELDCPU6502_H_ */
