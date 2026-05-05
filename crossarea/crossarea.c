#include <stdio.h>

struct vector_struct {
    int x;
    int y;
    int z;
};
struct matrix2{
    int a;
    int b;
    int c;
    int d;
};
struct matrix3{
    int a1;
    int a2;
    int a3;
    int b1;
    int b2;
    int b3;
    int c1;
    int c2;
    int c3;
};
struct scalar {
    int magnitude;
};
typedef struct vector_struct Vec;
typedef struct matrix2 Matrix2x2;
typedef struct matrix2 Matrix3x3;
typedef struct scalar Scalar;

Vec get_vector(Vec a, Vec b){
    Vec resultVec;
    resultVec.x = a.x - b.x;
    resultVec.y = a.y - b.y;
    resultVec.z = a.z - b.z;
    return resultVec;
}
Scalar get_2_by_2_det(Matrix2x2 matrix2){
    Scalar result;
    result.magnitude =  matrix2.a * matrix2.d - matrix2.c * matrix2.d;
    return result;
}

Scalar get_3_by_3_det(Matrix3x3 matrix3) {
    Scalar result;
}

int get_cross_product(){

}


int get_magnitude(){

}

int get_cross_area(){

    return 0;
}


int main(){

}
