/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define PWM_B14 DT_ALIAS(pwm_led0)

#define STEP_SIZE PWM_USEC(10)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct pwm_dt_spec pwm_ledb14 = PWM_DT_SPEC_GET(PWM_B14);

int main(void)
{
	int ret;
	bool led_state = true;
	uint32_t pulse_led;

	if (!pwm_is_ready_dt(&pwm_ledb14)) {
		printk("Error: one or more PWM devices not ready\n");
		return 0;
	}

	while (1) {


		for (pulse_led = 0U; pulse_led <= pwm_ledb14.period;
		     pulse_led += STEP_SIZE) {
			ret = pwm_set_pulse_dt(&pwm_ledb14, pulse_led);
			if (ret != 0) {
				printk("Error %d: red write failed\n", ret);
				return 0;
			}
			printf("PWM period : %i ns PWM duty cicle %f\n", pwm_ledb14.period, (float)pulse_led/pwm_ledb14.period);
			k_msleep(SLEEP_TIME_MS);
		}


	}
	return 0;
}
