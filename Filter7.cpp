#include "Image_Class.h"
#include <iostream>
using namespace std;
void darkenImage(Image& img) {
    for (int i = 0; i < img.height; ++i)
     for (int j = 0; j < img.width; ++j)
      for (int k = 0; k < 3; ++k)
       img(j, i, k) *=0.5;
}
 void lightenImage(Image& img){
    for (int i = 0; i < img.height; ++i)
     for (int j = 0; j < img.width; ++j)
      for (int k = 0; k < 3 ; ++k)
       img(j, i, k) = img(j, i, k) + (255-img(j, i, k)) * 0.5;
  } int main () {
        Image img("mario.jpg");
        darkenImage(img);
        img.saveImage("dark_mario.jpg");
        lightenImage(img);
        img.saveImage("light_mario.jpg");

    
    
 return 0;       /* code */
  }  

    
    
        /* code */
    
    
    
        /* code */
    
       



    
        /* code */
    
    
    
        /* code */
    
    

