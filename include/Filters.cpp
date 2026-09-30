#include "Image_Class.h"
#include <iostream>
#include "Filters.h"
using namespace std;

void greyScale(Image& image)
{
   for (int i = 0; i < image.width; ++i)
   {
      for (int j = 0; j < image.height; ++j)
      {
         unsigned int clr = 0; //clr is short for color
         for (int k = 0; k <image.channels; ++k) clr += image(i, j, k);
         clr/=3;
         for (int k = 0; k < image.channels; ++k) image (i, j, k) = clr;
      }
   }
}

void applyBlackandWhite(Image& image)
{
  for(int i = 0; i < image.width ; ++i)
   {
      for(int j = 0; j< image.height ; ++j){

         unsigned int avg = 0;
        for(int k =0 ; k < 3; ++k){


           avg+= image(i , j , k) ;
         }

        avg= avg/3;

      unsigned char bwValue;
      if(avg >= 128){
         bwValue = 255;
      }
      else{
         bwValue = 0;
      }

        for(int k = 0; k < 3 ;++k){
         image(i , j ,k) = bwValue;
        }
      }
   }
}

void addFrame(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (i < 10 || i > image.width - 10 || j < 10 || j > image.height - 10 ) {
                    if (k == 0) {
                        image(i, j, k) = 255;
                    } else if (k == 1) {
                        image(i, j, k) = 0;
                    } else if (k == 2) {
                        image(i, j, k) = 255;
                    }
                }
            }
        }
    }
}

void flipImage(Image& image, char direction)
{ // temporary is an image copy to not overwrite thr imag and the changes then would be zzzzerro
   Image temp(image.width, image.height); //temp is for temporary
   for (int i = 0; i < image.width; ++i)
   {
      for (int j = 0; j < image.height; ++j)
      {
         int inew = i;
         int jnew = j;
         if (direction == 'h') inew = image.width - 1 - i;
         else if (direction == 'v') jnew = image.height -1 -j;
         for (int k = 0; k < image.channels; ++k) temp(inew, jnew, k) = image (i, j, k);
      }
   }
   image = temp;
}

void applyRotateImage(Image& image)
{
  int x;
  cout << "ُEnter rotation angle(90, 180, or 270)" << endl;
  cin >> x;
   if(x == 90)
   {
     Image rotatedImage(image.height , image.width);
     for(int i = 0; i < image.width ; ++i)
   {
      for(int j = 0; j< image.height ; ++j)
      {
          for(int k =0 ; k < 3; ++k)
          {
               rotatedImage(image.height - 1 - j , i , k)= image(i , j , k) ;
          }
      }
  
   }
    image = rotatedImage;
   }
    else if(x == 180)
   {
      Image rotatedImage(image.width, image.height);
     for(int i = 0; i < image.width ; ++i)
   {
      for(int j = 0; j< image.height ; ++j)
      {
          for(int k =0 ; k < 3; ++k)
          {
               rotatedImage(image.width - 1 - i , image.height - 1 -j , k)= image(i , j , k) ;
          }
      }

   }
   image = rotatedImage;
   }

   else if(x == 270)
   {
      Image rotatedImage(image.height , image.width);
     for(int i = 0; i < image.width ; ++i)
   {
      for(int j = 0; j< image.height ; ++j)
      {
          for(int k =0 ; k < 3; ++k)
          {
               rotatedImage(j , image.width - 1 - i , k)= image(i , j , k) ;
          }
      }

   }
   image = rotatedImage;
   }


  
}

Image resizePhoto(Image& image, int newWidth, int newHeight) {
    Image newPhoto(newWidth, newHeight);
    double scaleX = (double) image.width / newWidth;
    double scaleY = (double) image.height / newHeight;
    for (int i =0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {

                int origX = ( int ) ((i+0.5) * scaleX);
                int origY = ( int ) ((j+0.5) * scaleY);
                if (origX >= image.width) origX = image.width - 1;
                if (origY >= image.height) origY = image.height - 1;
                for (int k = 0; k < 3; ++k) {
                    newPhoto(i, j, k) = image(origX, origY, k);
            }
        }
    }
    return newPhoto;
}
