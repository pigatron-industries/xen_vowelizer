#ifndef Vocalizer_h
#define Vocalizer_h

#include "MultiFormantFilter.h"
#include "data/formants.h"

class Vocalizer {
    public:
        Vocalizer() {}
        void init(float sampleRate);
        float process(float in);

        // 0=i 1=e 2=a 3=o 5=u
        void setVowel(float vowel);
        // 0=bass 1=tenor 2=countertenor 3=alto 4=soprano
        void setRange(float range);

        //setResonance();
        //setDrive();

    private:
        MultiFormantFilter<VOCAL_FORMANT_SIZE> filter;

        float vowel;
        float range;

        uint8_t vowelInt;
        float vowelFraction;
        uint8_t rangeInt;
        float rangeFraction;

        void calculateFractions();
        void calculateFormants();

};

#endif