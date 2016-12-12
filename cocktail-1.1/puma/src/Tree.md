DEFINITION MODULE Tree;

IMPORT SYSTEM, IO;
(* line 36 "" *)


FROM SYSTEM	IMPORT ADDRESS;
FROM IO		IMPORT tFile;
FROM Strings	IMPORT tString;
FROM StringMem	IMPORT tStringRef;
FROM Idents	IMPORT tIdent;
FROM Texts	IMPORT tText;
FROM Sets	IMPORT tSet;
FROM Relations	IMPORT tRelation;
FROM Positions	IMPORT tPosition;

VAR ErrorCount	: CARDINAL;

CONST

   (* properties of attributes and attribute instances		*)

   Virtual	= 0;
   Computed	= 1;
   Reverse	= 2;	(* list attribute to be used for reversion *)
   Write	= 3;	(* Usage:				*)
   Read		= 4;	(*	  				*)
   Inherited	= 5;	(* Kind:				*)
   Synthesized	= 6;
   Input	= 7;	(* Mode:				*)
   Output	= 8;
   Tree		= 9;	(* Store:				*)
   Parameter	= 10;
   Stack	= 11;
   Variable	= 12;	(*	global variable			*)
   Demand	= 13;
   Funct	= 14;
   Ignore	= 15;
(* Abstract	= 16;						*)
   Thread	= 17;	(* specified thread			*)
   Test		= 18;	(* generated for check			*)
   Left		= 19;	(* lhs/rhs of rule (for instances)	*)
   Right	= 20;	(*					*)
   CopyDef	= 21;	(* defined by copy rule			*)
   CopyUse	= 22;	(* used by copy rule			*)
   NonBaseComp	= 23;	(* non inherited computation		*)
   MultInhComp	= 24;	(* multiple inherited computation	*)
   First	= 25;	(* first attribute of group		*)
   Dummy	= 26;	(* dummy attribute for complete evaluation *)
   Def		= 27;	(* marks definition of attribute	*)
   Use		= 28;	(* marks last use of attribute		*)
   ChildUse	= 29;	(* marks last use of rhs attribute	*)
   ParentUse	= 30;	(* marks last use of lhs attribute	*)
   Generated	= 31;	(* action part has been generated	*)

   (* properties of classes					*)

   Top		= 0;	(* declaration level:			*)
   Intermediate	= 1;	(*					*)
   Low		= 2;	(*	(has no extensions)		*)
   Referenced	= 3;	(* explicitly used			*)
   Reachable	= 4;	(* reachable maybe via extensions	*)
   Nonterminal	= 5;
   Terminal	= 6;
   Explicit	= 7;	(* class explicitely declared		*)
   Implicit	= 8;	(* class implicitely declared		*)
   Trace	= 9;	(*					*)
   String	= 10;	(* named by string, otherwise ident	*)
   HasSelector	= 11;	(* selector explicitly specified	*)
   HasChildren	= 12;	(*					*)
   HasAttributes= 13;	(*					*)
   HasActions	= 14;	(*					*)
(* Ignore	= 15;						*)
   Abstract	= 16;
   Mark		= 17;
   HasOutput	= 18;	(* has output attributes or tests	*)

(* line 340 "" *)

CONST
NoTree = NIL;

