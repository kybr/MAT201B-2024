#include "al/app/al_App.hpp"
#include "al/app/al_GUIDomain.hpp"
using namespace al;

float hertz(float midi) { return 440 * pow(2, (midi - 69) / 12); }

struct MyApp : public App {
   Parameter midi{"midi", "", -50, -50, 120};
    double phase = 0;

  void onInit() override {
    auto GUIdomain = GUIDomain::enableGUI(defaultWindowDomain());
    auto &gui = GUIdomain->newGUI();

    gui << midi;
  }

    void onDraw(Graphics& g) {
        g.clear(phase);
     }
    void onSound(AudioIOData& io) {
      while (io()) {
        phase +=  hertz(midi) / 48000.0;
        if (phase >= 1.0) {
          phase -= 1;
        }
        io.out(0) = phase;
      }
    }
};

int main() {
    MyApp app;
    app.configureAudio(48000, 512, 2, 0);
    app.start();
}