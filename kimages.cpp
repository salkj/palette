#include "kimages.h"

kimages::kimages(string path, int k) {
    this->map = new int**[256];
    for(int i=0; i<256; i++) {
        this->map[i] = new int*[256];
        for(int j=0; j<256; j++) {
            this->map[i][j] = new int[256];
        }
    }
    this->k = k;
    this->path = path;
    this->image.load(this->path.c_str());

    for (int r = 0; r < image.height(); r++) {
        for (int c = 0; c < image.width(); c++) {
            this->map[(int)image(c,r,0,0)][(int)image(c,r,0,1)][(int)image(c,r,0,2)] += 1;
        }
    }
}

vector<point> kimages::getPalette() {
    kmeans A(this->map, this->k);
    return A.cluster();
}

void kimages::displayPalette(){
	vector<point> palette = this->getPalette();
	cout << palette.size() << " -- Palette Size" << endl;
	CImg<float> img_temp = this->image;
	for (int r = 0; r < img_temp.height(); r++) {
        for (int c = 0; c < img_temp.width(); c++) {
            this->map[(int)image(c,r,0,0)][(int)image(c,r,0,1)][(int)image(c,r,0,2)] += 1;
        }
    }
    for(int i=0, p=0;i<img_temp.width();i+=(int)(img_temp.width()/this->k)){
		for(int j=i;j<(int)(img_temp.width()/this->k)+i;j++){
			for(int q=0;q<(int)(img_temp.height()/4);q++){
				img_temp(j, q, 0, 0) = palette[p].x;
				img_temp(j, q, 0, 1) = palette[p].y;
				img_temp(j, q, 0, 2) = palette[p].z;
			}
		}
		p++;
	}
	CImgDisplay main_disp(img_temp, "Palette");
	while (!main_disp.is_closed()){
        main_disp.wait();
    }
}
