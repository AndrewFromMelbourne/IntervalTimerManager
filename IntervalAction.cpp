#include "IntervalAction.h"
#include "IntervalTimerManager.h"

//-------------------------------------------------------------------------
// Copyright (C) 2012 Andrew Duncan.
//
// This software may be distributed and modified under the terms of the GNU
// General Public License version 2 (GPL2) as published by the Free Software
// Foundation and appearing in the file GPL2.TXT included in the packaging
// of this file. Please note that GPL2 Section 2[b] requires that all works
// based on this software must also be made publicly available under the
// terms of the GPL2 ("Copyleft").
//
//-------------------------------------------------------------------------

IntervalAction:: IntervalAction(
	uint8_t id,
	uint32_t interval,
	IntervalTimerManagerInterface& itmi)
:
	_id(id),
	_interval(interval),
	_nextActionTime(0),
	_active((interval > 0) ? true : false)
{
	itmi.manageAction(this);
}

//-------------------------------------------------------------------------

void
IntervalAction:: setInterval(
	uint32_t interval)
{
	_interval = interval;

	if (interval == 0)
	{
		_active = false;
	}
}

//-------------------------------------------------------------------------

boolean
IntervalAction:: activate()
{
	if (_interval > 0)
	{
		_active = true;
		_nextActionTime = millis() + _interval;
	}

	return _active;
}
