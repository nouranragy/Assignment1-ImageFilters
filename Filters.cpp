#include "Filters.h"
#include <algorithm>
#include<cmath>
using namespace std;

void applyPurpleFilter(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
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
void cropImage(Image& img, int x, int y, int W, int H) {
    if (x < 0 || y < 0 || x + W > img.width || y + H > img.height || W <= 0 || H <= 0) {
        return;
    }

    Image croppedImage(W, H);
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            for (int c = 0; c < 3; ++c) {
                croppedImage(i, j, c) = img(x + i, y + j, c);
            }
        }
    }
    img = croppedImage;
}

void darkenImage(Image& img) {
    for (int i = 0; i < img.height; ++i)
        for (int j = 0; j < img.width; ++j)
            for (int k = 0; k < 3; ++k)
                img(j, i, k) *=0.5;
}
void lightenImage(Image& img){
    for (int i = 0; i < img.height; ++i)
        for (int j = 0; j < img.width; ++j)
            for (int k = 0; k < 3 ; ++k)
                img(j, i, k) = img(j, i, k) + (255-img(j, i, k)) * 0.5;
}
void greyScale(Image& image) //filter1
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
void applyInvertFilter(Image& image) {
    for (int i= 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k ) {
                image.setPixel(i, j, k, 255 - image.getPixel(i, j, k));
            }
        }
    }
}
void flipImage(Image& image, char direction)
{
    Image temp(image.width, image.height);
    for (int i = 0; i < image.width; ++i)
        for (int j = 0; j < image.height; ++j)
            for (int k = 0; k < image.channels; ++k)
                temp(direction == 'h' ? image.width - 1 - i : i,
                     direction == 'v' ? image.height - 1 - j : j, k) = image(i, j, k);
    image = temp;
}
void addFrame(Image& photo, int frameType)
{
    const int width  = photo.width;
    const int height = photo.height;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            // Distance from the nearest edge (0 = outermost pixel)
            int d = min({ i, j, width - 1 - i, height - 1 - j });

            int r, g, b;

            if (frameType == 1) {
                // Solid magenta frame, 10px wide
                if (d >= 10) continue;
                r = 255; g = 0; b = 255;
            }
            else if (frameType == 2) {
                // Purple frame, 15px wide, with a white inner line at 18-20px
                if (d >= 18 && d <= 20) {
                    r = g = b = 255;
                } else if (d < 15) {
                    r = 180; g = 50; b = 200;
                } else {
                    continue;
                }
            }
            else {
                return; // unknown frame type: leave the photo untouched
            }

            photo(i, j, 0) = r;
            photo(i, j, 1) = g;
            photo(i, j, 2) = b;
        }
    }
}
void applyInfrared(Image& photo)
{
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
            int newR = sumR / count;
            int newG = sumG / count;
            int newB = sumB / count;
            newPhoto.setPixel(j ,i , 0 , newR);
            newPhoto.setPixel(j ,i , 1 , newG);
            newPhoto.setPixel(j ,i , 2 , newB);
        }
    }
    photo = newPhoto;
}

Image resizePhoto(Image& image, int newWidth, int newHeight)
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
}
bool mergeImage(Image& theImage) // the first code i did tried three diff ones

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
void skewImage(Image& myImage, double degrees)
{
    double t = tan(degrees * 3.141 / 180);
    int newWidth = myImage.width + (int)(myImage.height * t + 0.5);
    Image temp (newWidth, myImage.height);
    for (int i = 0; i < newWidth; ++i)
    {
        for (int j = 0; j <myImage.height; ++j)
        {
            for (int k = 0; k< 3; ++k) temp (i, j, k) = 255;
        }
    }
    for (int j = 0; j < myImage.height; ++j)
    {
        int shift = (int)((myImage.height - 1 - j) * t + 0.5);
        for (int i = 0; i< myImage.width; ++i)
        {
            for (int k = 0; k < 3; ++k) temp (i + shift, j, k) = myImage(i, j, k);

        }
    }
    myImage = temp;

}

void applyOilPainting(Image& image)
{
    Image newimage(image.width , image.height);
    int radius = 2;
    int levels = 15;

    for(int i =0 ;  i< image.width;i++){
        for(int j =0 ; j< image.height;j++){
            int intensityCount[256] = {0};
            long rSum[256] = {0};
            long gSum[256] = {0};
            long bSum[256] = {0};

            for(int dx = -radius ; dx<= radius ; dx++){
                for(int dy = -radius ; dy<= radius ; dy++){
                    int nx = i + dx;
                    int ny = j+dy;

                    if(nx >= 0 && nx < image.width && ny >= 0 && ny < image.height ){

                        unsigned char r = image(nx,ny,0);
                        unsigned char g = image(nx,ny,1);
                        unsigned char b = image(nx,ny,2);

                        int curIntensity = (r + g + b)/ 3;
                        int level =  (curIntensity * levels) /255;

                        intensityCount[level]++;
                        rSum[level] += r;
                        gSum[level] += g;
                        bSum[level] += b;
                    }
                }
            }

            int maxFrequency = 0;
            int bestLevel = 0;
            for(int l = 0; l < levels ; l++)
            {
                if(intensityCount[l] > maxFrequency){
                    maxFrequency = intensityCount[l];
                    bestLevel = l;
                }
            }

            if(maxFrequency > 0){
                newimage(i,j,0) = rSum[bestLevel] / maxFrequency;
                newimage(i,j,1) = gSum[bestLevel] / maxFrequency;
                newimage(i,j,2) = bSum[bestLevel] / maxFrequency;

            }
            else{
                for(int k = 0; k <3 ; k++){
                    newimage(i,j,k) = image(i,j,k);
                }
            }
        }
    }
    image = newimage;
}




