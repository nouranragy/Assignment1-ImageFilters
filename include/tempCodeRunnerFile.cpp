void greyScale(Image &image)
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