#ifndef Glottis_h
#define Glottis_h

#include <inttypes.h>


class Glottis {
    public:
        void init(float sampleRate);
        float process(float lambda, float noiseSource);
        void finishBlock();

        void setAutoWobble(bool _autoWobble) { autoWobble = _autoWobble; }
        void setFrequency(float _targetFrequency) { targetFrequency = _targetFrequency; }
        void setTenseness(float _targetTenseness) { targetTenseness = _targetTenseness; }

    private:
	    void setupWaveform(float lambda);
        float normalizedLFWaveform(float t);
        float getNoiseModulator();
	
        float sampleRate;
        float timeInWaveform;
        float frequency, oldFrequency, newFrequency, smoothFrequency, targetFrequency;
        float oldTenseness, newTenseness, targetTenseness;
        float waveformLength;

        float rd;
        float alpha;
        float e0;
        float epsilon;
        float shift;
        float delta;
        float te;
        float omega;

        float totalTime;
        float intensity, loudness;
        float vibratoAmount;
        float vibratoFrequency;
        bool autoWobble;
        bool isTouched;
        bool alwaysVoice;

};

#endif