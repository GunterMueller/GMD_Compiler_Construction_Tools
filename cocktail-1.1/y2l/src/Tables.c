#include <stdio.h>
#include <string.h>
#include "Memory.h"
#include "StringMem.h"
#include "Tables.h"

/* types for nodes of linked lists */
typedef struct tName {
		tStringRef name;
		tStringRef alias;
		struct tName *cdr;
	       };

typedef struct tToken {
		tStringRef name;
		int value;
		struct tToken *cdr;
	       };

typedef struct tType {
		tStringRef name;
		tStringRef type;
		struct tType *cdr;
	       };

typedef struct tRule {
		int tag; /* 0 = text, 1 = rule */
		union {
			struct tCell * text;
			struct tElmt * rule;
		      } car;
		struct tRule *cdr;
	       };

/* heads of linked lists */
struct tName * name_list = 0;
struct tToken * token_list = 0;

struct tType * type_list = 0;
struct tCell * oper_list = 0;
struct tCell * global_list = 0;
struct tCell * action_list;

tStringRef start_symbol = 0;

struct tElmt * rule_elmts_list;
struct tCell * text_list = 0;
struct tRule * rule_list = 0;

int token_val;
int type = 0;
int generate_actions = 1;

bool MyEqual (r, s)
tStringRef r;
tString s;
{
  return LengthSt (r) == strlen (s) && IsEqualSt (r, s);
}

void print_symbol (r)
tStringRef r;
{
  register struct tName * p;
  char v[256];

  StGetString (r, v);
  if (v[0] == '\'') {
    (void) printf ("%s", v);
    return;
  }
  for (p = name_list; p; p = p->cdr)
    if (MyEqual (p->name, v)) {
      WriteString (stdout, p->alias);
      return;
    }
  (void) printf ("%s", v);
}

/* check if name is already in name_list */
int unique_name (v)
char * v;
{
  register struct tName * p;
  for (p = name_list; p; p = p->cdr)
    if (p->alias && MyEqual (p->alias, v)) return 0;
  return 1;
}

/* if name not yet in list, append it */
void put_name (name)
tStringRef name;
{
  register struct tName * p;
  char s[256];

  for (p = name_list; p; p = p->cdr) {
    StGetString (name, s);
    if (MyEqual (p->name, s)) return;
  }
  p = (struct tName *) Alloc (sizeof (struct tName));
  p->name  = name;
  p->alias = 0;
  p->cdr   = name_list;
  name_list = p;
}

/* transform every ident with dots */
void process_names ()
{
  register struct tName * p;
  register int i;
  int dotflag;
  char s[256];
  char v[256];

  for (p = name_list; p; p= p->cdr) {
    StGetString (p->name, s);
    if (s[0] != '\'') {
      dotflag = 0;
      for (i = 0; s[i]; i++) 
        if (s[i] == '.') {
  	  dotflag = 1;
	  s[i] = '_';
        }
      if (dotflag) {
        i = 0;
        do {
	  i++;
	  (void) sprintf (v, "%s_%d", s, i);
        } while (! unique_name (v));
        p->alias = PutString (v, strlen (v));
      } else
        p->alias = p->name;
    } else
      p->alias = p->name;
  }
}

/* if token not yet in list, append it */
void put_token (name, value)
tStringRef name;
int	value;
{
  register struct tToken * p;
  char s[256];

  for (p = token_list; p; p = p->cdr) {
    StGetString (name, s);
    if (MyEqual (p->name, s)) return;
  }
  p = (struct tToken *) Alloc (sizeof (struct tToken));
  p->name  = name;
  p->value = value;
  p->cdr   = token_list;
  token_list = p;
}

/* print the TOKEN section */
void aux_print_tokens (p)
struct tToken * p;
{
  register int i, v;
  char s[256];

  if (p) {
    aux_print_tokens (p->cdr);
    (void) printf ("\t");
    print_symbol (p->name);
    if (p->value) {
      v = p->value;
    } else {
      StGetString (p->name, s);
      if (s[0] == '\'') {
	if (s[1] == '\\') {
	  switch (s[2]) {
	    case 'b' : v = 8; break;
	    case 't' : v = 9; break;
	    case 'n' : v = 10; break;
	    case 'f' : v = 12; break;
	    case 'r' : v = 13; break;
	    default :
	      if ((s[2] >= '0') && (s[2] <= '7')) {
		v = 0;
		for (i = 2; s[i] != '\''; i++)
		  v = 8 * v + s[i] - '0';
	      } else
		v = (int) s[2];
	      break;
	  }
	} else
	  if ((s[1] == '\'') && (s[2] == '\'') && (s[4] =='\0')) {
	    v = (int) '\'';
	  } else
	    if (s[3]) {
	      v = token_val++;
	    } else
	      v = (int) s[1];
      } else
	v = token_val++;
    }
    if (v)
      (void) printf ("\t= %d", (int) v);
    (void) printf ("\n");
  }
}

