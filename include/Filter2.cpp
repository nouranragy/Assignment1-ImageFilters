#include "Image_Class.h"
#include <iostream>
using namespace std;

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
int main()
{
   string filename , outputFilename;
   cout << "Please enter colored image name to turn to black and white" << endl;
   cin >> filename;

   Image image(filename);
   
   applyBlackandWhite(image);
   
   cout<<"Please enter the output image name (e.g., result.png)" << endl;
   cin >> outputFilename;
   image.saveImage(outputFilename);

    
   return 0;

}