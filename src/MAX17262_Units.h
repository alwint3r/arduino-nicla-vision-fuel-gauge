#ifndef MAX17262_UNITS_H_
#define MAX17262_UNITS_H_

#include <cstdint>
#include <ratio>

template <typename T>
class Unit
{
public:
    Unit(T value): value_(value) {}

    virtual uint16_t toLSB() = 0;

    virtual T getValue()
    {
        return value_;
    }

protected:
    T value_;
};

class Capacity : public Unit<float>
{
public:
    Capacity(float value);

    uint16_t toLSB() override;

    static Capacity fromLSB(uint16_t lsb);

protected:
    static constexpr float lsbSize_ = 0.5; // 0.5 mAh
};

class Percentage : public Unit<uint16_t>
{
public:
    Percentage(uint16_t value);

    uint16_t toLSB() override;

    static Percentage fromLSB(uint16_t lsb);

protected:
    static constexpr float lsbSize_ = 0.00390625; // 1/256 %
};


class Voltage : public Unit<float>
{
public:
    Voltage(float value);

    uint16_t toLSB() override;

    static Voltage fromLSB(uint16_t lsb);

    float volt();

protected:
    static constexpr float lsbSize_ = 0.078125; // 1.25mV/16
};

class Current : public Unit<float>
{
public:
    Current(float value);

    uint16_t toLSB() override;

    static Current fromLSB(uint16_t lsb);
    static Current fromMilliAmp(uint16_t ma);

    float ma();

protected:
    static constexpr float lsbSize_ = 156.25; // uA
};

class Temperature : public Unit<float>
{
public:
    Temperature(float value);

    uint16_t toLSB() override;

    static Temperature fromLSB(uint16_t lsb);

protected:
    static constexpr float lsbSize_ = 0.00390625; // 1/256 %
};

class Resistance : public Unit<float>
{
public:
    Resistance(float value);

    uint16_t toLSB() override;

    static Resistance fromLSB(uint16_t lsb);

protected:
    static constexpr float lsbSize_ = 0.000244140625; // 1/4096 Ohm
};

class Time : public Unit<float>
{
public:
    Time(float value);

    uint16_t toLSB() override;

    static Time fromLSB(uint16_t lsb);

protected:
    static constexpr float lsbSize_ = 5.625; // s
};

#endif
