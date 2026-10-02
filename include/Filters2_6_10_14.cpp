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

void applyDetectImageEdges(Image& image)
{
   applyBlackandWhite(image);
   Image newimage(image.width , image.height);
    for(int i = 0; i < image.width-1 ; ++i)
    {
      for(int j = 0; j< image.height-1 ; ++j)
      {
         if(image( i,j,0) != image(i +1 , j,0) || image(i,j,0)!= image(i,j+1 , 0) )
            {
            for(int k =0 ; k < 3; ++k)
            {
                newimage(i,j,k) = 0;
             }
             
            }
            else 
            {
             for(int k =0 ; k < 3; ++k)
            {
                newimage(i,j,k) = 255;
             }
            }
         
      }
    }

    image = newimage;
  
}

void applyScanlineFilter(Image& image)
{
   
    for(int i = 0; i < image.width ; ++i)
   {
      for(int j = 0; j< image.height ; ++j)
      {
         for(int k =0 ; k < 3; ++k)
         {
            if(j % 2 == 0) 
            {
            image(i,j,k) *=0.5;

            }
            else
            {
               image(i,j,k) = min(255 , image(i,j,k) +15);
            }
         }
      }
   }
}
int main()
{
   string filename , outputFilename;
   cout << "Please enter image name:" << endl;
   cin >> filename;

   Image image(filename);

   int choice;
   cout << "Choose Filter:\n1. Black & White\n2. Rotate Image\n3. Both (Black & White + Rotate) \n4.DetectImageEdges \n5.ScanlineFilter\nEnter choice: " << endl;
   cin >> choice;

   if(choice == 1){
      applyBlackandWhite(image);
   }
   else if(choice == 2){
      applyRotateImage(image);
   }
    else if(choice == 3){
      applyRotateImage(image);
      applyBlackandWhite(image);
   }
   else if(choice == 4)
   {
     applyDetectImageEdges(image);
   }
   else if(choice == 5)
   {
     applyScanlineFilter(image);
   }
   
   
   cout<<"Please enter the output image name (e.g., result.png)" << endl;
   cin >> outputFilename;
   image.saveImage(outputFilename);

   cout << "Done successfully!" << endl;

    
   return 0;

}