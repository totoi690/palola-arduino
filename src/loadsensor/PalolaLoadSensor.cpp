#include "PalolaLoadSensor.h"

PalolaLoadSensor::PalolaLoadSensor(int dout, int pd_sck) {
    _pinDOUT = dout;
    _pinPD_SCK = pd_sck;
    _tare = 0;
    _currentWeight = 0;
    _maxWeight = 0;
    _loadSensor = HX711();

    // _loadSensor.set_scale(CALIBRATION_FACTOR);
    // _loadSensor.tare();
}

PalolaLoadSensor::PalolaLoadSensor() {
    _pinDOUT = D4;
    _pinPD_SCK = D5;
    _tare = 0;
    _currentWeight = 0;
    _maxWeight = 0;
    _loadSensor = HX711();
}

boolean PalolaLoadSensor::isReady() {
    return _loadSensor.is_ready();
}

void PalolaLoadSensor::turnOn() {
    _loadSensor.power_up();
}

void PalolaLoadSensor::setArduinoPinsOutput() {
    _loadSensor.begin(_pinDOUT, _pinPD_SCK);
}

void PalolaLoadSensor::setTare(float newTare) {
    _tare = newTare;
}

long PalolaLoadSensor::getWeight() {
    _loadSensor.power_up();
    delay(100);

    if (_loadSensor.is_ready() == false) {
        return -1;
    }

    _currentWeight = _loadSensor.get_units(10);
    _currentWeight -= _tare;

    // if (_currentWeight < 0) {
    //     _currentWeight = 0;
    // }

    _loadSensor.power_down();
    
    return _currentWeight;
}

boolean PalolaLoadSensor::isBowlEmpty() {
    return _currentWeight < (_maxWeight * MIN_EMPTY_PERCENTAGE);
}

HX711 PalolaLoadSensor::getLoadSensor() {
    return _loadSensor;
}