Classes = 1;
NoClass = 2;
Class = 3;
Attributes = 4;
NoAttribute = 5;
AttrOrAction = 6;
Child = 7;
Attribute = 8;
ActionPart = 9;
Codes = 10;
Designators = 11;
NoDesignator = 12;
Designator = 13;
Ident = 14;
Remote = 15;
Any = 16;
Anys = 17;
Layouts = 18;
NoLayout = 19;
LayoutAny = 20;
Names = 21;
NoName = 22;
Name = 23;
Spec = 49;
TreeNames = 50;
NoTreeName = 51;
TreeName = 52;
Routines = 53;
NoRoutine = 54;
Routine = 55;
Procedure = 56;
Function = 57;
Predicate = 58;
Parameters = 59;
NoParameter = 60;
Param = 61;
Type = 62;
Rules = 63;
NoRule = 64;
Rule = 65;
Patterns = 66;
NoPattern = 67;
OnePattern = 68;
PatternsList = 69;
NoPatternsList = 70;
OnePatternsList = 71;
Pattern = 72;
Decompose = 73;
VarDef = 74;
NilTest = 75;
DontCare1 = 76;
DontCare = 77;
Value = 78;
Exprs = 79;
NoExpr = 80;
OneExpr = 81;
NamedExpr = 82;
Expr = 83;
Compose = 84;
VarUse = 85;
AttrDesc = 86;
Nil = 87;
Call = 88;
Binary = 89;
PreOperator = 90;
PostOperator = 91;
Index = 92;
Parents = 93;
TargetExpr = 94;
StringExpr = 95;
Statements = 96;
NoStatement = 97;
Statement = 98;
ProcCall = 99;
Condition = 100;
Assignment = 101;
Reject = 102;
Fail = 103;
TargetStmt = 104;
Nl = 105;
WriteStr = 106;
Formals = 107;
NoFormal = 108;
Formal = 109;
DummyFormal = 110;
TypeDesc = 111;
NodeTypes = 112;
UserType = 113;
Path = 114;
Var = 115;
ConsType = 116;
Field = 117;
Tests = 118;
NoTest = 119;
OneTest = 120;
TestKind = 121;
TestIsType = 122;
TestNil = 123;
TestNonlin = 124;
TestValue = 125;
Decisions = 126;
NoDecision = 127;
Decision = 128;
Decided = 129;

TYPE tTree = POINTER TO yyNode;
tProcTree = PROCEDURE (tTree);
(* line 110 "" *)


TYPE
   INTEGER0		= SHORTCARD;
   tAttrProperties	= BITSET;
   tClassProperties	= BITSET;
   tClass		= tTree;
   ProcOfT		= PROCEDURE (tTree);

VAR
   Options	: tSet;
   f		: tFile;
   SourceFile	: ARRAY [0..255] OF CHAR;
   NoCodeAttr	,
   NoCodeClass	: BITSET;

PROCEDURE InitIdentifyClass	(t: tTree);
PROCEDURE InitIdentifyClass2	(t: tTree);
PROCEDURE IdentifyClass		(t: tTree; Ident: tIdent): tTree;
PROCEDURE IdentifyAttribute	(t: tTree; Ident: tIdent): tTree;
PROCEDURE ForallClasses		(t: tTree; Proc: ProcOfT);
PROCEDURE ForallAttributes	(t: tTree; Proc: ProcOfT);
PROCEDURE Error		(ErrorCode: INTEGER; Pos: tPosition);
PROCEDURE Warning	(ErrorCode: INTEGER; Pos: tPosition);
PROCEDURE Information	(ErrorCode: INTEGER; Pos: tPosition);
PROCEDURE ErrorI	(ErrorCode: INTEGER; Pos: tPosition; iClass: INTEGER; iPtr: ADDRESS);
PROCEDURE WarningI	(ErrorCode: INTEGER; Pos: tPosition; iClass: INTEGER; iPtr: ADDRESS);
PROCEDURE InformationI	(ErrorCode: INTEGER; Pos: tPosition; iClass: INTEGER; iPtr: ADDRESS);
PROCEDURE WI		(i: tIdent);
PROCEDURE WE		(i: tIdent);
PROCEDURE WN		(n: INTEGER);

(* line 382 "" *)
(* line 818 "" *)




