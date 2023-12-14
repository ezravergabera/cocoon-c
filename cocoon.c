#include <stdlib.h>

struct Token {
    char* type;
    char* value;
};

struct Token tokens[100];

struct Token* createToken(const char* type, const char* value) {
    struct Token* tok = (struct Token*)malloc(sizeof(struct Token));

    tok->type = type;
    tok->value = value;

    return tok;
}

struct Position {
    int idx;
    int ln;
    int col;
    char* fn;
    char* ftext;
};

struct Position* createPos(int idx, int ln, int col, char* fn, char* ftext) {
    struct Position* pos = (struct Position*)malloc(sizeof(struct Position));

    pos->idx = idx;
    pos->ln = ln;
    pos->col = col;
    pos->fn = fn;
    pos->ftext = ftext;

    return pos;
}

void advance(struct Position* pos, char current_char) {
    pos->idx++;
    pos->col++;

    if (current_char == '\n') {
        pos->ln++;
        pos->col = 0;
    }
}

struct Position* copyPos(struct Position* pos) {
    return createPos(pos->idx, pos->ln, pos->col, pos->fn, pos->ftext);
}

struct Lexer {
    char* fn;
    char* text;
    struct Position* pos;
    char current_char;
};

struct Lexer* createLexer(const char* fn, const char* text) {
    struct Lexer* lexer = (struct Lexer*)malloc(sizeof(struct Lexer));

    lexer->fn = fn;
    lexer->text = text;
    lexer->pos = createPos(-1, 0, -1, fn, text);
    lexer->current_char = NULL;
    advanceLexer(lexer);

    return lexer;
}

void advanceLexer(struct Lexer* lex) {
    advance(lex->pos, lex->current_char);
    lex->current_char = lex->text[lex->pos->idx];
}

struct Token make_tokens() {
    
}