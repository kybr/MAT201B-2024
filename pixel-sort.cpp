#include "al/app/al_App.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/graphics/al_Image.hpp"
#include "al/io/al_File.hpp"

using namespace std;
using namespace al;

struct MyApp : public App {
    Mesh current;
    Mesh image;
    void onCreate() {
        auto file = File::currentPath() + "../church.jpg";
        auto image = Image(file);
        for (int j = 0; j < image.height(); j++) {
          for (int i = 0; i < image.width(); i++) {
            auto pixel = image.at(i, j); // 0-255 (unsigned char / uint8)
            current.vertex(1.0 * i / image.width(), 1.0 * j / image.height(), 0);
            current.color(pixel.r / 255.0, pixel.g / 255.0, pixel.b / 255.0);
          }
        }
    }
    void onAnimate(double dt) {
    }
    void onDraw(al::Graphics& g) {
        g.clear(0.0);
        g.meshColor();
        g.pointSize(10);
        g.draw(current);
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