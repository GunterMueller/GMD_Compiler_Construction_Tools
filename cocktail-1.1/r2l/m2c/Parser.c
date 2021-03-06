#include "SYSTEM_.h"

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_StdIO
#include "StdIO.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_DefTable
#include "DefTable.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

struct Parser_1 Parser_ParsTabName;

#define IdentUndefined	10
#define ImproperUse	11
#define IdentDefBefore	12
#define Error	3
#define C_1_String	7
typedef struct S_1 {
    Scanner_tScanAttribute Scan;
} tParsAttribute;
static Strings_tString string;
static Idents_tIdent ANY;
static DefTable_DefRange Definition;
static BOOLEAN complement;
static Texts_tText Export, Global, Local, Begin, C_2_Close, Default, Eof;
static void WriteChar ARGS((CHAR Ch, BOOLEAN InClass));
#define yyInitStackSize	100
#define yyNoState	0
#define yyFirstTerminal	0
#define yyLastTerminal	38
#define yyFirstSymbol	0
#define yyLastSymbol	79
#define yyTableMax	251
#define yyNTableMax	114
#define yyFirstReadState	1
#define yyLastReadState	69
#define yyFirstReadTermState	70
#define yyLastReadTermState	96
#define yyLastReadNontermState	111
#define yyFirstReduceState	112
#define yyLastReduceState	188
#define yyStartState	1
#define yyStopState	112
#define yyFirstFinalState	yyFirstReadTermState
#define yyLastState	yyLastReduceState
typedef SHORTCARD yyTableElmt;
typedef yyTableElmt yyTCombRange;
typedef yyTableElmt yyNCombRange;
typedef yyTableElmt yyStateRange;
typedef yyTableElmt yyReadRange;
typedef yyTableElmt yyReadReduceRange;
typedef yyTableElmt yyReduceRange;
typedef yyTableElmt yySymbolRange;
typedef struct S_2 {
    yyStateRange Check, Next;
} yyTCombType;
typedef yyStateRange yyNCombType;
typedef yyTCombType *yyTCombTypePtr;
typedef yyNCombType *yyNCombTypePtr;
typedef struct S_3 {
    yyStateRange A[1000000 + 1];
} *yyStackType;
static struct S_4 {
    yyTCombTypePtr A[yyLastReadState + 1];
} yyTBasePtr;
static struct S_5 {
    yyNCombTypePtr A[yyLastReadState + 1];
} yyNBasePtr;
static struct S_6 {
    yyReadRange A[yyLastReadState + 1];
} yyDefault;
static struct S_7 {
    yyTCombType A[yyTableMax + 1];
} yyTComb;
static struct S_8 {
    yyNCombType A[yyNTableMax - (yyLastTerminal + 1) + 1];
} yyNComb;
static struct S_9 {
    yyTableElmt A[yyLastReduceState - yyFirstReduceState + 1];
} yyLength;
static struct S_10 {
    yySymbolRange A[yyLastReduceState - yyFirstReduceState + 1];
} yyLeftHandSide;
static struct S_11 {
    yySymbolRange A[yyLastReadState + 1];
} yyContinuation;
static struct S_12 {
    yyReduceRange A[yyLastReadNontermState - yyFirstReadTermState + 1];
} yyFinalToProd;
static BOOLEAN yyIsInitialized;
static System_tFile yyTableFile;
static void Copy ARGS((CHAR Source[], LONGCARD , CHAR Target[], LONGCARD ));
struct S_16 {
    tParsAttribute A[1000000 + 1];
};
struct S_17 {
    CHAR A[127 + 1];
};
static void ErrorRecovery ARGS((yySymbolRange *Terminal, yyStackType StateStack, LONGINT StackSize, LONGINT StackPtr));
struct S_18 {
    CHAR A[127 + 1];
};
static void ComputeContinuation ARGS((yyStackType Stack, LONGINT StackSize, LONGINT StackPtr, Sets_tSet *ContinueSet));
static BOOLEAN IsContinuation ARGS((yySymbolRange Terminal, yyStackType ParseStack, LONGINT StackSize, LONGINT StackPtr));
static void ComputeRestartPoints ARGS((yyStackType ParseStack, LONGINT StackSize, LONGINT StackPtr, Sets_tSet *RestartSet));
static yyStateRange Next ARGS((yyStateRange State, yySymbolRange Symbol));
static void yyGetTables ARGS(());
struct S_19 {
    yyTCombRange A[yyLastReadState + 1];
};
struct S_20 {
    yyNCombRange A[yyLastReadState + 1];
};
static CARDINAL yyGetTable ARGS((ADDRESS Address));
static void yyErrorCheck ARGS((INTEGER ErrorCode, INTEGER Info));
static void BeginParser ARGS(());


