#ifndef IMAGEFILTER_BLUR_HPP
#define IMAGEFILTER_BLUR_HPP

#include "kernel.hpp"

class Blur : public KernelFilter {
public:
    Blur(View _view);

    Bmp apply() override;
};


#endif //IMAGEFILTER_BLUR_HPP
