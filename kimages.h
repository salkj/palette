#include <iostream>
#include <string>
#include <vector>
#include "CImg.h"
#include "kmeans.h"

using namespace std;
using namespace cimg_library;

class kimages {
private:
    int k;
    CImg<unsigned char> image;
    string path;
    kmeans* worker;
public:
    kimages(string path, int k);
    vector<point> getPalette();
    void displayPalette();
    void rebuildImage();
    void rebuildGif();
};