static void WriteChar
# ifdef __STDC__
(CHAR Ch, BOOLEAN InClass)
# else
(Ch, InClass)
CHAR Ch;
BOOLEAN InClass;
# endif
{
  if ('A' <= Ch && Ch <= 'Z' || 'a' <= Ch && Ch <= 'z' || '0' <= Ch && Ch <= '9') {
    StdIO_WriteC(Ch);
  } else {
    switch (Ch) {
    case '\n':;
      StdIO_WriteS((STRING)"\\n", 2L);
      break;
    case '\t':;
      StdIO_WriteS((STRING)"\\t", 2L);
      break;
    case ((CHAR)'\13'):;
      StdIO_WriteS((STRING)"\\v", 2L);
      break;
    case '\b':;
      StdIO_WriteS((STRING)"\\b", 2L);
      break;
    case '\r':;
      StdIO_WriteS((STRING)"\\r", 2L);
      break;
    case '\f':;
      StdIO_WriteS((STRING)"\\f", 2L);
      break;
    case '"':;
      StdIO_WriteS((STRING)"\\\"", 2L);
      break;
    case ']':;
      StdIO_WriteS((STRING)"\\]", 2L);
      break;
    case '.':;
      StdIO_WriteS((STRING)"\\.", 2L);
      break;
    case '^':;
      StdIO_WriteS((STRING)"\\^", 2L);
      break;
    case '-':;
      StdIO_WriteS((STRING)"\\-", 2L);
      break;
    case '\\':;
      StdIO_WriteS((STRING)"\\\\", 2L);
      break;
    default :
      if (InClass) {
        StdIO_WriteC(Ch);
      } else {
        StdIO_WriteC('"');
        StdIO_WriteC(Ch);
        StdIO_WriteC('"');
      }
      break;
    }
  }
}

static void Copy
# ifdef __STDC__
(CHAR Source[], LONGCARD O_2, CHAR Target[], LONGCARD O_1)
# else
(Source, O_2, Target, O_1)
CHAR Source[];
LONGCARD O_2;
CHAR Target[];
LONGCARD O_1;
# endif
{
  CARDINAL i, j;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_2 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Source, O_2, CHAR)
  if ((O_2 - 1) < (O_1 - 1)) {
    j = (O_2 - 1);
  } else {
    j = (O_1 - 1);
  }
  {
    LONGCARD B_1 = 0, B_2 = j;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        Target[i] = Source[i];
        if (i >= B_2) break;
      }
  }
  if ((O_1 - 1) > j) {
    Target[j + 1] = CHR(0);
  }
  FREE_OPEN_ARRAYS
}

void Parser_TokenName
# ifdef __STDC__
(CARDINAL Token, CHAR Name[], LONGCARD O_3)
# else
(Token, Name, O_3)
CARDINAL Token;
CHAR Name[];
LONGCARD O_3;
# endif
{
  switch (Token) {
  case 0:;
    Copy((STRING)"_EndOfFile", 10L, Name, O_3);
    break;
  case 1:;
    Copy((STRING)"Ident", 5L, Name, O_3);
    break;
  case 2:;
    Copy((STRING)"Number", 6L, Name, O_3);
    break;
  case 3:;
    Copy((STRING)"String", 6L, Name, O_3);
    break;
  case 4:;
    Copy((STRING)"Char", 4L, Name, O_3);
    break;
  case 5:;
    Copy((STRING)"TargetCode", 10L, Name, O_3);
    break;
  case 6:;
    Copy((STRING)"GLOBAL", 6L, Name, O_3);
    break;
  case 7:;
    Copy((STRING)"BEGIN", 5L, Name, O_3);
    break;
  case 8:;
    Copy((STRING)"CLOSE", 5L, Name, O_3);
    break;
  case 9:;
    Copy((STRING)"DEFINE", 6L, Name, O_3);
    break;
  case 10:;
    Copy((STRING)"START", 5L, Name, O_3);
    break;
  case 11:;
    Copy((STRING)"RULES", 5L, Name, O_3);
    break;
  case 12:;
    Copy((STRING)".", 1L, Name, O_3);
    break;
  case 13:;
    Copy((STRING)",", 1L, Name, O_3);
    break;
  case 14:;
    Copy((STRING)"=", 1L, Name, O_3);
    break;
  case 15:;
    Copy((STRING)":", 1L, Name, O_3);
    break;
  case 16:;
    Copy((STRING)"/", 1L, Name, O_3);
    break;
  case 17:;
    Copy((STRING)"|", 1L, Name, O_3);
    break;
  case 18:;
    Copy((STRING)"+", 1L, Name, O_3);
    break;
  case 19:;
    Copy((STRING)"-", 1L, Name, O_3);
    break;
  case 20:;
    Copy((STRING)"*", 1L, Name, O_3);
    break;
  case 21:;
    Copy((STRING)"?", 1L, Name, O_3);
    break;
  case 22:;
    Copy((STRING)"(", 1L, Name, O_3);
    break;
  case 23:;
    Copy((STRING)")", 1L, Name, O_3);
    break;
  case 24:;
    Copy((STRING)"[", 1L, Name, O_3);
    break;
  case 25:;
    Copy((STRING)"]", 1L, Name, O_3);
    break;
  case 26:;
    Copy((STRING)"{", 1L, Name, O_3);
    break;
  case 27:;
    Copy((STRING)"}", 1L, Name, O_3);
    break;
  case 28:;
    Copy((STRING)"<", 1L, Name, O_3);
    break;
  case 29:;
    Copy((STRING)">", 1L, Name, O_3);
    break;
  case 30:;
    Copy((STRING)"NOT", 3L, Name, O_3);
    break;
  case 31:;
    Copy((STRING)"LOCAL", 5L, Name, O_3);
    break;
  case 32:;
    Copy((STRING)"EXPORT", 6L, Name, O_3);
    break;
  case 33:;
    Copy((STRING)"#", 1L, Name, O_3);
    break;
  case 34:;
    Copy((STRING)"EOF", 3L, Name, O_3);
    break;
  case 35:;
    Copy((STRING)":-", 2L, Name, O_3);
    break;
  case 36:;
    Copy((STRING)"DEFAULT", 7L, Name, O_3);
    break;
  case 37:;
    Copy((STRING)"COMPL", 5L, Name, O_3);
    break;
  case 38:;
    Copy((STRING)"SEQUENCE", 8L, Name, O_3);
    break;
  }
}

