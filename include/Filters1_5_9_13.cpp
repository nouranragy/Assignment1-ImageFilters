#include "Image_Class.h"
#include <algorithm>
using namespace std;

void greyScale(Image &image)
{
   for (int i = 0; i < image.width; ++i)
   {
      for (int j = 0; j < image.height; ++j)
      {
         unsigned int clr = 0; // clr is short for color
         for (int k = 0; k < image.channels; ++k)
            clr += image(i, j, k);
         clr /= 3;
         for (int k = 0; k < image.channels; ++k)
            image(i, j, k) = clr;
      }
   }
}

void flipImage(Image &image, char direction)
{                                         // temporary is an image copy to not overwrite thr imag and the changes then would be zzzzerro
   Image temp(image.width, image.height); // temp is for temporary
   for (int i = 0; i < image.width; ++i)
   {
      for (int j = 0; j < image.height; ++j)
      {
         int inew = i;
         int jnew = j;
         if (direction == 'h')
            inew = image.width - 1 - i;
         else if (direction == 'v')
            jnew = image.height - 1 - j;
         for (int k = 0; k < image.channels; ++k)
            temp(inew, jnew, k) = image(i, j, k);
      }
   }
   image = temp;
} // DO NOT COPY THATS AN OLD FILTER BUT MY FILTER USES IT AS WELL!!!!
Image resizePhoto(Image &image, int newWidth, int newHeight)
{
   Image newPhoto(newWidth, newHeight);
   double scaleX = (double)image.width / newWidth;
   double scaleY = (double)image.height / newHeight;
   for (int i = 0; i < newWidth; ++i)
   {
      for (int j = 0; j < newHeight; ++j)
      {

         int origX = (int)((i + 0.5) * scaleX);
         int origY = (int)((j + 0.5) * scaleY);
         if (origX >= image.width)
            origX = image.width - 1;
         if (origY >= image.height)
            origY = image.height - 1;
         for (int k = 0; k < 3; ++k)
         {
            newPhoto(i, j, k) = image(origX, origY, k);
         }
      }
   }
   return newPhoto;
} // filter 9
bool mergeImage(Image &theImage) // the first code i did tried three diff ones 

{
   cout << "Enter the path of other image, ex (image.png): ";
   string theOtherImage; cin >> theOtherImage;
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
      cout << "Different sizes, plaese choose from options\n" << "option 1 resize both or option 2 merge the common area, enter 1 or 2: ";
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

void sunlight(Image& theImage)
{
   int yelow[3] = {255, 255, 0};
   for(int i = 0; i < theImage.width; ++i)
   {
      for (int j = 0; j <theImage.height; ++j)
      {
         for(int k = 0; k < 3; ++k)
         {
            theImage(i, j, k) = 0.75 * theImage(i, j, k) + 0.25 * yelow[k];
         }
      }
   }
}