TYPE
yytNodeHead = RECORD yyKind, yyMark: SHORTCARD;  END;
yClasses = RECORD yyHead: yytNodeHead; END;
yNoClass = RECORD yyHead: yytNodeHead; END;
yClass = RECORD yyHead: yytNodeHead; Name: tIdent; Properties: tClassProperties; Attributes: tTree; Extensions: tTree; Next: tTree; BaseClass: tTree; Formals: tTree; TypeDesc: tTree; Index: SHORTCARD; END;
yAttributes = RECORD yyHead: yytNodeHead; END;
yNoAttribute = RECORD yyHead: yytNodeHead; END;
yAttrOrAction = RECORD yyHead: yytNodeHead; Next: tTree; END;
yChild = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; Type: tIdent; Properties: tAttrProperties; END;
yAttribute = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; Type: tIdent; Properties: tAttrProperties; END;
yActionPart = RECORD yyHead: yytNodeHead; Next: tTree; END;
yCodes = RECORD yyHead: yytNodeHead; Export: tText; Import: tText; Global: tText; Local: tText; Begin: tText; Close: tText; ExportLine: tPosition; ImportLine: tPosition; GlobalLine: tPosition; LocalLine: tPosition; BeginLine: tPosition; CloseLine: tPosition; END;
yDesignators = RECORD yyHead: yytNodeHead; END;
yNoDesignator = RECORD yyHead: yytNodeHead; END;
yDesignator = RECORD yyHead: yytNodeHead; Selector: tIdent; Attribute: tIdent; Pos: tPosition; Next: tTree; Object: tClass; Type: tIdent; END;
yIdent = RECORD yyHead: yytNodeHead; Attribute: tIdent; Pos: tPosition; Next: tTree; END;
yRemote = RECORD yyHead: yytNodeHead; Designators: tTree; Type: tIdent; Attribute: tIdent; Pos: tPosition; Next: tTree; END;
yAny = RECORD yyHead: yytNodeHead; Code: tStringRef; Next: tTree; END;
yAnys = RECORD yyHead: yytNodeHead; Layouts: tTree; Next: tTree; END;
yLayouts = RECORD yyHead: yytNodeHead; END;
yNoLayout = RECORD yyHead: yytNodeHead; END;
yLayoutAny = RECORD yyHead: yytNodeHead; Code: tStringRef; Next: tTree; END;
yNames = RECORD yyHead: yytNodeHead; END;
yNoName = RECORD yyHead: yytNodeHead; END;
yName = RECORD yyHead: yytNodeHead; Name: tIdent; Pos: tPosition; Next: tTree; Object: tClass; END;
ySpec = RECORD yyHead: yytNodeHead; TrafoName: tIdent; TreeNames: tTree; Public: tTree; Extern: tTree; Codes: tTree; Routines: tTree; END;
yTreeNames = RECORD yyHead: yytNodeHead; END;
yNoTreeName = RECORD yyHead: yytNodeHead; END;
yTreeName = RECORD yyHead: yytNodeHead; Name: tIdent; Pos: tPosition; Next: tTree; Classes: tTree; ClassCount: SHORTCARD; END;
yRoutines = RECORD yyHead: yytNodeHead; END;
yNoRoutine = RECORD yyHead: yytNodeHead; END;
yRoutine = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; Pos: tPosition; InParams: tTree; OutParams: tTree; Extern: tTree; Local: tText; LocalLine: tPosition; Rules: tTree; InForm: tTree; OutForm: tTree; ParamDecls: tTree; IsExtern: BOOLEAN; Decisions: tTree; END;
yProcedure = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; Pos: tPosition; InParams: tTree; OutParams: tTree; Extern: tTree; Local: tText; LocalLine: tPosition; Rules: tTree; InForm: tTree; OutForm: tTree; ParamDecls: tTree; IsExtern: BOOLEAN; Decisions: tTree; END;
yFunction = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; Pos: tPosition; InParams: tTree; OutParams: tTree; Extern: tTree; Local: tText; LocalLine: tPosition; Rules: tTree; InForm: tTree; OutForm: tTree; ParamDecls: tTree; IsExtern: BOOLEAN; Decisions: tTree; ReturnParams: tTree; ReturnForm: tTree; END;
yPredicate = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; Pos: tPosition; InParams: tTree; OutParams: tTree; Extern: tTree; Local: tText; LocalLine: tPosition; Rules: tTree; InForm: tTree; OutForm: tTree; ParamDecls: tTree; IsExtern: BOOLEAN; Decisions: tTree; END;
yParameters = RECORD yyHead: yytNodeHead; END;
yNoParameter = RECORD yyHead: yytNodeHead; END;
yParam = RECORD yyHead: yytNodeHead; IsRef: BOOLEAN; Name: tIdent; Pos: tPosition; Type: tTree; Next: tTree; END;
yType = RECORD yyHead: yytNodeHead; Name: tIdent; Pos: tPosition; Names: tTree; END;
yRules = RECORD yyHead: yytNodeHead; END;
yNoRule = RECORD yyHead: yytNodeHead; END;
yRule = RECORD yyHead: yytNodeHead; Line: tPosition; Patterns: tTree; Exprs: tTree; Expr: tTree; Statements: tTree; Next: tTree; VarDecls: tTree; HasTempos: BOOLEAN; HasPatterns: BOOLEAN; Tempo: tIdent; Index: SHORTCARD; Tests: tTree; HasExit: BOOLEAN; HasAssign: BOOLEAN; HasTargetCode: BOOLEAN; HasRejectOrFail: BOOLEAN; END;
yPatterns = RECORD yyHead: yytNodeHead; END;
yNoPattern = RECORD yyHead: yytNodeHead; Pos: tPosition; END;
yOnePattern = RECORD yyHead: yytNodeHead; Pattern: tTree; Next: tTree; END;
yPatternsList = RECORD yyHead: yytNodeHead; END;
yNoPatternsList = RECORD yyHead: yytNodeHead; END;
yOnePatternsList = RECORD yyHead: yytNodeHead; Patterns: tTree; Next: tTree; END;
yPattern = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; END;
yDecompose = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Selector: tIdent; Expr: tTree; Patterns: tTree; Widen: BOOLEAN; Object: tClass; END;
yVarDef = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Name: tIdent; Object: tClass; END;
yNilTest = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Selector: tIdent; END;
yDontCare1 = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; END;
yDontCare = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Tempos: tTree; END;
yValue = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Expr: tTree; END;
yExprs = RECORD yyHead: yytNodeHead; END;
yNoExpr = RECORD yyHead: yytNodeHead; Pos: tPosition; END;
yOneExpr = RECORD yyHead: yytNodeHead; Expr: tTree; Next: tTree; END;
yNamedExpr = RECORD yyHead: yytNodeHead; Expr: tTree; Next: tTree; Name: tIdent; END;
yExpr = RECORD yyHead: yytNodeHead; Pos: tPosition; END;
yCompose = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Expr: tTree; Exprs: tTree; Widen: BOOLEAN; Object: tClass; Tempo: tIdent; TypeDesc: tTree; END;
yVarUse = RECORD yyHead: yytNodeHead; Pos: tPosition; Name: tIdent; Object: tClass; END;
yAttrDesc = RECORD yyHead: yytNodeHead; Pos: tPosition; Name: tIdent; Object: tClass; Attribute: tIdent; Type: tIdent; END;
yNil = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; END;
yCall = RECORD yyHead: yytNodeHead; Pos: tPosition; Expr: tTree; Exprs: tTree; Patterns: tTree; Object: tClass; END;
yBinary = RECORD yyHead: yytNodeHead; Pos: tPosition; Lop: tTree; Operator: tIdent; Rop: tTree; END;
yPreOperator = RECORD yyHead: yytNodeHead; Pos: tPosition; Operator: tIdent; Expr: tTree; END;
yPostOperator = RECORD yyHead: yytNodeHead; Pos: tPosition; Operator: tIdent; Expr: tTree; END;
yIndex = RECORD yyHead: yytNodeHead; Pos: tPosition; Expr: tTree; Exprs: tTree; END;
yParents = RECORD yyHead: yytNodeHead; Pos: tPosition; Expr: tTree; END;
yTargetExpr = RECORD yyHead: yytNodeHead; Pos: tPosition; Expr: tTree; UsedNames: tSet; END;
yStringExpr = RECORD yyHead: yytNodeHead; Pos: tPosition; String: tStringRef; END;
yStatements = RECORD yyHead: yytNodeHead; END;
yNoStatement = RECORD yyHead: yytNodeHead; END;
yStatement = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; END;
yProcCall = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; Call: tTree; END;
yCondition = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; Expr: tTree; END;
yAssignment = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; Adr: tTree; Expr: tTree; Object: tClass; END;
yReject = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; END;
yFail = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; END;
yTargetStmt = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; Parameters: tTree; Stmt: tTree; UsedNames: tSet; END;
yNl = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; END;
yWriteStr = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; String: tStringRef; END;
yFormals = RECORD yyHead: yytNodeHead; END;
yNoFormal = RECORD yyHead: yytNodeHead; END;
yFormal = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; TypeDesc: tTree; Path: tTree; END;
yDummyFormal = RECORD yyHead: yytNodeHead; Next: tTree; END;
yTypeDesc = RECORD yyHead: yytNodeHead; END;
yNodeTypes = RECORD yyHead: yytNodeHead; TreeName: tTree; Types: tSet; END;
yUserType = RECORD yyHead: yytNodeHead; Type: tIdent; END;
yPath = RECORD yyHead: yytNodeHead; END;
yVar = RECORD yyHead: yytNodeHead; Name: tIdent; IsOutput: BOOLEAN; IsRegister: BOOLEAN; END;
yConsType = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; END;
yField = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; END;
yTests = RECORD yyHead: yytNodeHead; END;
yNoTest = RECORD yyHead: yytNodeHead; END;
yOneTest = RECORD yyHead: yytNodeHead; Next: tTree; Path: tTree; END;
yTestKind = RECORD yyHead: yytNodeHead; Next: tTree; Path: tTree; TypeDesc: tTree; Name: tIdent; END;
yTestIsType = RECORD yyHead: yytNodeHead; Next: tTree; Path: tTree; TypeDesc: tTree; Name: tIdent; END;
yTestNil = RECORD yyHead: yytNodeHead; Next: tTree; Path: tTree; END;
yTestNonlin = RECORD yyHead: yytNodeHead; Next: tTree; Path: tTree; Path2: tTree; TypeDesc: tTree; END;
yTestValue = RECORD yyHead: yytNodeHead; Next: tTree; Path: tTree; Expr: tTree; TypeDesc: tTree; END;
yDecisions = RECORD yyHead: yytNodeHead; END;
yNoDecision = RECORD yyHead: yytNodeHead; END;
yDecision = RECORD yyHead: yytNodeHead; Then: tTree; Else: tTree; OneTest: tTree; Cases: SHORTCARD; IsUnchanged: BOOLEAN; END;
yDecided = RECORD yyHead: yytNodeHead; Else: tTree; Rule: tTree; END;