CARDINAL Parser_Parser
# ifdef __STDC__
()
# else
()
# endif
{
  yyStateRange yyState;
  yySymbolRange yyTerminal;
  yySymbolRange yyNonterminal;
  yyTableElmt yyStackPtr;
  LONGINT yyStateStackSize;
  LONGINT yyAttrStackSize;
  yyTableElmt yyShortStackSize;
  yyStackType yyStateStack;
  struct S_16 *yyAttributeStack;
  tParsAttribute yySynAttribute;
  Scanner_tScanAttribute yyRepairAttribute;
  yySymbolRange yyRepairToken;
  yyTCombTypePtr yyTCombPtr;
  yyNCombTypePtr yyNCombPtr;
  BOOLEAN yyIsRepairing;
  CARDINAL yyErrorCount;
  struct S_17 yyTokenString;

  BeginParser();
  yyState = yyStartState;
  yyTerminal = Scanner_GetToken();
  yyStateStackSize = yyInitStackSize;
  yyAttrStackSize = yyInitStackSize;
  DynArray_MakeArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyStateRange));
  DynArray_MakeArray((ADDRESS *)&yyAttributeStack, &yyAttrStackSize, (LONGINT)sizeof(tParsAttribute));
  yyShortStackSize = yyStateStackSize - 1;
  yyStackPtr = 0;
  yyErrorCount = 0;
  yyIsRepairing = FALSE;
  for (;;) {
    if (yyStackPtr >= yyShortStackSize) {
      DynArray_ExtendArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyStateRange));
      DynArray_ExtendArray((ADDRESS *)&yyAttributeStack, &yyAttrStackSize, (LONGINT)sizeof(tParsAttribute));
      yyShortStackSize = yyStateStackSize - 1;
    }
    yyStateStack->A[yyStackPtr] = yyState;
    for (;;) {
      yyTCombPtr = (yyTCombTypePtr)((LONGCARD)yyTBasePtr.A[yyState] + yyTerminal * sizeof(yyTCombType));
      if (yyTCombPtr->Check == yyState) {
        yyState = yyTCombPtr->Next;
        goto EXIT_2;
      }
      yyState = yyDefault.A[yyState];
      if (yyState == yyNoState) {
        yyState = yyStateStack->A[yyStackPtr];
        if (yyIsRepairing) {
          yyRepairToken = yyContinuation.A[yyState];
          yyState = Next(yyState, yyRepairToken);
          if (yyState <= yyLastReadTermState) {
            Scanner_ErrorAttribute((LONGCARD)yyRepairToken, &yyRepairAttribute);
            Parser_TokenName((LONGCARD)yyRepairToken, yyTokenString.A, 128L);
            Errors_ErrorMessageI((LONGCARD)Errors_TokenInserted, (LONGCARD)Errors_Repair, Scanner_Attribute.Position, (LONGCARD)Errors_Array, ADR(yyTokenString));
            if (yyState >= yyFirstFinalState) {
              yyState = yyFinalToProd.A[yyState - 70];
            }
            INC(yyStackPtr);
            yyAttributeStack->A[yyStackPtr].Scan = yyRepairAttribute;
            yyStateStack->A[yyStackPtr] = yyState;
          }
          if (yyState >= yyFirstFinalState) {
            goto EXIT_2;
          }
        } else {
          INC(yyErrorCount);
          ErrorRecovery(&yyTerminal, yyStateStack, yyStateStackSize, (LONGINT)yyStackPtr);
          yyIsRepairing = TRUE;
        }
      }
    } EXIT_2:;
    if (yyState >= yyFirstFinalState) {
      if (yyState <= yyLastReadTermState) {
        INC(yyStackPtr);
        yyAttributeStack->A[yyStackPtr].Scan = Scanner_Attribute;
        yyTerminal = Scanner_GetToken();
        yyIsRepairing = FALSE;
      }
      for (;;) {
        switch (yyState) {
        case 112:;
          DynArray_ReleaseArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyTableElmt));
          DynArray_ReleaseArray((ADDRESS *)&yyAttributeStack, &yyAttrStackSize, (LONGINT)sizeof(tParsAttribute));
          return yyErrorCount;
          break;
        case 113:;
        case 111:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 44;
          StdIO_WriteNl();
          StdIO_WriteS((STRING)"%%", 2L);
          StdIO_WriteNl();
          StdIO_WriteNl();
          StdIO_WriteS((STRING)"void BeginScanner ()", 20L);
          StdIO_WriteNl();
          StdIO_WriteS((STRING)"{", 1L);
          StdIO_WriteNl();
          Texts_WriteText((System_tFile)IO_StdOutput, Begin);
          StdIO_WriteS((STRING)"}", 1L);
          StdIO_WriteNl();
          StdIO_WriteNl();
          StdIO_WriteS((STRING)"void CloseScanner ()", 20L);
          StdIO_WriteNl();
          StdIO_WriteS((STRING)"{", 1L);
          StdIO_WriteNl();
          Texts_WriteText((System_tFile)IO_StdOutput, C_2_Close);
          StdIO_WriteS((STRING)"}", 1L);
          StdIO_WriteNl();
          break;
        case 114:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 40;
          StdIO_WriteS((STRING)"%{", 2L);
          StdIO_WriteNl();
          Texts_WriteText((System_tFile)IO_StdOutput, Export);
          Texts_WriteText((System_tFile)IO_StdOutput, Global);
          StdIO_WriteS((STRING)"%}", 2L);
          StdIO_WriteNl();
          StdIO_WriteNl();
          break;
        case 115:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 39;
          break;
        case 116:;
        case 74:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 39;
          Export = yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_5.Text;
          break;
        case 117:;
        case 70:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 39;
          Global = yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_5.Text;
          break;
        case 118:;
        case 73:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 39;
          Local = yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_5.Text;
          break;
        case 119:;
        case 71:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 39;
          Begin = yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_5.Text;
          break;
        case 120:;
        case 72:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 39;
          C_2_Close = yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_5.Text;
          break;
        case 121:;
        case 76:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 39;
          Default = yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_5.Text;
          break;
        case 122:;
        case 75:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 39;
          Eof = yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_5.Text;
          StdIO_WriteS((STRING)"/*** sorry - cannot translate EOF ***/", 38L);
          StdIO_WriteNl();
          break;
        case 123:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 41;
          break;
        case 124:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 41;
          break;
        case 125:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 42;
          break;
        case 126:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 42;
          StdIO_WriteNl();
          StdIO_WriteNl();
          break;
        case 127:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 46;
          StdIO_WriteNl();
          StdIO_WriteS((STRING)"%Start", 6L);
          break;
        case 128:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 43;
          StdIO_WriteS((STRING)"\" \"	;", 5L);
          StdIO_WriteNl();
          StdIO_WriteS((STRING)"\\t	;", 4L);
          StdIO_WriteNl();
          StdIO_WriteS((STRING)"\\n	;", 4L);
          StdIO_WriteNl();
          StdIO_WriteS((STRING)".	{", 3L);
          Texts_WriteText((System_tFile)IO_StdOutput, Default);
          StdIO_WriteS((STRING)"}", 1L);
          StdIO_WriteNl();
          break;
        case 129:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 48;
          StdIO_WriteS((STRING)"%%", 2L);
          StdIO_WriteNl();
          StdIO_WriteNl();
          StdIO_WriteS((STRING)"%{", 2L);
          StdIO_WriteNl();
          Texts_WriteText((System_tFile)IO_StdOutput, Local);
          StdIO_WriteS((STRING)"%}", 2L);
          StdIO_WriteNl();
          StdIO_WriteNl();
          break;
        case 130:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 45;
          break;
        case 131:;
        case 100:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 45;
          break;
        case 132:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 49;
          break;
        case 133:;
        case 107:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 49;
          break;
        case 134:;
        case 103:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 47;
          break;
        case 135:;
        case 102:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 47;
          break;
        case 136:;
        case 101:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 47;
          break;
        case 137:;
        case 89:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 52;
          StdIO_WriteC(' ');
          Idents_WriteIdent((System_tFile)IO_StdOutput, yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_1.Ident);
          break;
        case 138:;
        case 104:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 54;
          break;
        case 139:;
        case 106:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 54;
          break;
        case 140:;
        case 105:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 54;
          break;
        case 141:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 56;
          StdIO_WriteC(',');
          break;
        case 142:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 55;
          StdIO_WriteC(',');
          break;
        case 143:;
        case 90:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 53;
          Idents_WriteIdent((System_tFile)IO_StdOutput, yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_1.Ident);
          break;
        case 144:;
        case 88:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 50;
          StdIO_WriteNl();
          break;
        case 145:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 57;
          if (DefTable_GetDef(yyAttributeStack->A[yyStackPtr - 1].Scan.U_1.V_1.Ident) == DefTable_NoDef) {
            DefTable_MakeIdentDef(yyAttributeStack->A[yyStackPtr - 1].Scan.U_1.V_1.Ident);
          } else {
            Idents_GetString(yyAttributeStack->A[yyStackPtr - 1].Scan.U_1.V_1.Ident, &string);
            Errors_ErrorMessageI((LONGCARD)IdentDefBefore, (LONGCARD)Error, yyAttributeStack->A[yyStackPtr - 1].Scan.Position, (LONGCARD)C_1_String, ADR(string));
          }
          Idents_WriteIdent((System_tFile)IO_StdOutput, yyAttributeStack->A[yyStackPtr - 1].Scan.U_1.V_1.Ident);
          StdIO_WriteC('\t');
          break;
        case 146:;
        case 95:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 51;
          Texts_WriteText((System_tFile)IO_StdOutput, yyAttributeStack->A[yyStackPtr + 4].Scan.U_1.V_5.Text);
          StdIO_WriteC('}');
          StdIO_WriteNl();
          break;
        case 147:;
        case 96:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 51;
          Texts_WriteText((System_tFile)IO_StdOutput, yyAttributeStack->A[yyStackPtr + 4].Scan.U_1.V_5.Text);
          StdIO_WriteC('}');
          StdIO_WriteNl();
          break;
        case 148:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 61;
          StdIO_WriteS((STRING)"	{", 2L);
          break;
        case 149:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 60;
          StdIO_WriteS((STRING)"	{", 2L);
          break;
        case 150:;
        case 110:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 59;
          break;
        case 151:;
        case 108:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 59;
          break;
        case 152:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 63;
          StdIO_WriteS((STRING)"	|", 2L);
          break;
        case 153:;
        case 109:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 62;
          break;
        case 154:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 64;
          break;
        case 155:;
        case 92:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 64;
          StdIO_WriteC('>');
          break;
        case 156:;
        case 91:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 64;
          StdIO_WriteS((STRING)"/*** sorry - cannot translate NOT ***/", 38L);
          StdIO_WriteNl();
          break;
        case 157:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 68;
          StdIO_WriteC('<');
          break;
        case 158:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 65;
          break;
        case 159:;
        case 93:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 65;
          StdIO_WriteC('^');
          break;
        case 160:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 66;
          break;
        case 161:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 66;
          break;
        case 162:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 69;
          StdIO_WriteC('/');
          break;
        case 163:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 67;
          break;
        case 164:;
        case 94:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 67;
          StdIO_WriteC('$');
          break;
        case 165:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 58;
          break;
        case 166:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 58;
          break;
        case 167:;
        case 80:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 58;
          StdIO_WriteC('+');
          break;
        case 168:;
        case 81:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 58;
          StdIO_WriteC('*');
          break;
        case 169:;
        case 82:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 58;
          StdIO_WriteC('?');
          break;
        case 170:;
        case 84:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 58;
          StdIO_WriteC('{');
          StdIO_WriteI((LONGINT)yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_2.Number, 0L);
          StdIO_WriteC(',');
          StdIO_WriteI((LONGINT)yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_2.Number, 0L);
          StdIO_WriteC('}');
          break;
        case 171:;
        case 83:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 58;
          StdIO_WriteC('{');
          StdIO_WriteI((LONGINT)yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_2.Number, 0L);
          StdIO_WriteC(',');
          StdIO_WriteI((LONGINT)yyAttributeStack->A[yyStackPtr + 5].Scan.U_1.V_2.Number, 0L);
          StdIO_WriteC('}');
          break;
        case 172:;
        case 87:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 58;
          StdIO_WriteC(')');
          break;
        case 173:;
        case 99:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 58;
          break;
        case 174:;
        case 79:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 58;
          WriteChar(yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_4.Ch, FALSE);
          break;
        case 175:;
        case 77:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 58;
          Definition = DefTable_GetDef(yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_1.Ident);
          if (Definition != DefTable_NoDef) {
            if (DefTable_GetKind(Definition) == DefTable_Ident) {
              StdIO_WriteC('{');
              Idents_WriteIdent((System_tFile)IO_StdOutput, yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_1.Ident);
              StdIO_WriteC('}');
            } else {
              Idents_GetString(yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_1.Ident, &string);
              Errors_ErrorMessageI((LONGCARD)ImproperUse, (LONGCARD)Error, yyAttributeStack->A[yyStackPtr + 1].Scan.Position, (LONGCARD)C_1_String, ADR(string));
            }
          } else {
            if (yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_1.Ident == ANY) {
              StdIO_WriteC('.');
            } else {
              Idents_WriteIdent((System_tFile)IO_StdOutput, yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_1.Ident);
            }
          }
          break;
        case 176:;
        case 78:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 58;
          StdIO_WriteC('"');
          StringMem_WriteString((System_tFile)IO_StdOutput, yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_3.String);
          StdIO_WriteC('"');
          break;
        case 177:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 71;
          StdIO_WriteC('(');
          break;
        case 178:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 70;
          StdIO_WriteC('|');
          break;
        case 179:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 72;
          complement = FALSE;
          break;
        case 180:;
        case 98:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 73;
          break;
        case 181:;
        case 86:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 73;
          StdIO_WriteC(']');
          break;
        case 182:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 75;
          StdIO_WriteC('[');
          if (complement) {
            StdIO_WriteC('^');
          }
          break;
        case 183:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 74;
          complement = !complement;
          break;
        case 184:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 76;
          break;
        case 185:;
        case 97:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 76;
          break;
        case 186:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 77;
          WriteChar(yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_4.Ch, TRUE);
          break;
        case 187:;
        case 85:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 77;
          WriteChar(yyAttributeStack->A[yyStackPtr + 4].Scan.U_1.V_4.Ch, TRUE);
          break;
        case 188:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 78;
          WriteChar(yyAttributeStack->A[yyStackPtr - 1].Scan.U_1.V_4.Ch, TRUE);
          StdIO_WriteC('-');
          break;
        }
        yyNCombPtr = (yyNCombTypePtr)((LONGCARD)yyNBasePtr.A[yyStateStack->A[yyStackPtr]] + yyNonterminal * sizeof(yyNCombType));
        yyState = *yyNCombPtr;
        INC(yyStackPtr);
        yyAttributeStack->A[yyStackPtr] = yySynAttribute;
        if (yyState < yyFirstFinalState) {
          goto EXIT_3;
        }
      } EXIT_3:;
    } else {
      INC(yyStackPtr);
      yyAttributeStack->A[yyStackPtr].Scan = Scanner_Attribute;
      yyTerminal = Scanner_GetToken();
      yyIsRepairing = FALSE;
    }
  } EXIT_1:;
}

