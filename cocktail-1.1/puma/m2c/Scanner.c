#include "SYSTEM_.h"

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Source
#include "Source.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

INTEGER Scanner_TokenLength;
Scanner_tScanAttribute Scanner_Attribute;
struct Scanner_11 Scanner_ScanTabName;
PROC Scanner_Exit;

static INTEGER NestingLevel;
static Positions_tPosition Position, StringPos;
#define yyTabSpace	8
#define yyDNoState	0
#define yyFileStackSize	16
#define yyInitBufferSize	(1024 * 8 + 256)
#define yyFirstCh	'\0'
#define yyLastCh	((CHAR)'\177')
#define yyEolCh	'\n'
#define yyEobCh	((CHAR)'\177')
#define yyDStateCount	209
#define yyTableSize	2236
#define yyEobState	65
#define yyDefaultState	66
#define STD	1
#define comment	3
#define Str1	5
#define Str2	7
#define CStr1	9
#define CStr2	11
#define targetcode	13
#define expr	15
typedef SHORTCARD yyTableElmt;
typedef yyTableElmt yyStateRange;
typedef yyTableElmt yyTableRange;
typedef struct S_1 {
    yyStateRange Check, Next;
} yyCombType;
typedef yyCombType *yyCombTypePtr;
typedef struct S_6 {
    CHAR A[1000000 + 1];
} *yytChBufferPtr;
typedef CHAR yyChRange;
static struct S_7 {
    LONGCARD A[yyDStateCount + 1];
} yyBasePtr;
static struct S_8 {
    yyStateRange A[yyDStateCount + 1];
} yyDefault;
static struct S_9 {
    yyCombType A[yyTableSize + 1];
} yyComb;
static struct S_10 {
    yyStateRange A[yyDStateCount + 1];
} yyEobTrans;
static struct S_11 {
    CHAR A[yyLastCh + 1];
} yyToLower, yyToUpper;
static struct S_12 {
    yyStateRange A[1000000 + 1];
} *yyStateStack;
static LONGINT yyStateStackSize;
static yyStateRange yyStartState;
static yyStateRange yyPreviousStart;
static CHAR yyCh;
static System_tFile yySourceFile;
static BOOLEAN yyEof;
static yytChBufferPtr yyChBufferPtr;
static INTEGER yyChBufferStart;
static LONGINT yyChBufferSize;
static INTEGER yyChBufferIndex;
static INTEGER yyBytesRead;
static CARDINAL yyLineCount;
static INTEGER yyLineStart;
static SHORTCARD yyFileStackPtr;
static struct S_13 {
    struct S_14 {
        System_tFile SourceFile;
        BOOLEAN Eof;
        yytChBufferPtr ChBufferPtr;
        INTEGER ChBufferStart;
        LONGINT ChBufferSize;
        INTEGER ChBufferIndex;
        INTEGER BytesRead;
        CARDINAL LineCount;
        INTEGER LineStart;
    } A[yyFileStackSize - 1 + 1];
} yyFileStack;
static void yyInitialize ARGS(());
static void yyStart ARGS((yyStateRange State));
static void yyPrevious ARGS(());
static void yyEcho ARGS(());
static void yyLess ARGS((INTEGER n));
static void yyTab ARGS(());
static void yyTab1 ARGS((INTEGER a));
static void yyTab2 ARGS((INTEGER a, INTEGER b));
static void yyEol ARGS((INTEGER Column));
static void output ARGS((CHAR c));
static void unput ARGS((CHAR c));
static CHAR input ARGS(());
static void yyGetTables ARGS(());
struct S_16 {
    yyTableRange A[yyDStateCount + 1];
};
static CARDINAL yyGetTable ARGS((System_tFile TableFile, ADDRESS Address));
static void yyErrorMessage ARGS((SHORTCARD ErrorCode));
static void yyExit ARGS(());


