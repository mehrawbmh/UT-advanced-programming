#include "sharpen.hpp"

Sharpen::Sharpen(View _view) : KernelFilter(_view) {
    this->matrix = {{0,  -1, 0},
                    {-1, 5,  -1},
                    {0,  -1, 0}};
}

Bmp Sharpen::apply() {
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
