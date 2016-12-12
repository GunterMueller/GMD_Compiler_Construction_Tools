/************************************************************************/
/*									*/
/* scanner for yacc input language					*/
/*									*/
/************************************************************************/

EXPORT {
# include "StringMem.h"
# include "Positions.h"
# include "Tables.h"

typedef struct	{ tPosition Position;
		     tStringRef		string;
		     int		number;
		     struct tCell *	action;
		} tScanAttribute;

extern void ErrorAttribute ();
}

GLOBAL {

# include <string.h>

# define IDENT		1
# define C_IDENT	2
# define NUMBER		3
# define LEFT		4
# define RIGHT		5
# define NONASSOC	6
# define TOKEN		7
# define PREC		8
# define TYPE		9
# define START		10
# define UNION		11
# define MARK		12
# define LESS		13
# define GREATER	14
# define COMMA		15
# define BAR		16
# define LBRACE		17
# define RBRACE		18
# define SEMICOLON	19
# define COLON		20

char UNION1  [] = "\ntypedef union {";
char UNION2  [] = "} YYSTYPE;\n";

void ErrorAttribute (Token, Attribute)
   int Token;
   tScanAttribute *Attribute;
{
  Attribute->string = 0;
}

int level = 0;	/* nesting level of braces in actions */

void get_put ()	/* this procedure has a side-effect */
{
  int l,i;
  char v [256];

  l = GetWord (v);
  if (v [0] == '\'')
    for (i = 1; v [i+1] != '\0'; i++)
      if ((v [i-1] != '\\') && (v [i] == '\\') && (v [i+1] == '\''))
	v [i] = '\'';
  Attribute.string = PutString (v, l);
  put_name (Attribute.string);
}

char v [256], w [256];
int i, l = 0;
tStringRef r;
}

DEFAULT {
   (void) GetWord (w);
   (void) fprintf (stderr, "%3d, %2d: illegal character: '%s'\n",
      Attribute.Position.Line, Attribute.Position.Column, w);
}

DEFINE
	Letter	= {A-Za-z._} .
	Digit	= {0-9} .
	Octal	= {0-7} .
	comment	= "/*" -{*}* "*"+ (-{*/} -{*}* "*"+) * "/" .
	ToSkip	= ( {\ \t\n} | comment ) * .

START Code, Union, RulePart, Action, String1, String2, Comment, SubPart

RULES

/* scan idents, literals and numbers */
#RulePart# Letter (Letter | Digit) * / ToSkip ":" :
				  { get_put (); return C_IDENT; }
#STD, RulePart# Letter (Letter | Digit) * :
				  { get_put (); return IDENT; }
#STD, RulePart# ' - {'\\\n} + '	: { get_put ();
				    if (yyStartState == RulePart)
				      put_token (Attribute.string, 0); 
				    return IDENT; }
#STD, RulePart# ' \\ Octal + '	: { get_put ();
				    if (yyStartState == RulePart)
				      put_token (Attribute.string, 0); 
				    return IDENT; }
#STD, RulePart# ' \\ ANY + '	: { get_put ();
				    if (yyStartState == RulePart)
				      put_token (Attribute.string, 0); 
				    return IDENT; }
#STD, RulePart# Digit +		: { (void) GetWord (v);
				    Attribute.number = atoi (v);
				    return NUMBER; }

#STD# "%left"		: { return LEFT		; }
#STD# "%right"		: { return RIGHT	; }
#STD# "%nonassoc"	: { return NONASSOC	; }
#STD# "%token"		: { return TOKEN	; }
#STD, RulePart# "%prec"	: { return PREC		; }
#STD# "%type"		: { return TYPE		; }
#STD# "%start"		: { return START	; }

#STD# "%union"		: { yyStart (Union); level = 0; l = 0;
			    put_global (PutString (UNION1, strlen (UNION1))); }
#Union# \{		: { if (level) l += GetWord (&v [l]); level ++; }
#Union# - {{\}\n} *	: { l += GetWord (&v [l]); }
#Union# \n		: { yyEol (0); l += GetWord (&v [l]);
			    put_global (PutString (v, l)); l = 0; }
#Union# \} ;?		: { if (--level) 
			      l += GetWord (&v [l]);
			    else {
			      put_global (PutString (v, l)); l = 0;
			      put_global (PutString (UNION2, strlen (UNION2)));
			      yyPrevious;
			      return UNION;
			    } }

#STD#	   %%		: { yyStart (RulePart); l = 0; return MARK; }
#RulePart# %%		: { yyStart (SubPart ); l = 0; return MARK; }

