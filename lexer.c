#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"

// store the formula that needs to be calculated
char *buffer;
// store token value 
char token_value[MAX_TOKEN_LENGTH];

// status used to match a number, eg 3.14
typedef enum {
    INITIAL_STATUS,
    IN_INT_PART_STATUS,
    DOT_STATUS,
    IN_FRAC_PART_STATUS
} LexerStatus;


void next()
{
    // position of token_value
    int pos = 0;
    LexerStatus status = INITIAL_STATUS;
    char current_char;

    // default token kind
    token.kind = UNKNOWN_TOKEN;
    while (*buffer != '\0') {
        current_char = *buffer;

        // match number end
        if ((status == IN_INT_PART_STATUS || status == IN_FRAC_PART_STATUS)
            && !isdigit(current_char) && current_char != '.') {
            token.kind = NUMBER_TOKEN;
            sscanf(token_value, "%lf", &token.value);
            return;
        }

        // skip
        if (isspace(current_char)) {
            if (current_char == '\n') {
                token.kind = END_TOKEN;
                return;
            }
            buffer++;
            continue;
        }

        if (pos >= MAX_TOKEN_LENGTH-1) {
            fprintf(stderr, "token is too long.\n");
            exit(1);
        }


        token_value[pos++] = *buffer++;
        token_value[pos] = '\0';

        if (current_char == '+') {
            token.kind = ADD_OPERATOR_TOKEN;
            return;
        } else if (current_char == '-') {
            token.kind = SUB_OPERATOR_TOKEN;
            return;
        } else if (current_char == '*') {
            token.kind = MUL_OPERATOR_TOKEN;
            return;
        } else if (current_char == '/') {
            token.kind = DIV_OPERATOR_TOKEN;
            return;
        } else if (current_char == '(') {
            token.kind = LEFT_PAREN_TOKEN;
            return;
        } else if (current_char == ')') {
            token.kind = RIGHT_PAREN_TOKEN;
            return;
        } else if (isdigit(current_char)) {
            if (status == INITIAL_STATUS) {
                status = IN_INT_PART_STATUS;
            } else if (status == DOT_STATUS) {
                status = IN_FRAC_PART_STATUS;
            }
        } else if (current_char == '.') {
            if (status == IN_INT_PART_STATUS) {
                status = DOT_STATUS;
            } else {
                fprintf(stderr, "syntax error\n");
                exit(1);
            }
        }
    }
}

void set_buffer(char *line)
{
    buffer = line;
}
