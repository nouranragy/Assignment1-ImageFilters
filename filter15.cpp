#include <iostream>
#include <algorithm>
#include "Image_Class.h"
using namespace std;
void applyPurpleFilter(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned char r = image(i, j, 0);
            unsigned char g = image(i, j, 1);
            unsigned char b = image(i, j, 2);
            int new_r = min(255, (int)(r * 1));
            int new_g = (int)(g * .5);
            int new_b = min(255, (int)(b * 1.1));
            image(i, j, 0) = new_r;
            image(i, j, 1) = new_g;
            image(i, j, 2) = new_b;
            

        }
    }
}
int main() {
    string filename = "luffy.jpg";
    Image img(filename);
    applyPurpleFilter(img);
    img.saveImage("luffy_purple.jpg");
    return 0;
}