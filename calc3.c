///////////////////////////////
//      '       KU MATH 127
//     (@)>     BY LUCAS
//   //KU       FRIAS FOR
//     ""       DAVID AND LILY
/////////////////////////////////
// "DOMO ARIGATO MR ROBOTO
// MATA AU HU MADE...... //
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
//some useful structs

//basic components of a 3d Vec3tor
struct vector_struct {
    int x;
    int y;
    int z;
};
//2x2 matrix
struct matrix2{
    int a;
    int b;
    int c;
    int d;
};
//3x3 (i just used a-h because i found a formula
// online that has the determinant like that
struct matrix3{
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
    int i;
};
//scalar, just so i have pretty types :)
struct scalar {
    float magnitude;
};
typedef struct vector_struct Vec3;
typedef struct matrix2 Matrix2x2;
typedef struct matrix3 Matrix3x3;
typedef struct scalar Scalar;
//typedef all those suckas into existance

//1.1 adding new more complicated stuff like planes!! and... planes!!!
struct plane{
    Vec3 r0;
    Vec3 r;
    Vec3 n;
};
typedef struct plane Plane;

Vec3 get_vector_displacement(Vec3 a, Vec3 b){

    //get_Vec3tor: returns a Vec3
    //and combines two Vec3s giving
    //their component in order of
    // ---->  with get_Vec3tor(A, B)
    //  AB
    Vec3 resultVec3;
    //crazy easy addition
    resultVec3.x = a.x - b.x;
    resultVec3.y = a.y - b.y;
    resultVec3.z = a.z - b.z;
    return resultVec3;
}
Scalar get_2_by_2_det(Matrix2x2 matrix2){
    //get_2_by_2_det: gets the determinant
    //of a 2x2 matrix, given a matrix2
    //returns as a scalar result
    Scalar result;
    //the formula: given
    // | A B | ---->  = AD - BC
    // | C D |  det
    result.magnitude =  matrix2.a * matrix2.d - matrix2.c * matrix2.d;
    return result;
}

Scalar get_3_by_3_det(Matrix3x3 m) {
    //get_3_by_3_det: returns a 3x3 determinant
    // by breaking the result into 2x2 matrixes
    // and getting their determinants
    Scalar result;
    //lucas!!! why didn't you use the matrix
    // 2x2 function for each 2x2 determinant?
    // well, because i would have to cast
    // each 3x3 matrix value INTO a new 2x2
    // matrix. and that would take more time/stack
    // space. this formula is cheap and easy and works
    // sorry it's not pretty charlie
    result.magnitude =
        m.a * (m.e * m.i - m.f * m.h)
        - m.b * (m.d * m.i - m.f * m.g)
        + m.c * (m.d*m.h - m.e * m.g);
    return result;
}

Scalar get_magnitude(Vec3 vec) {
    //get_magnitude: given a Vec3,
    // this function returns the magnitude
    // in a scalar quantity
    Scalar result;
    // ||VEC|| = sqrt(VEC.X^2 + VEC.Y^2 + VEC.Z^2)
    // this is that
    result.magnitude = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
    return result;

}
Vec3 get_cross_product(Vec3 a, Vec3 b){
    //get cross product: with two vectors
    // a and b, this function returns the
    // cross product of A and B as a vector

    //okay now hate me here
    // my previous function for the cross product
    // works, but it's scalar,
    // so we just make a result Vec3
    Vec3 result;
    //and then cast the matrix values from a, b
    Matrix3x3 m;
    m.d = a.x;
    m.e = a.y;
    m.f = a.z; //lordy lord
    m.g = b.x; //forgive me
    m.h = b.y;
    m.i = b.z;
    //this just calculates each terms
    // x, y, z etc
    result.x = (m.e * m.i - m.f * m.h);
    result.y = (m.d * m.i - m.f * m.g);
    result.z = (m.d*m.h - m.e * m.g);
    return result;
}

Scalar calculate_vector_triangle(Vec3 a, Vec3 b, Vec3 c){
    //calculate_vector_triangle: given a, b, c, calculate
    // the area of a triangle in 3d space and return
    // it as a scalar value
    //STEP 1: get the ->AB and -> AC of our triangle
    //
    //          C
    //        /  \
    //       /    \
    //      A------B
    //so then we get the cross product OF those two vectors
    // as a vector that we can preform magnitude operations on
    Vec3 AB = get_vector_displacement(a, b);
    Vec3 AC = get_vector_displacement(a, c);
    //STEP 2, get the cross product of them
    Vec3 ABcrossAC = get_cross_product(AB, AC);
    //STEP 3, get the magnitude of the resulting cross product vector
    Scalar areaResult;
    //ugly fugly freaking ugly code
    // casting into scalars was a greaaatttt ideaaa
    areaResult.magnitude = 0.5 * (get_magnitude(ABcrossAC).magnitude);
    //this is the cx area of a rectangle but times 0.5 makes it
    // all good
    return areaResult;
}

//make a plane from two pints
Plane make_plane_from_three_points(Vec3 a, Vec3 b, Vec3 c){
    //make_plane_from_three_points: returns a plane after given
    // three Vec3 points A, B, and C. A is the basis point of
    // creating the plane
    // first get the displacement vectors
    Vec3 AB = get_vector_displacement(a, b);
    Vec3 AC = get_vector_displacement(a, c);
    //get cross product nuthin cray cray
    Vec3 n = get_cross_product(AB, AC);
    //MAKE PLANES USEFUL AGAIN!!!
    Plane resultPlane;
    //just convert a plane from the result plane
    resultPlane.n = n; //vector normal to the plane
    resultPlane.r0 = a;// these two are kinda arbitrary from 3 points
    resultPlane.r = b;
    return resultPlane;

}
bool check_if_vec3_exists_on_plane(Plane plane, Vec3 vec){
    //check_if_point_exists_on_plane: returns
    // true or false if a vec3 exists at that
    // point it's defined at on the plane NOT
    // if they intersect
    int A = plane.n.x;
    int B = plane.n.y;
    int C = plane.n.z;
    //the formula (simple ) is
    // A(x-x0) + B (y-y0) + C(z-z0) = 0
    // where A,B,C are xyz on the normal vec3
    // and x0,y0,z0 is a point on the plane
    int X0 = plane.r0.x;
    int Y0 = plane.r0.y;
    int Z0 = plane.r0.z;
    //now we have to check and return the value
    int result = A * (vec.x - X0)
        + B * (vec.y - Y0)
        + C * (vec.z - Z0);
    //now we check the result. if it's
    // zero than it's on the plane
    // otherwise returns false
    printf("%d", result);
    if (result == 0) return true;
    else return false;
}


int main(){
    Vec3 a = {0, 0, 0};
    Vec3 b = {1, 0, 0};
    Vec3 c = {0,1,0};
    Vec3 testVector = {0,0,1};
    Plane p = make_plane_from_three_points(a, b, c);
    if (check_if_vec3_exists_on_plane(p, testVector)){
        printf("it works");
    }
    else {
        printf("off the plane");
    }
}
