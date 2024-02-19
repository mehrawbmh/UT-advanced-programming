#include "kernel.hpp"

KernelFilter::KernelFilter(View _view) : Filter(_view) {}

Pixel KernelFilter::applyKernel(const Bmp &bmp, int row, int col, const vector<vector<float>> &kernel) {
    float sumG = 0, sumR = 0, sumB = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int x = row + i;
            int y = col + j;

            if (x < 0 || x >= bmp.infoHdr.width) {
                x = row;
            }
            if (y < 0 || y >= bmp.infoHdr.height) {
                y = col;
            }

            sumB += static_cast<float>(bmp.data[x][y].blu) * kernel[i + 1][j + 1];
            sumG += static_cast<float>(bmp.data[x][y].grn) * kernel[i + 1][j + 1];
            sumR += static_cast<float>(bmp.data[x][y].red) * kernel[i + 1][j + 1];
        }
    }

    sumB = std::max(0.f, std::min(sumB, 255.f));
    sumR = std::max(0.f, std::min(sumR, 255.f));
    sumG = std::max(0.f, std::min(sumG, 255.f));

    return {static_cast<uint8_t>(sumR), static_cast<uint8_t>(sumG), static_cast<uint8_t>(sumB)};
}
