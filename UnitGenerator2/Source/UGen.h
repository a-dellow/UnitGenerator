//
//  UGen.h
//  UnitGenerator
//
//  Created by Aaron on 23/04/2024.
//

#ifndef UGen_h
#define UGen_h

class SineOsc {
    public:
        SineOsc(){}
        SineOsc(double sampleRate, double amplitude, double phase)
        {
            mTs = 1 / sampleRate;
            mAmp = amplitude;
            mPhase = phase;
        }
        double process (double freq) {
            double newPhase = mPhase + freq * 2 * M_PI * mTs;
            mPhase = fmod(newPhase,  2 * M_PI);
            return  mAmp * cos (mPhase);
        }
    
    private:
        double mTs;
        double mAmp;
        double mPhase;
};

// PolyBLEP Saw Oscillator
class SawOsc {
public:
    SawOsc(){}
    SawOsc(float sampleRate):mSampleRate(sampleRate){}
    
    float polyBLEP(float t, float dt){
        if (t < dt) {
            t /= dt;
            return t + t - t * t - 1.0;
        }
        else if (t > 1.0 - dt) {
            t = (t - 1.0)/dt;
            return t * t + t + t + 1.0;
        }
        else return 0;
    }
    
    float process(float freq) {
        float result = (2 * mPhase - 1) - polyBLEP(mPhase, mIncr);
        if (freq != mFreq) {
            mIncr = freq / mSampleRate;
            freq = mFreq;
        }
        mPhase = fmod(mPhase + mIncr, 1.0);
        return result;
    }
    
private:
    float mPhase{0};
    float mFreq{0};
    float mSampleRate{0};
    float mIncr{0};
    
};

#endif /* UGen_h */
