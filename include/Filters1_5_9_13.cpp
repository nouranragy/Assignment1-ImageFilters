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

int main()
{
   Image image("issues.jpg");
   if (image.loadNewImage("issues.jpg")) cout << "Laoding is done" << endl;
   cout << "for grey scale filter enter 1 : " << "\n" << "for flipping filter enter 2 : " << endl;
   int filter; cin >> filter;
   if (filter == 1) greyScale(image);
   else if (filter == 2)
   {
      cout << "for horizontal flip enter h : " << "\n" << "for vertical flip enter v : " << endl;
      char direction; cin >> direction;
      flipImage(image, direction);
   }
   if (image.saveImage("issues.png")) cout << "done editing" << endl;
}