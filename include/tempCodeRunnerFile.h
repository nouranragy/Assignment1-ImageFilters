#ifndef FILTERS_H
#define FILTERS_H

#include "Image_Class.h"

void greyScale(Image& image);
void applyBlackandWhite(Image& image);
void addFrame(Image& image);
void flipImage(Image& image, char direction);
void applyRotateImage(Image& image);
Image resizePhoto(Image& image, int newWidth, int newHeight);

#endif