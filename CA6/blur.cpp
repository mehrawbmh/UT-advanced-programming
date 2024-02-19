#include "blur.hpp"

Blur::Blur(View _view) : KernelFilter(_view) {
    this->matrix = {{0.625, 0.125, 0.625},
                    {0.125, 0.25,  0.125},
                    {0.625, 0.125, 0.625}};
}

Bmp Blur::apply() {
    Bmp newBmp;
    BMP::create(newBmp, this->previous.infoHdr.width, this->previous.infoHdr.height);
    for (int i = 0; i < this->previous.infoHdr.width; i++) {
        for (int j = 0; j < this->previous.infoHdr.height; j++) {
            if (this->containsView(i, j, this->view)) {
                newBmp.data[i][j] = this->applyKernel(this->previous, i, j, this->matrix);
            } else {
                newBmp.data[i][j] = this->previous.data[i][j];
            }
        }
    }
    return newBmp;
}