void Scanner_ErrorAttribute
# ifdef __STDC__
(INTEGER Token, Scanner_tScanAttribute *pAttribute)
# else
(Token, pAttribute)
INTEGER Token;
Scanner_tScanAttribute *pAttribute;
# endif
{
  pAttribute->Position = Scanner_Attribute.Position;
  switch (Token) {
  case 1:;
    pAttribute->U_1.V_1.Ident.Ident = Idents_NoIdent;
    break;
  case 2:;
    pAttribute->U_1.V_2.Operator.Ident = Idents_NoIdent;
    break;
  case 3:;
    pAttribute->U_1.V_3.IncOperator.Ident = Idents_NoIdent;
    break;
  case 4:;
    Texts_MakeText(&pAttribute->U_1.V_4.TargetBlock.Text);
    break;
  case 5:;
    pAttribute->U_1.V_5.String.StringRef = Idents_GetStringRef(Idents_NoIdent);
    break;
  case 6:;
    pAttribute->U_1.V_6.Number.StringRef = Idents_GetStringRef(Idents_NoIdent);
    break;
  case 7:;
    pAttribute->U_1.V_7.TargetCode.StringRef = Idents_GetStringRef(Idents_NoIdent);
    break;
  case 8:;
    pAttribute->U_1.V_8.WhiteSpace.StringRef = Idents_GetStringRef(Idents_NoIdent);
    break;
  case 9:;
    pAttribute->U_1.V_9.yy9.StringRef = Idents_GetStringRef(Idents_NoIdent);
    break;
  default :
    break;
  }
}

void Scanner_Error
# ifdef __STDC__
(CHAR Text[], LONGCARD O_1, Positions_tPosition Position)
# else
(Text, O_1, Position)
CHAR Text[];
LONGCARD O_1;
Positions_tPosition Position;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Text, O_1, CHAR)
  Errors_Message(Text, O_1, (LONGCARD)Errors_Error, Position);
  INC(Tree_ErrorCount);
  FREE_OPEN_ARRAYS
}

void Scanner_ErrorI
# ifdef __STDC__
(CHAR Text[], LONGCARD O_2, Positions_tPosition Position, Idents_tIdent Ident)
# else
(Text, O_2, Position, Ident)
CHAR Text[];
LONGCARD O_2;
Positions_tPosition Position;
Idents_tIdent Ident;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_2 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Text, O_2, CHAR)
  Errors_MessageI(Text, O_2, (LONGCARD)Errors_Error, Position, (LONGCARD)Errors_Ident, ADR(Ident));
  INC(Tree_ErrorCount);
  FREE_OPEN_ARRAYS
}

void Scanner_Warning
# ifdef __STDC__
(CHAR Text[], LONGCARD O_3, Positions_tPosition Position)
# else
(Text, O_3, Position)
CHAR Text[];
LONGCARD O_3;
Positions_tPosition Position;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_3 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Text, O_3, CHAR)
  if (!Sets_IsElement(ORD('s'), &Tree_Options)) {
    Errors_Message(Text, O_3, (LONGCARD)Errors_Warning, Position);
  }
  FREE_OPEN_ARRAYS
}

void Scanner_WarningI
# ifdef __STDC__
(CHAR Text[], LONGCARD O_4, Positions_tPosition Position, Idents_tIdent Ident)
# else
(Text, O_4, Position, Ident)
CHAR Text[];
LONGCARD O_4;
Positions_tPosition Position;
Idents_tIdent Ident;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_4 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Text, O_4, CHAR)
  if (!Sets_IsElement(ORD('s'), &Tree_Options)) {
    Errors_MessageI(Text, O_4, (LONGCARD)Errors_Warning, Position, (LONGCARD)Errors_Ident, ADR(Ident));
  }
  FREE_OPEN_ARRAYS
}

