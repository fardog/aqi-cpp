#include "AQI.h"

using namespace AQI;

Measurement::Measurement(Pollutant pollutant, float value) : pollutant(pollutant), value(value)
{
}

const int Measurement::PM2_5_BREAKPOINT_COUNT = 7;
Measurement::Breakpoint Measurement::PM2_5_BREAKPOINTS[7] = {
    {0.0, 12.1, 0, 50},
    {12.1, 35.5, 51, 100},
    {35.5, 55.5, 101, 150},
    {55.5, 150.5, 151, 200},
    {150.5, 250.5, 201, 300},
    {250.5, 350.5, 301, 400},
    {350.5, 500.5, 401, 500}};
Measurement::BreakpointDef Measurement::PM2_5_DEF = {PM2_5_BREAKPOINTS, PM2_5_BREAKPOINT_COUNT};

const int Measurement::PM10_BREAKPOINT_COUNT = 7;
Measurement::Breakpoint Measurement::PM10_BREAKPOINTS[7] = {
    {0, 55, 0, 50},
    {55, 155, 51, 100},
    {155, 255, 101, 150},
    {255, 355, 151, 200},
    {355, 425, 201, 300},
    {425, 505, 301, 400},
    {505, 605, 401, 500}};
Measurement::BreakpointDef Measurement::PM10_DEF = {PM10_BREAKPOINTS, PM10_BREAKPOINT_COUNT};

Measurement::Breakpoint *Measurement::getBreakpoint()
{
    BreakpointDef def = getBreakpointDef();

    for (int i = 0; i < def.count; i++)
    {
        Breakpoint *bp = &def.breakpoints[i];
        if (value >= bp->min && value < bp->max)
        {
            return bp;
        }
    }

    return nullptr;
}

Measurement::BreakpointDef Measurement::getBreakpointDef()
{
    switch (pollutant)
    {
    case Pollutant::PM2_5:
        return PM2_5_DEF;
    case Pollutant::PM10:
        return PM10_DEF;
    }
}

Pollutant Measurement::getPollutant()
{
    return pollutant;
}

float Measurement::getValue()
{
    return value;
}

float Measurement::getAQI()
{
    Breakpoint *pb = getBreakpoint();
    if (!pb)
    {
        return -1;
    }

    return (pb->iMax - pb->iMin) * (value - pb->min) / (pb->max - pb->min) + pb->iMin;
}

Measurements::Measurements(Measurement *measurements, int count) : measurements(measurements), count(count), value(measurements[0])
{
    calculateAQI();
}

void Measurements::calculateAQI()
{
    for (int i = 0; i < count; i++)
    {
        if (value.getAQI() < measurements[i].getAQI())
        {
            value = measurements[i];
        }
    }
}

float Measurements::getAQI()
{
    return value.getAQI();
}

Pollutant Measurements::getPollutant()
{
    return value.getPollutant();
}
