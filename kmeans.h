#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct point {
        float x, y, z;
        float distanceTo(point b);
	};

class kmeans {
public:
    struct clusters {
        point center;
        vector<point> pts;
        float recenter();
    };
    kmeans(int*** map, int k);
    vector<point> cluster();
    
private:
    int*** map;
    int k;
};
