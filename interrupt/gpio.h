#ifndef __GPIO_H_
#define __GPIO_H_

	void led_init(void);
	void led_on(int num);
	void led_off(int num);
	void buzzer_init(void);
	void buzzer_on(void);
	void buzzer_init(void);
	void k1_init(void);
	int k1_is_down(void);
	void k_init(void);
	int k_is_down(int num);
	void irq_init(void (*fun)(void));

#endif