static void ErrorRecovery
# ifdef __STDC__
(yySymbolRange *Terminal, yyStackType StateStack, LONGINT StackSize, LONGINT StackPtr)
# else
(Terminal, StateStack, StackSize, StackPtr)
yySymbolRange *Terminal;
yyStackType StateStack;
LONGINT StackSize;
LONGINT StackPtr;
# endif
{
  BOOLEAN TokensSkipped;
  Sets_tSet ContinueSet;
  Sets_tSet RestartSet;
  yySymbolRange Token;
  struct S_18 TokenArray;
  Strings_tString TokenString;
  Strings_tString ContinueString;

  Errors_ErrorMessage((LONGCARD)Errors_SyntaxError, (LONGCARD)Errors_Error, Scanner_Attribute.Position);
  Sets_MakeSet(&ContinueSet, (LONGCARD)yyLastTerminal);
  ComputeContinuation(StateStack, StackSize, StackPtr, &ContinueSet);
  Strings_AssignEmpty(&ContinueString);
  {
    yySymbolRange B_3 = Sets_Minimum(&ContinueSet), B_4 = Sets_Maximum(&ContinueSet);

    if (B_3 <= B_4)
      for (Token = B_3;; Token += 1) {
        if (Sets_IsElement((LONGCARD)Token, &ContinueSet)) {
          Parser_TokenName((LONGCARD)Token, TokenArray.A, 128L);
          Strings_ArrayToString(TokenArray.A, 128L, &TokenString);
          if (Strings_Length(&ContinueString) + Strings_Length(&TokenString) + 1 <= Strings_cMaxStrLength) {
            Strings_Concatenate(&ContinueString, &TokenString);
            Strings_Append(&ContinueString, ' ');
          }
        }
        if (Token >= B_4) break;
      }
  }
  Errors_ErrorMessageI((LONGCARD)Errors_ExpectedTokens, (LONGCARD)Errors_Information, Scanner_Attribute.Position, (LONGCARD)Errors_String, ADR(ContinueString));
  Sets_ReleaseSet(&ContinueSet);
  Sets_MakeSet(&RestartSet, (LONGCARD)yyLastTerminal);
  ComputeRestartPoints(StateStack, StackSize, StackPtr, &RestartSet);
  TokensSkipped = FALSE;
  while (!Sets_IsElement((LONGCARD)(*Terminal), &RestartSet)) {
    *Terminal = Scanner_GetToken();
    TokensSkipped = TRUE;
  }
  Sets_ReleaseSet(&RestartSet);
  if (TokensSkipped) {
    Errors_ErrorMessage((LONGCARD)Errors_RestartPoint, (LONGCARD)Errors_Information, Scanner_Attribute.Position);
  }
}

