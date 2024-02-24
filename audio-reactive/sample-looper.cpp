#include "al/app/al_App.hpp"
#include "al/math/al_Random.hpp"
#include "Gamma/SamplePlayer.h"

using namespace al;

struct MyApp : public App {

  gam::SamplePlayer<float, gam::ipl::Cubic, gam::phsInc::Loop> player;

  void onInit() override {
    player.load("truth.wav");
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

  void onSound(AudioIOData& io) override {
    while (io()) {
      float s = player();
        io.out(0) = s;
        io.out(1) = s;
    }
  }
};

int main() {
  MyApp app;
  app.start();
}