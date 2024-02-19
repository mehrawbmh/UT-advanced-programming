#ifndef IMAGEFILTER_EMBOSS_HPP
#define IMAGEFILTER_EMBOSS_HPP

#include "kernel.hpp"

class Emboss : public KernelFilter {
public:
    Emboss(View _view);

    Bmp apply() override;
};

#endif //IMAGEFILTER_EMBOSS_HPP
