#include <stdio.h>
#include "LPC17xx.h"
#include <RTL.h>

long global_c1 = 0, global_c2 = 0;

__task void task1(void){
	for(;;){
		global_c1 += 3;
	}
}

__task void task2(void){
	for(;;){
		global_c2 += 2;
	}
}

int main(void){
	SystemInit();
	os_tsk_create(task1, 1);
	os_tsk_create(task2, 1);
	os_tsk_delete_self();

	os_sys_init(task1);
}
