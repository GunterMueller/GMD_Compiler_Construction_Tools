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

#ifndef DEFINITION_System
#include "System.h"
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

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
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

INTEGER Scanner_CurArg, Scanner_ArgCount;
INTEGER Scanner_TokenLength;
Scanner_tScanAttribute Scanner_Attribute;
struct Scanner_2 Scanner_ScanTabName;
PROC Scanner_Exit;

#define TokIdentifier	1
#define TokInteger	2
#define TokString	3
#define TokTargetCode	4
#define TokCode	5
#define TokWhiteSpace	7
#define TokAfter	24
#define TokBefore	25
#define TokBegin	10
#define TokCheck	26
#define TokClose	11
#define TokDeclare	12
#define TokDemand	28
#define TokEnd	13
#define TokEval	14
#define TokExport	15
#define TokFor	71
#define TokFunction	6
#define TokGlobal	16
#define TokIgnore	72
#define TokImport	30
#define TokInherited	34
#define TokInput	31
#define TokLeft	37
#define TokLocal	18
#define TokModule	19
#define TokNone	39
#define TokOutput	32
#define TokParser	35
#define TokPrec	36
#define TokProperty	70
#define TokRemote	76
#define TokReverse	21
#define TokRight	38
#define TokRule	22
#define TokScanner	77
#define TokSelect	74
#define TokStack	20
#define TokSubunit	75
#define TokSynthesized	33
#define TokThread	27
#define TokTree	23
#define TokView	78
#define TokVirtual	17
#define TokLParent	40
#define TokRParent	41
#define TokLBracket	42
#define TokRBracket	43
#define TokLBrace	44
#define TokRBrace	45
#define TokComma	46
#define TokSemiColon	47
#define TokDot	48
#define TokColon	49
#define TokEqual	50
#define TokBar	51
#define TokAssign	52
#define TokPlus	53
#define TokMinus	54
#define TokAsterisk	55
#define TokSlash	56
#define TokLAngle	57
#define TokRAngle	58
#define TokRArrow	59
#define TokCopy	60
#define TokArrow	61
#define TokLArrow	62
static INTEGER NestingLevel;
static Positions_tPosition Position;
#define yyTabSpace	8
#define yyDNoState	0
#define yyFileStackSize	16
#define yyInitBufferSize	(1024 * 8 + 256)
#define yyFirstCh	'\0'
#define yyLastCh	((CHAR)'\177')
#define yyEolCh	'\n'
#define yyEobCh	((CHAR)'\177')
#define yyDStateCount	292
#define yyTableSize	3035
#define yyEobState	91
#define yyDefaultState	92
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
typedef struct S_2 {
    CHAR A[1000000 + 1];
} *yytChBufferPtr;
typedef CHAR yyChRange;
static struct S_3 {
    LONGCARD A[yyDStateCount + 1];
} yyBasePtr;
static struct S_4 {
    yyStateRange A[yyDStateCount + 1];
} yyDefault;
static struct S_5 {
    yyCombType A[yyTableSize + 1];
} yyComb;
static struct S_6 {
    yyStateRange A[yyDStateCount + 1];
} yyEobTrans;
static struct S_7 {
    CHAR A[yyLastCh + 1];
} yyToLower, yyToUpper;
static struct S_8 {
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
static struct S_9 {
    struct S_10 {
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
struct S_12 {
    CHAR A[255 + 1];
};
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
struct S_13 {
    yyTableRange A[yyDStateCount + 1];
};
static CARDINAL yyGetTable ARGS((System_tFile TableFile, ADDRESS Address));
static void yyErrorMessage ARGS((SHORTCARD ErrorCode));
static void yyExit ARGS(());


void Scanner_ErrorAttribute
# ifdef __STDC__
(CARDINAL Token, Scanner_tScanAttribute *Attribute)
# else
(Token, Attribute)
CARDINAL Token;
Scanner_tScanAttribute *Attribute;
# endif
{
  {
    register Scanner_tScanAttribute *W_1 = Attribute;

    switch (Token) {
    case TokIdentifier:;
      W_1->U_1.V_2.Ident = Idents_NoIdent;
      break;
    case TokInteger:;
      W_1->U_1.V_3.Integer = 0;
      break;
    case TokTargetCode:;
      Texts_MakeText(&W_1->U_1.V_4.Text);
      break;
    case TokString:;
    case TokCode:;
    case TokWhiteSpace:;
      W_1->U_1.V_1.StringRef = Idents_GetStringRef(Idents_NoIdent);
      break;
    default :
      break;
    }
  }
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
  Strings_tString String, Word, TargetCode;
  struct S_12 Argument;
  SHORTCARD j;
  CHAR ch;

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
        case 292:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          if (NestingLevel == 0) {
            Texts_MakeText(&Scanner_Attribute.U_1.V_4.Text);
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
        case 291:;
          DEC(NestingLevel);
          if (NestingLevel == 0) {
            yyStart(STD);
            Texts_Append(&Scanner_Attribute.U_1.V_4.Text, &TargetCode);
            Scanner_Attribute.Position = Position;
            return TokTargetCode;
          } else {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&TargetCode, &Word);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 24:;
        case 101:;
          if (NestingLevel > 0) {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&TargetCode, &Word);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 290:;
          if (NestingLevel > 0) {
            Strings_Append(&TargetCode, '\t');
          }
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 289:;
          if (NestingLevel > 0) {
            Texts_Append(&Scanner_Attribute.U_1.V_4.Text, &TargetCode);
            Strings_AssignEmpty(&TargetCode);
          }
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 25:;
          if (NestingLevel > 0) {
            Scanner_GetWord(&Word);
            Strings_Append(&TargetCode, Strings_Char(&Word, 2));
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 44:;
          if (NestingLevel > 0) {
            Strings_Append(&TargetCode, '\\');
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 288:;
          yyStart(comment);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 286:;
          yyPrevious();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 30:;
        case 50:;
        case 96:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 32:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 31:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_3.Integer = Strings_StringToInt(&Word);
          return TokInteger;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 285:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&String);
          if (Sets_IsElement(ORD('c'), &Tree_Options)) {
            yyStart(CStr1);
          } else {
            yyStart(Str1);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 284:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&String);
          if (Sets_IsElement(ORD('c'), &Tree_Options)) {
            yyStart(CStr2);
          } else {
            yyStart(Str2);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 29:;
        case 97:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 28:;
        case 98:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 27:;
        case 49:;
        case 71:;
        case 99:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 26:;
        case 48:;
        case 70:;
        case 100:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 283:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 282:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 281:;
          Strings_Append(&String, Strings_Char(&String, 1));
          yyPrevious();
          if (yyStartState == targetcode) {
            Strings_Concatenate(&TargetCode, &String);
          } else {
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&String);
            return TokString;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 280:;
          Strings_Append(&String, Strings_Char(&String, 1));
          yyPrevious();
          if (yyStartState == targetcode) {
            Strings_Concatenate(&TargetCode, &String);
          } else {
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&String);
            return TokString;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 279:;
          Strings_Append(&String, '\t');
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 278:;
          Errors_Message((STRING)"unclosed string", 15L, (LONGCARD)Errors_Error, Scanner_Attribute.Position);
          INC(Tree_ErrorCount);
          Strings_Append(&String, Strings_Char(&String, 1));
          yyEol(0L);
          yyPrevious();
          if (yyStartState == targetcode) {
            Strings_Concatenate(&TargetCode, &String);
          } else {
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&String);
            return TokString;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 277:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokLParent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 276:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokRParent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 275:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokComma;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 274:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokRArrow;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 272:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokDot;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 241:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokColon;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 270:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokLAngle;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 271:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokLArrow;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 269:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokEqual;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 268:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokRAngle;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 267:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokLBracket;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 266:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokRBracket;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 265:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(expr);
          INC(NestingLevel);
          return TokLBrace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 264:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokAfter;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 259:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokBefore;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 253:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokCheck;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 248:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokRemote;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 18:;
        case 43:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          return TokCode;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 242:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          if (NestingLevel <= 1) {
            return TokAssign;
          } else {
            Scanner_GetWord(&Word);
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
            return TokCode;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 240:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          if (NestingLevel <= 1) {
            return TokCopy;
          } else {
            Scanner_GetWord(&Word);
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
            return TokCode;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 239:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          if (NestingLevel <= 1) {
            return TokSemiColon;
          } else {
            Scanner_GetWord(&Word);
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
            return TokCode;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 238:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          return TokColon;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 23:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokArrow;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 237:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          INC(NestingLevel);
          if (NestingLevel <= 2) {
            return TokLBrace;
          } else {
            Scanner_GetWord(&Word);
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
            return TokCode;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 236:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          DEC(NestingLevel);
          if (NestingLevel == 0) {
            yyStart(STD);
          }
          if (NestingLevel <= 1) {
            return TokRBrace;
          } else {
            Scanner_GetWord(&Word);
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
            return TokCode;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 235:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          return TokCode;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 45:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          return TokCode;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 19:;
        case 102:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          return TokWhiteSpace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 234:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          yyEol(0L);
          return TokWhiteSpace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 233:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          yyTab();
          return TokWhiteSpace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 21:;
        case 47:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, 2, &String);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&String);
          return TokCode;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 22:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, (Strings_tStringIndex)Strings_Length(&Word), &String);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&String);
          return TokCode;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 46:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          return TokCode;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 232:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(targetcode);
          return TokBegin;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 227:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(targetcode);
          return TokClose;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 222:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokDeclare;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 217:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokDemand;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 211:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokEnd;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 209:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokEval;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 206:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(targetcode);
          return TokExport;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 200:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokFor;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 198:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokFunction;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 190:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(targetcode);
          return TokGlobal;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 184:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokIgnore;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 179:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(targetcode);
          return TokImport;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 38:;
        case 51:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokInput;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 39:;
        case 87:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokInherited;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 174:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokLeft;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 171:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          yyStart(targetcode);
          return TokLocal;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 166:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokModule;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 160:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokNone;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 37:;
        case 72:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokOutput;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 156:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokParser;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 151:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokPrec;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 149:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokProperty;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 36:;
        case 86:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokReverse;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 141:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokRight;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 137:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokRule;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 134:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokScanner;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 128:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokSelect;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 123:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokStack;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 119:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokSubunit;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 35:;
        case 85:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokSynthesized;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 113:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokThread;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 108:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokTree;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 104:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokView;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 34:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          return TokVirtual;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 17:;
        case 40:;
        case 41:;
        case 42:;
        case 52:;
        case 53:;
        case 54:;
        case 55:;
        case 56:;
        case 57:;
        case 58:;
        case 59:;
        case 60:;
        case 61:;
        case 62:;
        case 63:;
        case 64:;
        case 65:;
        case 66:;
        case 67:;
        case 68:;
        case 73:;
        case 74:;
        case 75:;
        case 76:;
        case 77:;
        case 78:;
        case 79:;
        case 80:;
        case 81:;
        case 82:;
        case 83:;
        case 84:;
        case 88:;
        case 89:;
        case 103:;
        case 105:;
        case 106:;
        case 107:;
        case 109:;
        case 110:;
        case 111:;
        case 112:;
        case 114:;
        case 115:;
        case 116:;
        case 117:;
        case 118:;
        case 120:;
        case 121:;
        case 122:;
        case 124:;
        case 125:;
        case 126:;
        case 127:;
        case 129:;
        case 130:;
        case 131:;
        case 132:;
        case 133:;
        case 135:;
        case 136:;
        case 138:;
        case 139:;
        case 140:;
        case 142:;
        case 143:;
        case 144:;
        case 145:;
        case 146:;
        case 147:;
        case 148:;
        case 150:;
        case 152:;
        case 153:;
        case 154:;
        case 155:;
        case 157:;
        case 158:;
        case 159:;
        case 161:;
        case 162:;
        case 163:;
        case 164:;
        case 165:;
        case 167:;
        case 168:;
        case 169:;
        case 170:;
        case 172:;
        case 173:;
        case 175:;
        case 176:;
        case 177:;
        case 178:;
        case 180:;
        case 181:;
        case 182:;
        case 183:;
        case 185:;
        case 186:;
        case 187:;
        case 188:;
        case 189:;
        case 191:;
        case 192:;
        case 193:;
        case 194:;
        case 195:;
        case 196:;
        case 197:;
        case 199:;
        case 201:;
        case 202:;
        case 203:;
        case 204:;
        case 205:;
        case 207:;
        case 208:;
        case 210:;
        case 212:;
        case 213:;
        case 214:;
        case 215:;
        case 216:;
        case 218:;
        case 219:;
        case 220:;
        case 221:;
        case 223:;
        case 224:;
        case 225:;
        case 226:;
        case 228:;
        case 229:;
        case 230:;
        case 231:;
        case 243:;
        case 244:;
        case 245:;
        case 246:;
        case 247:;
        case 249:;
        case 250:;
        case 251:;
        case 252:;
        case 254:;
        case 255:;
        case 256:;
        case 257:;
        case 258:;
        case 260:;
        case 261:;
        case 262:;
        case 263:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_2.Ident = Idents_MakeIdent(&Word);
          return TokIdentifier;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 33:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart - Scanner_TokenLength;
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, (Strings_tStringIndex)Strings_Length(&Word), &String);
          Scanner_Attribute.U_1.V_2.Ident = Idents_MakeIdent(&String);
          return TokIdentifier;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 95:;
          while (yyChBufferPtr->A[yyChBufferIndex] == ' ') {
            INC(yyChBufferIndex);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 94:;
          DEC1(yyLineStart, 7 - (yyChBufferIndex - yyLineStart - 2) % 8);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 93:;
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
        case 69:;
        case 90:;
        case 273:;
        case 287:;
          DEC(yyChBufferIndex);
          DEC(Scanner_TokenLength);
          break;
        case 92:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = yyChBufferIndex - yyLineStart;
          INC(yyChBufferIndex);
          Scanner_TokenLength = 1;
          Scanner_GetWord(&Word);
          Errors_MessageI((STRING)"illegal character", 17L, (LONGCARD)Errors_Error, Scanner_Attribute.Position, (LONGCARD)Errors_String, ADR(Word));
          INC(Tree_ErrorCount);
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
        case 91:;
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
                case targetcode:;
                case expr:;
                  Errors_Message((STRING)"unclosed target code", 20L, (LONGCARD)Errors_Error, Scanner_Attribute.Position);
                  INC(Tree_ErrorCount);
                  break;
                case comment:;
                  Errors_Message((STRING)"unclosed comment", 16L, (LONGCARD)Errors_Error, Scanner_Attribute.Position);
                  INC(Tree_ErrorCount);
                  break;
                case CStr1:;
                case CStr2:;
                case Str1:;
                case Str2:;
                  Errors_Message((STRING)"unclosed string", 15L, (LONGCARD)Errors_Error, Scanner_Attribute.Position);
                  INC(Tree_ErrorCount);
                  break;
                default :
                  break;
                }
                yyStart(STD);
                INC(Scanner_CurArg);
                if (Scanner_CurArg <= Scanner_ArgCount) {
                  GetArgument(Scanner_CurArg, Argument.A, 256L);
                  j = 0;
                  do {
                    ch = Argument.A[j];
                    Tree_SourceFile.A[j] = ch;
                    INC(j);
                  } while (!(ch == '\0'));
                  Scanner_BeginFile(Tree_SourceFile.A, 256L);
                  Strings_ArrayToString(Tree_SourceFile.A, 256L, &String);
                  Scanner_Attribute.Position.File = Idents_MakeIdent(&String);
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
(CHAR FileName[], LONGCARD O_1)
# else
(FileName, O_1)
CHAR FileName[];
LONGCARD O_1;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(FileName, O_1, CHAR)
  if (yyStateStack->A[0] == yyDNoState) {
    yyGetTables();
    yyStateStack->A[0] = yyDefaultState;
  }
  yyInitialize();
  yySourceFile = Source_BeginSource(FileName, O_1);
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
    register struct S_10 *W_2 = &yyFileStack.A[yyFileStackPtr - 1];

    W_2->SourceFile = yySourceFile;
    W_2->Eof = yyEof;
    W_2->ChBufferPtr = yyChBufferPtr;
    W_2->ChBufferStart = yyChBufferStart;
    W_2->ChBufferSize = yyChBufferSize;
    W_2->ChBufferIndex = yyChBufferIndex;
    W_2->BytesRead = yyBytesRead;
    W_2->LineCount = yyLineCount;
    W_2->LineStart = yyLineStart;
  }
  yyChBufferSize = yyInitBufferSize;
  DynArray_MakeArray((ADDRESS *)&yyChBufferPtr, &yyChBufferSize, (LONGINT)sizeof(CHAR));
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
    register struct S_10 *W_3 = &yyFileStack.A[yyFileStackPtr - 1];

    yySourceFile = W_3->SourceFile;
    yyEof = W_3->Eof;
    yyChBufferPtr = W_3->ChBufferPtr;
    yyChBufferStart = W_3->ChBufferStart;
    yyChBufferSize = W_3->ChBufferSize;
    yyChBufferIndex = W_3->ChBufferIndex;
    yyBytesRead = W_3->BytesRead;
    yyLineCount = W_3->LineCount;
    yyLineStart = W_3->LineStart;
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
  struct S_13 Base;

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
    BEGIN_System();
    BEGIN_StringMem();
    BEGIN_Strings();
    BEGIN_Idents();
    BEGIN_Texts();
    BEGIN_Tree();
    BEGIN_Sets();
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
