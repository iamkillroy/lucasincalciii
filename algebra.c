#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

bool is_mathematical_symbol(char symbol){
    //is_mathematical_symbol: given a single char symbol, this
    // function returns true if the char is any of these symbols:
    //      +  -  *  /  ^  =
    // and false otherwise
    switch(symbol){
        case '+':
            return true;
        case '-':
            return true;
        case '*':
            return true;
        case '/':
            return true;
        case '^':
            return true;
        case '=':
            return true;
        case ' ':
            return true;
    }
    return false;
}



Scalar resolve_no_variable_algebra_statement(CompleteAlgebraStatement cas){
    char mathBuffer [MAX_EQUATION_SIZE] = {0};
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
    //okay now we've cast the whole statement into a char array
    // we're going to evaluate this like PEDMAS
    // P - parantheses
    // E - exponents
    // M - multiplication
    // D - division
    // A - addition
    // S - subtraction

    //STEP 1 - P
    // let's see if there's parantheses
    for (int i = 0; mathBuffer[i] != 0 && i<64; i++){
        //making sure we don't go null terminated or etc
        if (mathBuffer[i] == '('){
            //we found one, let's store the parantheses value
            char paranthesesStatement  [64] = {0} ;
            //go until the end.
            int j = 0;
            while (mathBuffer[i] != ')') {
                paranthesesStatement[j++] = mathBuffer[i++];
            }
            //now we have the whole value, null terminated. we can throw this recursively into
            // this function again and again as long as we replace the value in the end
            CompleteAlgebraStatement paraStatement = generate_complete_statement(paranthesesStatement);//passes a char * at 0
            Scalar paraResult = resolve_no_variable_algebra_statement(paraStatement);//evaluate what that is
            char * charPointerOfResult = float_to_char(paraResult.magnitude);
            //ai generated slop to do with the awful reality of copying the correct
            // buffer result here i guess
            char newBuffer[64] = {0};
            int writeIdx = 0;

            // find the start of '('
            int parenStart = i; // where '(' was found
            int parenEnd = i;   // will point to ')'
            while (mathBuffer[parenEnd] != ')') parenEnd++;

            // copy everything before '('
            for (int k = 0; k < parenStart; k++) {
                newBuffer[writeIdx++] = mathBuffer[k];
            }

            // insert the result string
            for (int k = 0; charPointerOfResult[k] != 0; k++) {
                newBuffer[writeIdx++] = charPointerOfResult[k];
            }

            // copy everything after ')'
            for (int k = parenEnd + 1; mathBuffer[k] != 0 && k < 64; k++) {
                newBuffer[writeIdx++] = mathBuffer[k];
            }

            // replace mathBuffer with newBuffer
            memcpy(mathBuffer, newBuffer, 64);
            free(charPointerOfResult);//manage memory kids
            //don't do crack and leave that sh free
        }
    }


    //STEP IDK -- ADDITION
    for (int i = 0; mathBuffer[i]!=0;i++){
        if (mathBuffer[i] == '+'){
            printf("found math -- ");
            //let's do some quick nonsense checks
            if (i-1==-1){continue;}//aka, adding with a char before the space
            if (mathBuffer[i+1] == 0){continue;} //and make sure the next number does exist
            printf("it's not weird!\n");
            if (is_mathematical_symbol(mathBuffer[i-1]) || is_mathematical_symbol(mathBuffer[i+1])){continue;}
            //okay so now we're gonna get the number up until it's the next mathematical symbol, and we're gonna reverse it
            // to get the first part in A + B
            char numBefore [32] = {0}; //this is the num before
            char numAfter [32] = {0};
            //first let's gat that reverse thing
            int lenOfNumBefore = 0;
            int lenOfNumAfter = 0;
            //let's go from the beginning to the end for each answer
            // so we know where to fill in
            int beginningOfAnswer = i-1;
            int endOfAnswer = i+1;
            for (int beforeI = i-1; !is_mathematical_symbol(mathBuffer[beforeI]); beforeI--){
                numBefore[lenOfNumBefore] = mathBuffer[beforeI];
                lenOfNumBefore++;
                beginningOfAnswer--;
            }
            printf("the first addend is %s", numBefore);
            //now we do num after
            for (int afterI = i+1; !is_mathematical_symbol(mathBuffer[afterI]); afterI++){
                numAfter[lenOfNumAfter] = mathBuffer[afterI];
                lenOfNumAfter++;
                endOfAnswer++;
            };
            printf("\nthe second addend is %s\n", numAfter);
            //okay now let's convert both to floats
            float addPartA = atof(numBefore);
            float addPartB = atof(numAfter);
            float result = addPartA + addPartB;
            printf("\n%f is the result of %f + %f", result, addPartA, addPartB);
            //okay no we convert this result to a char
            char * resultAsString = float_to_char(result);
            char * copyOfResultAsString = resultAsString;
            //now we copy the buffer piece by piece, except when we get to the first num part
            char copyOfMathBuffer[MAX_EQUATION_SIZE] = {0};//nullterm
            for (int j =0;j<beginningOfAnswer;j++){
                copyOfMathBuffer[j] = mathBuffer[i];
            }
            //okay now we're at the answer fill part, so we're gonna fill this in
            for (int k=0;*resultAsString!=0;resultAsString++){
                copyOfMathBuffer[k] = *resultAsString;
                k++;
            }
            for (int l= endOfAnswer;mathBuffer[l]!=0;l++){
                copyOfMathBuffer[l] = mathBuffer[l];
            }
            for (int m =0; m<MAX_EQUATION_SIZE;m++){
                mathBuffer[m] = copyOfMathBuffer[m];
            }
            free(copyOfResultAsString);//always free!
            //can't free og because that's freeing an advanced pointer
        }
    }

}

int main(){
    char * hello = "1+2";
    CompleteAlgebraStatement math = generate_complete_statement(hello);
    printf("%f", resolve_no_variable_algebra_statement(math).magnitude);
}
