#include "al/app/al_App.hpp"
#include "al/graphics/al_Shapes.hpp"

using namespace std;
using namespace al;

// make a spherical mesh with texture coordinates
// open a file, an image
// make a texture
// draw
// * configure texture drawing
// * bind texture
// * draw mesh

struct MyApp : public App {
    Mesh skydome;
    void onCreate() {
        addSphereWithTexcoords(skydome);
        skydome.primitive(Mesh::LINES);
    }
    void onAnimate(double dt) {
    }
    void onDraw(al::Graphics& g) {
        g.clear(1);
        g.color(0);
        g.draw(skydome);
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