//-------------------------------------------------------------------------
//
// The MIT License (MIT)
//
// Copyright (c) 2013 Andrew Duncan
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------

#ifndef INTERVAL_TIMER_H
#define INTERVAL_TIMER_H

//-------------------------------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>

//-------------------------------------------------------------------------

class IntervalTimerManagerInterface;

//-------------------------------------------------------------------------

class IntervalAction 
{
public:  

    IntervalAction(
        uint8_t id,
        uint32_t interval,
        IntervalTimerManagerInterface& itmi);

    virtual void action() {}

    void reset() { _nextActionIn = _interval; }

    uint8_t getId() const { return _id; }

    uint32_t getInterval() const { return _interval; }
    void setInterval(uint32_t interval);

    uint32_t getNextActionIn() const { return _nextActionIn; }
    void setNextActionIn(uint32_t nextActionIn)
    {
        _nextActionIn = nextActionIn;
    }

    boolean activate();
    void deactivate() { _active = false; }
    boolean isActive() const { return _active; }

private: 

    uint8_t _id;
    uint32_t _interval;     
    uint32_t _nextActionIn;
    boolean _active;
};

//-------------------------------------------------------------------------

#endif
