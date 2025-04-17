#include "Scheduler.h"

static uint32_t scheduledEvents;

void addSchedulerEvent(uint32_t Event){
	scheduledEvents |= Event;
}

void removeSchedulerEvent(uint32_t Event){
	scheduledEvents &= ~Event;
}

uint32_t getScheduledEvents(){
	return scheduledEvents;
}
