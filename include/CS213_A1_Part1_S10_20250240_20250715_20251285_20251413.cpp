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

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <iostream>
#include <string>
#include "Image_Class.h"
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
void applyInvertFilter(Image &image)
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
   void addFrame(Image & image)
   {
      for (int i = 0; i < image.width; ++i)
      {
         for (int j = 0; j < image.height; ++j)
         {
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

void darkenImage(Image &img)
{
   for (int i = 0; i < img.height; ++i)
      for (int j = 0; j < img.width; ++j)
         for (int k = 0; k < 3; ++k)
            img(j, i, k) *= 0.5;
}
void lightenImage(Image &img)
{
   for (int i = 0; i < img.height; ++i)
      for (int j = 0; j < img.width; ++j)
         for (int k = 0; k < 3; ++k)
            img(j, i, k) = img(j, i, k) + (255 - img(j, i, k)) * 0.5;
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
      cout << "10. Save Image\n";
      cout << "11. Exit\n";
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
         addFrame(theImage);
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
      case 11:
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