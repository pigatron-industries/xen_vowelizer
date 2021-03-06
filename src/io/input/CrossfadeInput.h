#ifndef CrossfadeInput_h
#define CrossfadeInput_h

#include <inttypes.h>
#include "AnalogInput.h"

class CrossfadeInput : public AnalogInput {
    public:
        CrossfadeInput(uint8_t _pin, float _realMin, float _realMax) : 
            AnalogInput(_pin, _realMin, _realMax, 0, 1) {
        }

        inline bool update() {
            if(AnalogInput::update()) {
                dryLevel = (sinf(getValue()*M_PI - M_PI*0.5) + 1)*0.5;
                wetLevel = (sinf((1-getValue())*M_PI - M_PI*0.5) + 1)*0.5;
            }
            return isChanged();
        }

        inline float getDryLevel() { return dryLevel; }
        inline float getWetLevel() { return wetLevel; }

    private:
        float dryLevel;
        float wetLevel;

};

#endif