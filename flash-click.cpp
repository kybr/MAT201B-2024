#include "al/app/al_App.hpp"
using namespace al;
struct MyApp : public App {
    bool shouldClick = false;
    bool shouldFlash = false;
    void onCreate() { }
    void onAnimate(double dt) { }
    void onDraw(Graphics& g) {
        g.clear(shouldFlash);
        shouldFlash = false;
     }
    void onSound(AudioIOData& io) {
      io();
      if (shouldClick) {
        io.out(0) = 1;
        shouldClick = false;
      }
      else {
        io.out(0) = 0;
      }
      while (io()) {
        io.out(0) = 0;
      }
    }

    bool onKeyDown(Keyboard const& k) {
        shouldClick = true;
        shouldFlash = true;
    }
};

int main() {
    MyApp app;
    app.configureAudio(48000, 512, 2, 0);
    app.start();
}