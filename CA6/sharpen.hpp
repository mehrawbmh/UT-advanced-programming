#ifndef IMAGEFILTER_SHARPEN_HPP
#define IMAGEFILTER_SHARPEN_HPP

#include "kernel.hpp"

class Sharpen : public KernelFilter {
public:
    Sharpen(View _view);

    Bmp apply() override;
};

#endif //IMAGEFILTER_SHARPEN_HPP
