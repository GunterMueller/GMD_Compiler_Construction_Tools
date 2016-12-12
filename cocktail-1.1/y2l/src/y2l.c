# include "Scanner.h"
# include "Parser.h"

extern char *strcpy(), *strcat();

main (argc, argv)
   int argc;
   char * argv [];
{
  while (++ argv, -- argc) if (argv [0][0] == '-') generate_actions = 0;
  InitStringMemory	();
  BeginScanner		();
  (void) Parser		();
  CloseParser		();
  process_names		();
  print_global		();
  print_tokens		();
  print_opers		();
  print_rules		();
  return 0;
}
