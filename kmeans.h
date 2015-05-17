#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct point {
        float x, y, z;
        int col, row;
        float distanceTo(point b);
	};
	
struct clusters {
        point center;
        vector<point> pts;
        float recenter();
    };
    
class kmeans {
public:
    kmeans(int k);
    vector<point> cluster(int ih, int iw, bool t);
    vector<clusters> getClusters(int ih, int iw, bool t);
    void pushPointData(point a);
private:
	vector<point> init_data;
	vector<clusters> final_centers;
    int k;
};
