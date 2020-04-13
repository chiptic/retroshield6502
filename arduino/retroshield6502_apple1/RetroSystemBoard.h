/*
 * RetroSystemBoard.h
 *
 * Created on: 13 apr. 2020
 */

#ifndef RETROSYSTEMBOARD_H_
#define RETROSYSTEMBOARD_H_

#include <avr/pgmspace.h>
#include "pins2_arduino.h"
#include <DIO2.h>

#include "RetroDeviceCpu6502.h"


class DeviceAddressDef {
public:

	constexpr DeviceAddressDef(const unsigned char* addrPtr, const word baseAddr, const word lastAddr)
		:  _baseAddr(baseAddr), _lastAddr(lastAddr), _addrPtr(addrPtr) {
    }
    constexpr word getBaseAddr() const {return _baseAddr;}
    constexpr word getLastAddr() const {return _lastAddr;}
    constexpr const unsigned char* getAddrPtr() const {return _addrPtr;}

protected:
    const word _baseAddr;
    const word _lastAddr;
    const byte *_addrPtr;
};



class RetroSystemBoard {
public:

	__attribute__((always_inline))
	static inline byte isCpuDataFetchCycle() {
		return RetroDeviceCpu6502::isCpuDataFetchCycle();
	}


	__attribute__((always_inline))
	static inline byte fetchDataFromCpu() {
		return RetroDeviceCpu6502::fetchDataFromCpu();
	}

	__attribute__((always_inline))
	static inline void supplyDataToCpu(byte val) {
		RetroDeviceCpu6502::supplyDataToCpu(val);
	}


    __attribute__((always_inline))
    static inline byte isAddressOfDevice(const DeviceAddressDef addrDef, const word busAddr) {
		return ((busAddr >= addrDef.getBaseAddr()) && (busAddr <= addrDef.getLastAddr()));
    }

    __attribute__((always_inline))
    static inline byte isAddressOfBottomDevice(const DeviceAddressDef addrDef, const word busAddr) {
		return (busAddr <= addrDef.getLastAddr());
    }

    __attribute__((always_inline))
    static inline byte isAddressOfTopDevice(const DeviceAddressDef addrDef, const word busAddr) {
		return (busAddr >= addrDef.getBaseAddr());
    }


    __attribute__((always_inline))
    static inline void transferProgramDataByte(const DeviceAddressDef addrDef, const word busAddr) {
    	if (RetroDeviceCpu6502::isCpuDataFetchCycle()) {
        	// Read a byte from the program address space with a 16-bit (near) address.
    		RetroDeviceCpu6502::supplyDataToCpu(pgm_read_byte_near(addrDef.getAddrPtr() + (busAddr - addrDef.getBaseAddr())));
    	} else {

    	}
    }

    __attribute__((always_inline))
    static inline void transferMemoryDataByte(const DeviceAddressDef addrDef, const word busAddr) {
    	if (RetroDeviceCpu6502::isCpuDataFetchCycle()) {
    		RetroDeviceCpu6502::supplyDataToCpu(addrDef.getAddrPtr()[busAddr - addrDef.getBaseAddr()]);
    	} else {
    		((byte *) (addrDef.getAddrPtr()))[busAddr - addrDef.getBaseAddr()] = RetroShieldAdapter::fetchDataFromCpu();
    	}
    }



	static void initCpuDeviceAdapter()	{
		RetroDeviceCpu6502::initCpuDevicePorts();
	}

	static void assertReset()	{
		RetroDeviceCpu6502::assertReset();
	}

	static void releaseReset()	{
		RetroDeviceCpu6502::releaseReset();
	}

    __attribute__((always_inline))
    static inline void startCpuDataAccessPhase() {
    	RetroDeviceCpu6502::openCpuDataAccessPhase();
    }

    __attribute__((always_inline))
    static inline void finishCpuDataAccessPhase() {
    	RetroDeviceCpu6502::closeCpuDataAccessPhase();
    }

    __attribute__((always_inline))
    static inline word readCpuBusAddress() {
		return RetroDeviceCpu6502::readCpuBusAddress();
    }


};



#endif /* RETROSYSTEMBOARD_H_ */
