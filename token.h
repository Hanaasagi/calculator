#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

typedef enum {
    UNKNOWN_TOKEN,
    NUMBER_TOKEN,
    ADD_OPERATOR_TOKEN,
    SUB_OPERATOR_TOKEN,
    MUL_OPERATOR_TOKEN,
    DIV_OPERATOR_TOKEN,
    LEFT_PAREN_TOKEN,
    RIGHT_PAREN_TOKEN,
    END_TOKEN
} TokenKind;

#define MAX_TOKEN_LENGTH (100)

typedef struct {
    TokenKind kind;
    double value;
} Token;

Token token;

void set_buffer(char *line);
void next();

#endif
