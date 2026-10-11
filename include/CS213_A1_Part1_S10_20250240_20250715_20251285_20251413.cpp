/*
 *CS213-Assignment 1 - Part 1
 *File: CS213_A1_Part1_S10_20250240_20250715_20251285_20251413.cpp
 *
 *Team Memberes:
 *[Rodaina Nassar Ibrahim] - ID: [20250240] - Section: [S10]
 *[Nouran Ragy Gamal] - ID: [20250715] - Section: [S10]
 *[Fatma Abd elaziem Mohamed] - ID: [20251285] - Section: [S10]
 *[Malak Ehab Youssef] - ID: [20251413] - Section: [S10]
 *
 *work Breakdown:
 *Filter 1 (Greyscale) - [Rodaina Nassar Ibrahim]
 *Filter 2 (Black&White) - [Nouran Ragy Gamal]
 *Filter 3 (Invert) - [Fatma Abdelaziem Mohamed]
 *Filter 4 (Frame) - [Malak Ehab Youssef]
 *Filter 5 (Flip) - [Rodaina Nassar Ibrahim]
 *Filter 6 (Rotate) - [Nouran Ragy Gamal]
 *Filter 7 (Darken/Lighten) - [Fatma Abdelaziem Mohamed]
 *Filter 8 (Resize) - [Malak Ehab Youssef]
 *Menu/Load/Save - [Rodaina Nassar Ibrahim -Nouran Ragy Gamal - Malak Ehab Youssef]
 */

#include "Image_Class.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include<limits>
using namespace std;


void greyScale(Image& image) //filter1
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

void applyBlackandWhite(Image& image)//filter2
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
void applyInvertFilter(Image &image)//filter3
{
   for (int i = 0; i < image.width; ++i)
   {
      for (int j = 0; j < image.height; ++j)
      {
         for (int k = 0; k < 3; ++k)
         {
            image.setPixel(i, j, k, 255 - image.getPixel(i, j, k));
         }
      }
   }
}
void addFrame(Image& photo, int frameType)//fiter4
{
   const int width = photo.width;
   const int height = photo.height;
   for (int i = 0; i< width; ++i)
   {
      for (int j = 0; j < height; ++j)
      {
         int d = min({i, j, width - 1 - i, height - 1 - j});
         int r, g, b;
         if (frameType == 1)
         {
            if (d >= 10) continue;
            r = 255; g = 0; b = 255;
         }
         else if (frameType == 2)
         {
            if (d >= 18 && d <= 20) r = g = b = 255;
            else if (d < 15) 
            {r = 180; g = 50; b = 200;}
            else
            {
               continue;
            }
         }
         else{return;}
         photo (i, j, 0) = r;
         photo(i, j, 1) = g;
         photo(i, j, 2) = b;

      }
   }
}

void flipImage(Image& image, char direction)//filter5
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

void applyRotateImage(Image& image)//filter6
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

void darkenImage(Image &img)//filter7
{
   for (int i = 0; i < img.height; ++i)
      for (int j = 0; j < img.width; ++j)
         for (int k = 0; k < 3; ++k)
            img(j, i, k) *= 0.5;
}
void lightenImage(Image &img)//filter7
{
   for (int i = 0; i < img.height; ++i)
      for (int j = 0; j < img.width; ++j)
         for (int k = 0; k < 3; ++k)
            img(j, i, k) = img(j, i, k) + (255 - img(j, i, k)) * 0.5;
}

