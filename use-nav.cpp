#include "al/app/al_App.hpp"
#include "al/math/al_Random.hpp"

struct MyApp : public al::App {
    al::Mesh mesh;
    void onCreate() {
        mesh.primitive(al::Mesh::TRIANGLES);

        mesh.vertex(0, 0, 0);
        mesh.color(1, 0, 0);

        mesh.vertex(0, 1, 0);
        mesh.color(0, 1, 0);

        mesh.vertex(1, 0, 0);
        mesh.color(0, 0, 1);

        nav().pos(0, 0, 4);
    }
    void onAnimate(double dt) {
        static double phase = 0;
        phase += dt;
        if (phase >= 1) {
            phase -= 1;
            nav().faceToward(al::rnd::ball<al::Vec3d>());
        }
    }
    void onDraw(al::Graphics& g) {
        g.clear(1);
        g.meshColor();
        g.draw(mesh);
    }
};

int main() {
    MyApp app;
    app.configureAudio(48000, 512, 2, 0);
    app.start();
}

// int main() {  MyApp().start(); }
