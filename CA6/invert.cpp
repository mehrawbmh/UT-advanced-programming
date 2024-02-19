#include "invert.hpp"

InvertFilter::InvertFilter(View _view) : Filter(_view) {}

Bmp InvertFilter::apply() {
    Bmp newBmp;
    BMP::create(newBmp, this->previous.infoHdr.width, this->previous.infoHdr.height);
    for (int i = 0; i < this->previous.infoHdr.width; i++) {
        for (int j = 0; j < this->previous.infoHdr.height; j++) {
            if (this->containsView(i, j, view)) {
                newBmp.data[i][j] = Pixel(
                        255 - this->previous.data[i][j].red,
                        255 - this->previous.data[i][j].grn,
                        255 - this->previous.data[i][j].blu
                );
            } else {
                newBmp.data[i][j] = this->previous.data[i][j];
            }
        }
    }
    return newBmp;
}
