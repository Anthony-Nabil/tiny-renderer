#include "tgaimage.h"
#include <algorithm>
#include <cmath>
#include "model.h"
#include "geometry.h"
#include <vector>
#include <cmath>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
Model *model = NULL;

// dimentions of the image 
const int width = 800;
const int height = 800;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

int main(int argc, char** argv) {
    TGAImage image(height, width, TGAImage::RGB);
    // image.set(50, 50, red);
    // diagonal line
    // line(15, 15, 65, 65, image, white);
    // line(20, 13, 40, 80, image, red); 
    // line(80, 40, 13, 20, image, red);

    // check if the user has provided a model file
    if (2==argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("obj/african_head.obj");
    }


    for (int i=0; i<model->nfaces(); i++) { 
        std::vector<int> face = model->face(i); 
        for (int j=0; j<3; j++) { 
            Vec3f v0 = model->vert(face[j]); 
            Vec3f v1 = model->vert(face[(j+1)%3]); 
            int x0 = (v0.x+1.)*width/2.; 
            int y0 = (v0.y+1.)*height/2.; 
            int x1 = (v1.x+1.)*width/2.; 
            int y1 = (v1.y+1.)*height/2.; 
            line(x0, y0, x1, y1, image, white); 
        } 
    }

        
        image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
        image.write_tga_file("output.tga");
        delete model;
        return 0;
}

// void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
//     for (float t=0.; t<1.; t+=.0001) { 
//         int x = x0 + (x1-x0)*t; 
//         int y = y0 + (y1-y0)*t; 
//         image.set(x, y, color); 
//     } 
// }


// void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 

//     int dx = x1 - x0;
//     int dy = y1 - y0;

//     float derror = dy/ (float) dx;
//     float error = 0;

//     int y = y0;

//     // check if x0 is greater than x1 and if so swap them, so it transposes the line
//     bool steep = false;
//     if (std::abs(x1-x0) < std::abs(y1-y0)) {
//         std::swap(x0, y0);
//         std::swap(x1, y1);
//         steep = true;
//     }

//         // checks if x0 is greater than x1 and if so swap them
//         if (x0>x1) { 
//         std::swap(x0, x1); 
//         std::swap(y0, y1); 
//     }

//     for (int x=x0; x<=x1; x++) { 

//         // t = the percentage of the distance covered from x0 to x1
//         float t = (x-x0)/(float)(x1-x0); 

//         // y is calculated as y0 + (y1-y0)*t
//         int y = y0*(1.-t) + y1*t; 


//         // check for out of bounds
//         if (x >= 0 && x < image.get_width() && y >= 0 && y < image.get_height()) {
//             if (steep) {
//                 image.set(y, x, color);
//             } else {
//                 image.set(x, y, color);
//             }
//         }  

//         // image.set(x, y, color); 
//     }
// }

// /**
//  * Draws a line on a TGAImage object.
//  * 
//  * @param x0: The starting x-coordinate of the line.
//  * @param y0: The starting y-coordinate of the line.
//  * @param x1: The ending x-coordinate of the line.
//  * @param y1: The ending y-coordinate of the line.
//  * @param image: A reference to a TGAImage object on which the line will be drawn.
//  * @param color: The color of the line.
//  */
// void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
//     bool steep = false;

//     // Check if the line is steep and swap the x and y coordinates if necessary
//     if (std::abs(x1 - x0) < std::abs(y1 - y0)) {
//         std::swap(x0, y0);
//         std::swap(x1, y1);
//         steep = true;
//     }

//     // Check if the starting x-coordinate is greater than the ending x-coordinate and swap them if necessary
//     if (x0 > x1) {
//         std::swap(x0, x1);
//         std::swap(y0, y1);
//     }

//     int dx = x1 - x0;
//     int dy = y1 - y0;

//     float derror = std::abs(static_cast<float>(dy) / dx);
//     float error = 0;
//     int y = y0;

//     for (int x = x0; x <= x1; x++) {
//         // Set the corresponding pixel on the TGAImage object to the specified color
//         if (steep) {
//             image.set(y, x, color); // if the line is steep, transpose the x and y coordinates since it was swapped earlier
//         } else {
//             image.set(x, y, color);
//         }

//         error += derror;

//         if (error > 0.5) {
//             y += (y1 > y0) ? 1 : -1;
//             // subtract 1 instead of 0.5 as to restart the error accumulation on every iteration
//             // and prevent cases such as 0.7 where the code will always increment/decrement the y value
//             // making the line have a slope of 1 instead of 0.7 
//             error -= 1.0;
//         }

//         // Check if the x and y coordinates are within the bounds of the TGAImage object and set the corresponding pixel if they are
//         if (x >= 0 && x < image.get_width() && y >= 0 && y < image.get_height()) {
//             if (steep) {
//                 image.set(y, x, color);
//             } else {
//                 image.set(x, y, color);
//             }
//         }
//     }
// }




/**
 * Draws a line on a TGAImage object.
 * 
 * @param x0: The starting x-coordinate of the line.
 * @param y0: The starting y-coordinate of the line.
 * @param x1: The ending x-coordinate of the line.
 * @param y1: The ending y-coordinate of the line.
 * @param image: A reference to a TGAImage object on which the line will be drawn.
 * @param color: The color of the line.
 */
void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
    bool steep = false;

    // Check if the line is steep and swap the x and y coordinates if necessary
    if (std::abs(x1 - x0) < std::abs(y1 - y0)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    // Check if the starting x-coordinate is greater than the ending x-coordinate and swap them if necessary
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;

    float derror2 = std::abs(dy) * 2;
    float error2 = 0;
    int y = y0;

    // calculate the increment value for y
    const int yincr =  (y1 > y0) ? 1 : -1;


    if (steep)
    {
        for(int x = x0; x <= x1; x++)
        {
            image.set(y, x, color);


            error2 += derror2;

            if (error2 > dx)
            {
                y += yincr;
                error2 -= dx * 2;
            }
        }
    }

    else
    {
        for(int x = x0; x <= x1; x++)
        {
            image.set(x, y, color);
            error2 += derror2;

            if (error2 > dx)
            {
                y += yincr;
                error2 -= dx * 2;
            }
        }
    }
}


//     for (int x = x0; x <= x1; x++) {
//         // Set the corresponding pixel on the TGAImage object to the specified color
//         if (steep) {
//             image.set(y, x, color); // if the line is steep, transpose the x and y coordinates since it was swapped earlier
//         } else {
//             image.set(x, y, color);
//         }

//         // accumulate the error
//         error2 += derror2;

//         if (error2 > dx) {
//             y += (y1 > y0) ? 1 : -1;
//             // subtract 1 instead of 0.5 as to restart the error accumulation on every iteration
//             // and prevent cases such as 0.7 where the code will always increment/decrement the y value
//             // making the line have a slope of 1 instead of 0.7 
//             error2 -= dx * 2;
//         }
//     }
// }