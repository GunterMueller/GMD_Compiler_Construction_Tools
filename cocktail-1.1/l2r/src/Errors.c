/************************************************************************/
/*									*/
/* error handler for l2r						*/
/*									*/
/************************************************************************/

# include "Errors.h"
# include <stdio.h>
# include "Sets.h"

# define MissingBrace		9
# define MissingQuote		10
# define MissingDQuote		11
# define UnclosedComment	12

static void WriteErrorMessage (ErrorCode, ErrorClass, Position)
   short ErrorCode, ErrorClass;
   tPosition Position;
   {
      (void) fprintf (stderr, "%3d, %2d: ", Position.Line, Position.Column);

      switch (ErrorClass) {
      case xxFatal		: (void) fprintf (stderr, "Fatal       "); break;
      case xxRestriction	: (void) fprintf (stderr, "Restriction "); break;
      case xxError		: (void) fprintf (stderr, "Error       "); break;
      case xxWarning		: (void) fprintf (stderr, "Warning     "); break;
      case xxRepair		: (void) fprintf (stderr, "Repair      "); break;
      case xxNote		: (void) fprintf (stderr, "Note        "); break;
      case xxInformation	: (void) fprintf (stderr, "Information "); break;
      default			: (void) fprintf (stderr, "Error class %d ", ErrorClass);
      }

      switch (ErrorCode) {
      case xxNoText		: break;
      case xxSyntaxError	: (void) fprintf (stderr, "syntax error"	); break;
      case xxExpectedTokens	: (void) fprintf (stderr, "expected tokens"	); break;
      case xxRestartPoint	: (void) fprintf (stderr, "restart point"	); break;
      case xxTokenInserted	: (void) fprintf (stderr, "token inserted "	); break;
      case MissingBrace		: (void) fprintf (stderr, "} missing"		); break;
      case MissingQuote		: (void) fprintf (stderr, "' missing"		); break;
      case MissingDQuote	: (void) fprintf (stderr, "\" missing"		); break;
      case UnclosedComment	: (void) fprintf (stderr, "unclosed comment"	); break;
      default			: (void) fprintf (stderr, "error code %d", ErrorCode);
      }
   }

static void WriteInfo (InfoClass, Info)
   short	InfoClass;
   char *	Info;
   {
      if (InfoClass == xxNone) return;
      (void) fprintf (stderr, ": ");
      switch (InfoClass) {
      case xxInteger	: (void) fprintf (stderr, "%d", * (int *)	Info); break;
      case xxShort	: (void) fprintf (stderr, "%d", * (short *)	Info); break;
      case xxSet	: WriteSet	 (stderr, (tSet *)		Info); break;
      case xxString	: (void) fprintf (stderr, "%s",			Info); break;
      default		: (void) fprintf (stderr, "info class: %d", InfoClass);
      }
   }

void ErrorMessageI
# ifdef __STDC__
   (short ErrorCode, short ErrorClass, tPosition Position, short InfoClass, char * Info)
# else
   (ErrorCode, ErrorClass, Position, InfoClass, Info)
   short	ErrorCode, ErrorClass;
   tPosition	Position;
   short	InfoClass;
   char *	Info;
# endif
   {
      extern void exit ();

      WriteErrorMessage (ErrorCode, ErrorClass, Position);
      WriteInfo (InfoClass, Info);
      (void) fprintf (stderr, "\n");
      if (ErrorClass == xxFatal) exit (1);
   }

void ErrorMessage
# ifdef __STDC__
   (short ErrorCode, short ErrorClass, tPosition Position)
# else
   (ErrorCode, ErrorClass, Position)
   short	ErrorCode, ErrorClass;
   tPosition	Position;
# endif
   {
      ErrorMessageI (ErrorCode, ErrorClass, Position, xxNone, (char *) NULL);
   }
