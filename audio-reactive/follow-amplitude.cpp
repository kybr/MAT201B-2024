// Karl Yerkes | MAT201B
// 2022-02-22  | Audio-reactive visualizer
//

#include "al/app/al_App.hpp"
#include "al/app/al_GUIDomain.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/math/al_Functions.hpp"  // al::abs

#include "Gamma/SamplePlayer.h"  // XXX
#include "Gamma/Analysis.h"
#include "Gamma/Effects.h"

using namespace al;

struct MyApp : App {
  Parameter value{"value", 0, 0, 1};

  gam::SamplePlayer<float, gam::ipl::Linear, gam::phsInc::Loop> player;
  gam::EnvFollow<> follow;

  Mesh sphere;

  void onCreate() override { addSphere(sphere); 
  
    follow.lag(0.5); 
  
  }

  void onDraw(Graphics& g) override {
    g.clear(0.2);

    g.scale(0.9 * value.get());
    g.draw(sphere);

    // properties of things we can draw?
    //
    // position
    // scale
    // rotation
    // symmetry
    // complexity (polygon count)
    // primitive
    // color
    // material / surface (smooth, rough, translucent)
    // texture (as in wrapped image)
    // lighting
    // number (how many things are there?)
    // shape
    // curvature (straight angles or curved?)
  }

  void onSound(AudioIOData& io) override {
    while (io()) {
      float s = player();
      io.out(0) = io.out(1) = s;

      value.set(follow(s));

      // qualities of sound?
      //
      // pitch / frequency / f0 (fundamnetal frequency)
      // pan / spatialization (where is the sound? what is the space?)
      // amplitude / volume / loudness / power
      // envelope (amplitude changes over time)
      // timbre (spectral changes over time)
      // rhythm
      //
      // https://github.com/adamstark/Gist
    }
  }

  void onInit() override {
    player.load("truth.wav");

    auto GUIdomain = GUIDomain::enableGUI(defaultWindowDomain());
    auto& gui = GUIdomain->newGUI();
    gui.add(value);
    parameterServer() << value;
  }

  void onMessage(osc::Message& m) override { m.print(); }
  bool onKeyDown(const Keyboard& k) override { return false; }
  void onAnimate(double dt) override {}
};

int main() {
  MyApp app;
  app.configureAudio(48000, 512, 2, 2);
  app.start();
}
