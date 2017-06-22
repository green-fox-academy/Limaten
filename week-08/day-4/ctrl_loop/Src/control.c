#include "control.h"
#include <stdio.h>

#define DEFAULT_P			0.1
#define DEFAULT_PI_P		0.05
#define DEFAULT_PI_I		0.01

void pi_init(pi_ctrler_t *ctrler)
{
	ctrler->i = DEFAULT_PI_I;
	ctrler->p = DEFAULT_PI_P;
	ctrler->ref = 0;
	ctrler->sense = 0;
	ctrler->out = 0;
	ctrler->integr = 0;
	ctrler->out = 0;
	ctrler->out_max = 0;
	ctrler->out_min = 0;
}

void p_init(p_ctrler_t *ctrler)
{
	ctrler->p = DEFAULT_P;
	ctrler->ref = 0;
	ctrler->sense = 0;
	ctrler->out = 0;
	ctrler->out = 0;
	ctrler->out_max = 0;
	ctrler->out_min = 0;
}

float pi_control(pi_ctrler_t *ctrler)
{
	float err = ctrler->ref - ctrler->sense;
	ctrler->integr += err;
	float out = err * ctrler->p + ctrler->integr * ctrler->i;

	if (out < ctrler->out_min) {
		ctrler->integr -= err;
		out = ctrler->out_min;
	} else if (out > ctrler->out_max) {
		ctrler->integr -= err;
		out = ctrler->out_max;
	}

	ctrler->out = out;
	return out;
}

float p_control(p_ctrler_t *ctrler)
{
	float err = ctrler->ref - ctrler->sense;
	float out = err * ctrler->p;

	if (out < ctrler->out_min)
		out = ctrler->out_min;
	else if (out > ctrler->out_max)
		out = ctrler->out_max;

	ctrler->out = out;
	return out;
}
