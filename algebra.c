#include <stdint.h>
#include <stdio.h>


#define MAX_EQUATION_SIZE 512


typedef struct short_algebra_statement {
    uint64_t algebra_chars;
} ShortAlgebraStatement;

typedef struct complete_algebra_statement {
    ShortAlgebraStatement partA;
    ShortAlgebraStatement partB;
    ShortAlgebraStatement partC;
    ShortAlgebraStatement partD;
} CompleteAlgebraStatement;

typedef struct scalar{
    float magnitude;
} Scalar;


ShortAlgebraStatement generate_algebra_statement_from_char(char * algebra){
    //generate_short_algebra_statement_from_char -- given a char pointer to a cstring,
    // generates a short algebra statement from this. a short algebra statement is stored
    // by converting each char (exlucding white spaces) into a byte stored in uint64_t
    // assuming the algebra statement doesn't exceed the size 8 bytes (hence short)
    ShortAlgebraStatement result;
    result.algebra_chars = 0;//clears the space
    for (int i = 0;*algebra != 0;){
        //we end at the null terminated c string, but we also can't overwrite here
        if (i > 7){break;}//breaks at 8

        if (*algebra != ' '){//if we don't have a space, it's a char to pass
            //in order to make sure we read it correctly and easily, we're storing this backwards, where
            // the last byte is the first. that way, shift operations are easier
            // translating this to english:
            //      - add the result of the conversion of the char of algebra to an unsinged integer
            //      - to the sum of each and space so that we do a bistmak
            //      - and it with the original result
            result.algebra_chars |= ((uint64_t)(uint8_t)*algebra) << (i * 8);//weird cast i have to do
            i++;
        }
        *algebra++;//increment our pointer
    }
    //DEBUG CHECK
    /*for (int i = 0; i<8; i++){
        printf("%c", (uint8_t)(result.algebra_chars >> (i * 8)));
        }*/
    return result;
}

CompleteAlgebraStatement generate_complete_statement(char *string) {
    //create_complete_statement: creates a algebra statement using
    // confusing slop
    CompleteAlgebraStatement result = {0};
    ShortAlgebraStatement *parts[4] = {
        &result.partA, &result.partB, &result.partC, &result.partD
    }; //make a pointer sum of each of the results from the complete statement

    for (int i = 0; i < 4 && *string != 0; i++) {//while both we're not greater than 64 and also the string is not -
        *parts[i] = generate_algebra_statement_from_char(string); //set the pointer value at parts of i to the shortalgerastatement
        // advance string by 8 non-space characters
        int count = 0;
        while (*string != 0 && count < 8) {//if the string is not null then we keep iterating
            if (*string != ' ') count++;
            string++;
        }
    }
    return result;
}

Scalar resolve_no_variable_algebra_statement(CompleteAlgebraStatement cas){
    char mathBuffer [64] = {0};
    //make an array of all parts
    uint64_t parts[4] = {
        cas.partA.algebra_chars,
        cas.partB.algebra_chars,
        cas.partC.algebra_chars,
        cas.partD.algebra_chars
    };

    //now let's iterate and find the part
    for (int i = 0; i < 64; i++) {
        int partIndex = i / 8;   // which part (should round down cuz int cu)
        int byteIndex = i % 8;   // floor divide for white byte
        mathBuffer[i] = (uint8_t)(parts[partIndex] >> (byteIndex * 8));//the mathbuffer by pushing back
    }
    printf("%s", mathBuffer);

}

int main(){
    char * hello = "1+2+3+4+5+6+7+8+9+10+11+12+13";
    CompleteAlgebraStatement math = generate_complete_statement(hello);
    resolve_no_variable_algebra_statement(math);
}
