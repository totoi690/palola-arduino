#include "PalolaStepper.h"

static byte HOR[4][4] = {
    {1, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 1, 1, 0},
    {1, 1, 0, 0}
};    // {1001, 0011, 0110, 1100} - sentido Horário Full Step
static byte AHO[4][4] = {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};    // {1100, 0110, 0011, 1001} - sentido Anti-Horário Full Step

PalolaStepper::PalolaStepper(int pin1, int pin2, int pin3, int pin4) {
    _pin1 = pin1;
    _pin2 = pin2;
    _pin3 = pin3;
    _pin4 = pin4;
}

PalolaStepper::PalolaStepper() {
    _pin1 = 0;
    _pin2 = 0;
    _pin3 = 0;
    _pin4 = 0;
}

void PalolaStepper::setArduinoPinsOutput() {
    pinMode(_pin1, OUTPUT);
    pinMode(_pin2, OUTPUT);
    pinMode(_pin3, OUTPUT);
    pinMode(_pin4, OUTPUT);
}

void PalolaStepper::loadMatrixIntoArduino(byte matrix[4]) {
    digitalWrite(_pin1, matrix[0]);
    digitalWrite(_pin2, matrix[1]);
    digitalWrite(_pin3, matrix[2]);
    digitalWrite(_pin4, matrix[3]);
}

void PalolaStepper::rotateAHO() {                   // Movimento no sentido anti-horário 
  for(int i = 0; i < 512; i++)      // incrementa o contador i de 0 a 511 - uma volta
  
    for(int j = 0; j < 4; j++)      // incrementa o contador j de 0 a 3 
    {
      loadMatrixIntoArduino(AHO[j]);              // Carrega bytes da Matriz AHO na Porta B 
      delay (STEPPER_DELAY_PHASE);          // Atraso de tempo entre as fases em milisegundos
    }    
}

void PalolaStepper::rotateHOR() {                    // Movimento no sentido horário 
  for(int i = 0; i < 512; i++)      // incrementa o contador i de 0 a 511 - uma volta
  
    for(int j = 0; j < 4; j++)      // incrementa o contador j de 0 a 3 
    {
      loadMatrixIntoArduino(HOR[j]);               // Carrega bytes da Matriz HOR na Porta B 
      delay (STEPPER_DELAY_PHASE);          // Atraso de tempo entre as fases em milisegundos
    }
}

void PalolaStepper::dispenseMeal(float foodQuantity) {
    Serial.println("Dispensing meal...");
    int turns = STEPPER_TURNS_FOR_MEAL;
    if (foodQuantity > 0) {
        turns = int(STEPPER_TURNS_FOR_MEAL * foodQuantity);
    }

    for (int i = 0; i < STEPPER_TURNS_FOR_MEAL; i++) {
        rotateHOR();
    }
    turnOff();
}

void PalolaStepper::turnOff() {
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2, LOW);
    digitalWrite(_pin3, LOW);
    digitalWrite(_pin4, LOW);
}