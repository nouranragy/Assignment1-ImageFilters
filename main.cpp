#include <iostream>
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
void draken_lighten_filter(Image&photo){
int choice;
float amount;
cout << "1.lighten Image\n";
cout << "2.draken Image\n";
cout << "choose option (1 or 2): ";
cin >> choice;
cout << "enter level presentage (0 - 100):";
cin >> amount;
float factor = amount / 100.0;
for (int i = 0; i < photo.width; ++i) {
    for (int j = 0; j <photo.height; ++j) {
        for (int k = 0; k < 3; ++k) {
            if (choice == 1){ 
            
                photo(i,j,k) = min(255, photo(i,j,k) + (int)(photo(i,j,k) * factor))
        
            ;} else {
                photo(i,j,k) = max(0,(int)(photo(i,j,k) * (1.0 - factor)));}
        }
    }
}


}int main() {
 Image photo("mario.jpg");
 draken_lighten_filter(photo);   
    photo.saveImage("marioframed.jpg");
    return 0;
}
