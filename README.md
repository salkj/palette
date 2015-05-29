Palette
==========================
k-means clustering is a method of vector quantization, originally from signal processing, that is popular for cluster analysis in data mining. k-means clustering aims to partition n observations into k clusters in which each observation belongs to the cluster with the nearest mean, serving as a prototype of the cluster. This results in a partitioning of the data space into Voronoi cells.

![alt tag](http://i.imgur.com/7ftALSy.png?1)

Functions
==========================

getPalette()
--------------------------
returns a vector of point structs that contain the r,g,b values of the palette.

displayPalette()
--------------------------
displays the original image with its corresponding palette superimposed.

rebuildImage()
--------------------------
after running k-means clustering on the data, we set each point's colour to its centroid's colour.

rebuildGif()
--------------------------
timelapse gif version of rebuildImage()

reduceGif(path, k)
--------------------------
takes a gif and reduce its colour to its k-determined palette.

Dependencies
==========================
- CImg 1.6.x

Sample
==========================
```
#include "kimages.h"

int main(){
  kimages foo("\pictures\image.bmp", 5);
  foo.displayPalette();
  return 0;
}
```

TODO
==========================
- Change the palettes of other images to fit new ones.
- Video colour change
- Fix for gifs with matte backgrounds or transparency.
