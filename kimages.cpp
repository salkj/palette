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

kimages::kimages(CImg<unsigned char> img, int k) {
	k = k < 1 ? 3 : k;
    worker = new kmeans(k);
    this->image = img;
    for (int r = 0; r < img.height(); r++) {
        for (int c = 0; c < img.width(); c++) {
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
	return worker->cluster(image.height(), image.width(), true);
}

void kimages::displayPalette(){
	vector<point> palette = this->getPalette();
	cout << palette.size() << " -- Palette Size" << endl;
	CImg<float> img_temp = this->image;

    for(int i=0, p=0;i<img_temp.width();i+=(int)(img_temp.width()/this->k)){
		for(int j=i;j<(int)(img_temp.width()/this->k)+i;j++){
			for(int q=0;q<(int)(img_temp.height()/4);q++){
				img_temp(j, q, 0, 0) = (int)palette[p].x;
				img_temp(j, q, 0, 1) = (int)palette[p].y;
				img_temp(j, q, 0, 2) = (int)palette[p].z;
			}
		}
		p++;
	}
	img_temp.save("palette.bmp");
}

void kimages::rebuildImage(){
	CImg<float> img_temp(image.width(), image.height(), 1, 3);
	vector<clusters> centers = worker->getClusters(image.height(), image.width(), true);
	for(int i=0;i<centers.size();i++){
		for(int j=0;j<centers[i].pts.size();j++){
			img_temp(centers[i].pts[j].col, centers[i].pts[j].row, 0, 0) = (int)centers[i].center.x;
			img_temp(centers[i].pts[j].col, centers[i].pts[j].row, 0, 1) = (int)centers[i].center.y;
			img_temp(centers[i].pts[j].col, centers[i].pts[j].row, 0, 2) = (int)centers[i].center.z;
		}
	}
	img_temp.save("rebuild.bmp");
}

void kimages::rebuildGif(){
	CImg<float> img_temp(image.width(), image.height(), 1, 3);
	vector<clusters> centers = worker->getClusters(image.height(), image.width(), true);
	CImgList<float> images;
	for(int i=0;i<centers.size();i++){
		for(int j=0;j<centers[i].pts.size();j++){
			img_temp(centers[i].pts[j].col, centers[i].pts[j].row, 0, 0) = (int)centers[i].center.x;
			img_temp(centers[i].pts[j].col, centers[i].pts[j].row, 0, 1) = (int)centers[i].center.y;
			img_temp(centers[i].pts[j].col, centers[i].pts[j].row, 0, 2) = (int)centers[i].center.z;
			// Need to make even
			if((centers[i].pts.size() % (j+1)) == 0){
				images.push_back(img_temp);
			}
		}
		images.push_back(img_temp);
	}
	images.push_back(img_temp);
	images.save_gif_external("rebuild.gif",25,0);
}

void kimages::reduceGif(string path, int k){
	CImgList<unsigned char> images;
	images.load_gif_external(path.c_str());
	CImgList<unsigned char> new_gif;
	for(int i=0;i<images.size();i++){
		kimages temp(images[i], k);
		CImg<unsigned char> reducedImage = temp.reduceImage();
		new_gif.push_back(reducedImage);
	}
	new_gif.save_gif_external("reducedGif.gif",15,0);
}

CImg<unsigned char> kimages::reduceImage(){
	CImg<unsigned char> img_temp(image.width(), image.height(), 1, 3);
	vector<clusters> centers = worker->getClusters(image.height(), image.width(), false);
	for(int i=0;i<centers.size();i++){
		for(int j=0;j<centers[i].pts.size();j++){
			img_temp(centers[i].pts[j].col, centers[i].pts[j].row, 0, 0) = (int)centers[i].center.x;
			img_temp(centers[i].pts[j].col, centers[i].pts[j].row, 0, 1) = (int)centers[i].center.y;
			img_temp(centers[i].pts[j].col, centers[i].pts[j].row, 0, 2) = (int)centers[i].center.z;
		}
	}
	return img_temp;
}
