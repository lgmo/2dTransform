#include <fstream>
#include <iostream>

using namespace std;

struct rgb {
    unsigned char r;
    unsigned char g;
    unsigned char b;

    rgb() {}
    rgb(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
};

int main() {
    int height = 600, width=800;
    string version = "P6";

    ofstream file("picture.ppm", ios::binary);

    if (file.is_open()) {
        file << version << endl;
        file << width << endl;
        file << height << endl;
        file << 255 << endl;
    }
    for (int y=0; y<height; y++)
        for (int x=0; x<width; x++) {
            rgb pixel;
            if ((x % (width/4) == 0) || (y % (height/4) == 0) || x == width-1 || y == height-1)
                pixel = rgb(255, 255, 255);
            else 
                pixel = rgb(0, 0, 0);
            file.write((char*) &pixel, sizeof(rgb));
        }
    file.close();
}
