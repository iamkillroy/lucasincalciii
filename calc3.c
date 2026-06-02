///////////////////////////////
//      '       KU MATH 127
//     (@)>     BY LUCAS
//   //KU       FRIAS FOR
//     ""       DAVID AND LILY
/////////////////////////////////
// "DOMO ARIGATO MR ROBOTO
// MATA AU HU MADE...... //
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "algebra.c"
//some useful structs
#define MAX_ALGEBRA_STATEMENT_SIZE 1024
//basic components of a 3d Vec3tor
struct vector_struct {
    float x;
    float y;
    float z;
};
typedef struct vector_start_and_end {
    float xi;
    float yi;
    float zi;
    float xf;
    float yf;
    float zf;
} FullVector;
//2x2 matrix
struct matrix2{
    float a;
    float b;
    float c;
    float d;
};
//3x3 (i just used a-h because i found a formula
// online that has the determinant like that
struct matrix3{
    float a;
    float b;
    float c;
    float d;
    float e;
    float f;
    float g;
    float h;
    float i;
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
typedef struct scalar3d {
    Scalar x;
    Scalar y;
    Scalar z;
} Scalar3D;

typedef struct physic_basic_object {
    float mass;
    Vec3 position;
    Vec3 velocity;
    Vec3 acceleration;
    Vec3 forces[];
} PDot;

typedef struct math_variables {
    float a;
    float b;
    float c;
    float d;
    float f;
    float g;
    float h;
    float i;
    float j;
    float k;
    float l;
    float m;
    float p;
    float q;
    float r;
    float s;
    float t;
    float u;
    float v;
    float w;
    float x;
    float y;
    float z;
} MathVariables;

typedef struct physic_force_vector {
    float newtons;
    Vec3 position;
} PVector;

typedef struct time {
    uint64_t seconds;
} Time;

typedef struct algebraic_statement {
    char * statement;
} AlgebraStatement;

typedef struct param_of_func {
    AlgebraStatement XofT;
    AlgebraStatement YofT;
    AlgebraStatement ZofT;
} Parametrization;

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
FullVector make_full_vector_from_two_vector_points(Vec3 a, Vec3 b){
    //make_full_vector_from_two_vector_points: given Vec3 a and Vec3 b
    //creates and returns a new FullVector that begins at a and ends at b
    FullVector resultVector = {a.x, a.y, a.z, b.x, b.y, b.z};
    return resultVector;
}
Vec3 get_start_from_full_vector(FullVector fv){
    //get_start_from_full_vector: given a full vector
    // fv, this returns the START of the vector from it's initial position
    Vec3 startVector;
    startVector.x = fv.xi;
    startVector.y = fv.yi;
    startVector.z = fv.zi;
    return startVector;
}
Vec3 get_end_from_full_vector(FullVector fv){
    //get_end_from_full_vector: given a full vector
    // fv, this returns the END of the vector from it's initial position
    Vec3 endVector;
    endVector.x = fv.xf;
    endVector.y = fv.yf;
    endVector.z = fv.zf;
    return endVector;
}
Scalar get_2_by_2_det(Matrix2x2 matrix2){
    //get_2_by_2_det: gets the determinant
    //of a 2x2 matrix, given a matrix2
    //returns as a scalar result
    Scalar result;
    //the formula: given
    // | A B | ---->  = AD - BC
    // | C D |  det
    result.magnitude =  matrix2.a * matrix2.d - matrix2.c * matrix2.b;
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

void print_vec3(Vec3 vector){
    printf("{%f, %f, %f}", vector.x, vector.y, vector.z);
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
    result.y = -1 * (m.d * m.i - m.f * m.g);
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
    print_vec3(ABcrossAC);
    //STEP 3, get the magnitude of the resulting cross product vector
    Scalar areaResult;
    printf("\n%f\n", (get_magnitude(ABcrossAC).magnitude));
    //ugly fugly freaking ugly code
    // casting into scalars was a greaaatttt ideaaa
    areaResult.magnitude = 0.5 * (get_magnitude(ABcrossAC).magnitude);
    //this is the cx area of a rectangle but times 0.5 makes it
    // all good
    return areaResult;
}

Scalar calculate_vector_parallelogram(Vec3 a, Vec3 b, Vec3 c){
    //calculate_vector_parallelogram: given a, b, c, calculate
    // the area of a PARALLELOGRAM not triangle in 3d space and return
    // it as a scalar value (same as triangle but without the 1/2)
    //STEP 1: get the ->AB and -> AC of our parallelogram
    //
    //          C----------D
    //        /           /
    //       /           /
    //      A----------B
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
    areaResult.magnitude = (get_magnitude(ABcrossAC).magnitude);
    //this is the cx area of a rectangle
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
    // i know this isn't the dot product function but it's finna be okay
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



Scalar get_dot_product(Vec3 a, Vec3 b){
    // get_dot_product: given two vectors, a and b
    // returns the dot product of the vectors as a scalar
    Scalar result;
    //thanks kaden!!!!
    result.magnitude = a.x * b.x + a.y * b.y * a.z * b.z;
    return result;
}

Scalar3D get_distance_change(Vec3 velocity, Vec3 acceleration, Time time){
    //get_distance_change: given a velocity V and acceleration A
    // using the formula:
    // change in x/y/z = v*t + 1/2 at^2
    //returns the displacement as a 3D vector displacement
    Scalar3D result;
    //just do that formula three times and return the resulting change
    result.x.magnitude = velocity.x * time.seconds + 0.5f * acceleration.x * pow(time.seconds, 2);
    result.y.magnitude = velocity.y * time.seconds + 0.5f * acceleration.x * pow(time.seconds, 2);
    result.z.magnitude = velocity.z * time.seconds + 0.5f * acceleration.z * pow(time.seconds, 2);
    return result;
}

Scalar3D get_velocity_change(Vec3 velocity, Vec3 acceleration, Time time){
    //get_velocity_change: given a velocity V and acceleration A
    // using the formula:
    // new velocity (vf) = v0 + at
    //returns the new velocity as a 3D vector displacement
    Scalar3D result;
    //just do that formula three times and return the resulting change
    result.x.magnitude = velocity.x + acceleration.x * time.seconds;
    result.y.magnitude =  velocity.y + acceleration.y * time.seconds;
    result.z.magnitude =  velocity.z + acceleration.z * time.seconds;
    return result;

}

Scalar3D get_acceleration_change(Vec3 velocity, Vec3 acceleration, Time time){
    //get_velocity_change: given a velocity V and acceleration A
    // using the formula:
    // new velocity (vf) = v0 + at
    //returns the new velocity as a 3D vector displacement
    Scalar3D result;
    //just do that formula three times and return the resulting change
    result.x.magnitude = velocity.x + acceleration.x * time.seconds;
    result.y.magnitude =  velocity.y + acceleration.y * time.seconds;
    result.z.magnitude =  velocity.z + acceleration.z * time.seconds;
    return result;

}

PDot time_push(PDot pdot, Time time){
    //time_push: given a pdot (and time)
    // pushes the pdot object through time by one second
    // the resulting pdot accounts for the change in position,
    // velocity, acceleration, etc
    Scalar3D distanceChangeIn3D = get_distance_change(pdot.velocity, pdot.acceleration, time);
    pdot.position.x += distanceChangeIn3D.x.magnitude;
    pdot.position.y += distanceChangeIn3D.y.magnitude;
    pdot.position.z += distanceChangeIn3D.z.magnitude;

    Scalar3D velocityChangeIn3D = get_distance_change(pdot.velocity, pdot.acceleration, time);
    pdot.velocity.x += velocityChangeIn3D.x.magnitude;
    pdot.velocity.y += velocityChangeIn3D.y.magnitude;
    pdot.velocity.z += velocityChangeIn3D.z.magnitude;

    Scalar3D accelChangeIn3D = get_distance_change(pdot.velocity, pdot.acceleration, time);
    pdot.acceleration.x += accelChangeIn3D.x.magnitude;
    pdot.acceleration.y += accelChangeIn3D.y.magnitude;
    pdot.acceleration.z += accelChangeIn3D.z.magnitude;
    return pdot;
}

char * float_to_char(float a){
    //float_to_char: given a user passed float, this function converts
    // the float to a char array WHICH IS MALLOCED TO THE HEAP. IT MUST
    // BE C A L L E E FREED!!! you've been warned
    //unlike your malloc mine sucks ass!!!
    char *buffer = malloc(sizeof(char) * 32);//thank you Miss Delan A of Australiba
    //stackoverfow post here: https://stackoverflow.com/questions/2988791/converting-float-to-char
    if (a == (int) a){//aka is it whole
        //copy it up till we see the period
        int ret = snprintf(buffer, sizeof(char )* 32, "%d", (int) a);
    }
    else{
        int ret = snprintf(buffer, sizeof(char )* 32, "%f", a);
    }
    //malloc our char buffer to the heap
    return buffer;
}
bool has_symbol(char symbol, char * statement){
    //has_symbol: given a char symbol through each statement,
    //returns a bool where it is
    for (;;){
        if (*statement == symbol){return true;}
        else if (*statement == 0){return false;}
        statement++;
    }
}
int where_is_symbol(char symbol, char * statement){
    //where_is_symbol: given a char symbol and a statement,
    // returns the FIRST instance of that character
    // else returns -1 if there is no instance of that character,
    // but use has_symbol
    for (int i =0;;i++){
        if (symbol == 0){return -1;}
        if (symbol == *statement){return i;}
        statement++;
    }
}

Scalar evaluate_algebra_statement(AlgebraStatement as, MathVariables mv){
    //evaluate_algebra_statement: given an algebra statement as,
    // evaluate each characters and return a Scalar in terms of
    // a float value response from the algebraic statement.
    // does NOT support radians or imaginary numbers
    char characters[100];//make our char buffe
    int endOfStatement = 0;
    while (as.statement[endOfStatement] != '\0') {//while we're still in the cstring
        characters[endOfStatement] = as.statement[endOfStatement]; //put the char into the char buffer
        endOfStatement++;
    }
    //now we're going to increment through each operation and evluate it
    // remember!!!!
    //  P * parantheses
    //  E * exponents
    //  M * multiplication
    //  D * division
    //  A * addition
    //  S * subtrction
    // so we're gonna have these arrays
    //so each loop will evaluate in this order
    // first: parantheses loop
    bool evaluatingPara = false;
    uint8_t beginningOfParaStatement = 255;
    uint8_t endOfParaStatement = 255;
    for (int i = 0; i<endOfStatement; i++){
        if (characters[i] == '(') {
            evaluatingPara = true;
            beginningOfParaStatement = i; // set the beginnign
            //now here's the trick: recursively call this function
            // by making an algebraic statement from ( until ) and
            // use that resulting scalar in our main statement
            AlgebraStatement inParaStatement; //this is a parastatement
            char paraBuffer[50]; //get that char buffer
            while (!(characters[i] == ')')){
                paraBuffer[i] = characters[i];
                i++; //iterate the iteratable var a second time
                //gross i know!!! but does the job even
                // if it's a little dirty with it
            }
            endOfParaStatement = i; //set the end
            Scalar paraResult =  evaluate_algebra_statement(inParaStatement, mv);
            //okay so now we evaluated this and we have a scalar result from our evaluation (presumably)
            // now we have to snip between beginning and end and get
            // (3a + 4b + 3^c) + 23k = (19) + 23k

            //this subroutine is complex
            // so the idea behind it is, given an array A (in our case a char vector, but really could be any array)
            // we wanna trim the elements so that from range A:B the elements are removed
            // as tim peters my queen once said:
            //      "Explicit is better than implicit" --- Tim Peters, The Zen of Python
            // also i'm not dutch, so i don't know the most obvious way to do this. i'm sure
            // stdlib has a function that does this but goddamit this is an educational project!!!
            // anyways back the explanation: basically we're gonna first shift everything down so our
            // example statement:
            //      char * e = "(3K + 2) + 1"
            // turns into:
            //      char *e = "(_____) + 1"
            // then we copy this char buffer and clear it

            char newAlgebraStatement[100];
            //this is our new copy of the statement
            //now, we finna copy this for every value up till we achieve the i result
            // o(n) yep i know
            for (int i =0; i>beginningOfParaStatement; i++){
                newAlgebraStatement[i] = characters[i];
                //get the CHARACTER array which returns the character value at that certain point
            }
            //okay now we're at the parastatement's result. we're gonna convert the para
            // scalar value from a float value to become a char array and then throw that in
            for (int i=0; i<endOfParaStatement; i++){
                newAlgebraStatement[i] = 0;
                //now we solve the
            }
        }
    }
    Scalar duhn;
    return duhn;
}


int main(){
    Vec3 firstVec = {3, 5, 4};
    Vec3 secondVec = {-7,4,4};
    print_vec3(get_cross_product(firstVec, secondVec));

}
