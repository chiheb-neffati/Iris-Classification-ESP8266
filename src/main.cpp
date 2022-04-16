#include <Arduino.h>

#include "TensorFlowLite_ESP32.h"
#include "tensorflow/lite/experimental/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

#include "Data.h"
#include "HandleOutput.h"

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

  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  model = tflite::GetModel(model_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION)
  {
    error_reporter->Report("Model version does not match Schema");
  }

  static tflite::ops::micro::AllOpsResolver resolver;

  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArena, error_reporter);

  interpreter = &static_interpreter;

  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk)
  {
    error_reporter->Report("AllocateTensors() failed");
  }

  input = interpreter->input(0);
  output = interpreter->output(0);
}

void loop()
{
  for (unsigned int i = 0; i < 30; i++)
  {
    input->data.f[0] = testInput[i][0];
    input->data.f[1] = testInput[i][1];

    TfLiteStatus invoke_status = interpreter->Invoke();
    if (invoke_status != kTfLiteOk)
    {
      error_reporter
          ->Report("Invoke failed on input: %f, %f\n", testInput[i][0], testInput[i][1]);
    }

    Serial.print("Expected :   ");
    Serial.print("|     ");
    Serial.print(testOutput[i][0]);
    Serial.print("         ");
    Serial.print(testOutput[i][1]);
    Serial.print("         ");
    Serial.print(testOutput[i][2]);
    Serial.print("     |");
    Serial.println("");

    Serial.print("Prediction : ");
    Serial.print("|   ");
    Serial.print(output->data.f[0], 3);
    Serial.print("     ");
    Serial.print(output->data.f[1], 3);
    Serial.print("     ");
    Serial.print(output->data.f[2], 3);
    Serial.print("   |");
    Serial.println("");

    OutputHandler(D4, output->data.f);

    Serial.println("----------------------------------------------");
  }
}
