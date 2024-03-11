#include "tgaimage.h"
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

// dimentions of the image 
const int width = 100;
const int height = 100;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

int main(int argc, char** argv) {
        TGAImage image(height, width, TGAImage::RGB);
        image.set(50, 50, red);
        line(13, 20, 80, 40, image, white); 
        line(20, 13, 40, 80, image, red); 
        line(80, 40, 13, 20, image, red);

        
        image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
        image.write_tga_file("output.tga");
        return 0;

}

// void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
//     for (float t=0.; t<1.; t+=.0001) { 
//         int x = x0 + (x1-x0)*t; 
//         int y = y0 + (y1-y0)*t; 
//         image.set(x, y, color); 
//     } 
// }

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 

    // check if x0 is greater than x1
    bool steep = false;
    if (std::abs(x1-x0) < std::abs(y1-y0)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

        if (x0>x1) { // make it left−to−right 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 

    for (int x=x0; x<=x1; x++) { 

        // t = the percentage of the distance covered from x0 to x1
        float t = (x-x0)/(float)(x1-x0); 

        // y is calculated as y0 + (y1-y0)*t
        int y = y0*(1.-t) + y1*t; 


        // check for out of bounds
        if (x >= 0 && x < image.get_width() && y >= 0 && y < image.get_height()) {
            if (steep) {
                image.set(y, x, color);
            } else {
                image.set(x, y, color);
            }
        }  
        
        // image.set(x, y, color); 
    }
}