void print_tokens ()
{
  token_val = 257;
  (void) printf ("\nTOKEN\n");
  aux_print_tokens (token_list);
  (void) printf ("\terror\n");
}

/* put type of symbol to list */
void put_type (name, type)
tStringRef name;
tStringRef type;
{
  struct tType *p;

  p = (struct tType *) Alloc (sizeof (struct tType));
  p->name = name;
  p->type = type;
  p->cdr  = type_list;
  type_list = p;
}

/* get type of symbol */
tStringRef search_type (t)
tStringRef t;
{
  char s[256];
  register struct tType * p;

  StGetString (t, s);
  for (p = type_list; p; p = p->cdr)
    if (MyEqual (p->name, s)) return p->type;
  return 0;
}

tStringRef aux_get_type (p, n)
struct tElmt * p;
int * n;
{
  if (p->tag != 2 /* lhs */) {
    tStringRef t = aux_get_type (p->cdr, n);
    if (p->tag == 0 /* symbol */ || p->tag == 1 /* action */ || p->tag == 4 /* last action */) -- * n;
    if (! * n) {
      return search_type (p->car.symbol);
    } else {
      return t;
    }
  } else {
    return 0;
  }
}

tStringRef aux_get_type_0 ()
{
  register struct tElmt * p;

  for (p = rule_elmts_list; p->cdr; p = p->cdr);
  return search_type (p->car.symbol);
}

/* if n = 0 get type of lhs, else of n-th rhs item, 0 if no type */
tStringRef get_type (n)
int n;
{ 
  if (n < 0) {
    return 0;
  } else if (! n) {
    return aux_get_type_0 ();
  } else
    return aux_get_type (rule_elmts_list, &n);
}

/* put operand to list */
void put_oper (s)
tStringRef s;
{
  struct tCell * p;

  p = (struct tCell *) Alloc (sizeof (struct tCell));
  p->car = s;
  p->cdr = oper_list;
  oper_list = p;
}

/* print OPER section */
void aux_print_opers (p)
struct tCell * p;
{
  if (p) {
    aux_print_opers (p->cdr);
    print_symbol (p->car);
    (void) printf ("\t");
  }
}

void print_opers ()
{
  if (oper_list) {
    (void) printf ("\nOPER");
    aux_print_opers (oper_list);
    (void) printf ("\n");
  }
}

/* put text to GLOBAL section */
void put_global (v)
tStringRef v;
{
  struct tCell * p;

  p = (struct tCell *) Alloc (sizeof (struct tCell));
  p->car = v;
  p->cdr = global_list;
  global_list = p;
}

char * YACC1 [] = {
   "\n",
   "# define tParsAttribute	YYSTYPE\n",
   "# define yySynAttribute	yyval\n",
   "# define yyTerminal	yychar\n",
   "# define yyclearin\n",
   "# define yyerrok\n",
   "# ifndef YYMAXDEPTH\n",
   "# define YYMAXDEPTH	150\n",
   "# endif\n",
   0
};

char * YACC2 [] = {
   "# ifndef YYSTYPE\n",
   "# define YYSTYPE	int\n",
   "# endif\n",
   0
};

char * YACC3 [] = {
   "YYSTYPE yylval;\n",
   "# define yylvalDef\n",
   "# define YYERROR\n",
   "# define YYACCEPT	ReleaseArray (& yyStateStack, & yyStateStackSize, sizeof (yyStateRange)); \\\\\n",
   "			ReleaseArray (& yyAttributeStack, & yyAttrStackSize, sizeof (tParsAttribute)); \\\\\n",
   "			return(0)\n",
   "# define YYABORT	ReleaseArray (& yyStateStack, & yyStateStackSize, sizeof (yyStateRange)); \\\\\n",
   "			ReleaseArray (& yyAttributeStack, & yyAttrStackSize, sizeof (tParsAttribute)); \\\\\n",
   "			return(1)\n",
   "# define YYBACKUP(newtoken, newvalue)	YYERROR\n",
   "# define YYRECOVERING()	yyIsRepairing\n",
   "\n",
   0
};

void yacc_globals ()
{
   register int i;

   for (i = 0; YACC1 [i]; i++)
      put_global (PutString (YACC1 [i], strlen (YACC1 [i])));
   if (! type) for (i = 0; YACC2 [i]; i++)
      put_global (PutString (YACC2 [i], strlen (YACC2 [i])));
   for (i = 0; YACC3 [i]; i++)
      put_global (PutString (YACC3 [i], strlen (YACC3 [i])));
}