Image resizePhoto(Image& image, int newWidth, int newHeight)//fiter8
 {
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
/*bool mergeImage(Image& theImage) //filter9
{
   cout << "Enter the path of other image, ex (image.png): ";
   string theOtherImage; cin >> theOtherImage;
   Image otherImage;
   try
   {
      otherImage.loadNewImage(theOtherImage);
   }
   catch(...)
   {
      cout << "Error, " << theOtherImage << "is not loaded\n";
      return false;
   }
   int option = 1, x = (theImage.width - otherImage.width) / 2, y = (theImage.height - otherImage.height) / 2;
   if (theImage.width != otherImage.width || theImage.height != otherImage.height)
   {
      cout << "Different sizes, plaese choose from options\n"
         << "option 1 resize both or option 2 merge the common area, enter 1 or 2: ";
      cin >> option;
      if (option == 2)
      {
         cout << "Enter x and y, the place of the other image on x,y respectivly: ";
         cin >> x >> y;
      }
   }
   if (option != 1 && option != 2)
   {
      cout << "Invalid option";
      return false;
   }
   int left = max(0, x), top = max(0, y);
   int right = min(theImage.width, x + otherImage.width), bottom = min(theImage.height, y + otherImage.height);
   if (option == 2 && (right <= left || bottom <= top))
   {
      cout << "There is no overlapping\n";
      return false;
   }
   if (option == 1)
   {
      int w = max(theImage.width, otherImage.width), h = max(theImage.height, otherImage.height);
      theImage = resizePhoto(theImage, w, h);
      otherImage = resizePhoto(otherImage, w, h);
      left = top = x = y = 0;
      right = w;
      bottom = h;
   }
   Image merging(right - left, bottom - top);
   for (int i = 0; i < merging.width; ++i)
   {
      for (int j = 0; j < merging.height; ++j)
      {
         for (int k = 0; k < 3; ++k)
         {
            merging(i, j, k) = (theImage(left + i, top + j, k) + otherImage(left + i - x, top + j - y, k)) / 2;
         }
      }
   }
   theImage = merging;
   return true;
}*/
void applyDetectImageEdges(Image &image)
{
   applyBlackandWhite(image);
   Image newimage(image.width, image.height);
   for (int i = 0; i < image.width - 1; ++i)
   {
      for (int j = 0; j < image.height - 1; ++j)
      {
         if (image(i, j, 0) != image(i + 1, j, 0) || image(i, j, 0) != image(i, j + 1, 0))
         {
            for (int k = 0; k < 3; ++k)
            {
               newimage(i, j, k) = 0;
            }
         }
         else
         {
            for (int k = 0; k < 3; ++k)
            {
               newimage(i, j, k) = 255;
            }
         }
      }
   }

   image = newimage;
}
void cropImage(Image &img, int x, int y, int W, int H)
{
   if (x < 0 || y < 0 || x + W > img.width || y + H > img.height || W <= 0 || H <= 0)
   {
      return;
   }

   Image croppedImage(W, H); //filter 11
   for (int i = 0; i < W; ++i)
   {
      for (int j = 0; j < H; ++j)
      {
         for (int c = 0; c < 3; ++c)
         {
            croppedImage(i, j, c) = img(x + i, y + j, c);
         }
      }
   }
   img = croppedImage;
}
/*void setBlur(Image &photo, int level) //filter12
{
   Image newPhoto(photo.width, photo.height);
   for (int i = 0; i < photo.height; ++i)
   {
      for (int j = 0; j < photo.width; ++j)
      {
         int sumR = 0;
         int sumG = 0;
         int sumB = 0;
         int count = 0;
         for (int dx = -level; dx <= level; ++dx)
         {
            for (int dy = -level; dy <= level; ++dy)
            {
               int ni = i + dx;
               int nj = j + dy;
               if (ni >= 0 && ni < photo.height && nj >= 0 && nj < photo.width)
               {
                  sumR += photo.getPixel(nj, ni, 0);
                  sumG += photo.getPixel(nj, ni, 1);
                  sumB += photo.getPixel(nj, ni, 2);
                  ++count;
               }
            }
         }
         int newR = sumR / count;
         int newG = sumG / count;
         int newB = sumB / count;
         newPhoto.setPixel(j, i, 0, newR);
         newPhoto.setPixel(j, i, 1, newG);
         newPhoto.setPixel(j, i, 2, newB);
      }
   }
   photo = newPhoto;
}*/
/*void sunlight(Image &theImage) //filter13
{
   int yelow[3] = {255, 255, 0};
   for (int i = 0; i < theImage.width; ++i)
   {
      for (int j = 0; j < theImage.height; ++j)
      {
         for (int k = 0; k < 3; ++k)
         {
            theImage(i, j, k) = 0.75 * theImage(i, j, k) + 0.25 * yelow[k];
         }
      }
   }
}*/
void applyScanlineFilter(Image &image)//filter14
{

   for (int i = 0; i < image.width; ++i)
   {
      for (int j = 0; j < image.height; ++j)
      {
         for (int k = 0; k < 3; ++k)
         {
            if (j % 2 == 0)
            {
               image(i, j, k) *= 0.5;
            }
            else
            {
               image(i, j, k) = min(255, image(i, j, k) + 15);
            }
         }
      }
   }
}
void applyPurpleFilter(Image &image)//filter15
{
   for (int i = 0; i < image.width; ++i)
   {
      for (int j = 0; j < image.height; ++j)
      {
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
/*void applyInfrared(Image &photo)//filter16
{
   for (int i = 0; i < photo.width; ++i)
   {
      for (int j = 0; j < photo.height; ++j)
      {
         for (int k = 0; k < 3; ++k)
         {
            if (k == 0)
            {
               photo(i, j, k) = 255;
            }
            else if (k == 1 || k == 2)
            {
               int originalvalue = photo(i, j, k);
               photo(i, j, k) = 255 - originalvalue;
            }
         }
      }
   }
}*/
/*void skewImage(Image &myImage, double degrees)//filter17 bonus 1
{
   double t = tan(degrees * 3.141 / 180);
   int newWidth = myImage.width + (int)(myImage.height * t + 0.5);
   Image temp(newWidth, myImage.height);
   for (int i = 0; i < newWidth; ++i)
   {
      for (int j = 0; j < myImage.height; ++j)
      {
         for (int k = 0; k < 3; ++k)
            temp(i, j, k) = 255;
      }
   }
   for (int j = 0; j < myImage.height; ++j)
   {
      int shift = (int)((myImage.height - 1 - j) * t + 0.5);
      for (int i = 0; i < myImage.width; ++i)
      {
         for (int k = 0; k < 3; ++k)
            temp(i + shift, j, k) = myImage(i, j, k);
      }
   }
   myImage = temp;
}*/
void applyOilPainting(Image &image) //filter18 bonus 2
{
   Image newimage(image.width, image.height);
   int radius = 2;
   int levels = 15;

   for (int i = 0; i < image.width; i++)
   {
      for (int j = 0; j < image.height; j++)
      {
         int intensityCount[256] = {0};
         long rSum[256] = {0};
         long gSum[256] = {0};
         long bSum[256] = {0};

         for (int dx = -radius; dx <= radius; dx++)
         {
            for (int dy = -radius; dy <= radius; dy++)
            {
               int nx = i + dx;
               int ny = j + dy;

               if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height)
               {

                  unsigned char r = image(nx, ny, 0);
                  unsigned char g = image(nx, ny, 1);
                  unsigned char b = image(nx, ny, 2);

                  int curIntensity = (r + g + b) / 3;
                  int level = (curIntensity * levels) / 255;

                  intensityCount[level]++;
                  rSum[level] += r;
                  gSum[level] += g;
                  bSum[level] += b;
               }
            }
         }

         int maxFrequency = 0;
         int bestLevel = 0;
         for (int l = 0; l < levels; l++)
         {
            if (intensityCount[l] > maxFrequency)
            {
               maxFrequency = intensityCount[l];
               bestLevel = l;
            }
         }

         if (maxFrequency > 0)
         {
            newimage(i, j, 0) = rSum[bestLevel] / maxFrequency;
            newimage(i, j, 1) = gSum[bestLevel] / maxFrequency;
            newimage(i, j, 2) = bSum[bestLevel] / maxFrequency;
         }
         else
         {
            for (int k = 0; k < 3; k++)
            {
               newimage(i, j, k) = image(i, j, k);
            }
         }
      }
   }
   image = newimage;
}

void Save(Image &image, bool &isModified)
{
   if (!isModified)
      return;
   cout << "You have unsaved Image, will you save it first (y/n)";
   char saveImage;
   cin >> saveImage;
   if (saveImage == 'y' || saveImage == 'Y')
   {
      cout << "Enter name of file to save (ex., iamge.jpg): ";
      string imageName;
      cin >> imageName;
      try
      {
         image.saveImage(imageName);
         cout << "Saved successfully" << '\n';
         isModified = false;
      }
      catch (...)
      {
         cout << "Failed" << '\n';
      }
   }
}
bool loadImage(Image &image, string &imageName, bool &isModified)
{
   while (true)
   {
      cout << "Enter image name to edit or 'cancel' to skip: ";
      cin >> imageName;
      if (imageName == "cancel")
         return false;
      try
      {
         image.loadNewImage(imageName);
         cout << "image loaded";
         isModified = false;
         return true;
      }
      catch (...)
      {
         cout << "Error !!!" << imageName << " is not loaded" << ", try again" << endl;
      }
   }
}
void skewImage(Image &myImage, double degrees)
{
   double t = tan(degrees * 3.141 / 180);
   int newWidth = myImage.width + (int)(myImage.height * t + 0.5);
   Image temp(newWidth, myImage.height);
   for (int i = 0; i < newWidth; ++i)
   {
      for (int j = 0; j < myImage.height; ++j)
      {
         for (int k = 0; k < 3; ++k)
            temp(i, j, k) = 255;
      }
   }
   for (int j = 0; j < myImage.height; ++j)
   {
      int shift = (int)((myImage.height - 1 - j) * t + 0.5);
      for (int i = 0; i < myImage.width; ++i)
      {
         for (int k = 0; k < 3; ++k)
            temp(i + shift, j, k) = myImage(i, j, k);
      }
   }
   myImage = temp;
}
void sunlight(Image &theImage)
{
   int yelow[3] = {255, 255, 0};
   for (int i = 0; i < theImage.width; ++i)
   {
      for (int j = 0; j < theImage.height; ++j)
      {
         for (int k = 0; k < 3; ++k)
         {
            theImage(i, j, k) = 0.75 * theImage(i, j, k) + 0.25 * yelow[k];
         }
      }
   }
}
bool mergeImage(Image &theImage) // the first code i did tried three diff ones

{
   cout << "Enter the path of other image, ex (image.png): ";
   string theOtherImage;
   cin >> theOtherImage;
   Image otherImage;
   try
   {
      otherImage.loadNewImage(theOtherImage);
   }
   catch (...)
   {
      cout << "Error, " << theOtherImage << " is not loaded\n";
      return false;
   }
   int option = 1, x = (theImage.width - otherImage.width) / 2, y = (theImage.height - otherImage.height) / 2; // x and y are the top left of the other image on the image
   if (theImage.width != otherImage.width || theImage.height != otherImage.height)
   {
      cout << "Different sizes, plaese choose from options\n"
           << "option 1 resize both or option 2 merge the common area, enter 1 or 2: ";
      cin >> option;
      if (option == 2)
      {
         cout << "Enter x and y, the place of the other image on x,y respectivly: ";
         cin >> x >> y;
      }
   }
   if (option != 1 && option != 2)
   {
      cout << "Invalid option";
      return false;
   }
   int left = max(0, x), top = max(0, y);
   int right = min(theImage.width, x + otherImage.width), bottom = min(theImage.height, y + otherImage.height);
   if (option == 2 && (right <= left || bottom <= top))
   {
      cout << "There is no overlapping\n";
      return false;
   }
   if (option == 1)
   {
      int w = max(theImage.width, otherImage.width), h = max(theImage.height, otherImage.height);
      theImage = resizePhoto(theImage, w, h);
      otherImage = resizePhoto(otherImage, w, h);
      left = top = x = y = 0;
      right = w;
      bottom = h;
   }
   Image merging(right - left, bottom - top);
   for (int i = 0; i < merging.width; ++i)
   {
      for (int j = 0; j < merging.height; ++j)
      {
         for (int k = 0; k < 3; ++k)
         {
            merging(i, j, k) = (theImage(left + i, top + j, k) + otherImage(left + i - x, top + j - y, k)) / 2;
         }
      }
   }
   theImage = merging;
   return true;
}
void setBlur(Image &photo, int level)
{
   Image newPhoto(photo.width, photo.height);
   for (int i = 0; i < photo.height; ++i)
   {
      for (int j = 0; j < photo.width; ++j)
      {
         int sumR = 0;
         int sumG = 0;
         int sumB = 0;
         int count = 0;
         for (int dx = -level; dx <= level; ++dx)
         {
            for (int dy = -level; dy <= level; ++dy)
            {
               int ni = i + dx;
               int nj = j + dy;
               if (ni >= 0 && ni < photo.height && nj >= 0 && nj < photo.width)
               {
                  sumR += photo.getPixel(nj, ni, 0);
                  sumG += photo.getPixel(nj, ni, 1);
                  sumB += photo.getPixel(nj, ni, 2);
                  ++count;
               }
            }
         }
         int newR = sumR / count;
         int newG = sumG / count;
         int newB = sumB / count;
         newPhoto.setPixel(j, i, 0, newR);
         newPhoto.setPixel(j, i, 1, newG);
         newPhoto.setPixel(j, i, 2, newB);
      }
   }
   photo = newPhoto;
}
void applyInfrared(Image &photo)
{
   for (int i = 0; i < photo.width; ++i)
   {
      for (int j = 0; j < photo.height; ++j)
      {
         for (int k = 0; k < 3; ++k)
         {
            if (k == 0)
            {
               photo(i, j, k) = 255;
            }
            else if (k == 1 || k == 2)
            {
               int originalvalue = photo(i, j, k);
               photo(i, j, k) = 255 - originalvalue;
            }
         }
      }
   }
}
int main()
{
   Image theImage;
   string imageName;
   bool isModified = false, running = true;
   cout << "== Image Procesing program ===" << '\n';
   while (true)
   {
      cout << "Enter path of Image to edit: ";
      cin >> imageName;
      try
      {
         theImage.loadNewImage(imageName);
         cout << "\nImage loaded\n" << endl;
         break;
      }
      catch (...)
      {
         cout << "Error !!!" << imageName << " is not loaded" << ", try again" << endl;
      }
   }
   while (running)
   {
      cout << "\n--------------------------------\n";
      cout << "1. Load New Image\n";
      cout << "2. edit with Greysacle Filter\n";               // filter1
      cout << "3. edit with Black and White Filter\n";        // filter2
      cout << "4. edit with Invert Image Filter\n";          //filter 3
      cout << "5. edit by Adding a frame Filter\n";         // filter4
      cout << "6. edit by Flipping the iamge Filter\n";    // filter5
      cout << "7. edit by Rotating image Filter\n";       // filter6
      cout << "8. edit with Darken of Lighten Filter\n"; //filter7
      cout << "9. edit by Resizing the image Filter\n"; // filter8
      cout << "10. Merge with another Image\n"; //filter9
      cout << "11. Apply Detect Edges Filter\n";
      cout << "12. Crop Image Filter\n";
      cout << "13. Blur the Image Filter\n";
      cout << "14. add more SunLight Filter\n";
      cout << "15. Apply Scanlines Filter\n";
      cout << "16. Apply Purple effect Filter\n";
      cout << "17. Apply Infrared effect Filter\n";
      cout << " 18. Skewing the Image Filter\n";
      cout << "19 . apply the Oil Painting effect filter\n";
      cout << "20. Save Image\n";
      cout << "21. Exit\n";
      cout << "Kindly Choose an option from the above: ";
      int choise;
      cin >> choise;
      switch (choise)
      {
      case 1:
      {
         Save(theImage, isModified);
         loadImage(theImage, imageName, isModified);
         cout << "\n Image is Loaded!\n";
         break;
      }
      case 2:
      {
         greyScale(theImage);
         isModified = true;
         cout << "grey scale filter applied\n";
         break;
      }
      case 3:
      {
         applyBlackandWhite(theImage);
         isModified = true;
         cout << "Black & White applied.\n";
         break;
      }
      case 4:
      {
         applyInvertFilter(theImage);
         isModified = true;
         cout << "Invert Image applied\n";
         break;
      }
      case 5:
      {
         bool frameType;
         addFrame(theImage, frameType);
         isModified = true;
         cout << "Frame added.\n";
         break;
      }
      case 6:
      {
         cout << "Enter the flipping direction ('h' - 'v'): ";
         char direction;
         cin >> direction;
         flipImage(theImage, direction);
         isModified = true;
         cout << "Image flipped.\n";
         break;
      }
      case 7:
      {
         applyRotateImage(theImage);
         isModified = true;
         break;
      }
      case 8:
      {
         cout << "For image darken 'd' - for image lighten 'l'\n";
         char choice; cin >> choice;
         if (choice == 'd' || choice == 'D')
         {
            darkenImage(theImage);
            isModified = true;
            break;
         }
         else if (choice == 'l' || choice == 'L')
         {
            lightenImage(theImage);
            isModified = true;
            break;
         }
         break;
         
      } 
      case 9:
      {
         int w, h;
         cout << "Enter target width : ";
         cin >> w;
         cout << "Enter target hight : ";
         cin >> h;
         theImage = resizePhoto(theImage, w, h);
         isModified = true;
         cout << "Image resized.\n";
         break;
      }
      case 10:
      {
         if (mergeImage(theImage))
         {
            isModified = true;
            cout << "Image merged.\n";
         }
         break;
      }
      case 11:
      {
         applyDetectImageEdges(theImage);
         isModified = true;
         cout << "Edge detection applied.\n";
         break;
      }
      case 12:
      {
         cout << "Image size is " << theImage.width << " x " << theImage.height<< '\n';
      }
      case 13:
      {
         int level;
         cout << "Enter blurring index, from 1 - 20\n";
         if (level < 1)break;
         setBlur(theImage, level);
         isModified = true;
         cout << "Image blur Applied\n";
         break;

      }
      case 14:
      {
         sunlight(theImage);
         isModified = true;
         cout << "SunLight effect applied\n";
         break;
      }
      case 15:
      {
         applyScanlineFilter(theImage);
         isModified = true;
         cout << "ScanLine filter applied\n";
         break;
      }
      case 16:
      {
         applyPurpleFilter(theImage);
         isModified = true;
         cout << "Purple filter applied\n";
         break;
      }
      case 17:
      {
         applyInfrared(theImage);
         isModified = true;
         cout << "Infrared effect applied\n";
         break;
      }
      case 18:
      {
         double degrees;
         cout << "Enter skew angle in degrees (0 - 80): ";
         if (!(cin >> degrees) || degrees <= 0 || degrees >= 85)
         {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');//weird smth i found on the internet that fixes the problem
            cout << "Invalid angle\n";
            break;
         }
         skewImage(theImage, degrees);
         isModified = true;
         cout << "Image skewed\n";
         break;
      }
      case 19:
      {
         applyOilPainting(theImage);
         isModified = true;
         cout << "Oil painting filter applied.\n";
         break;
      }
      case 20:
      {
         cout << "Enter Image name to save image as: ";
         string savedImage;
         cin >> savedImage;
         try
         {
            theImage.saveImage(savedImage);
            isModified = false;
            cout << "Image saved.\n";
         }
         catch (...)
         {
            cout << "Error saving image.\n";
         }
         break;
      }
      case 21:
      {
         Save(theImage, isModified);
         running = false;
         cout << "Exiting the Program Bye Bye !!!\n";
         break;
      }
      default:
      {
         cout << "Invalid Input, choose from the above Options please!!!\n";
         break;
      }
      }
   }
   return 0;
}