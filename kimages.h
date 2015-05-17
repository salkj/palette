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
    kimages(CImg<unsigned char> img, int k);
    CImg<unsigned char> reduceImage();
public:
    kimages(string path, int k);
    vector<point> getPalette();
    void displayPalette();
    void rebuildImage();
    void rebuildGif();
    void reduceGif(string path, int k);
};