INTEGER Scanner_GetToken
# ifdef __STDC__
()
# else
()
# endif
{
  yyStateRange yyState;
  yyCombTypePtr yyTablePtr;
  BOOLEAN yyRestartFlag;
  INTEGER yyi, yySource, yyTarget, yyChBufferFree;
  Strings_tString Word, String, TargetCode;

  for (;;) {
    yyState = yyStartState;
    Scanner_TokenLength = 0;
    for (;;) {
      for (;;) {
        yyTablePtr = (yyCombTypePtr)(yyBasePtr.A[yyState] + ORD(yyChBufferPtr->A[yyChBufferIndex]) * sizeof(yyCombType));
        if (yyTablePtr->Check != yyState) {
          yyState = yyDefault.A[yyState];
          if (yyState == yyDNoState) {
            goto EXIT_3;
          }
        } else {
          yyState = yyTablePtr->Next;
          INC(Scanner_TokenLength);
          yyStateStack->A[Scanner_TokenLength] = yyState;
          INC(yyChBufferIndex);
        }
      } EXIT_3:;
      for (;;) {
        switch (yyStateStack->A[Scanner_TokenLength]) {
        case 209:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          if (NestingLevel == 0) {
            Texts_MakeText(&Scanner_Attribute.U_1.V_4.TargetBlock.Text);
            Strings_AssignEmpty(&TargetCode);
            Position = Scanner_Attribute.Position;
          } else {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&TargetCode, &Word);
          }
          INC(NestingLevel);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 208:;
          DEC(NestingLevel);
          if (NestingLevel == 0) {
            yyStart(STD);
            Texts_Append(&Scanner_Attribute.U_1.V_4.TargetBlock.Text, &TargetCode);
            Scanner_Attribute.Position = Position;
            return 4;
          } else {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&TargetCode, &Word);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 22:;
        case 75:;
          if (NestingLevel > 0) {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&TargetCode, &Word);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 207:;
          if (NestingLevel > 0) {
            Strings_Append(&TargetCode, '\t');
          }
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 206:;
          if (NestingLevel > 0) {
            Texts_Append(&Scanner_Attribute.U_1.V_4.TargetBlock.Text, &TargetCode);
            Strings_AssignEmpty(&TargetCode);
          }
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 23:;
          if (NestingLevel > 0) {
            Scanner_GetWord(&Word);
            Strings_Append(&TargetCode, Strings_Char(&Word, 2));
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 37:;
          if (NestingLevel > 0) {
            Strings_Append(&TargetCode, '\\');
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 203:;
        case 205:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(comment);
          Position = Scanner_Attribute.Position;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 201:;
          yyPrevious();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 28:;
        case 42:;
        case 70:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 30:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 29:;
        case 43:;
        case 59:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_6.Number.StringRef = StringMem_PutString(&Word);
          return 6;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 200:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&String);
          StringPos = Scanner_Attribute.Position;
          if (Sets_IsElement(ORD('c'), &Tree_Options)) {
            yyStart(CStr1);
          } else {
            yyStart(Str1);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 199:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&String);
          StringPos = Scanner_Attribute.Position;
          if (Sets_IsElement(ORD('c'), &Tree_Options)) {
            yyStart(CStr2);
          } else {
            yyStart(Str2);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 27:;
        case 71:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 26:;
        case 72:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 25:;
        case 41:;
        case 58:;
        case 73:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 24:;
        case 40:;
        case 57:;
        case 74:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 198:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 197:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 196:;
          Strings_Append(&String, Strings_Char(&String, 1));
          yyPrevious();
          if (yyStartState == targetcode) {
            Strings_Concatenate(&TargetCode, &String);
          } else {
            Scanner_Attribute.U_1.V_5.String.StringRef = StringMem_PutString(&String);
            return 5;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 195:;
          Strings_Append(&String, Strings_Char(&String, 1));
          yyPrevious();
          if (yyStartState == targetcode) {
            Strings_Concatenate(&TargetCode, &String);
          } else {
            Scanner_Attribute.U_1.V_5.String.StringRef = StringMem_PutString(&String);
            return 5;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 194:;
          Strings_Append(&String, '\t');
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 193:;
          Scanner_Error((STRING)"unclosed string", 15L, Scanner_Attribute.Position);
          Strings_Append(&String, Strings_Char(&String, 1));
          yyEol(0L);
          yyPrevious();
          if (yyStartState == targetcode) {
            Strings_Concatenate(&TargetCode, &String);
          } else {
            Scanner_Attribute.U_1.V_5.String.StringRef = StringMem_PutString(&String);
            return 5;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 192:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 9;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 118:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          if (NestingLevel == 0) {
            Position = Scanner_Attribute.Position;
          }
          yyStart(expr);
          INC(NestingLevel);
          return 34;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 18:;
        case 35:;
        case 204:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_7.TargetCode.StringRef = StringMem_PutString(&Word);
          return 7;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 191:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          INC(NestingLevel);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_7.TargetCode.StringRef = StringMem_PutString(&Word);
          return 7;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 190:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          DEC(NestingLevel);
          if (NestingLevel == 0) {
            yyStart(STD);
            return 35;
          } else {
            Scanner_GetWord(&Word);
            Scanner_Attribute.U_1.V_7.TargetCode.StringRef = StringMem_PutString(&Word);
            return 7;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 188:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_7.TargetCode.StringRef = StringMem_PutString(&Word);
          return 7;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 189:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_9.yy9.StringRef = StringMem_PutString(&Word);
          return 9;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 19:;
        case 76:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_8.WhiteSpace.StringRef = StringMem_PutString(&Word);
          return 8;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 187:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_8.WhiteSpace.StringRef = StringMem_PutString(&Word);
          yyEol(0L);
          return 8;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 186:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_8.WhiteSpace.StringRef = StringMem_PutString(&Word);
          yyTab();
          return 8;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 21:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, 2, &String);
          Scanner_Attribute.U_1.V_7.TargetCode.StringRef = StringMem_PutString(&String);
          return 7;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 38:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_7.TargetCode.StringRef = StringMem_PutString(&Word);
          return 7;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 150:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(targetcode);
          return 19;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 145:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(targetcode);
          return 20;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 167:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(targetcode);
          return 16;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 156:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(targetcode);
          return 18;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 161:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(targetcode);
          return 17;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 126:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(targetcode);
          return 30;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 31:;
        case 44:;
        case 45:;
        case 46:;
        case 47:;
        case 48:;
        case 49:;
        case 50:;
        case 60:;
        case 128:;
        case 202:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_2.Operator.Ident = Idents_MakeIdent(&Word);
          return 2;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 33:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_3.IncOperator.Ident = Idents_MakeIdent(&Word);
          return 3;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 32:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, (Strings_tStringIndex)Strings_Length(&Word), &String);
          Scanner_Attribute.U_1.V_2.Operator.Ident = Idents_MakeIdent(&String);
          return 2;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 185:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 10;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 182:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 11;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 178:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 12;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 177:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 13;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 172:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 14;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 168:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 15;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 140:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 21;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 133:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 22;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 132:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 23;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 77:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 24;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 61:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 25;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 131:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 26;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 130:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 27;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 129:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 28;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 127:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 29;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 79:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 31;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 121:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 32;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 119:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 33;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 117:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 35;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 116:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 36;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 115:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 37;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 114:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 38;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 113:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 39;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 112:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 40;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 111:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 41;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 107:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 42;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 104:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 43;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 103:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 44;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 97:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 45;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 89:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 46;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 80:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 31;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 78:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return 40;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 17:;
        case 34:;
        case 51:;
        case 52:;
        case 53:;
        case 54:;
        case 55:;
        case 56:;
        case 62:;
        case 63:;
        case 81:;
        case 82:;
        case 83:;
        case 84:;
        case 85:;
        case 86:;
        case 87:;
        case 88:;
        case 90:;
        case 91:;
        case 92:;
        case 93:;
        case 94:;
        case 95:;
        case 96:;
        case 98:;
        case 99:;
        case 100:;
        case 101:;
        case 102:;
        case 105:;
        case 106:;
        case 108:;
        case 109:;
        case 110:;
        case 120:;
        case 122:;
        case 123:;
        case 124:;
        case 125:;
        case 134:;
        case 135:;
        case 136:;
        case 137:;
        case 138:;
        case 139:;
        case 141:;
        case 142:;
        case 143:;
        case 144:;
        case 146:;
        case 147:;
        case 148:;
        case 149:;
        case 151:;
        case 152:;
        case 153:;
        case 154:;
        case 155:;
        case 157:;
        case 158:;
        case 159:;
        case 160:;
        case 162:;
        case 163:;
        case 164:;
        case 165:;
        case 166:;
        case 169:;
        case 170:;
        case 171:;
        case 173:;
        case 174:;
        case 175:;
        case 176:;
        case 179:;
        case 180:;
        case 181:;
        case 183:;
        case 184:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.Ident.Ident = Idents_MakeIdent(&Word);
          return 1;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 69:;
          while (yyChBufferPtr->A[yyChBufferIndex] == ' ') {
            INC(yyChBufferIndex);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 68:;
          DEC1(yyLineStart, 7 - (yyChBufferIndex - yyLineStart - 2) % 8);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 67:;
          INC(yyLineCount);
          yyLineStart = yyChBufferIndex - 1;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 1:;
        case 2:;
        case 3:;
        case 4:;
        case 5:;
        case 6:;
        case 7:;
        case 8:;
        case 9:;
        case 10:;
        case 11:;
        case 12:;
        case 13:;
        case 14:;
        case 15:;
        case 16:;
        case 20:;
        case 36:;
        case 39:;
        case 64:;
          DEC(yyChBufferIndex);
          DEC(Scanner_TokenLength);
          break;
        case 66:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart;
          INC(yyChBufferIndex);
          Scanner_TokenLength = 1;
          Scanner_GetWord(&Word);
          Errors_MessageI((STRING)"illegal character", 17L, (LONGCARD)Errors_Error, Scanner_Attribute.Position, (LONGCARD)Errors_String, ADR(Word));
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case yyDNoState:;
          yyGetTables();
          yyStateStack->A[0] = yyDefaultState;
          if (yyFileStackPtr == 0) {
            yyInitialize();
            yySourceFile = System_StdInput;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 65:;
          DEC(yyChBufferIndex);
          DEC(Scanner_TokenLength);
          if (Scanner_TokenLength == 0) {
            yyState = yyStartState;
          } else {
            yyState = yyStateStack->A[Scanner_TokenLength];
          }
          if (yyChBufferIndex != yyChBufferStart + yyBytesRead) {
            yyState = yyEobTrans.A[yyState];
            if (yyState != yyDNoState) {
              INC(yyChBufferIndex);
              INC(Scanner_TokenLength);
              yyStateStack->A[Scanner_TokenLength] = yyState;
              yyRestartFlag = TRUE;
              goto EXIT_4;
            }
          } else {
            yySource = yyChBufferIndex - Scanner_TokenLength - 1;
            yyTarget = General_MaxAlign - Scanner_TokenLength % General_MaxAlign - 1;
            if (yySource != yyTarget) {
              {
                LONGINT B_1 = 1, B_2 = Scanner_TokenLength;

                if (B_1 <= B_2)
                  for (yyi = B_1;; yyi += 1) {
                    yyChBufferPtr->A[yyTarget + yyi] = yyChBufferPtr->A[yySource + yyi];
                    if (yyi >= B_2) break;
                  }
              }
              DEC1(yyLineStart, yySource - yyTarget);
              yyChBufferStart = yyTarget + Scanner_TokenLength + 1;
            } else {
              yyChBufferStart = yyChBufferIndex;
            }
            if (!yyEof) {
              yyChBufferFree = General_Exp2(General_Log2(yyChBufferSize - 4 - General_MaxAlign - Scanner_TokenLength));
              if (yyChBufferFree < yyChBufferSize / 8) {
                DynArray_ExtendArray((ADDRESS *)&yyChBufferPtr, &yyChBufferSize, (LONGINT)sizeof(CHAR));
                if (yyChBufferPtr == NIL) {
                  yyErrorMessage(1);
                }
                yyChBufferFree = General_Exp2(General_Log2(yyChBufferSize - 4 - General_MaxAlign - Scanner_TokenLength));
                if (yyStateStackSize < yyChBufferSize) {
                  DynArray_ExtendArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyStateRange));
                  if (yyStateStack == NIL) {
                    yyErrorMessage(1);
                  }
                }
              }
              yyChBufferIndex = yyChBufferStart;
              yyBytesRead = Source_GetLine(yySourceFile, ADR(yyChBufferPtr->A[yyChBufferIndex]), (LONGCARD)yyChBufferFree);
              if (yyBytesRead <= 0) {
                yyBytesRead = 0;
                yyEof = TRUE;
              }
              yyChBufferPtr->A[yyChBufferStart + yyBytesRead] = yyEobCh;
              yyChBufferPtr->A[yyChBufferStart + yyBytesRead + 1] = '\0';
              yyRestartFlag = TRUE;
              goto EXIT_4;
            }
            if (Scanner_TokenLength == 0) {
              Scanner_Attribute.Position.Line = yyLineCount;
              Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart;
              Scanner_CloseFile();
              if (yyFileStackPtr == 0) {
                switch (yyStartState) {
                case comment:;
                  Scanner_Error((STRING)"unclosed comment", 16L, Position);
                  break;
                case expr:;
                case targetcode:;
                  Scanner_Error((STRING)"unclosed target code", 20L, Position);
                  break;
                case CStr1:;
                case CStr2:;
                case Str1:;
                case Str2:;
                  Scanner_Error((STRING)"unclosed string", 15L, StringPos);
                  break;
                default :
                  break;
                }
              }
              if (yyFileStackPtr == 0) {
                return Scanner_EofToken;
              }
              yyRestartFlag = FALSE;
              goto EXIT_4;
            }
          }
          break;
        default :
          yyErrorMessage(0);
          break;
        }
      } EXIT_4:;
      if (yyRestartFlag) {
      } else {
        goto EXIT_2;
      }
    } EXIT_2:;
  } EXIT_1:;
}

void Scanner_BeginFile
# ifdef __STDC__
(CHAR FileName[], LONGCARD O_5)
# else
(FileName, O_5)
CHAR FileName[];
LONGCARD O_5;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_5 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(FileName, O_5, CHAR)
  if (yyStateStack->A[0] == yyDNoState) {
    yyGetTables();
    yyStateStack->A[0] = yyDefaultState;
  }
  yyInitialize();
  yySourceFile = Source_BeginSource(FileName, O_5);
  if (yySourceFile < 0) {
    yyErrorMessage(5);
  }
  FREE_OPEN_ARRAYS
}

static void yyInitialize
# ifdef __STDC__
()
# else
()
# endif
{
  if (yyFileStackPtr >= yyFileStackSize) {
    yyErrorMessage(3);
  }
  INC(yyFileStackPtr);
  {
    register struct S_14 *W_1 = &yyFileStack.A[yyFileStackPtr - 1];

    W_1->SourceFile = yySourceFile;
    W_1->Eof = yyEof;
    W_1->ChBufferPtr = yyChBufferPtr;
    W_1->ChBufferStart = yyChBufferStart;
    W_1->ChBufferSize = yyChBufferSize;
    W_1->ChBufferIndex = yyChBufferIndex;
    W_1->BytesRead = yyBytesRead;
    W_1->LineCount = yyLineCount;
    W_1->LineStart = yyLineStart;
  }
  yyChBufferSize = yyInitBufferSize;
  DynArray_MakeArray((ADDRESS *)&yyChBufferPtr, &yyChBufferSize, (LONGINT)sizeof(CHAR));
  if (yyChBufferPtr == NIL) {
    yyErrorMessage(1);
  }
  yyChBufferStart = General_MaxAlign;
  yyChBufferPtr->A[yyChBufferStart - 1] = yyEolCh;
  yyChBufferPtr->A[yyChBufferStart] = yyEobCh;
  yyChBufferPtr->A[yyChBufferStart + 1] = '\0';
  yyChBufferIndex = yyChBufferStart;
  yyEof = FALSE;
  yyBytesRead = 0;
  yyLineCount = 1;
  yyLineStart = yyChBufferStart - 1;
}

void Scanner_CloseFile
# ifdef __STDC__
()
# else
()
# endif
{
  if (yyFileStackPtr == 0) {
    yyErrorMessage(4);
  }
  Source_CloseSource(yySourceFile);
  DynArray_ReleaseArray((ADDRESS *)&yyChBufferPtr, &yyChBufferSize, (LONGINT)sizeof(CHAR));
  {
    register struct S_14 *W_2 = &yyFileStack.A[yyFileStackPtr - 1];

    yySourceFile = W_2->SourceFile;
    yyEof = W_2->Eof;
    yyChBufferPtr = W_2->ChBufferPtr;
    yyChBufferStart = W_2->ChBufferStart;
    yyChBufferSize = W_2->ChBufferSize;
    yyChBufferIndex = W_2->ChBufferIndex;
    yyBytesRead = W_2->BytesRead;
    yyLineCount = W_2->LineCount;
    yyLineStart = W_2->LineStart;
  }
  DEC(yyFileStackPtr);
}

void Scanner_GetWord
# ifdef __STDC__
(Strings_tString *Word)
# else
(Word)
Strings_tString *Word;
# endif
{
  INTEGER i, WordStart;

  WordStart = yyChBufferIndex - Scanner_TokenLength - 1;
  {
    LONGINT B_3 = 1, B_4 = Scanner_TokenLength;

    if (B_3 <= B_4)
      for (i = B_3;; i += 1) {
        Word->Chars.A[i] = yyChBufferPtr->A[WordStart + i];
        if (i >= B_4) break;
      }
  }
  Word->Length = Scanner_TokenLength;
}

void Scanner_GetLower
# ifdef __STDC__
(Strings_tString *Word)
# else
(Word)
Strings_tString *Word;
# endif
{
  INTEGER i, WordStart;

  WordStart = yyChBufferIndex - Scanner_TokenLength - 1;
  {
    LONGINT B_5 = 1, B_6 = Scanner_TokenLength;

    if (B_5 <= B_6)
      for (i = B_5;; i += 1) {
        Word->Chars.A[i] = yyToLower.A[yyChBufferPtr->A[WordStart + i]];
        if (i >= B_6) break;
      }
  }
  Word->Length = Scanner_TokenLength;
}

void Scanner_GetUpper
# ifdef __STDC__
(Strings_tString *Word)
# else
(Word)
Strings_tString *Word;
# endif
{
  INTEGER i, WordStart;

  WordStart = yyChBufferIndex - Scanner_TokenLength - 1;
  {
    LONGINT B_7 = 1, B_8 = Scanner_TokenLength;

    if (B_7 <= B_8)
      for (i = B_7;; i += 1) {
        Word->Chars.A[i] = yyToUpper.A[yyChBufferPtr->A[WordStart + i]];
        if (i >= B_8) break;
      }
  }
  Word->Length = Scanner_TokenLength;
}

static void yyStart
# ifdef __STDC__
(yyStateRange State)
# else
(State)
yyStateRange State;
# endif
{
  yyPreviousStart = yyStartState;
  yyStartState = State;
}

static void yyPrevious
# ifdef __STDC__
()
# else
()
# endif
{
  yyStateRange s;

  s = yyStartState;
  yyStartState = yyPreviousStart;
  yyPreviousStart = s;
}

static void yyEcho
# ifdef __STDC__
()
# else
()
# endif
{
  INTEGER i;

  {
    LONGINT B_9 = yyChBufferIndex - Scanner_TokenLength, B_10 = yyChBufferIndex - 1;

    if (B_9 <= B_10)
      for (i = B_9;; i += 1) {
        IO_WriteC((System_tFile)IO_StdOutput, yyChBufferPtr->A[i]);
        if (i >= B_10) break;
      }
  }
}

static void yyLess
# ifdef __STDC__
(INTEGER n)
# else
(n)
INTEGER n;
# endif
{
  DEC1(yyChBufferIndex, Scanner_TokenLength - n);
  Scanner_TokenLength = n;
}

static void yyTab
# ifdef __STDC__
()
# else
()
# endif
{
  DEC1(yyLineStart, yyTabSpace - 1 - (yyChBufferIndex - yyLineStart - 2) % yyTabSpace);
}

static void yyTab1
# ifdef __STDC__
(INTEGER a)
# else
(a)
INTEGER a;
# endif
{
  DEC1(yyLineStart, yyTabSpace - 1 - (yyChBufferIndex - yyLineStart - Scanner_TokenLength + a - 1) % yyTabSpace);
}

static void yyTab2
# ifdef __STDC__
(INTEGER a, INTEGER b)
# else
(a, b)
INTEGER a, b;
# endif
{
  DEC1(yyLineStart, yyTabSpace - 1 - (yyChBufferIndex - yyLineStart - Scanner_TokenLength + a - 1) % yyTabSpace);
}

static void yyEol
# ifdef __STDC__
(INTEGER Column)
# else
(Column)
INTEGER Column;
# endif
{
  INC(yyLineCount);
  yyLineStart = yyChBufferIndex - 1 - Column;
}

static void output
# ifdef __STDC__
(CHAR c)
# else
(c)
CHAR c;
# endif
{
  IO_WriteC((System_tFile)IO_StdOutput, c);
}

static void unput
# ifdef __STDC__
(CHAR c)
# else
(c)
CHAR c;
# endif
{
  DEC(yyChBufferIndex);
  yyChBufferPtr->A[yyChBufferIndex] = c;
}

static CHAR input
# ifdef __STDC__
()
# else
()
# endif
{
  if (yyChBufferIndex == yyChBufferStart + yyBytesRead) {
    if (!yyEof) {
      DEC1(yyLineStart, yyBytesRead);
      yyChBufferIndex = 0;
      yyChBufferStart = 0;
      yyBytesRead = Source_GetLine(yySourceFile, (ADDRESS)yyChBufferPtr, (LONGCARD)General_Exp2(General_Log2(yyChBufferSize)));
      if (yyBytesRead <= 0) {
        yyBytesRead = 0;
        yyEof = TRUE;
      }
      yyChBufferPtr->A[yyBytesRead] = yyEobCh;
      yyChBufferPtr->A[yyBytesRead + 1] = '\0';
    }
  }
  if (yyChBufferIndex == yyChBufferStart + yyBytesRead) {
    return '\0';
  } else {
    INC(yyChBufferIndex);
    return yyChBufferPtr->A[yyChBufferIndex - 1];
  }
}

void Scanner_BeginScanner
# ifdef __STDC__
()
# else
()
# endif
{
  NestingLevel = 0;
}

void Scanner_CloseScanner
# ifdef __STDC__
()
# else
()
# endif
{
}

static void yyGetTables
# ifdef __STDC__
()
# else
()
# endif
{
  CARDINAL BlockSize, j, n;
  System_tFile TableFile;
  yyStateRange i;
  struct S_16 Base;

  BlockSize = 64000 / sizeof(yyCombType);
  TableFile = OpenInput(Scanner_ScanTabName.A, 128L);
  Checks_ErrorCheck((STRING)"yyGetTables.OpenInput", 21L, TableFile);
  if (yyGetTable(TableFile, ADR(Base)) / sizeof(yyTableElmt) - 1 != yyDStateCount || yyGetTable(TableFile, ADR(yyDefault)) / sizeof(yyTableElmt) - 1 != yyDStateCount || yyGetTable(TableFile, ADR(yyEobTrans)) / sizeof(yyTableElmt) - 1 != yyDStateCount) {
    yyErrorMessage(2);
  }
  n = 0;
  j = 0;
  while (j <= yyTableSize) {
    INC1(n, yyGetTable(TableFile, ADR(yyComb.A[j])) / sizeof(yyCombType));
    INC1(j, BlockSize);
  }
  if (n != yyTableSize + 1) {
    yyErrorMessage(2);
  }
  Close(TableFile);
  for (i = 0; i <= yyDStateCount; i += 1) {
    yyBasePtr.A[i] = (LONGCARD)ADR(yyComb.A[Base.A[i]]);
  }
}

static CARDINAL yyGetTable
# ifdef __STDC__
(System_tFile TableFile, ADDRESS Address)
# else
(TableFile, Address)
System_tFile TableFile;
ADDRESS Address;
# endif
{
  INTEGER N;
  yyTableElmt Length;

  N = Read(TableFile, ADR(Length), (LONGINT)sizeof(yyTableElmt));
  Checks_ErrorCheck((STRING)"yyGetTable.Read1", 16L, N);
  N = Read(TableFile, Address, (LONGINT)Length);
  Checks_ErrorCheck((STRING)"yyGetTable.Read2", 16L, N);
  return Length;
}

static void yyErrorMessage
# ifdef __STDC__
(SHORTCARD ErrorCode)
# else
(ErrorCode)
SHORTCARD ErrorCode;
# endif
{
  Positions_WritePosition((System_tFile)IO_StdError, Scanner_Attribute.Position);
  switch (ErrorCode) {
  case 0:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)": Scanner: internal error", 25L);
    break;
  case 1:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)": Scanner: out of memory", 24L);
    break;
  case 2:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)": Scanner: table mismatch", 25L);
    break;
  case 3:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)": Scanner: too many nested include files", 40L);
    break;
  case 4:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)": Scanner: file stack underflow (too many calls of CloseFile)", 61L);
    break;
  case 5:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)": Scanner: cannot open input file", 33L);
    break;
  }
  IO_WriteNl((System_tFile)IO_StdError);
  (*Scanner_Exit)();
}

