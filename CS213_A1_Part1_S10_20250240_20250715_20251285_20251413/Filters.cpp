#include "Filters.h"

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

void applyRotateImage(Image& image , int angle)
{


    if(angle == 90)
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
    else if(angle == 180)
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

    else if(angle == 270)
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
                    image(i,j,k) = std::min(255 , image(i,j,k) +15);
                }
            }
        }
    }
}





