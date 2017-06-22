#ifndef CONTROL_H
#define CONTROL_H

typedef struct {
	float ref;
	float sense;
	float integr;
	float p;
	float i;
	float out_max;
	float out_min;
	float out;
} pi_ctrler_t;

typedef struct {
	float ref;
	float sense;
	float p;
	float out_max;
	float out_min;
	float out;
} p_ctrler_t;

void p_init(p_ctrler_t *ctrler);
void pi_init(pi_ctrler_t *ctrler);

float p_control(p_ctrler_t *ctrler);
float pi_control(pi_ctrler_t *ctrler);

#endif /* CONTROL_H */