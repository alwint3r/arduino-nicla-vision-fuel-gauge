#include "MAX17262_Units.h"

Capacity::Capacity(float value) : Unit(value)
{
}

Capacity Capacity::fromLSB(uint16_t lsb)
{
    return Capacity(lsb * lsbSize_);
}

uint16_t Capacity::toLSB()
{
    return value_ / lsbSize_;
}

Percentage::Percentage(uint16_t value) : Unit(value)
{
}

Percentage Percentage::fromLSB(uint16_t lsb)
{
    return Percentage(lsb * lsbSize_);
}

uint16_t Percentage::toLSB()
{
    return value_ / lsbSize_;
}

Voltage::Voltage(float value) : Unit(value)
{
}

Voltage Voltage::fromLSB(uint16_t lsb)
{
    return Voltage(lsb * lsbSize_);
}

float Voltage::volt()
{
    return value_ / 1000.0;
}

uint16_t Voltage::toLSB()
{
    return value_ / lsbSize_;
}

Current::Current(float value) : Unit(value)
{
}

Current Current::fromLSB(uint16_t lsb)
{
    return Current(lsb * lsbSize_);
}

Current Current::fromMilliAmp(uint16_t ma)
{
    return Current(ma / 1000);
}

float Current::ma()
{
    return value_ / 1000.0;
}

uint16_t Current::toLSB()
{
    return value_ / lsbSize_;
}

Temperature::Temperature(float value) : Unit(value)
{
}

Temperature Temperature::fromLSB(uint16_t lsb)
{
    return Temperature(lsb * lsbSize_);
}

uint16_t Temperature::toLSB()
{
    return value_ / lsbSize_;
}

Resistance::Resistance(float value) : Unit(value)
{
}

Resistance Resistance::fromLSB(uint16_t lsb)
{
    return Resistance(lsb * lsbSize_);
}

uint16_t Resistance::toLSB()
{
    return value_ / lsbSize_;
}

Time::Time(float value) : Unit(value)
{
}

Time Time::fromLSB(uint16_t lsb)
{
    return Time(lsb * lsbSize_);
}

uint16_t Time::toLSB()
{
    return value_ / lsbSize_;
}
