#include <Arduino.h>

// Importing TensorFlow Lite library

#include "TensorFlowLite_ESP32.h"
#include "tensorflow/lite/experimental/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

// Importing our model's data along with the testing data:
#include "Data.h"
// You can find more about the model making process in the notebook in the "Iris python folder"
// or in this link : https://github.com/chiheb-neffati/Iris-patern-recognition-and-classification

#include "HandleOutput.h"

// Setting up global variables
namespace
{
  tflite::ErrorReporter *error_reporter = nullptr;
  const tflite::Model *model = nullptr;
  tflite::MicroInterpreter *interpreter = nullptr;
  TfLiteTensor *input = nullptr;
  TfLiteTensor *output = nullptr;

  constexpr int kTensorArena = 4 * 1024;
  uint8_t tensor_arena[kTensorArena];
}

void setup()
{
  Serial.begin(115200);
  pinMode(D4, OUTPUT);

  // Setting up the error reporter,
  // The error reporter will report to Serial
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Getting the model's data :
  model = tflite::GetModel(model_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION)
  {
    error_reporter->Report("Model version does not match Schema");
  }

  // Get the Neural Network's needed operations:
  static tflite::ops::micro::AllOpsResolver resolver;

  // Build an interpreter to make predictions:
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArena, error_reporter);

  interpreter = &static_interpreter;

  // Allocating memory for the interpreter :
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk)
  {
    error_reporter->Report("AllocateTensors() failed");
  }

  // Initialising the input's and output's buffer:
  input = interpreter->input(0);
  output = interpreter->output(0);
}

void loop()
{
  // Looping through the testing data
  for (uint8_t i = 0; i < 30; i++)
  {

    // Copying testing Input to the interpreter's input buffer:
    input->data.f[0] = testInput[i][0];
    input->data.f[1] = testInput[i][1];

    // Making a prediction :
    TfLiteStatus invoke_status = interpreter->Invoke();
    if (invoke_status != kTfLiteOk)
    {
      error_reporter
          ->Report("Invoke failed on input: %f, %f\n", testInput[i][0], testInput[i][1]);
    }

    // Printing the expected Output :
    Serial.print("Expected :   ");
    Serial.print("|     ");
    Serial.print(testOutput[i][0]);
    Serial.print("         ");
    Serial.print(testOutput[i][1]);
    Serial.print("         ");
    Serial.print(testOutput[i][2]);
    Serial.print("     |");
    Serial.println("");

    // Printing the Prediction Output :
    Serial.print("Prediction : ");
    Serial.print("|   ");
    Serial.print(output->data.f[0], 3);
    Serial.print("     ");
    Serial.print(output->data.f[1], 3);
    Serial.print("     ");
    Serial.print(output->data.f[2], 3);
    Serial.print("   |");
    Serial.println("");

    // Calling the output handler:
    OutputHandler(D4, output->data.f);
    // See the "HandleOutput.h" file to learn more about the output handler fucntion

    Serial.println("----------------------------------------------");
  }
}
