#ifndef INTERVAL_TIMER_H
#define INTERVAL_TIMER_H

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

#include <inttypes.h>

//-------------------------------------------------------------------------

class IntervalTimerManagerInterface;

//-------------------------------------------------------------------------

class IntervalAction 
{
private: 

	uint8_t _id;
	uint32_t _interval;     
	uint32_t _nextActionTime;     

public:  

	IntervalAction(
		uint8_t id,
		uint32_t interval,
		IntervalTimerManagerInterface& itmi);

	virtual void action() {}

	uint8_t getId() const { return _id; }

	uint32_t getInterval() const { return _interval; }
	void setInterval(uint32_t interval) { _interval = interval; }

	uint32_t getNextActionTime() const { return _nextActionTime; }
	void setNextActionTime(uint32_t nextActionTime)
	{
		_nextActionTime = nextActionTime;
	}
};

//-------------------------------------------------------------------------

#endif
