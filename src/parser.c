#include <stdio.h>
#include <stdlib.h>
#include "token.h"

// test example 
// -10 + 50 * 2 / -(1 - 6) + (6 + 1 ) * 10 - (2-0.9)
// result will be 78.9

#define BUFFER_SIZE (1024)

double parse_expression(void);

double parse_primary_expression()
{

    double value = 0.0;
    int minus_flag = 0;

    next();

    // if token is minus, get next token
    if (token.kind == SUB_OPERATOR_TOKEN) {
        minus_flag = 1;
        next();
    }

    if (token.kind == NUMBER_TOKEN) {
        value = token.value;
    } else if (token.kind == LEFT_PAREN_TOKEN) {
        // ( expr )
        value = parse_expression();
        if (token.kind != RIGHT_PAREN_TOKEN) {
            fprintf(stderr, "missing ')'\n");
            exit(1);
        }
    }

    if (minus_flag) {
        value = -value;
    }

    next();
    
    return value;
}

double parse_term()
{
    double v1;
    double v2;
    int operator;

    v1 = parse_primary_expression();
    for (;;) {

        if (token.kind != MUL_OPERATOR_TOKEN
            && token.kind != DIV_OPERATOR_TOKEN) {
            break;
        }
        operator = token.kind;
        v2 = parse_primary_expression();
        if (operator == MUL_OPERATOR_TOKEN) {
            v1 *= v2;
        } else if (operator == DIV_OPERATOR_TOKEN) {
            v1 /= v2;
        }
    }
    return v1;
}

double parse_expression()
{
    double v1;
    double v2;
    int operator;

    v1 = parse_term();
    for (;;) {

        if (token.kind != ADD_OPERATOR_TOKEN 
            && token.kind != SUB_OPERATOR_TOKEN) {
            break;
        }
        operator = token.kind;
        v2 = parse_term();
        if (operator == ADD_OPERATOR_TOKEN) {
            v1 += v2;
        } else if (operator == SUB_OPERATOR_TOKEN) {
            v1 -= v2;
        }
    }
    return v1;
}

double parse_line(void)
{
    double value;

    value = parse_expression();

    return value;
}

int main(int argc, char **argv)
{
    char line[BUFFER_SIZE];
    double value;

    printf("welcome to calculator !\n");
    while (fgets(line, BUFFER_SIZE, stdin) != NULL) {
        set_buffer(line);
        value = parse_line();
        printf(">>%f\n", value);
    }

    return 0;
}