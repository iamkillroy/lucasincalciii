///////////////////////////////
//      '       KU MATH 127
//     (@)>     BY LUCAS
//   //KU       FRIAS FOR
//     ""       DAVID AND LILY
/////////////////////////////////
// "DOMO ARIGATO MR ROBOTO
// MATA AU HU MADE...... //
// LIB: calc3.h -->
// defines calc 3 in c and allows
// manipulation of 3D objects,
// in 3D space. Includes:
//      * Vectors
//      * Matrixes
//      * Cross Product
//      * Dot Product
//      * Surface Area of 2D Objects in 3D
//          * Triangle in 3D
//          * Paralelogram in 3D
//      * Planes
//      * Planes
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef CALC3_H
#define CALC3_H
// ─────────────────────────────────────────────
//  STRUCTS
// ─────────────────────────────────────────────

typedef struct vector_struct {
    float x;
    float y;
    float z;
} Vec3;

typedef struct matrix2 {
    float a;
    float b;
    float c;
    float d;
} Matrix2x2;

typedef struct vector_start_and_end {
    float xi;
    float yi;
    float zi;
    float xf;
    float yf;
    float zf;
} FullVector;

typedef struct matrix3 {
    float a;
    float b;
    float c;
    float d;
    float e;
    float f;
    float g;
    float h;
    float i;
} Matrix3x3;

typedef struct scalar {
    float magnitude;
} Scalar;

typedef struct plane {
    Vec3 r0;
    Vec3 r;
    Vec3 n;
} Plane;



typedef struct physic_basic_object {
    float mass;
    Vec3 position;
    Vec3 velocity;
    Vec3 acceleration;
    Vec3 forces[];
} PDot;

typedef struct physic_force_vector {
    float newtons;
    Vec3 position;
} PVector;

// ─────────────────────────────────────────────
//  VECTOR OPERATIONS
// ─────────────────────────────────────────────

Vec3 get_vector_displacement(Vec3 a, Vec3 b);

FullVector make_full_vector_from_two_vector_points(Vec3 a, Vec3 b);
Vec3 get_start_from_full_vector(FullVector fv);
Vec3 get_end_from_full_vector(FullVector fv);


Scalar get_magnitude(Vec3 vec);

Vec3 get_cross_product(Vec3 a, Vec3 b);

Scalar get_dot_product(Vec3 a, Vec3 b);

// ─────────────────────────────────────────────
//  MATRIX / DETERMINANT OPERATIONS
// ─────────────────────────────────────────────

Scalar get_2_by_2_det(Matrix2x2 matrix2);

Scalar get_3_by_3_det(Matrix3x3 m);

// ─────────────────────────────────────────────
//  AREA CALCULATIONS
// ─────────────────────────────────────────────

Scalar calculate_vector_triangle(Vec3 a, Vec3 b, Vec3 c);

Scalar calculate_vector_parallelogram(Vec3 a, Vec3 b, Vec3 c);

// ─────────────────────────────────────────────
//  PLANE OPERATIONS
// ─────────────────────────────────────────────

Plane make_plane_from_three_points(Vec3 a, Vec3 b, Vec3 c);

bool check_if_vec3_exists_on_plane(Plane plane, Vec3 vec);

#endif // CALC3_H