static void ComputeContinuation
# ifdef __STDC__
(yyStackType Stack, LONGINT StackSize, LONGINT StackPtr, Sets_tSet *ContinueSet)
# else
(Stack, StackSize, StackPtr, ContinueSet)
yyStackType Stack;
LONGINT StackSize;
LONGINT StackPtr;
Sets_tSet *ContinueSet;
# endif
{
  yySymbolRange Terminal;

  Sets_AssignEmpty(ContinueSet);
  for (Terminal = yyFirstTerminal; Terminal <= yyLastTerminal; Terminal += 1) {
    if (IsContinuation(Terminal, Stack, StackSize, StackPtr)) {
      Sets_Include(ContinueSet, (LONGCARD)Terminal);
    }
  }
}

static BOOLEAN IsContinuation
# ifdef __STDC__
(yySymbolRange Terminal, yyStackType ParseStack, LONGINT StackSize, LONGINT StackPtr)
# else
(Terminal, ParseStack, StackSize, StackPtr)
yySymbolRange Terminal;
yyStackType ParseStack;
LONGINT StackSize;
LONGINT StackPtr;
# endif
{
  LONGINT State;
  yySymbolRange Nonterminal;
  yyStackType Stack;

  DynArray_MakeArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
  {
    LONGINT B_5 = 0, B_6 = StackPtr;

    if (B_5 <= B_6)
      for (State = B_5;; State += 1) {
        Stack->A[State] = ParseStack->A[State];
        if (State >= B_6) break;
      }
  }
  State = Stack->A[StackPtr];
  for (;;) {
    Stack->A[StackPtr] = State;
    State = Next((yyStateRange)State, Terminal);
    if (State == yyNoState) {
      DynArray_ReleaseArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
      return FALSE;
    }
    if (State <= yyLastReadTermState) {
      DynArray_ReleaseArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
      return TRUE;
    }
    for (;;) {
      if (State == yyStopState) {
        DynArray_ReleaseArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
        return TRUE;
      } else {
        DEC1(StackPtr, yyLength.A[State - 112]);
        Nonterminal = yyLeftHandSide.A[State - 112];
      }
      State = Next(Stack->A[StackPtr], Nonterminal);
      if (StackPtr >= StackSize) {
        DynArray_ExtendArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
      }
      INC(StackPtr);
      if (State < yyFirstFinalState) {
        goto EXIT_5;
      }
      State = yyFinalToProd.A[State - 70];
    } EXIT_5:;
  } EXIT_4:;
}

