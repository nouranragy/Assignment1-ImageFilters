
#include "Image_Class.h"
using namespace std;
void invertfilter(Image&photo){
for (int i = 0; i < photo.width; ++i) {
    for (int j = 0; j <photo.height; ++j) {
        for (int k = 0; k < 3; ++k) {
            photo(i,j,k) = 255 - photo(i,j,k);
        }
    }
}
}  
int main() {
 Image photo("mario.jpg");
 invertfilter(photo);   
    photo.saveImage("marioframed.jpg");
    return 0;
}
