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

class BlinkAction
:
    public IntervalAction
{
public:

    BlinkAction(
        uint8_t pin,
        uint8_t id,
        uint32_t interval,
        IntervalTimerManagerInterface& itmi)
    :
        _pin(pin),
        IntervalAction(id, interval, itmi)
    {
        pinMode(_pin, OUTPUT);
    }
    
    virtual void action();

private:

    uint8_t _pin;
};

//-------------------------------------------------------------------------

void BlinkAction::action()
{
    digitalWrite(_pin, !digitalRead(_pin));
}

//-------------------------------------------------------------------------

IntervalTimerManager<1> blinkIntervalManager;

BlinkAction a1(13, 0, 1000, blinkIntervalManager);

//-------------------------------------------------------------------------

void setup() 
{
    a1.activate();
}
 
//-------------------------------------------------------------------------

void loop() 
{  
    blinkIntervalManager.task();
}
