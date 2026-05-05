///////////////////////////////
//      '       KU MATH 127
//     (@)>     BY LUCAS
//   //KU       FRIAS FOR
//     ""       DAVID AND LILY
/////////////////////////////////
// "DOMO ARIGATO MR ROBOTO
// MATA AU HU MADE...... //
// demo.c -- combining tsoding's incredible little
// PNG generating library and Mac OS system calls,
// this file sets* to display ANY given 3D Calc III
// object and output it.  * sets does not mean does
// use at yo own risk

#define OLIVEC_IMPLEMENTATION
#include "olive.c"
#include "calc3.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"   // optional, for saving to PNG

#define WIDTH  800
#define HEIGHT 600
#define SCALE 300
#define CAM_Z 20  // pretend camera is 5 units back

//define my pixels
uint32_t pixels[WIDTH * HEIGHT];

//DRAW FUNCTIONS --- draw Calc3 objects in 3d space approriately




#define ROT_X 0.4f   // tilt down slightly
#define ROT_Y 0.6f   // spin right slightly

// rotate around X axis (tilts up/down)
Vec3 rotateX(Vec3 v, float angle) {
    return (Vec3){
        v.x,
        v.y * cos(angle) - v.z * sin(angle),
        v.y * sin(angle) + v.z * cos(angle)
    };
}

// rotate around Y axis (spins left/right)
Vec3 rotateY(Vec3 v, float angle) {
    return (Vec3){
        v.x * cos(angle) + v.z * sin(angle),
        v.y,
       -v.x * sin(angle) + v.z * cos(angle)
    };
}

Vec3 transform(Vec3 v) {
    v = rotateX(v, ROT_X);
    v = rotateY(v, ROT_Y);
    return v;
}

void draw_vec_from(Olivec_Canvas oc, Vec3 start, Vec3 end, uint32_t color) {
    int cx = WIDTH / 2, cy = HEIGHT / 2;

    // apply rotation before projection
    Vec3 s = transform(start);
    Vec3 e = transform(end);

    float view_z1 = s.z + CAM_Z;
    float view_z2 = e.z + CAM_Z;
    if (view_z1 < 0.5f || view_z2 < 0.5f) return;

    int x1 = cx + (int)(s.x / view_z1 * SCALE);
    int y1 = cy - (int)(s.y / view_z1 * SCALE);
    int x2 = cx + (int)(e.x / view_z2 * SCALE);
    int y2 = cy - (int)(e.y / view_z2 * SCALE);

    olivec_line(oc, x1, y1, x2, y2, color);
}




int main(void) {
    Olivec_Canvas oc = olivec_canvas(pixels, WIDTH, HEIGHT, WIDTH);
    olivec_fill(oc, 0xFF000000);
    Vec3 origin = {0,0,0};
    Vec3 zAxis = {0,0,-50};
    Vec3 xAxis = {50,0,0};
    Vec3 yAxis = {0,50,0};



    // X axis: goes left to right
    Vec3 xNeg = {-10, 0, 0};

    Vec3 xPos = { 10, 0, 0};

    // Y axis: goes down to up
    Vec3 yNeg = {0, -10, 0};
    Vec3 yPos = {0,  10, 0};

    // Z axis: goes into/out of screen
    Vec3 zNeg = {0, 0, -10};
    Vec3 zPos = {0, 0,  10};

    // draw each axis as one full line through origin

    draw_vec_from(oc, xNeg, xPos, 0xFF0000FF); // red   = X
    draw_vec_from(oc, yNeg, yPos, 0xFF00FF00); // green = Y
    draw_vec_from(oc, zNeg, zPos, 0xFFFF0000); // blue  = Z



    Vec3 triangleA = {-6,0,0};
    Vec3 triangleB = {0,7,0};
    Vec3 triangleC = {0,0,14};
    draw_vec_from(oc, triangleA, triangleB, 0xFFFFFFFF);
    draw_vec_from(oc, triangleB, triangleC, 0xFFFFFFFF);
    draw_vec_from(oc, triangleA, triangleC, 0xFFFFFFFF);



    stbi_write_png("out.png", WIDTH, HEIGHT, 4, pixels, sizeof(uint32_t) * WIDTH);
    system("open out.png");
    return 0;
}
