#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

uint32_t getScheduledEvents();
void addSchedulerEvent(uint32_t Event);
void removeSchedulerEvent(uint32_t Event);

#define LED_TOGGLE_EVENT (1 << 0)
#define LED_DELAY_EVENT (1 << 1)
#define BUTTON_POLL_EVENT (1 << 2)
#define APP_DELAY_FLAG_EVENT (1 << 3)
#define DEVICE_ID_AND_TEMP_EVENT (1 << 4)

#endif