static void yyExit
# ifdef __STDC__
()
# else
()
# endif
{
  IO_CloseIO();
  Exit(1L);
}

void BEGIN_Scanner()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    BEGIN_Strings();
    BEGIN_StringMem();
    BEGIN_Idents();
    BEGIN_Texts();
    BEGIN_Positions();
    BEGIN_Checks();
    BEGIN_System();
    BEGIN_General();
    BEGIN_Positions();
    BEGIN_IO();
    BEGIN_DynArray();
    BEGIN_Strings();
    BEGIN_Source();
    BEGIN_StringMem();
    BEGIN_Strings();
    BEGIN_Idents();
    BEGIN_Texts();
    BEGIN_Sets();
    BEGIN_Tree();
    BEGIN_Positions();
    BEGIN_Errors();

    (void)strncpy((char *)Scanner_ScanTabName.A, "Scanner.Tab", sizeof(Scanner_ScanTabName.A));
    Scanner_Exit = yyExit;
    yyFileStackPtr = 0;
    yyStartState = 1;
    yyPreviousStart = 1;
    yyBasePtr.A[yyStartState] = (LONGCARD)ADR(yyComb.A[0]);
    yyDefault.A[yyStartState] = yyDNoState;
    yyComb.A[0].Check = yyDNoState;
    yyChBufferPtr = (yytChBufferPtr)ADR(yyComb.A[0]);
    yyChBufferIndex = 1;
    yyStateStackSize = yyInitBufferSize;
    DynArray_MakeArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyStateRange));
    yyStateStack->A[0] = yyDNoState;
    for (yyCh = yyFirstCh; yyCh <= yyLastCh; yyCh += 1) {
      yyToLower.A[yyCh] = yyCh;
    }
    yyToUpper = yyToLower;
    for (yyCh = 'A'; yyCh <= 'Z'; yyCh += 1) {
      yyToLower.A[yyCh] = CHR(ORD(yyCh) - ORD('A') + ORD('a'));
    }
    for (yyCh = 'a'; yyCh <= 'z'; yyCh += 1) {
      yyToUpper.A[yyCh] = CHR(ORD(yyCh) - ORD('a') + ORD('A'));
    }
  }
}