/* print GLOBAL section */
void aux_print_global (p)
struct tCell * p;
{
  if (p) {
    aux_print_global (p->cdr);
    WriteString (stdout, p->car);
  }
}

void print_global ()
{
  if (global_list) {
    (void) printf ("EXPORT {\n");
    (void) printf ("# define yacc_interface\n");
    (void) printf ("# define lex_interface\n");
    (void) printf ("}\n\n");
    (void) printf ("GLOBAL {\n");
    aux_print_global (global_list);
    (void) printf ("}\n");
  }
}

/* put text to action */
void put_action (v)
tStringRef v;
{
  struct tCell * p;

  p = (struct tCell *) Alloc (sizeof (struct tCell));
  p->car = v;
  p->cdr = action_list;
  action_list = p;
}

/* put action list to rule */
void put_whole_action (v, b)
struct tCell  * v;
bool b;
{
  struct tElmt * p;

  p = (struct tElmt *) Alloc (sizeof (struct tElmt));
  p->tag = b ? 4 : 1;
  p->car.action = v;
  p->cdr = rule_elmts_list;
  rule_elmts_list = p;
}

/* put lhs to rule */
void put_lhs (v)
tStringRef v;
{
  struct tElmt * p;

  p = (struct tElmt *) Alloc (sizeof (struct tElmt));
  p->tag = 2;
  p->car.symbol = v;
  p->cdr = rule_elmts_list;
  rule_elmts_list = p;
}

/* put symbol to rule */
void put_symbol (v)
tStringRef v;
{
  struct tElmt * p;

  p = (struct tElmt *) Alloc (sizeof (struct tElmt));
  p->tag = 0;
  p->car.symbol = v;
  p->cdr = rule_elmts_list;
  rule_elmts_list = p;
}

/* put delimiter to rule */
void put_delim (v)
tStringRef v;
{
  struct tElmt * p;

  p = (struct tElmt *) Alloc (sizeof (struct tElmt));
  p->tag = 3;
  p->car.symbol = v;
  p->cdr = rule_elmts_list;
  rule_elmts_list = p;
}

/* put rule to RULE section */
void put_rule (v)
struct tElmt * v;
{
  struct tRule * p;

  p = (struct tRule *) Alloc (sizeof (struct tRule));
  p->tag = 1;
  p->car.rule = v;
  p->cdr = rule_list;
  rule_list = p;
}

/* put text to list */
void append_text (v)
tStringRef v;
{
  struct tCell * p;

  p = (struct tCell *) Alloc (sizeof (struct tCell));
  p->car = v;
  p->cdr = text_list;
  text_list = p;
}

/* put text list to rule */
void put_text (v)
struct tCell * v;
{
  struct tRule * p;

  if (v) {
    p = (struct tRule *) Alloc (sizeof (struct tRule));
    p->tag = 0;
    p->car.text = v;
    p->cdr = rule_list;
    rule_list = p;
    text_list = 0;
  }
}

/* print RULE section */
void print_actions (p)
struct tCell * p;
{
  if (p) {
    print_actions (p->cdr);
    WriteString (stdout, p->car);
  }
}

void print_rule_elmts (p)
struct tElmt * p;
{
  if (p) {
    print_rule_elmts (p->cdr);
    switch (p->tag) {
      case 1: /* action	*/
	if (generate_actions) {
	   (void) printf ("{{");
	   print_actions (p->car.action);
	   (void) printf (" ");
	}
	break;
      case 4: /* last action */
	if (generate_actions) {
	   (void) printf ("{ $$ = $1; {");
	   print_actions (p->car.action);
	   (void) printf (" ");
	}
	break;
      case 3: /* delim	*/
      case 0: /* symbol	*/
	print_symbol (p->car.symbol); (void) printf (" ");
	break;
      default: /* lhs	*/
	;
    }
  }
}

void print_text (p)
struct tCell * p;
{
  if (p) {
    print_text (p->cdr);
    WriteString (stdout, p->car);
  }
}

void aux_print_rules (p)
struct tRule * p;
{
  if (p) {
    aux_print_rules (p->cdr);
    if (p->tag) {
      print_rule_elmts (p->car.rule);
    } else
      print_text (p->car.text);
  }
}

void print_rules ()
{
  (void) printf ("\nRULE\n");
  if (start_symbol) {
    (void) printf ("\n__START__\t: ");
    print_symbol (start_symbol);
    (void) printf (" .");
  }
  aux_print_rules (rule_list);
  (void) printf ("\n");
}
