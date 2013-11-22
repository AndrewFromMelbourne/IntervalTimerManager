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

#ifndef INTERVAL_TIMER_MANAGER_H
#define INTERVAL_TIMER_MANAGER_H

//-------------------------------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>

#include "IntervalAction.h"

//-------------------------------------------------------------------------

class IntervalTimerManagerInterface
{
public:

    virtual void manageAction(IntervalAction* ia) {}
};

//-------------------------------------------------------------------------

template<uint8_t NumberOfTimers>
class IntervalTimerManager
:
    public IntervalTimerManagerInterface
{
public:

    //---------------------------------------------------------------------

    IntervalTimerManager()
    :
        _previous(0),
        _timersManaged(0)
    {
    }
  
    //---------------------------------------------------------------------

    virtual void
    manageAction(
        IntervalAction* ia)
    {
        if (_timersManaged < NumberOfTimers)
        {
            _actions[_timersManaged++] = ia;

            if (ia->isActive())
            {
                ia->reset();
            }
        }
    }

    //---------------------------------------------------------------------

    void
    task()
    {
        uint32_t now = millis();
        uint32_t elapsed = now - _previous;

        if (_previous > now)
        {
            elapsed = (0xFFFFFFFF - _previous) + now + 1;
        }

        if ((elapsed > 0) && (_previous != 0))
        {
            for (uint8_t i = 0; i < _timersManaged; ++i) 
            {
                IntervalAction* ia = _actions[i];

                if (ia->isActive())
                {
                    uint32_t nextActionIn = ia->getNextActionIn();

                    if (nextActionIn > 0)
                    {
                        if (nextActionIn > elapsed)
                        {
                            nextActionIn -= elapsed;
                        }
                        else
                        {
                            nextActionIn = 0;
                        }

                        ia->setNextActionIn(nextActionIn);
                    }

                    if (nextActionIn == 0)
                    {
                        ia->action();

                        if (ia->isActive())
                        {
                            ia->reset();
                        }
                    }
                }
            }
        }

        _previous = now;
    }

    //---------------------------------------------------------------------

private:

    uint32_t _previous;
    uint8_t _timersManaged;
    IntervalAction* _actions[NumberOfTimers];
};

//-------------------------------------------------------------------------

#endif