static void ComputeRestartPoints
# ifdef __STDC__
(yyStackType ParseStack, LONGINT StackSize, LONGINT StackPtr, Sets_tSet *RestartSet)
# else
(ParseStack, StackSize, StackPtr, RestartSet)
yyStackType ParseStack;
LONGINT StackSize;
LONGINT StackPtr;
Sets_tSet *RestartSet;
# endif
{
  yyStackType Stack;
  LONGINT State;
  yySymbolRange Nonterminal;
  Sets_tSet ContinueSet;

  DynArray_MakeArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
  {
    LONGINT B_7 = 0, B_8 = StackPtr;

    if (B_7 <= B_8)
      for (State = B_7;; State += 1) {
        Stack->A[State] = ParseStack->A[State];
        if (State >= B_8) break;
      }
  }
  Sets_MakeSet(&ContinueSet, (LONGCARD)yyLastTerminal);
  Sets_AssignEmpty(RestartSet);
  State = Stack->A[StackPtr];
  for (;;) {
    if (StackPtr >= StackSize) {
      DynArray_ExtendArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
    }
    Stack->A[StackPtr] = State;
    ComputeContinuation(Stack, StackSize, StackPtr, &ContinueSet);
    Sets_Union(RestartSet, ContinueSet);
    State = Next((yyStateRange)State, yyContinuation.A[State]);
    if (State >= yyFirstFinalState) {
      if (State <= yyLastReadTermState) {
        INC(StackPtr);
        State = yyFinalToProd.A[State - 70];
      }
      for (;;) {
        if (State == yyStopState) {
          DynArray_ReleaseArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
          Sets_ReleaseSet(&ContinueSet);
          return;
        } else {
          DEC1(StackPtr, yyLength.A[State - 112]);
          Nonterminal = yyLeftHandSide.A[State - 112];
        }
        State = Next(Stack->A[StackPtr], Nonterminal);
        INC(StackPtr);
        if (State < yyFirstFinalState) {
          goto EXIT_7;
        }
        State = yyFinalToProd.A[State - 70];
      } EXIT_7:;
    } else {
      INC(StackPtr);
    }
  } EXIT_6:;
}

