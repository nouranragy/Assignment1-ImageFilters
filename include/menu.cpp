#include "Filters.h"
#include <iostream>
#include <string>
// #include "stb_image_write.h"
// #include "stb_image.h"
#include "Image_Class.h"
using namespace std;

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