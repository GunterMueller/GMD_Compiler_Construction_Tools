/* variables and procedure for list management */
#include "ratc.h"

# ifdef __STDC__
# define ARGS(parameters)	parameters
# else
# define ARGS(parameters)	()
# endif

typedef struct tCell {
		tStringRef car;
		struct tCell * cdr;
	       };

typedef struct tElmt {
		int tag; /* 0 = symbol, 1 = action, 2 = lhs, 3 = delim, 4 = last action  */
		union {
			tStringRef symbol;
			struct tCell * action;
		      } car;
		struct tElmt * cdr;
	       };

extern void put_name		ARGS((tStringRef name));
extern void process_names	();

extern void put_token		ARGS((tStringRef name, int value));
extern void print_tokens	();

extern int type;

extern void put_type		ARGS((tStringRef name, tStringRef type));
extern tStringRef get_type	ARGS((int n));

extern void put_oper		ARGS((tStringRef s));
extern void print_opers		();

extern void put_global		ARGS((tStringRef v));
extern void yacc_globals	();
extern void print_global	();

extern struct tCell * action_list;
extern void put_action		ARGS((tStringRef v));

extern tStringRef start_symbol;

extern struct tElmt * rule_elmts_list;
extern void put_lhs 		ARGS((tStringRef v));
extern void put_symbol		ARGS((tStringRef v));
extern void put_whole_action	ARGS((struct tCell * v, /* bool */ int b));
extern void put_delim		ARGS((tStringRef v));

extern struct tCell * text_list;
extern void append_text		ARGS((tStringRef v));

extern void put_text		ARGS((struct tCell * v));
extern void put_rule		ARGS((struct tElmt * v));
extern void print_rules		();
extern int generate_actions;
