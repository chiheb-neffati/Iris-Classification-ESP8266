#include "HandleOutput.h"
#include <Arduino.h>

void Blink(int pin, int arg)
{
    for (int i = 0; i <= arg; i++)
    {
        digitalWrite(pin, LOW);
        delay(250);
        digitalWrite(pin, HIGH);
        delay(250);
    }
    delay(2000);
}

unsigned int GetArgMax(float array[3])
{
    return std::distance(array, std::max_element(array, array + 3));
}

void OutputHandler(int pin, float output_array[3])
{
    int arg;
    arg = GetArgMax(output_array);
    Serial.print("Species : ");
    Serial.println(Species[arg]);
    Blink(pin, arg);
}

// For more information open the HandleOutput.h file
