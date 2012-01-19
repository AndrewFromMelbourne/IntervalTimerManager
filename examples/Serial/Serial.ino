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

class SerialAction
:
    public IntervalAction
{
public:

    SerialAction(
        uint8_t id,
        uint32_t interval,
        IntervalTimerManagerInterface& itmi)
    :
        IntervalAction(id, interval, itmi)
    {
    }
    
    virtual void action();
};

//-------------------------------------------------------------------------

void SerialAction::action()
{
    Serial.print("action ");
    Serial.print(millis(), DEC);
    Serial.println("");
}

//-------------------------------------------------------------------------

IntervalTimerManager<1> serialIntervalManager;

SerialAction a1(0, 1000, serialIntervalManager);

//-------------------------------------------------------------------------

void setup() 
{
    Serial.begin(115200); 
    Serial.println("Starting Interval Timer Manager Test.");
	a1.activate();
}
 
//-------------------------------------------------------------------------

void loop() 
{  
    serialIntervalManager.task();
}
