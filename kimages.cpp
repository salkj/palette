#include "kimages.h"

kimages::kimages(string path, int k) {
	this-> k = k < 1 ? 3 : k;
    this->path = path;
    this->image.load(this->path.c_str());
    worker = new kmeans(this->k);
    for (int r = 0; r < image.height(); r++) {
        for (int c = 0; c < image.width(); c++) {
			point a;
			a.x = (int)image(c,r,0,0);
			a.y = (int)image(c,r,0,1);
			a.z = (int)image(c,r,0,2);
			a.col = c;
			a.row = r;
			worker->pushPointData(a);
        }
    }
}

vector<point> kimages::getPalette() {
	return worker->cluster(image.height(), image.width());
}

void kimages::displayPalette(){
	vector<point> palette = this->getPalette();
	cout << palette.size() << " -- Palette Size" << endl;
	CImg<float> img_temp = this->image;

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
	img_temp.save("palette.bmp");
	CImgDisplay main_disp(img_temp, "Palette");
	while (!main_disp.is_closed()){
        main_disp.wait();
    }
}

void kimages::rebuildImage(){
	CImg<float> img_temp(image.width(), image.height(), 1, 3);
	vector<clusters> centers = worker->getClusters(image.height(), image.width());
	for(int i=0;i<centers.size();i++){
		for(int j=0;j<centers[i].pts.size();j++){
			img_temp(centers[i].pts[j].col, centers[i].pts[j].row, 0, 0) = centers[i].center.x;
			img_temp(centers[i].pts[j].col, centers[i].pts[j].row, 0, 1) = centers[i].center.y;
			img_temp(centers[i].pts[j].col, centers[i].pts[j].row, 0, 2) = centers[i].center.z;
		}
	}
	img_temp.save("rebuild.bmp");
	CImgDisplay main_disp(img_temp, "Image Rebuild");
	while (!main_disp.is_closed()){
        main_disp.wait();
    }
}
