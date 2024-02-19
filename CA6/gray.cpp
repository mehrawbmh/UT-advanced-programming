#include "gray.hpp"

Bmp GrayScale::apply() {
    Bmp newBmp;
    BMP::create(newBmp, this->previous.infoHdr.width, this->previous.infoHdr.height);
    for (int i = 0; i < this->previous.infoHdr.width; i++) {
        for (int j = 0; j < this->previous.infoHdr.height; j++) {
            if (this->containsView(i, j, this->view)) {
                newBmp.data[i][j] = this->getAvg(this->previous.data[i][j]);
            } else {
                newBmp.data[i][j] = this->previous.data[i][j];
            }
        }
    }
    return newBmp;
}

Pixel GrayScale::getAvg(Pixel pixel) {
    int avg = (pixel.red + pixel.blu + pixel.grn) / 3;
    return {static_cast<uint8_t>(avg), static_cast<uint8_t>(avg), static_cast<uint8_t>(avg)};
}

GrayScale::GrayScale(View _view) : Filter(_view) {}
