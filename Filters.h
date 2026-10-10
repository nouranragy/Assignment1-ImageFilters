#ifndef FILTERS_H
#define FILTERS_H

#include "Image_Class.h"


void greyScale(Image& image); //filter1
void applyBlackandWhite(Image& image);
void applyRotateImage(Image& image , int angle);
void flipImage(Image& image, char direction);//filter5
Image resizePhoto(Image& image, int newWidth, int newHeight);
void addFrame(Image& photo, int frameType);
void applyInfrared(Image& photo);
void setBlur(Image& photo, int level);
bool mergeImage(Image& theImage);
void applyDetectImageEdges(Image& image);
void applyScanlineFilter(Image& image);
void sunlight(Image& theImage);
void skewImage(Image& myImage, double degrees);
#endif // FILTERS_H
