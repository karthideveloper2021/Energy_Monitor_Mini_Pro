#include "math.h"
#include "arduino.h"

class Voltage{
  float _offset;
  float _voltsum;
  int _pin;
  float _calibrateValue;

  public:

    void calibrate(int pin,float offset,float calibrateValue){
      this->_offset=offset;
      this->_pin=pin;
      this->_calibrateValue=calibrateValue;
    }

    float getVoltage(int sample=1000,int averageSampleCount=10){
      int Vmax=0;
      int Vmin=100000;
      int sampleRead;
      float averageVolt=0;
      for(int j=0;j<averageSampleCount;j++){
        for(int i=0;i<sample;i++){
          sampleRead=analogRead(_pin);
          if(sampleRead>=Vmax) Vmax=sampleRead;
          if(sampleRead<=Vmin) Vmin=sampleRead;
          delay(0.1);
        }
        averageVolt+=(Vmax-Vmin)/(2*sqrt(2));
        Vmax=0;
        Vmin=100000;
      }

      _voltsum=averageVolt/averageSampleCount;
      _voltsum=_voltsum-_offset;

      if(_voltsum<=10) _voltsum=0;

      return (_voltsum * _calibrateValue);
    }

};