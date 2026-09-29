#include <iostream>
#include "Image_Class.h"
using namespace std;

void addFrame(Image& photo) {
    for (int i = 0; i < photo.width; ++i) {
        for (int j = 0; j < photo.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (i < 10 || i > photo.width - 10 || j < 10 || j > photo.height - 10 ) {
                    if (k == 0) {
                        photo(i, j, k) = 255;
                    } else if (k == 1) {
                        photo(i, j, k) = 0;
                    } else if (k == 2) {
                        photo(i, j, k) = 255;
                    }
                }
            }
        }
    }
}

Image resizePhoto(Image& photo, int newWidth, int newHeight) {
    Image newPhoto(newWidth, newHeight);
    double scaleX = (double) photo.width / newWidth;
    double scaleY = (double) photo.height / newHeight;
    for (int i =0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {

                int origX = ( int ) ((i+0.5) * scaleX);
                int origY = ( int ) ((j+0.5) * scaleY);
                if (origX >= photo.width) origX = photo.width - 1;
                if (origY >= photo.height) origY = photo.height - 1;
                for (int k = 0; k < 3; ++k) {
                    newPhoto(i, j, k) = photo(origX, origY, k);
            }
        }
    }
    return newPhoto;
}

int main() {
    int choice;
    cout << "select a filter" << endl;
    cout << "4 to add a frame" << endl;
    cout << "8 to resize photo" << endl;
    cout << " Enter choice ( 4 or 8)" << endl;
    cin >> choice;

    if (choice == 4) {
        Image photo ("mario.bmp");
        addFrame(photo);
        photo.saveImage("marioFramed.jpg");
        cout << " frame applied " << endl;
    }
    else if (choice == 8) {
        Image photo ("mario.bmp");
        int newWidth, newHeight;
        cout << " Enter new width and height" << endl;
        cin >> newWidth >> newHeight;
        Image resized = resizePhoto(photo, newWidth, newHeight);
        resized.saveImage("marioresized.jpg");
        cout << "photo rsized" << endl;
    }
    else {
        cout << "Error" << endl;
    }

    return 0;
}
