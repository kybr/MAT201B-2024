#include "al/app/al_App.hpp"

// how to include things ~ how do we know what to include?
// fewer includes == faster compile == only include what you need
#include "al/math/al_Random.hpp"
#include "al/graphics/al_Shapes.hpp"

struct MyApp : public al::App {
    al::Mesh mesh;
    al::Nav predator, prey;
    al::Vec3d food;

    void onCreate() {
        addCone(mesh);
        mesh.generateNormals();

        prey.pos(3, 1, -2);
        predator.pos(-3, 1, 0);
        nav().pos(0, 2, 7);
        nav().faceToward(0,0,0);
    }

    double phase = 0;
    void onAnimate(double dt) {
        phase += dt;
        if (phase > 3) {
            phase -= 3;
            food = al::rnd::ball<al::Vec3d>() * 2;
        }

        double turn_rate = 0.05;
        double move_rate = 0.02;

        prey.faceToward(food, turn_rate);
        predator.faceToward(prey.pos(), turn_rate);

        prey.moveF(move_rate);
        predator.moveF(move_rate / 2);

        prey.step();
        predator.step();

        // automate the camera
        nav().faceToward(food, 0.01);
    }

    void onDraw(al::Graphics& g) {
        g.depthTesting(true);
        g.lighting(true);
        g.clear(1);
        
        g.color(0, 1, 0);
        g.pushMatrix();
        g.translate(prey.pos());
        g.rotate(prey.quat());
        g.scale(0.1);
        g.draw(mesh);
        g.popMatrix();

        g.color(1, 0, 0);
        g.pushMatrix();
        g.translate(predator.pos());
        g.rotate(predator.quat());
        g.scale(0.2);
        g.draw(mesh);
        g.popMatrix();

        g.color(0, 0, 0);
        g.pushMatrix();
        g.translate(food);
        g.scale(0.1);
        g.scale(0.1);
        g.draw(mesh);
        g.popMatrix();
    }
};

int main() {
    MyApp app;
    app.configureAudio(48000, 512, 2, 0);
    app.start();
}

// int main() {  MyApp().start(); }
