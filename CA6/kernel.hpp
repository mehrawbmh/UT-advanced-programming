#ifndef IMAGEFILTER_KERNEL_HPP
#define IMAGEFILTER_KERNEL_HPP

#include "filter.hpp"
#include <vector>

class KernelFilter : public Filter {
public:
    KernelFilter(View _view);
protected:
    vector<vector<float>> matrix;

    Pixel applyKernel(const Bmp &bmp, int row, int col, const vector<vector<float>> &matrix);
};


#endif //IMAGEFILTER_KERNEL_HPP
