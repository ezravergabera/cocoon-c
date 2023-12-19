#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

// IDENTIFIER
#define TT_ID "Identifier"

// OPERATORS
#define TT_ASSIGN 'Assignment'
#define TT_PLUS 'PLUS'
#define TT_MINUS 'MINUS'
#define TT_MUL 'MUL'
#define TT_DIV 'DIV'
#define TT_INTDIV 'INTDIV'
#define TT_EXPO 'EXPO'
#define TT_MOD 'MOD'

// UNARY
#define TT_INCRE 'INCREMENT'
#define TT_DECRE 'DECREMENT'
#define TT_POSITIVE 'POSITIVE'
#define TT_NEGATIVE 'NEGATIVE'

// RELATIONAL
#define TT_GREATER 'Greater_than'
#define TT_LESS 'Less_than'
#define TT_GREATEREQUAL 'Greater_Equal'
#define TT_LESSEQUAL 'Less_Equal'
#define TT_EQUALTO 'Equal_to'
#define TT_NOTEQUAL 'Not_Equal'

// LOGICAL
#define TT_NOT 'NOT'
#define TT_AND 'AND'
#define TT_OR 'OR'

// CONSTANTS
#define TT_INT 'Number'
#define TT_FLOAT 'Decimal'
#define TT_STR 'Text'
#define TT_BOOL 'Bool'

// DATA TYPES
#define TT_DTYPE 'Data_Type'

// KEYWORDS
#define TT_KWORD 'Keyword'

// RESERVED WORDS
#define TT_RWORD 'Reserved_Word'

// NOISE WORDS
#define TT_NWORD 'Noise_Word'

// COMMENTS
#define TT_COMMENT 'Comment'

// PUNTUATIONS
#define TT_DOT 'Dot'
#define TT_COMMA 'Comma'
#define TT_SEMICOLON 'Semicolon'
#define TT_LSQUARE 'Left_Square'
#define TT_RSQUARE 'Right_Square'
#define TT_LPAREN 'Left_Paren'
#define TT_RPAREN 'Right_Paren'

// END OF FILE
#define TT_EOF 'EOF'

// Check
bool isWhitespace(char cur_char) {
    switch (cur_char) {
        case 0:
        case ' ':
        case '\t':
        case '\n':
        case '\v':
        case '\r':
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool isAlphabet(char cur_char) {
    switch (cur_char) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
            return true;
            break;
        default:
            return false;
            break;
    }
}

typedef struct {
    char* type;
    char* value;
} Token;

Token* createToken(char* type, char* value) {
    Token* tok = (Token*)malloc(sizeof(Token));

    tok->type = type;
    tok->value = value;

    return tok;
}

typedef struct {
    Token* tokens;
    size_t used;
    size_t size;
} Tokens;

void initTokArr(Tokens* tokarr, size_t initialSize) {
    tokarr->tokens = malloc(sizeof(Token) * initialSize);
}

void insertTok(Tokens* tokarr, Token* tok) {
    if (tokarr->used == tokarr->size) {
        tokarr->size *= 2;
        tokarr->tokens = realloc(tokarr->tokens, tokarr->size * sizeof(tok));
    }
    tokarr->tokens[tokarr->used++] = *tok;
}

void freeTokArr(Tokens* tokarr) {
    free(tokarr->tokens);
    tokarr->tokens = NULL;
    tokarr->size = tokarr->used = 0;
}

typedef struct {
    int idx;
    int ln;
    int col;
} Position;

Position* createPos(int idx, int ln, int col) {
    Position* pos = (Position*)malloc(sizeof(Position));

    pos->idx = idx;
    pos->ln = ln;
    pos->col = col;

    return pos;
}

void advancePos(Position* pos, char current_char) {
    pos->idx++;
    pos->col++;

    if (current_char == '\n') {
        pos->ln++;
        pos->col = 0;
    }
}

Position* copyPos(Position* pos) {
    return createPos(pos->idx, pos->ln, pos->col);
}

typedef struct {
    const char* fn;
    const char* text;
    Position* pos;
    char current_char;
} Lexer;

Lexer* advanceLexer(Lexer* lex);

Lexer* createLexer(const char* fn, const char* text) {
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));

    lexer->fn = fn;
    lexer->text = text;
    lexer->pos = createPos(-1, 0, -1);
    lexer->current_char = NULL;
    lexer = advanceLexer(lexer);

    return lexer;
}

Lexer* advanceLexer(Lexer* lex) {
    advancePos(lex->pos, lex->current_char);
    lex->current_char = lex->text[lex->pos->idx];
    
    return lex;
}

char* scanIdentifier(Lexer* lexer) {
    char* lexeme;
    char cur_char = lexer->current_char;

    if (cur_char == 'a') {
        lexeme += cur_char;
    }

    Token* tok = createToken(TT_ID, lexeme);

    return tok;
}

struct Token* make_tokens(Lexer* lexer) {
    Tokens* tokens;
    initTokArr(&tokens, 5);

    while(lexer->current_char != NULL) {
        char cur_char = lexer->current_char;
        if (isWhitespace(cur_char))
            break;

        else if (isAlphabet(cur_char)) {
            Token* tok = scanIdentifier(lexer);
            insertTok(tokens, tok);
        }

        lexer = advanceLexer(lexer);
    }
}

Token* run(char* fn, char* text) {
    Lexer* lexer = createLexer(fn, text);
    Token* tokens = make_tokens(lexer);

    return tokens;
}

int main(){
    char* text;
    printf("cocoon > ");
    scanf("%s", &text);

    run("<stdin>", text);
    printf("%s", text);
    
    return 0;
}