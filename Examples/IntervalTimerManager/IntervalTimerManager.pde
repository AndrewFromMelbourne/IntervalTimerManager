#include "IntervalTimerManager.h"

//-------------------------------------------------------------------------

class SerialAction
:
    public IntervalAction
{
public:

    SerialAction(
        int id,
        int interval,
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

SerialAction a1(0, 1, serialIntervalManager);

//-------------------------------------------------------------------------

void setup() 
{
    Serial.begin(115200); 
    Serial.println("Starting Interval Timer Manager Test.");
}
 
//-------------------------------------------------------------------------

void loop() 
{  
    serialIntervalManager.task();
}
