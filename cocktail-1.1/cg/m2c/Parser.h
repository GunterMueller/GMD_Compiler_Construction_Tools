#define DEFINITION_Parser

extern struct Parser_1 {
    CHAR A[128 + 1];
} Parser_ParsTabName;
extern void Parser_TokenName ARGS((CARDINAL Token, CHAR Name[], LONGCARD ));
extern CARDINAL Parser_Parser ARGS(());
extern void Parser_CloseParser ARGS(());
extern void BEGIN_Parser();