yyNode = RECORD
CASE : SHORTCARD OF
| 0: Kind: SHORTCARD;
| 130: yyHead: yytNodeHead;
| Classes: Classes: yClasses;
| NoClass: NoClass: yNoClass;
| Class: Class: yClass;
| Attributes: Attributes: yAttributes;
| NoAttribute: NoAttribute: yNoAttribute;
| AttrOrAction: AttrOrAction: yAttrOrAction;
| Child: Child: yChild;
| Attribute: Attribute: yAttribute;
| ActionPart: ActionPart: yActionPart;
| Codes: Codes: yCodes;
| Designators: Designators: yDesignators;
| NoDesignator: NoDesignator: yNoDesignator;
| Designator: Designator: yDesignator;
| Ident: Ident: yIdent;
| Remote: Remote: yRemote;
| Any: Any: yAny;
| Anys: Anys: yAnys;
| Layouts: Layouts: yLayouts;
| NoLayout: NoLayout: yNoLayout;
| LayoutAny: LayoutAny: yLayoutAny;
| Names: Names: yNames;
| NoName: NoName: yNoName;
| Name: Name: yName;
| Spec: Spec: ySpec;
| TreeNames: TreeNames: yTreeNames;
| NoTreeName: NoTreeName: yNoTreeName;
| TreeName: TreeName: yTreeName;
| Routines: Routines: yRoutines;
| NoRoutine: NoRoutine: yNoRoutine;
| Routine: Routine: yRoutine;
| Procedure: Procedure: yProcedure;
| Function: Function: yFunction;
| Predicate: Predicate: yPredicate;
| Parameters: Parameters: yParameters;
| NoParameter: NoParameter: yNoParameter;
| Param: Param: yParam;
| Type: Type: yType;
| Rules: Rules: yRules;
| NoRule: NoRule: yNoRule;
| Rule: Rule: yRule;
| Patterns: Patterns: yPatterns;
| NoPattern: NoPattern: yNoPattern;
| OnePattern: OnePattern: yOnePattern;
| PatternsList: PatternsList: yPatternsList;
| NoPatternsList: NoPatternsList: yNoPatternsList;
| OnePatternsList: OnePatternsList: yOnePatternsList;
| Pattern: Pattern: yPattern;
| Decompose: Decompose: yDecompose;
| VarDef: VarDef: yVarDef;
| NilTest: NilTest: yNilTest;
| DontCare1: DontCare1: yDontCare1;
| DontCare: DontCare: yDontCare;
| Value: Value: yValue;
| Exprs: Exprs: yExprs;
| NoExpr: NoExpr: yNoExpr;
| OneExpr: OneExpr: yOneExpr;
| NamedExpr: NamedExpr: yNamedExpr;
| Expr: Expr: yExpr;
| Compose: Compose: yCompose;
| VarUse: VarUse: yVarUse;
| AttrDesc: AttrDesc: yAttrDesc;
| Nil: Nil: yNil;
| Call: Call: yCall;
| Binary: Binary: yBinary;
| PreOperator: PreOperator: yPreOperator;
| PostOperator: PostOperator: yPostOperator;
| Index: Index: yIndex;
| Parents: Parents: yParents;
| TargetExpr: TargetExpr: yTargetExpr;
| StringExpr: StringExpr: yStringExpr;
| Statements: Statements: yStatements;
| NoStatement: NoStatement: yNoStatement;
| Statement: Statement: yStatement;
| ProcCall: ProcCall: yProcCall;
| Condition: Condition: yCondition;
| Assignment: Assignment: yAssignment;
| Reject: Reject: yReject;
| Fail: Fail: yFail;
| TargetStmt: TargetStmt: yTargetStmt;
| Nl: Nl: yNl;
| WriteStr: WriteStr: yWriteStr;
| Formals: Formals: yFormals;
| NoFormal: NoFormal: yNoFormal;
| Formal: Formal: yFormal;
| DummyFormal: DummyFormal: yDummyFormal;
| TypeDesc: TypeDesc: yTypeDesc;
| NodeTypes: NodeTypes: yNodeTypes;
| UserType: UserType: yUserType;
| Path: Path: yPath;
| Var: Var: yVar;
| ConsType: ConsType: yConsType;
| Field: Field: yField;
| Tests: Tests: yTests;
| NoTest: NoTest: yNoTest;
| OneTest: OneTest: yOneTest;
| TestKind: TestKind: yTestKind;
| TestIsType: TestIsType: yTestIsType;
| TestNil: TestNil: yTestNil;
| TestNonlin: TestNonlin: yTestNonlin;
| TestValue: TestValue: yTestValue;
| Decisions: Decisions: yDecisions;
| NoDecision: NoDecision: yNoDecision;
| Decision: Decision: yDecision;
| Decided: Decided: yDecided;
END;
END;

