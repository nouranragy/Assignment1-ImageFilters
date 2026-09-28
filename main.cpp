#include <iostream>
#include "image_class.h"
using namespace std;
int main() {
    Image photo("mario.bmp");
    for (int i = 0; i < photo.width; ++i) {
        for (int j = 0; j < photo.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (i < 10 || i > photo.width - 10 || j < 10 || j > photo.height - 10 ) {
                    if (k == 0) {
                        photo(i, j, k) = 255;
                    } else if (k == 1) {
                        photo(i, j, k) = 0;
                    } else if (k == 2) {
                        photo(i, j, k) = 255;
                    }
                }
            }
        }
    }
    photo.saveImage("marioframed.jpg");
    return 0;
}