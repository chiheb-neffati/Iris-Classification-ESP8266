# Iris Classification Neural Network model running on ESP8266 MCU:
## About this Project:
This developped with the platform.io (VSCode extension), written in C++ and with the Arduino framework.<br>
The model was Created and trained Using TensorFlow, to learn more about the model creation process, you can find a notebook in the "Iris python" folder or you can visit this repository :<br>
https://github.com/chiheb-neffati/Iris-patern-recognition-and-classification
## How to run this project:
### On VSCode:
1- Install Platform.io extension.
2- Clone this repository.
3- Open the project folder with Platform.io.
4- Adjust your MCU's settings in the "platformio.ini" file<br>
(This should work with most MCU's, some code adjustments might be needed, this code was tested on a NodeMCU V3 ESP8266, <br>
To learn more about supported boards consult TensorFlow Lite's supported MicroController's list <br>
Link : https://www.tensorflow.org/lite/microcontrollers
5- Load the program on your MCU.
### On the Arduino IDE:
1- install the TensorFlow Lite library.
2- Clone this repository.
3- Open the project folder then the src folder.
4- Copy all the files to the folder where you will save you sketch file (.ino file).
5- Copy the content of 'main.cpp' file into your sketch.
6- load your sketch on your MCU.<br>
(some code adjustments might be needed)
## Any Suggestions ?
If You have any suggestions or advices on how to improve this project please don't hesitate, and let me know <br>
(E-mail : chihebneffati@gmail.com)
