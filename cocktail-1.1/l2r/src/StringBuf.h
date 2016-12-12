# include "ratc.h"

# ifdef __STDC__
# define ARGS(parameters)	parameters
# else
# define ARGS(parameters)	()
# endif

extern	void	BufString		ARGS((tString string));
   /* stores string 's' in the string buffer		*/

extern	void	WriteStringBuffer	();
   /* the contents of the string buffer is printed	*/
   /* on the terminal					*/

extern	void	InitStringBuffer	();
