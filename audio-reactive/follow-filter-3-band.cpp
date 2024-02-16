#include <iostream>

#include "al/app/al_DistributedApp.hpp"
#include "Gamma/Filter.h"
#include "Gamma/Analysis.h"

using namespace std;
using namespace al;

struct Foo : DistributedApp {
  gam::Biquad<> low;
  gam::Biquad<> mid;	
  gam::Biquad<> high;
  gam::EnvFollow<> follow_low;
  gam::EnvFollow<> follow_mid;
  gam::EnvFollow<> follow_high;
  float value_low;
  float value_mid;
  float value_high;

  void onInit() override {
    low.type(gam::LOW_PASS);
    low.freq(200.0);
    mid.type(gam::BAND_PASS);
    mid.freq(1500.0);
    high.type(gam::HIGH_PASS);
    high.freq(8000);
  }

  void onCreate() override { }

  void onAnimate(double dt) override { }

  void onDraw(Graphics &g) override {
    g.clear(value_low, value_mid, value_high);
  }

  bool onKeyDown(const Keyboard &k) override {
    return true;
  }

  void onSound(AudioIOData& io) override {
    while(io()) {
      float s = io.in(0);
      value_low = 10 * follow_low(low(s));
      value_mid = 10 * follow_mid(mid(s));
      value_high = 10 * follow_high(high(s));
    }
  }
};

int main() {
  Foo app;
  auto device = AudioDevice("Microphone"); // XXX replace with your input device
  app.configureAudio(device, 48000, 512, 0, 1);
  app.start();
}
