#ifndef IMAGEFILTER_INVERT_HPP
#define IMAGEFILTER_INVERT_HPP

#include <iostream>
#include "bmp.hpp"
#include "filter.hpp"

class InvertFilter : public Filter {
public:
    InvertFilter(View _view);

    InvertFilter() = default;

    Bmp apply() override;
};

#endif //IMAGEFILTER_INVERT_HPP
