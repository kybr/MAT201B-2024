// Karl Yerkes
// 2022-01-20

#include "al/app/al_App.hpp"
#include "al/app/al_GUIDomain.hpp"
#include "al/math/al_Random.hpp"
#include "al/graphics/al_Image.hpp"
#include "al/io/al_File.hpp"

using namespace al;

#include <fstream>
#include <vector>
using namespace std;

Vec3f randomVec3f(float scale) {
  return Vec3f(rnd::uniformS(), rnd::uniformS(), rnd::uniformS()) * scale;
}
string slurp(string fileName);  // forward declaration

struct AlloApp : App {
  Parameter pointSize{"/pointSize", "", 1.0, 0.0, 2.0};
  Parameter timeStep{"/timeStep", "", 0.1, 0.01, 0.6};
  //

  ShaderProgram pointShader;

  //  simulation state
  Mesh mesh;  // position *is inside the mesh* mesh.vertices() are the positions
  vector<Vec3f> velocity;
  vector<Vec3f> acceleration;
  vector<float> mass;

  void onInit() override {
    // set up GUI
    auto GUIdomain = GUIDomain::enableGUI(defaultWindowDomain());
    auto &gui = GUIdomain->newGUI();
    gui.add(pointSize);  // add parameter to GUI
    gui.add(timeStep);   // add parameter to GUI
    //
  }

Mesh current;

  void onCreate() override {
    pointShader.compile(slurp("../point-vertex.glsl"),
                        slurp("../point-fragment.glsl"),
                        slurp("../point-geometry.glsl"));

    mesh.primitive(Mesh::POINTS);

    auto file = File::currentPath() + "../colorful.png";
    auto image = Image(file);
    auto aspect_ratio = 1.0f * image.width() / image.height();
    for (int j = 0; j < image.height(); j++) {
      for (int i = 0; i < image.width(); i++) {
        auto pixel = image.at(i, j); // 0-255 (unsigned char / uint8)
        mesh.vertex(1.0 * i / image.width() * aspect_ratio, 1.0 * j / image.height(), 0);
        mesh.color(pixel.r / 255.0, pixel.g / 255.0, pixel.b / 255.0);
        mesh.texCoord(0.05, 0);  // s, t
      }
    }

    nav().pos(0, 0, 5);
  }

  void onAnimate(double dt) override {
  }

  bool onKeyDown(const Keyboard &k) override {
    if (k.key() == '1') {
    }
    return true;
  }

  void onDraw(Graphics &g) override {
    g.clear(0.3);
    g.shader(pointShader);
    g.shader().uniform("pointSize", pointSize / 100);
    g.blending(true);
    g.blendTrans();
    g.depthTesting(true);
    g.draw(mesh);
  }
};

int main() {
  AlloApp app;
  app.configureAudio(48000, 512, 2, 0);
  app.start();
}

string slurp(string fileName) {
  fstream file(fileName);
  string returnValue = "";
  while (file.good()) {
    string line;
    getline(file, line);
    returnValue += line + "\n";
  }
  return returnValue;
}