static yyStateRange Next
# ifdef __STDC__
(yyStateRange State, yySymbolRange Symbol)
# else
(State, Symbol)
yyStateRange State;
yySymbolRange Symbol;
# endif
{
  yyTCombTypePtr TCombPtr;
  yyNCombTypePtr NCombPtr;

  if (Symbol <= yyLastTerminal) {
    for (;;) {
      TCombPtr = (yyTCombTypePtr)((LONGCARD)yyTBasePtr.A[State] + Symbol * sizeof(yyTCombType));
      if (TCombPtr->Check != State) {
        State = yyDefault.A[State];
        if (State == yyNoState) {
          return yyNoState;
        }
      } else {
        return TCombPtr->Next;
      }
    } EXIT_8:;
  } else {
    NCombPtr = (yyNCombTypePtr)((LONGCARD)yyNBasePtr.A[State] + Symbol * sizeof(yyNCombType));
    return *NCombPtr;
  }
}

static void yyGetTables
# ifdef __STDC__
()
# else
()
# endif
{
  CARDINAL BlockSize, j, n;
  yyStateRange State;
  struct S_19 TBase;
  struct S_20 NBase;

  BlockSize = 64000 / sizeof(yyTCombType);
  yyTableFile = OpenInput(Parser_ParsTabName.A, 129L);
  yyErrorCheck((LONGINT)Errors_OpenParseTable, yyTableFile);
  if (yyGetTable(ADR(TBase)) / sizeof(yyTCombRange) - 1 != yyLastReadState || yyGetTable(ADR(NBase)) / sizeof(yyNCombRange) - 1 != yyLastReadState || yyGetTable(ADR(yyDefault)) / sizeof(yyReadRange) - 1 != yyLastReadState || yyGetTable(ADR(yyNComb)) / sizeof(yyNCombType) != yyNTableMax - yyLastTerminal || yyGetTable(ADR(yyLength)) / sizeof(yyTableElmt) - 1 != yyLastReduceState - yyFirstReduceState || yyGetTable(ADR(yyLeftHandSide)) / sizeof(yySymbolRange) - 1 != yyLastReduceState - yyFirstReduceState || yyGetTable(ADR(yyContinuation)) / sizeof(yySymbolRange) - 1 != yyLastReadState || yyGetTable(ADR(yyFinalToProd)) / sizeof(yyReduceRange) - 1 != yyLastReadNontermState - yyFirstReadTermState) {
    Errors_ErrorMessage((LONGCARD)Errors_WrongParseTable, (LONGCARD)Errors_Fatal, Positions_NoPosition);
  }
  n = 0;
  j = 0;
  while (j <= yyTableMax) {
    INC1(n, yyGetTable(ADR(yyTComb.A[j])) / sizeof(yyTCombType));
    INC1(j, BlockSize);
  }
  if (n != yyTableMax + 1) {
    Errors_ErrorMessage((LONGCARD)Errors_WrongParseTable, (LONGCARD)Errors_Fatal, Positions_NoPosition);
  }
  Close(yyTableFile);
  for (State = 1; State <= yyLastReadState; State += 1) {
    yyTBasePtr.A[State] = (yyTCombTypePtr)ADR(yyTComb.A[TBase.A[State]]);
  }
  for (State = 1; State <= yyLastReadState; State += 1) {
    yyNBasePtr.A[State] = (yyNCombTypePtr)ADR(yyNComb.A[NBase.A[State] - 39]);
  }
}