VAR TreeRoot	: tTree;
VAR HeapUsed	: LONGCARD;
VAR yyPoolFreePtr, yyPoolMaxPtr	: SYSTEM.ADDRESS;
VAR yyNodeSize	: ARRAY [0..129] OF SHORTCARD;
VAR yyExit	: PROC;

PROCEDURE yyAlloc	(): tTree;
PROCEDURE MakeTree	(Kind: SHORTCARD): tTree;
PROCEDURE IsType	(Tree: tTree; Kind: SHORTCARD): BOOLEAN;

PROCEDURE mClasses (): tTree;
PROCEDURE mNoClass (): tTree;
PROCEDURE mClass (pName: tIdent; pProperties: tClassProperties; pAttributes: tTree; pExtensions: tTree; pNext: tTree): tTree;
PROCEDURE mAttributes (): tTree;
PROCEDURE mNoAttribute (): tTree;
PROCEDURE mAttrOrAction (pNext: tTree): tTree;
PROCEDURE mChild (pNext: tTree; pName: tIdent; pType: tIdent; pProperties: tAttrProperties): tTree;
PROCEDURE mAttribute (pNext: tTree; pName: tIdent; pType: tIdent; pProperties: tAttrProperties): tTree;
PROCEDURE mActionPart (pNext: tTree): tTree;
PROCEDURE mCodes (pExport: tText; pImport: tText; pGlobal: tText; pLocal: tText; pBegin: tText; pClose: tText; pExportLine: tPosition; pImportLine: tPosition; pGlobalLine: tPosition; pLocalLine: tPosition; pBeginLine: tPosition; pCloseLine: tPosition): tTree;
PROCEDURE mDesignators (): tTree;
PROCEDURE mNoDesignator (): tTree;
PROCEDURE mDesignator (pSelector: tIdent; pAttribute: tIdent; pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mIdent (pAttribute: tIdent; pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mRemote (pDesignators: tTree; pType: tIdent; pAttribute: tIdent; pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mAny (pCode: tStringRef; pNext: tTree): tTree;
PROCEDURE mAnys (pLayouts: tTree; pNext: tTree): tTree;
PROCEDURE mLayouts (): tTree;
PROCEDURE mNoLayout (): tTree;
PROCEDURE mLayoutAny (pCode: tStringRef; pNext: tTree): tTree;
PROCEDURE mNames (): tTree;
PROCEDURE mNoName (): tTree;
PROCEDURE mName (pName: tIdent; pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mSpec (pTrafoName: tIdent; pTreeNames: tTree; pPublic: tTree; pExtern: tTree; pCodes: tTree; pRoutines: tTree): tTree;
PROCEDURE mTreeNames (): tTree;
PROCEDURE mNoTreeName (): tTree;
PROCEDURE mTreeName (pName: tIdent; pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mRoutines (): tTree;
PROCEDURE mNoRoutine (): tTree;
PROCEDURE mRoutine (pNext: tTree; pName: tIdent; pPos: tPosition; pInParams: tTree; pOutParams: tTree; pExtern: tTree; pLocal: tText; pLocalLine: tPosition; pRules: tTree): tTree;
PROCEDURE mProcedure (pNext: tTree; pName: tIdent; pPos: tPosition; pInParams: tTree; pOutParams: tTree; pExtern: tTree; pLocal: tText; pLocalLine: tPosition; pRules: tTree): tTree;
PROCEDURE mFunction (pNext: tTree; pName: tIdent; pPos: tPosition; pInParams: tTree; pOutParams: tTree; pExtern: tTree; pLocal: tText; pLocalLine: tPosition; pRules: tTree; pReturnParams: tTree): tTree;
PROCEDURE mPredicate (pNext: tTree; pName: tIdent; pPos: tPosition; pInParams: tTree; pOutParams: tTree; pExtern: tTree; pLocal: tText; pLocalLine: tPosition; pRules: tTree): tTree;
PROCEDURE mParameters (): tTree;
PROCEDURE mNoParameter (): tTree;
PROCEDURE mParam (pIsRef: BOOLEAN; pName: tIdent; pPos: tPosition; pType: tTree; pNext: tTree): tTree;
PROCEDURE mType (pName: tIdent; pPos: tPosition; pNames: tTree): tTree;
PROCEDURE mRules (): tTree;
PROCEDURE mNoRule (): tTree;
PROCEDURE mRule (pLine: tPosition; pPatterns: tTree; pExprs: tTree; pExpr: tTree; pStatements: tTree; pNext: tTree): tTree;
PROCEDURE mPatterns (): tTree;
PROCEDURE mNoPattern (pPos: tPosition): tTree;
PROCEDURE mOnePattern (pPattern: tTree; pNext: tTree): tTree;
PROCEDURE mPatternsList (): tTree;
PROCEDURE mNoPatternsList (): tTree;
PROCEDURE mOnePatternsList (pPatterns: tTree; pNext: tTree): tTree;
PROCEDURE mPattern (pPos: tPosition): tTree;
PROCEDURE mDecompose (pPos: tPosition; pSelector: tIdent; pExpr: tTree; pPatterns: tTree; pWiden: BOOLEAN): tTree;
PROCEDURE mVarDef (pPos: tPosition; pName: tIdent): tTree;
PROCEDURE mNilTest (pPos: tPosition; pSelector: tIdent): tTree;
PROCEDURE mDontCare1 (pPos: tPosition): tTree;
PROCEDURE mDontCare (pPos: tPosition): tTree;
PROCEDURE mValue (pPos: tPosition; pExpr: tTree): tTree;
PROCEDURE mExprs (): tTree;
PROCEDURE mNoExpr (pPos: tPosition): tTree;
PROCEDURE mOneExpr (pExpr: tTree; pNext: tTree): tTree;
PROCEDURE mNamedExpr (pExpr: tTree; pNext: tTree; pName: tIdent): tTree;
PROCEDURE mExpr (pPos: tPosition): tTree;
PROCEDURE mCompose (pPos: tPosition; pSelector: tIdent; pExpr: tTree; pExprs: tTree; pWiden: BOOLEAN): tTree;
PROCEDURE mVarUse (pPos: tPosition; pName: tIdent): tTree;
PROCEDURE mAttrDesc (pPos: tPosition; pName: tIdent; pAttribute: tIdent): tTree;
PROCEDURE mNil (pPos: tPosition; pSelector: tIdent): tTree;
PROCEDURE mCall (pPos: tPosition; pExpr: tTree; pExprs: tTree; pPatterns: tTree): tTree;
PROCEDURE mBinary (pPos: tPosition; pLop: tTree; pOperator: tIdent; pRop: tTree): tTree;
PROCEDURE mPreOperator (pPos: tPosition; pOperator: tIdent; pExpr: tTree): tTree;
PROCEDURE mPostOperator (pPos: tPosition; pOperator: tIdent; pExpr: tTree): tTree;
PROCEDURE mIndex (pPos: tPosition; pExpr: tTree; pExprs: tTree): tTree;
PROCEDURE mParents (pPos: tPosition; pExpr: tTree): tTree;
PROCEDURE mTargetExpr (pPos: tPosition; pExpr: tTree): tTree;
PROCEDURE mStringExpr (pPos: tPosition; pString: tStringRef): tTree;
PROCEDURE mStatements (): tTree;
PROCEDURE mNoStatement (): tTree;
PROCEDURE mStatement (pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mProcCall (pPos: tPosition; pNext: tTree; pCall: tTree): tTree;
PROCEDURE mCondition (pPos: tPosition; pNext: tTree; pExpr: tTree): tTree;
PROCEDURE mAssignment (pPos: tPosition; pNext: tTree; pAdr: tTree; pExpr: tTree): tTree;
PROCEDURE mReject (pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mFail (pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mTargetStmt (pPos: tPosition; pNext: tTree; pParameters: tTree; pStmt: tTree): tTree;
PROCEDURE mNl (pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mWriteStr (pPos: tPosition; pNext: tTree; pString: tStringRef): tTree;
PROCEDURE mFormals (): tTree;
PROCEDURE mNoFormal (): tTree;
PROCEDURE mFormal (pNext: tTree; pName: tIdent; pTypeDesc: tTree; pPath: tTree): tTree;
PROCEDURE mDummyFormal (pNext: tTree): tTree;
PROCEDURE mTypeDesc (): tTree;
PROCEDURE mNodeTypes (pTreeName: tTree; pTypes: tSet): tTree;
PROCEDURE mUserType (pType: tIdent): tTree;
PROCEDURE mPath (): tTree;
PROCEDURE mVar (pName: tIdent; pIsOutput: BOOLEAN; pIsRegister: BOOLEAN): tTree;
PROCEDURE mConsType (pNext: tTree; pName: tIdent): tTree;
PROCEDURE mField (pNext: tTree; pName: tIdent): tTree;
PROCEDURE mTests (): tTree;
PROCEDURE mNoTest (): tTree;
PROCEDURE mOneTest (pNext: tTree; pPath: tTree): tTree;
PROCEDURE mTestKind (pNext: tTree; pPath: tTree; pTypeDesc: tTree; pName: tIdent): tTree;
PROCEDURE mTestIsType (pNext: tTree; pPath: tTree; pTypeDesc: tTree; pName: tIdent): tTree;
PROCEDURE mTestNil (pNext: tTree; pPath: tTree): tTree;
PROCEDURE mTestNonlin (pNext: tTree; pPath: tTree; pPath2: tTree; pTypeDesc: tTree): tTree;
PROCEDURE mTestValue (pNext: tTree; pPath: tTree; pExpr: tTree; pTypeDesc: tTree): tTree;
PROCEDURE mDecisions (): tTree;
PROCEDURE mNoDecision (): tTree;
PROCEDURE mDecision (pThen: tTree; pElse: tTree; pOneTest: tTree; pCases: SHORTCARD; pIsUnchanged: BOOLEAN): tTree;
PROCEDURE mDecided (pElse: tTree; pRule: tTree): tTree;

PROCEDURE WriteTreeNode	(f: IO.tFile; Tree: tTree);
PROCEDURE ReverseTree	(Tree: tTree): tTree;
PROCEDURE CopyTree	(Tree: tTree): tTree;
PROCEDURE QueryTree	(Tree: tTree);
PROCEDURE BeginTree;
PROCEDURE CloseTree;

END Tree.
