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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MSF_GIF_IMPL
#include "msf_gif.h"


#define WIDTH  200 //width and height of image
#define HEIGHT 200 //smaller frame = faster gen speeds
#define SCALE 1000 //the scale (resolution) of the lines being generated. AKA the "quality"
#define CAM_Z 100 //the distance camera z is from (0,0,0) increase to get the result
#define FRAMECOUNT 255 //frame count. frame basis is
#define FRAMEMULT 1
#define CENTIFRAMESPERSEC 3


//define my pixels
uint32_t pixels[WIDTH * HEIGHT];

//DRAW FUNCTIONS --- draw Calc3 objects in 3d space approriately



///GLOBAL VARS
// these are used for rotation
// during iteration they get changed!
float ROT_X = -0.4f;  // tilt down slightly
float ROT_Y = 0.6f;  // spin right slightly
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
    v = rotateY(v, ROT_Y);
    v = rotateX(v, ROT_X);
    return v;
}
FullVector transformFull(FullVector fv) {
    Vec3 start = {fv.xi, fv.yi, fv.zi};
    Vec3 end   = {fv.xf, fv.yf, fv.zf};
    start = transform(start);
    end   = transform(end);
    return (FullVector){start.x, start.y, start.z, end.x, end.y, end.z};
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


void make_gif_from_pngs(int numFrames) {
    printf("making gif...\n");
    char filename[64];
    snprintf(filename, sizeof(filename), "work/out%d.png", 0);

    int w, h, c;
    stbi_info(filename, &w, &h, &c);

    MsfGifState gif = {};
    msf_gif_begin(&gif, w, h);

    for (int i = 0; i < numFrames; i++) {
        snprintf(filename, sizeof(filename), "work/out%d.png", i);
        uint8_t *px = stbi_load(filename, &w, &h, &c, 4);
        //okay another gripe/question
        // the third int parameter of this function is centiframes
        // HIGHER values mean LOWER frame rates
        // which seems pretty counter intuitive
        msf_gif_frame(&gif, px, CENTIFRAMESPERSEC, 16, w * 4);
        stbi_image_free(px);
    }

    MsfGifResult out = msf_gif_end(&gif);
    FILE *f = fopen("result.gif", "wb");
    fwrite(out.data, out.dataSize, 1, f);
    fclose(f);
    msf_gif_free(out);
    printf("done!\n");
}

void draw_frame_from_vectors(FullVector * arrayOfVectors, uint32_t lengthOfVectorArray, int frameNumber){
    printf("generating frames: %d/%d\n", frameNumber, FRAMECOUNT * FRAMEMULT);
    Olivec_Canvas oc = olivec_canvas(pixels, WIDTH, HEIGHT, WIDTH);
    //fill the background and draw vectors
    // dear tsoding
    // i'm sure there's a very good reason for this but why
    // for the love of all that is conventional
    // are we using ABGR instead of RGBA? is there a good
    // reason for this??? actually??? grrr for the weird
    // proprieratry format but thank you for the wonderful
    // png library
    olivec_fill(oc, 0xFF550000);
    char charbuf[32];
    snprintf(charbuf, sizeof(charbuf), "%d/%d ", frameNumber, FRAMECOUNT-1);
    olivec_text(oc, charbuf, 10, 10, olivec_default_font, 1, 0xFFFFFFFF);
    Vec3 origin = {0,0,0};
    //draw the positional vectors
    Vec3 xNeg = {-20, 0, 0};
    Vec3 xPos = {20, 0, 0};
    Vec3 yNeg = {0, -20, 0};
    Vec3 yPos = {0,  20, 0};
    Vec3 zNeg = {0, 0, -20};
    Vec3 zPos = {0, 0,  20};
    draw_vec_from(oc, xNeg, xPos, 0xFF0000FF); // red   = X
    draw_vec_from(oc, yNeg, yPos, 0xFF00FF00); // green = Y
    draw_vec_from(oc, zNeg, zPos, 0xFFFF0000); // blue  = Z
    for (int i = 0; i < lengthOfVectorArray; i++) {
        FullVector fv = arrayOfVectors[i];
        Vec3 start = get_start_from_full_vector(fv);
        Vec3 end = get_end_from_full_vector(fv);
        draw_vec_from(oc, start, end, 0xFFFFFFFF);
    }
    /*for (int i = 0; i < lengthOfVectorArray; i++) {
        Vec3 t = transform(arrayOfVectors[i]);
        float vz = t.z + CAM_Z;
        if (vz < 0.5f) continue;
        int px = WIDTH/2  + (int)(t.x / vz * SCALE);
        int py = HEIGHT/2 - (int)(t.y / vz * SCALE);
        olivec_rect(oc, px-3, py-3, 6, 6, 0xFFFFFF00); // yellow dot
        }*/
    char filename[64];
    snprintf(filename, sizeof(filename), "work/out%d.png", frameNumber);
    stbi_write_png(filename, WIDTH, HEIGHT, 4, pixels, sizeof(uint32_t) * WIDTH);
}


int main(void) {
    /*
     * main -- this is where you put yo
     * little simulation at.
     * the useful functions usually take more complicated components, like
     * FullVector for draw_frame_from_vectors.
     */

    //define three vectors on triangle
    FullVector triangleA = {-6,0,0, 0,7,0};//AKA AB
    FullVector triangleB = {0,7,0, 0,0,14}; //AKA BC
    FullVector triangleC = {0,0,14, -6,0,0,}; //AKA CA

    Vec3 AB = get_vector_displacement((Vec3){-6,0,0}, (Vec3){0,7,0});
    Vec3 AC = get_vector_displacement((Vec3){-6,0,0}, (Vec3){0,0,14});
    //STEP 2, get the cross product of them
    Vec3 ABcrossAC = get_cross_product(AB, AC);
    FullVector orthogonalVector = {-6,0,0, ABcrossAC.x, ABcrossAC.y, ABcrossAC.z};
    //FullVector pts[3] = {triangleA, triangleB, triangleC};
    FullVector pts[4] = {triangleA, triangleB, triangleC, orthogonalVector};


    uint32_t lengthOfPts = sizeof(pts)/sizeof(FullVector);


    /*for (int i = 0; i<(FRAMECOUNT * FRAMEMULT); i++){
        ROT_Y = ROT_Y + (0.1 * FRAMEMULT);
        ROT_X = ROT_X + (0.1 * FRAMEMULT);
        draw_frame_from_vectors(pts, lengthOfPts, i);
    }
    make_gif_from_pngs(FRAMECOUNT);*/
    for (int i = 0; i < (FRAMECOUNT * FRAMEMULT); i++) {
        float t = (float)i / (FRAMECOUNT * FRAMEMULT);  // 0.0 to 1.0
        ROT_Y = t * 2.0f * M_PI;  // full 360 spin
        ROT_X = 0.4f;              // fixed tilt, no wobble
        draw_frame_from_vectors(pts, lengthOfPts, i);
    }
  make_gif_from_pngs(FRAMECOUNT);

    //printf("%f", calculate_vector_triangle(a, b, c).magnitude);

    return 0;
}
