#include "Image_Class.h"
#include <vector>
using namespace std;

int main()
{
   Image image("issues.jpg");
   if (image.loadNewImage("issues.jpg"))
      cout << "Loading is done" << endl;
   cout << "for grey filter enter 1" << "\n"
        << "for flipping enter 2" << endl;
   int filter;
   cin >> filter;
   if (filter == 1)
   {
      for (int i = 0; i < image.width; ++i)
      {
         for (int j = 0; j < image.height; ++j)
         {
            unsigned int clr = 0; // clr is short for color
            for (int k = 0; k < image.channels; ++k)
               clr += image(i, j, k); // chaneel is for the value of clrs r,b,g
            clr /= 3;
            for (int k = 0; k < image.channels; ++k)
               image(i, j, k) = clr;
         }
      }
   }
   else
   {
      cout << " horizontal flip enter h : " << "\n"
           << " vertical flip enter v : " << endl;
      char direction;
      cin >> direction;
      Image temp(image.width, image.height);
      for (int i = 0; i < image.width; ++i)
      {
         for (int j = 0; j < image.height; ++j)
         {
            int inew = i; // inew = the new value of i
            int jnew = j; // same here
            if (direction == 'h')
               inew = image.width - 1 - i;
            else if (direction == 'v')
               jnew = image.height - 1 - j;
            for (int k = 0; k < image.channels; ++k)
               temp(inew, jnew, k) = image(i, j, k);
         }
      }
      image = temp;
   }
   if (image.saveImage("issues.png"))
      cout << "done editing" << endl;
}