#include "al/app/al_App.hpp"

using namespace std;
using namespace al;

struct MyApp : public App {
    void onCreate() {
    }
    void onAnimate(double dt) {
    }
    void onDraw(al::Graphics& g) {
    }
    bool onKeyDown(Keyboard const& k) {
        return true;
    }
};

int main() {
    MyApp app;
    app.configureAudio(48000, 512, 2, 0);
    app.start();
}