#ifndef __ILEDPLUS_H__
#define __ILEDPLUS_H__

#include "driver.h"
#include "device.h"
#include "kidbright32.h"
#include "ht16k33.h"

#include <math.h>
#include <string.h>
#include <inttypes.h>

class iLEDPlus : public Device
{
private:

public:
	// constructor
	iLEDPlus();

	// override
	void init(void);
	void process(Driver *drv);
	int prop_count(void);
	bool prop_name(int index, char *name);
	bool prop_unit(int index, char *unit);
	bool prop_attr(int index, char *attr);
	bool prop_read(int index, char *value);
	bool prop_write(int index, char *value);

	// method
	uint8_t* numberToBuffer(double n, int base=10, int decimal=0) ;

};

#endif