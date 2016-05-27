#include <linux/thermal.h>

#include "thermal_zone.h"

struct thermal_zone_device *pos = NULL, *fcm_tz;
extern struct list_head thermal_tz_list;

int obtiene_thermal_zone()
{
	int temp;

        list_for_each_entry(pos, &thermal_tz_list, node)
        {
                fcm_tz = pos;
                break;
        }

        thermal_zone_get_temp(fcm_tz, &temp);

        printk(KERN_INFO "FanCtlModule: name = %s\n", fcm_tz->type);
        printk(KERN_INFO "FanCtlModule: temp = %d\n", temp);

	return 0;

}
