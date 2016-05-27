#include <linux/kthread.h>
#include <linux/sched.h>

#include "hilo.h"
#include "thermal_zone.h"
#include "sysfs.h"

// task struct para el hilo de kernel
struct task_struct *task;

// Funcion que ejecutara el hilo
int hilo_function(void *data)
{
	printk(KERN_INFO "FanCtlModule: Ejecutando hilo\n");

	while(!kthread_should_stop())
	{
		printk(KERN_INFO "FanCtlModule: Temperatura %d\n", obtiene_temp());
		actualizando_archivo_temp(obtiene_temp());

		schedule_timeout_interruptible(HZ/2);
	}
	return 0;
}

int crea_hilo()
{
	int data = 100;

	// Inicio de hilo de kernel
	task = kthread_run(&hilo_function,(void *) &data,"Hilo");

	return 0;
}

int destruye_hilo()
{
	// terminando hilo
	kthread_stop(task);

	return 0;
	
}