static CARDINAL yyGetTable
# ifdef __STDC__
(ADDRESS Address)
# else
(Address)
ADDRESS Address;
# endif
{
  INTEGER N;
  yyTableElmt Length;

  N = Read(yyTableFile, ADR(Length), (LONGINT)sizeof(yyTableElmt));
  yyErrorCheck((LONGINT)Errors_ReadParseTable, N);
  N = Read(yyTableFile, Address, (LONGINT)Length);
  yyErrorCheck((LONGINT)Errors_ReadParseTable, N);
  return Length;
}

static void yyErrorCheck
# ifdef __STDC__
(INTEGER ErrorCode, INTEGER Info)
# else
(ErrorCode, Info)
INTEGER ErrorCode;
INTEGER Info;
# endif
{
  INTEGER ErrNo;

  if (Info < 0) {
    ErrNo = ErrNum();
    Errors_ErrorMessageI((LONGCARD)ErrorCode, (LONGCARD)Errors_Fatal, Positions_NoPosition, (LONGCARD)Errors_Integer, ADR(ErrNo));
  }
}

static void BeginParser
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_ArrayToString((STRING)"ANY", 3L, &string);
  ANY = Idents_MakeIdent(&string);
  if (!yyIsInitialized) {
    yyIsInitialized = TRUE;
    yyGetTables();
  }
}

void Parser_CloseParser
# ifdef __STDC__
()
# else
()
# endif
{
}

void BEGIN_Parser()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    BEGIN_Scanner();
    BEGIN_Positions();
    BEGIN_Errors();
    BEGIN_Strings();
    BEGIN_DynArray();
    BEGIN_Sets();
    BEGIN_System();
    BEGIN_Strings();
    BEGIN_StringMem();
    BEGIN_Idents();
    BEGIN_Texts();
    BEGIN_IO();
    BEGIN_StdIO();
    BEGIN_Errors();
    BEGIN_DefTable();

    yyIsInitialized = FALSE;
    (void)strncpy((char *)Parser_ParsTabName.A, "Parser.Tab", sizeof(Parser_ParsTabName.A));
  }
}
