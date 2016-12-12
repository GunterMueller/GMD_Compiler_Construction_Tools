# include "Positions.h"

# define xxNoText		0
# define xxSyntaxError		1	/* error codes		*/
# define xxExpectedTokens	2
# define xxRestartPoint		3
# define xxTokenInserted	4

# define xxNone			0
# define xxFatal		1	/* error classes	*/
# define xxRestriction		2
# define xxError		3
# define xxWarning		4
# define xxRepair		5
# define xxNote			6
# define xxInformation		7

# define xxInteger		1	/* info classes		*/
# define xxShort		2
# define xxLong			3
# define xxReal			4
# define xxBoolean		5
# define xxCharacter		6
# define xxString		7
# define xxSet			8

# ifdef __STDC__
# define ARGS(parameters)	parameters
# else
# define ARGS(parameters)	()
# endif

extern void ErrorMessage  ARGS((short ErrorCode, short ErrorClass, tPosition Position));
extern void ErrorMessageI ARGS((short ErrorCode, short ErrorClass, tPosition Position, short InfoClass, char * Info));
