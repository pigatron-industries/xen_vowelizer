#ifndef GlitchLoopController_h
#define GlitchLoopController_h

#include "Controller.h"
#include "io/input/AnalogInput.h"
#include "io/input/ExpInput.h"
#include "io/input/GateInput.h"
#include "modules/delays/SampleBuffer.h"

enum GlitchState {
    GLITCH_OFF,
    GLITCH_WRITE_DELAY,
    GLITCH_WRITE,
    GLITCH_READ_DELAY,
    GLITCH_READ
};

class GlitchLoopController : public Controller {
    public:
        static constexpr float MAX_DELAY = 0.5;

        GlitchLoopController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput sampleTimeInput = ExpInput(A0, 0.05);
        AnalogInput writeDelayStartInput = AnalogInput(A1, -5, 5, 0, MAX_DELAY);
        AnalogInput readDelayStartInput = AnalogInput(A2, -5, 5, 0, MAX_DELAY);
        AnalogInput dryGainInput = AnalogInput(A3, -5, 5, 0, 1);
        GateInput gateInput = GateInput(A5, 3);
        
        SampleBuffer buffer1;
        SampleBuffer buffer2;

        GlitchState state;

        float dryGain;

        int writeDelaySamples;
        int writeDelayCounter;
        int readDelaySamples;
        int readDelayCounter;
        int sampleRate;
};

#endif
