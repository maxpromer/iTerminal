#ifndef __IiLEDPlus_CPP__
#define __IiLEDPlus_CPP__

#include "iLEDPlus.h"
#include "esp_log.h"

uint8_t buffDisplay[16]; // 16x8
uint8_t font8x4[16 + 1][4] = {
    { 0x7c, 0x44, 0x7c, 0x00 }, // 0
    { 0x00, 0x7c, 0x00, 0x00 }, // 1
    { 0x5c, 0x54, 0x74, 0x00 }, // 2
    { 0x54, 0x54, 0x7c, 0x00 }, // 3
    { 0x70, 0x10, 0x7c, 0x00 }, // 4
    { 0x74, 0x54, 0x5c, 0x00 }, // 5
    { 0x7c, 0x54, 0x5c, 0x00 }, // 6
    { 0x40, 0x40, 0x7c, 0x00 }, // 7
    { 0x7c, 0x54, 0x7c, 0x00 }, // 8
    { 0x74, 0x54, 0x7c, 0x00 }, // 9
    { 0x3c, 0x50, 0x3c, 0x00 }, // A
    { 0x7c, 0x54, 0x38, 0x00 }, // B
    { 0x38, 0x44, 0x44, 0x00 }, // C
    { 0x7c, 0x44, 0x38, 0x00 }, // D
    { 0x7c, 0x54, 0x54, 0x00 }, // E
    { 0x7c, 0x50, 0x50, 0x00 }, // F
    { 0x10, 0x10, 0x10, 0x00 }  // -
};

iLEDPlus::iLEDPlus()
{
	polling_ms = 40;
}

void iLEDPlus::init(void)
{
	// Debug
	esp_log_level_set("*", ESP_LOG_VERBOSE);

	// clear error flag
	error = false;
	// clear initialized flag
	initialized = true;
}

int iLEDPlus::prop_count(void)
{
	// not supported
	return 0;
}

bool iLEDPlus::prop_name(int index, char *name)
{
	// not supported
	return false;
}

bool iLEDPlus::prop_unit(int index, char *unit)
{
	// not supported
	return false;
}

bool iLEDPlus::prop_attr(int index, char *attr)
{
	// not supported
	return false;
}

bool iLEDPlus::prop_read(int index, char *value)
{
	// not supported
	return false;
}

bool iLEDPlus::prop_write(int index, char *value)
{
	// not supported
	return false;
}
// --------------------------------------

void iLEDPlus::process(Driver *drv)
{

}

uint8_t* iLEDPlus::numberToBuffer(double n, int base, int decimal) {
	memset(buffDisplay, 0, sizeof(buffDisplay));
	char strBuff[20];
	memset(strBuff, 0, 20);
	if (base == 10) {
		sprintf(strBuff, "%f", n);
		ESP_LOGI("iLEDPlus", "%s", strBuff);
		while(1) {
			int n = strlen(strBuff);
			if (strBuff[n - 1] == '0') {
				strBuff[n - 1] = 0;
			} else if (strBuff[n - 1] == '.') {
				strBuff[n - 1] = 0;
				break;
			} else {
				break;
			}
		}
		ESP_LOGI("iLEDPlus", "%s", strBuff);
	} else if (base == 16 || base == 2 || base == 8) {
		itoa(n, strBuff, base);
	}
	
	int len = strlen(strBuff);
	int nextIndex = 0;
	bool hasDot = false;
	for (int i=0;i<len;i++) {
		if (strBuff[i] == '.') {
			hasDot = true;
			break;
		}
	}
	if (len < (hasDot ? 5 : 4)) {
		nextIndex = (hasDot ? 5 : 4) - len;
	}
	int i = 0;
	for (;;) {
		char c = strBuff[i];
		i++;
		if (c == '.' && nextIndex > 0) {
			buffDisplay[((nextIndex - 1) * 4) + 3] |= 0x04;
			continue;
		}
		memcpy(&buffDisplay[(nextIndex * 4) + 0], font8x4[((c >= '0' && c <= '9') ? c - '0' : c - 'a' + 10)], 4);
		nextIndex++;
		if (nextIndex == 4) {
			break;
		}
	}
	return buffDisplay;
}

#endif