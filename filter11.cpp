#include <iostream>
#include "Image_Class.h"
using namespace std;
void cropImage() {
    string filename = "toy1.jpg";
    Image image(filename);
    int x, y, W, H;
    cout << "Enter starting  point x and y: ";
    cin >> x >> y;
    cout << "Enter crop width and height (W H): ";
    cin >> W >> H;
    if (x < 0 || y < 0 || x + W > image.width || y + H > image.height) {
        cout << "Error: wrong sizes!" << endl;
        return;
    }
    Image croppedImage(W, H);
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            for (int c = 0; c < image.channels; ++c) {
                unsigned char val = image(x + i, y + j, c);
                croppedImage(i, j, c) = image(x + i, y + j, c);
            }
        }
    }
    string outputFilename = "toy1_cropped.png";
    
    croppedImage.saveImage(outputFilename);}
int main() {
    cropImage();
    
    
    return 0;
}


