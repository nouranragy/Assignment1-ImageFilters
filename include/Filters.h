#ifndef FILTERS_H
#define FILTERS_H

#include "Image_Class.h"

void greyScale(Image &image);
void applyBlackandWhite(Image &image);
void applyInvertFilter(Image &image); 
void addFrame(Image &image);
void flipImage(Image &image, char direction);
void applyRotateImage(Image &image);
void darkenImage(Image &img);
void lightenImage(Image &img);
Image resizePhoto(Image &image, int newWidth, int newHeight);

#endif