#STD# "%{"		: { yyStart (Code); l = 0; }
#Code# - {%\n} + | %	: { l += GetWord (&v [l]); }
#Code# \n		: { yyEol (0); l += GetWord (&v [l]);
			    put_global (PutString (v, l)); l = 0; }
#Code# "%}"		: { yyPrevious; v [l++] = '\n';
			    put_global (PutString (v, l)); l = 0; }

#STD, RulePart# "<"	: { return LESS		; }
#STD, RulePart# ">"	: { return GREATER	; }
#STD, RulePart# ","	: { return COMMA	; }
#STD, RulePart# "|"	: { return BAR		; }
#STD, RulePart# ";"	: { return SEMICOLON	; }
#STD, RulePart# ":"	: { return COLON	; }

/* scanning actions */
#RulePart# "{"		: { yyStart (Action);
			    level = 1;
			    action_list = 0;
			    l = 0; v [0] = '\0';
			    return LBRACE; }
#Action# "{"		: { level++; v [l++] = '{'; }

#Action# $ \< - {>} * \> (\- ? Digit + | $) :
			  { (void) GetWord (w);
			    v [l++] = '$';
			    for (i = 2; w [i] != '>'; i++);
			    i++;
			    while (v [l++] = w [i++]);
			    l--;
			    (void) strcpy (&v [l], ".");
			    l += 1;
			    for (i = 2; w [i] != '>'; v [l++] = w [i++]); }

#Action# $ (\- ? Digit + | $) :
			  { i = GetWord (w);
			    (void) strcpy (&v [l], w);
			    l += i;
			    if (w [1] == '$') {
			      r = get_type (0);
			    } else {
			      i = atoi (&w [1]);
			      if (i > 0) r = get_type (i);
			      else       r = 0;
			    }
			    if (r) {
			      StGetString (r, (tString) w);
			      v [l++] = '.';
			      (void) strcpy (&v [l], w);
			      l += strlen (w);
			    } }

#Action# '		: { yyStart (String1); v [l++] = '\''; }
#String1# - {'} +	: { l += GetWord (&v [l]); }
#String1# '		: { yyPrevious; l += GetWord (&v [l]); }

#Action# \"		: { yyStart (String2); v [l++] = '"'; }
#String2# - {"} +	: { l += GetWord (&v [l]); }
#String2# \"		: { yyPrevious; l += GetWord (&v [l]); }

#STD#    "/*"		: { yyStart (Comment); l = GetWord (v); }
#Action# "/*"		: { yyStart (Comment); l += GetWord (&v [l]); }
#Comment# - {\n*} + | "*"	: { l += GetWord (&v [l]); }
#Comment# \n		: { yyEol (0); l+= GetWord (&v [l]);
			    if (yyPreviousStart == Action) {
			      put_action  (PutString (v, l)); l = 0;
			    } else if (yyPreviousStart == STD) {
			      put_global  (PutString (v, l)); l = 0;
			    } else {
			      append_text (PutString (v, l)); l = 0;
			    } }
#Comment# "*/"		: { yyPrevious; l += GetWord (&v [l]);
			    if (yyStartState == STD) {
			      v [l++] = '\n'; put_global (PutString (v, l)); l = 0;
			    } }

#String1, String2, Comment# ANY : { v [l++] = '\\'; l += GetWord (&v [l]); }

#Action# - {${\}'"/\n} + | {/$}	: { l += GetWord (&v [l]); }
#Action# \n		: { yyEol (0); l += GetWord (&v [l]);
			    put_action (PutString (v, l)); l = 0; }
#Action# "}"		: { if (--level)
			      v [l++] = '}';
			    else {
			      yyStart (RulePart);
			      l += GetWord (&v [l]);
			      l += GetWord (&v [l]);
			      put_action (PutString (v, l)); l = 0;
			      Attribute.action = action_list;
			      return RBRACE;
			    } }

/* scan white space and comments between rules */
#RulePart# "/*"		: { yyStart (Comment); l += GetWord (&v [l]); }
#RulePart# " " +	: { l += GetWord (&v [l]); }
#RulePart# \t		: { yyTab; v [l++] = '\t'; }
#RulePart# \n		: { yyEol (0); l += GetWord (&v [l]);
			    append_text (PutString (v, l)); l = 0; }

/* scan tail after second %% */
#SubPart# ANY +		: { l += GetWord (&v [l]); }
#SubPart# \n		: { yyEol (0); l += GetWord (&v [l]);
			    put_global (PutString (v, l)); l = 0; }

\f | \r			:- {}
