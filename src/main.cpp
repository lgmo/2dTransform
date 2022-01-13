#include <fstream>
const int width = 800, height = 600;

using namespace std;

int main() {
    ofstream img("picture.ppm");
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;

    int r, g, b;
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            if ( x % (width/4) == 0|| y % (height/4) == 0 ) {
                r = 255; g = 255; b = 255;
            } else  {
                r = 0; g = 0; b = 0;
            }
            img << r << " " << g << " " << b <<endl;
        }
    }

    system("gthumb picture.ppm");
    return 0;
}