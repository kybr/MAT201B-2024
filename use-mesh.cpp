#include "al/app/al_App.hpp"

struct MyApp : public al::App {
    al::Mesh mesh;
    void onCreate() {
        mesh.primitive(al::Mesh::TRIANGLES);
        mesh.vertex(0, 0, 0);
        mesh.vertex(0, 1, 0);
        mesh.vertex(1, 0, 0);
        nav().pos(0, 0, 4);
    }
    void onDraw(al::Graphics& g) {
        g.clear(1);
        g.color(0);
        g.draw(mesh);
    }
};

int main() {
    MyApp app;
    app.configureAudio(48000, 512, 2, 0);
    app.start();
}

// int main() {  MyApp().start(); }