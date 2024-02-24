#include "al/app/al_App.hpp"
#include "al/math/al_Random.hpp"
#include "Gamma/SamplePlayer.h"
#include "Gamma/Filter.h"
#include "Gamma/Analysis.h"

using namespace al;

struct FilterFollow {
  gam::Biquad<> filter;
  gam::EnvFollow<> follow;
  float operator()(float in) {
    return gam::scl::mapLin(gam::scl::ampTodB(follow(filter(in))), -134.0f, 0.0f, 0.0f, 1.0f);
  }
};

struct MyApp : public App {
  Parameter parameter[3]{
    {"low", "", 0,  0, 127},
    {"mid", "", 0,  0, 127},
    {"high", "", 0, 0, 127}
  };
  FilterFollow follow[3]; 

  gam::SamplePlayer<float, gam::ipl::Cubic, gam::phsInc::Loop> player;

  void onInit() override {
    player.load("truth.wav");
    
    follow[0].filter.type(gam::LOW_PASS);
    follow[1].filter.type(gam::BAND_PASS);
    follow[2].filter.type(gam::HIGH_PASS);
    follow[0].filter.freq(200);
    follow[1].filter.freq(2000);
    follow[2].filter.freq(4000);
  }

  float time = 0;
  float delay = 0;
  void onAnimate(double dt) override {
    if (time > delay) {
      time -= delay;
      delay = rnd::uniform(1.0, 0.1);

      player.rate(rnd::uniform(1.5, 0.5) * (rnd::prob(0.5) ? -1 : 1));
      player.range(rnd::uniform(1.0), rnd::uniform(1.0));
    }
    time += dt;
  }

  void onDraw(Graphics& g) override {
    g.clear(parameter[0], parameter[1], parameter[2]);
  }

  void onSound(AudioIOData& io) override {
    while (io()) {
      float s = player();
        io.out(0) = s;
        io.out(1) = s;
        for (int i = 0; i < 3; i++) {
          parameter[i].set(follow[i](s));
        }
    }
  }
};

int main() {
  MyApp app;
  app.start();
}