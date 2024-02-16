
#include <iostream>

#include "al/app/al_DistributedApp.hpp"
#include "Gamma/Filter.h"
#include "Gamma/Analysis.h"
#include "Gamma/DFT.h"

using namespace std;
using namespace al;

struct Foo : DistributedApp {
  gam::STFT stft{ 2048, 2048/4, 0, gam::HANN, gam::MAG_PHASE };
  float value_low = 0;
  float value_mid = 0;
  float value_high = 0;

  void onInit() override { }

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
      if (stft(s)) {
        value_low = 0;
        value_high = 0;
        value_mid = 0;

        // ___ < 200
        for (int i = 0; i < 10; i++) {
          value_low += stft.bins()[i][0]; 
        }

        // 200 < ___ < 8000
        for (int i = 10; i < 341; i++) {
          value_mid += stft.bins()[i][0]; 
        }

        // ___ > 8000
        for (int i = 341; i < 1025; i++) {
          value_high += stft.bins()[i][0]; 
        }

        // scaled by number of bins
        //
        value_low /= 10;
        value_mid /= 331;
        value_high /= 684;

        // trial and error scaling
        //
        value_low *= 100;
        value_mid *= 300;
        value_high *= 10000;

        //printf("l:%f m:%f h:%f\n", value_low, value_mid, value_high);

      }
    }
  }
};

int main() {
  Foo app;
  auto device = AudioDevice("Microphone"); // XXX replace with your input device
  app.configureAudio(device, 48000, 512, 0, 1);
  app.start();
}
