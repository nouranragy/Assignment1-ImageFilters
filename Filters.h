#ifndef FILTERS_H
#define FILTERS_H

#include "Image_Class.h"

void applyBlackandWhite(Image& image);
void applyRotateImage(Image& image , int angle);
void applyDetectImageEdges(Image& image);
void applyScanlineFilter(Image& image);
#endif // FILTERS_H
