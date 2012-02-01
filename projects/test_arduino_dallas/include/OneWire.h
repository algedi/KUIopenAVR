#ifndef DS18B20_h
#define DS18B20_h

#include <inttypes.h>

// you can exclude DS18B20_search by defining that to 0
#ifndef DS18B20_SEARCH
#define DS18B20_SEARCH 1
#endif

// You can exclude CRC checks altogether by defining this to 0
#ifndef DS18B20_CRC
#define DS18B20_CRC 1
#endif

// Select the table-lookup method of computing the 8-bit CRC
// by setting this to 1.  The lookup table no longer consumes
// limited RAM, but enlarges total code size by about 250 bytes
#ifndef DS18B20_CRC8_TABLE
#define DS18B20_CRC8_TABLE 0
#endif

// You can allow 16-bit CRC checks by defining this to 1
// (Note that DS18B20_CRC must also be 1.)
#ifndef DS18B20_CRC16
#define DS18B20_CRC16 0
#endif

#define FALSE 0
#define TRUE  1

class DS18B20
{
	private:
		uint8_t bitmask;
		volatile uint8_t *baseReg;

		// KUI 
//		int nHighByte; 
//		int nLowByte;
//		int nTReading;
//		int nSignBit;
//		int nTc_100;
//		int nWhole;
//		int nFract;

//		char cI;
//		char cPresent;
//		char ccData[12];
//		byte nnAddr[8];
		uint8_t nnData[12];
		uint8_t nnAddr[8];

	#if DS18B20_SEARCH
		// global search state
		unsigned char ROM_NO[8];
		uint8_t LastDiscrepancy;
		uint8_t LastFamilyDiscrepancy;
		uint8_t LastDeviceFlag;
	#endif

  public:
    DS18B20( uint8_t pin);

    // Perform a 1-Wire reset cycle. Returns 1 if a device responds
    // with a presence pulse.  Returns 0 if there is no device or the
    // bus is shorted or otherwise held low for more than 250uS
    uint8_t reset(void);

	// ***************
	// * KUI modific *
	// ***************

	uint16_t ReadDS18B20(void);
	bool IsPositive(void);
	int Read(void);
	int GetCelsius(void);
	int GetDecimal(int nDecimal);

    // Issue a 1-Wire rom select command, you do the reset first.
    void select( uint8_t rom[8]);

    // Issue a 1-Wire rom skip command, to address all on bus.
    void skip(void);

    // Write a byte. If 'power' is one then the wire is held high at
    // the end for parasitically powered devices. You are responsible
    // for eventually depowering it by calling depower() or doing
    // another read or write.
    void write(uint8_t v, uint8_t power = 0);

    // Read a byte.
    uint8_t read(void);

    // Write a bit. The bus is always left powered at the end, see
    // note in write() about that.
    void write_bit(uint8_t v);

    // Read a bit.
    uint8_t read_bit(void);

    // Stop forcing power onto the bus. You only need to do this if
    // you used the 'power' flag to write() or used a write_bit() call
    // and aren't about to do another read or write. You would rather
    // not leave this powered if you don't have to, just in case
    // someone shorts your bus.
    void depower(void);

#if DS18B20_SEARCH
    // Clear the search state so that if will start from the beginning again.
    void reset_search();

    // Look for the next device. Returns 1 if a new address has been
    // returned. A zero might mean that the bus is shorted, there are
    // no devices, or you have already retrieved all of them.  It
    // might be a good idea to check the CRC to make sure you didn't
    // get garbage.  The order is deterministic. You will always get
    // the same devices in the same order.
    uint8_t search(uint8_t *newAddr);
#endif

#if DS18B20_CRC
    // Compute a Dallas Semiconductor 8 bit CRC, these are used in the
    // ROM and scratchpad registers.
    static uint8_t crc8( uint8_t *addr, uint8_t len);

#if DS18B20_CRC16
    // Compute a Dallas Semiconductor 16 bit CRC. Maybe. I don't have
    // any devices that use this so this might be wrong. I just copied
    // it from their sample code.
    static unsigned short crc16(unsigned short *data, unsigned short len);
#endif
#endif
};

#endif
