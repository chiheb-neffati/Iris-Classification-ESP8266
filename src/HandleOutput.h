/*
This file contains an output handler which will :
1 - Get the position of the largest element (in value) in the output array (this will be done with the GetArgMax function)
2 - Will blink an led n times, depending on the argument returned from the previous function
3 - Write the Species name in the serial monitor (With the OutputHandler function)


Max Argument position = 0 :
    Blink led once
    Species is Iris Setosa
Max Argument position = 1 :
    Blink led 2 times
    Species is Iris Versicolor
Max Argument position = 2 :
    Blink led 3 times
    Species is Iris Virginica
*/
const char Species[3][16] = {"Iris Setosa", "Iris Versicolor", "Iris Virginica"};
void Blink(int pin, int arg);
unsigned int GetArgMax(float array[3]);
void OutputHandler(int pin, float output_array[3]);