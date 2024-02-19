#include "filter.hpp"
#include <iostream>

using namespace std;

Filter::Filter(View _view) {
    this->view = _view;
}

Bmp Filter::readBmp(const string &inputFile) {
    Bmp bmp;
    ReadResult result = BMP::read(bmp, inputFile);
    if (result != ReadResult::success) {
        throw runtime_error("invalid bmp file provided");
    }
    return bmp;
}

void Filter::writeBmp(const string &outputFile, Bmp bmp) {
    BMP::write(bmp, outputFile);
}

void Filter::setPhoto(Bmp picture) {
    this->previous = picture;
}

bool Filter::containsView(int i, int j, const View &_view) {
    return (i >= _view.x) && (i < (_view.x + _view.h)) &&
           (j >= _view.y) && (j < _view.y + _view.w);
}
