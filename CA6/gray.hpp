#ifndef IMAGEFILTER_GRAY_HPP
#define IMAGEFILTER_GRAY_HPP

#include <iostream>
#include "filter.hpp"

class GrayScale : public Filter {
private:
    Pixel getAvg(Pixel pixel);
public:
    GrayScale(View _view);
    GrayScale() = default;
    Bmp apply() override;
};


#endif //IMAGEFILTER_GRAY_HPP
