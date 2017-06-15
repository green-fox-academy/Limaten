#ifndef _FREQ_MEAS_H
#define _FREQ_MEAS_H

#include <stdint.h>

#define OVF_STEPS			(65536)
#define TC1_STEP_TIME_US	(4.0)
#define TC1_STEP_TIME_MS	(TC1_STEP_TIME_US / 1000.0)
#define TC1_STEP_TIME_S		(TC1_STEP_TIME_MS / 1000.0)
#define CS_DEFAULT			(0b011)

void freq_meas_init();
float get_freq();

#endif // _FREQ_MEAS_H