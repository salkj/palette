#include <iostream>
#include <string>
#include <vector>
#include "CImg.h"
#include "kmeans.h"

using namespace std;
using namespace cimg_library;

class kimages {
private:
    int*** map;
    int k;
    CImg<unsigned char> image;
    string path;
public:
    kimages(string path, int k);
    vector<point> getPalette();
    void displayPalette();
};

