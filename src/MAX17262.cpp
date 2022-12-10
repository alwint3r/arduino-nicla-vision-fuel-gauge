#include "MAX17262.h"
#include "MAX17262_Registers.h"

MAX17262::MAX17262(I2CWriteFunction write, I2CReadFunction read, DelayFunction delay)
    : config_(),
      write_(write),
      read_(read),
      delay_(delay)
{
}

bool MAX17262::begin(FuelGaugeConfig config)
{
    config_ = config;

    int por = read_(STATUS_REG) & 0x0002;
    if (por)
    {
        while (read_(FSTAT_REG) & 1)
        {
            delay_(10);
        }

        int hibernate = read_(HIBER_CFG_REG);
        write_(SOFTWK_CFG_REG, 0x90);
        write_(HIBER_CFG_REG, 0);
        write_(SOFTWK_CFG_REG, 0);

        write_(DESIGN_CAP_REG, config.batteryCapacity.toLSB());
        write_(ICHG_TERM_REG, config.chargeTerminationCurrent.toLSB());
        write_(VEMPTY_REG, config.voltageEmpty.toLSB());

        // assume battery charge voltage is 4.2 Volt
        write_(MODEL_CFG_REG, 0x8000);

        while (read_(MODEL_CFG_REG) & 0x8000)
        {
            delay_(10);
        }

        // restore hibernate config
        write_(HIBER_CFG_REG, hibernate);
    }

    int status = read_(STATUS_REG);
    writeAndVerify(STATUS_REG, status & 0xFFFD);
}

int MAX17262::writeAndVerify(uint8_t reg, int value)
{
    int attempt = 0;
    int readValue = 0;
    do
    {
        write_(reg, value);
        delay_(1);
        readValue = read_(reg);
    } while (value != readValue && attempt++ < 3);

    return readValue == value;
}