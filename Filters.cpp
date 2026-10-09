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

void addFrame(Image& photo, int frameType) {
    int width = photo.width;
    int height = photo.height;
    for (int i = 0; i < photo.width; ++i) {
        for (int j = 0; j < photo.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (frameType == 1) {
                    if (i < 10 || i > photo.width - 10 || j < 10 || j > photo.height - 10 ) {
                        if (k == 0) {
                            photo(i, j, k) = 255;
                        } else if (k == 1) {
                            photo(i, j, k) = 0;
                        } else if (k == 2) {
                            photo(i, j, k) = 255;
                        }
                    }
                } else if (frameType == 2) {
                    bool outer = (i < 15 || i >= width - 15 || j < 15 || j > height - 15 );
                    bool innerLine = ((i >= 18 && i <= 20) || (i >= width - 21 && i <= width - 19) || (j >= 18 && j <= 20) || (j >= height - 21 && j <= height - 19));
                    if (innerLine) {
                        photo(i, j, k) = 255;
                    } else if (outer) {
                        if (k == 0) {
                            photo(i, j, k) = 180;
                        } else if (k == 1) {
                            photo(i, j, k) = 50;
                        } else if (k == 2) {
                            photo(i, j, k) = 200;
                        }
                    }
                }
            }
        }
    }
}

void setBlur(Image& photo, int level) {
    Image newPhoto(photo.width, photo.height);
    for (int i = 0; i < photo.height; ++i) {
        for (int j = 0; j < photo.width; ++j) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            int count = 0;
            for (int dx = -level; dx <= level; ++dx) {
                for (int dy = -level; dy <= level; ++dy) {
                    int ni = i + dx;
                    int nj = j + dy;
                    if (ni >= 0 && ni < photo.height && nj >= 0 && nj < photo.width) {
                        sumR += photo.getPixel(nj , ni , 0);
                        sumG += photo.getPixel(nj , ni , 1);
                        sumB += photo.getPixel(nj , ni , 2);
                        ++count;
                    }
                }
            }
            if (count > 0) {
            int newR = sumR / count;
            int newG = sumG / count;
            int newB = sumB / count;
            newPhoto.setPixel(j ,i , 0 , newR);
            newPhoto.setPixel(j ,i , 1 , newG);
            newPhoto.setPixel(j ,i , 2 , newB);
            }
        }
    }
    photo = newPhoto;
}

void applyInfrared(Image& photo) {
    for (int i = 0; i < photo.width; ++i) {
        for (int j = 0; j < photo.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (k == 0) {
                    photo(i, j, k) = 255;
                } else if (k == 1 || k == 2) {
                    int originalvalue = photo(i, j, k);
                    photo(i, j, k) = 255 - originalvalue;
                }
            }
        }
    }
}




