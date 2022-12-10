#ifndef MAX17262_H_
#define MAX17262_H_

#include "MAX17262_Units.h"
#include <functional>

struct FuelGaugeConfig
{
    Capacity batteryCapacity;
    Voltage voltageEmpty;
    Current chargeTerminationCurrent;

    FuelGaugeConfig()
        : batteryCapacity(650),
          voltageEmpty(3300),
          chargeTerminationCurrent(Current::fromMilliAmp(128))
    {
    }

    FuelGaugeConfig(Capacity batteryCapacity, Voltage voltageEmpty, Current chargeTerminationCurrent)
        : batteryCapacity(batteryCapacity),
          voltageEmpty(voltageEmpty),
          chargeTerminationCurrent(chargeTerminationCurrent)
    {
    }
};

class MAX17262
{
public:
    using I2CWriteFunction = std::function<int(uint8_t, uint16_t)>;
    using I2CReadFunction = std::function<int(uint8_t)>;
    using DelayFunction = std::function<void(uint32_t)>;

    MAX17262(I2CWriteFunction write, I2CReadFunction read, DelayFunction delay);

    bool begin(FuelGaugeConfig config);

    Percentage getSOC();

private:
    int writeAndVerify(uint8_t reg, int value);

private:
    FuelGaugeConfig config_;
    I2CReadFunction read_;
    I2CWriteFunction write_;
    DelayFunction delay_;
};

#endif