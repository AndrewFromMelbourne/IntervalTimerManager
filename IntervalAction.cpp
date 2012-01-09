#include "IntervalAction.h"
#include "IntervalTimerManager.h"

IntervalAction:: IntervalAction(
	uint8_t id,
	uint32_t interval,
	IntervalTimerManagerInterface& itmi)
:
	_id(id),
	_interval(interval),
	_nextActionTime(0)
{
	itmi.manageAction(this);
}
