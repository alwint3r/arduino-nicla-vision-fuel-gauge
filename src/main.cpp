#include <Arduino.h>
#include <Wire.h>

static constexpr auto FG_ADDR = 0x36;
static constexpr auto STATUS_REGISTER = 0;

int WriteRegister(uint8_t address, uint16_t value)
{
    Wire1.beginTransmission(FG_ADDR);
    Wire1.write(address);
    Wire1.write(value & 0xFF);
    Wire1.write(value >> 8);
    return Wire1.endTransmission();
}

int ReadRegister(uint8_t address)
{
    Wire1.beginTransmission(FG_ADDR);
    Wire1.write(address);
    if (Wire1.endTransmission() != 0)
    {
        return -1;
    }

    int ret = Wire1.requestFrom(FG_ADDR, 2);
    if (ret < 2)
    {
        Serial.println("No data available");
        return -1;
    }

    uint8_t buffer[2] = {0};
    Wire1.readBytes(buffer, ret);

    int result = buffer[0] | buffer[1] << 8;
    return result;
}

bool WriteAndVerifyRegister(uint8_t address, int writeValue)
{
    int attempt = 0;
    int readValue = 0;
    do
    {
        WriteRegister(address, writeValue);
        delay(1);
        readValue = ReadRegister(address);
    } while (writeValue != readValue && attempt++ < 3);

    return readValue == writeValue;
}

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    delay(3000);

    Wire1.begin();

    int por = ReadRegister(STATUS_REGISTER) & 0x0002;
    Serial.print("POR: ");
    Serial.println(por);

    if (por)
    {
        // TODO: POR detected
        while (ReadRegister(0x3D) & 1)
        {
            delay(10);
        }

        Serial.println("FSTAT.DNR == 0");

        int hibernateCFG = ReadRegister(0xBA);
        WriteRegister(0x60, 0x90);
        WriteRegister(0xBA, 0x0);
        WriteRegister(0x60, 0x0);

        int DesignCap = 0x1450;
        int IchgTerm = 0x0333;
        int VEmpty = 0xa561;
        float ChargeVoltage = 4.2;

        WriteRegister(0x18, DesignCap);
        WriteRegister(0x1E, IchgTerm);
        WriteRegister(0x3A, VEmpty);

        if (ChargeVoltage > 4.275)
        {
            WriteRegister(0xDB, 0x8400);
        }
        else
        {
            WriteRegister(0xDB, 0x8000);
        }

        while (ReadRegister(0xDB) & 0x8000)
        {
            delay(10);
        }

        Serial.println("ModelCFG.Refresh == 0");

        WriteRegister(0xBA, hibernateCFG);
    }

    int status = ReadRegister(0x00);
    WriteAndVerifyRegister(0x00, status & 0xFFFD);
}

void loop()
{
    int RepSOC = ReadRegister(0x06);
    Serial.print("RepSOC = ");
    Serial.println(RepSOC);

    int soc = RepSOC / 256;
    Serial.print("SOC = ");
    Serial.println(soc);

    delay(3000);
}