#ifndef IMAGEFILTER_FILTER_HPP
#define IMAGEFILTER_FILTER_HPP

#include "bmp.hpp"
#include "string"

using namespace std;

struct View {
    int x = 0;
    int y = 0;
    int w = -1;
    int h = -1;
};

class Filter {
public:
    Filter(View _view);;

    Filter() = default;

    virtual Bmp apply() = 0;

    static Bmp readBmp(const string &inputFile);

    static void writeBmp(const string &outputFile, Bmp bmp);

    void setPhoto(Bmp picture);

protected:
    Bmp previous;

    View view = {0, 0, 100000, 100000};

    bool containsView(int i, int j, const View &view);
};

#endif //IMAGEFILTER_FILTER_HPP
