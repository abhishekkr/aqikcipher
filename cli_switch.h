/*
 * To manage command line switches.
 */

typedef enum { false, true } bool;

bool match(char *arg, char *maybe);

bool switch_encode(char *arg);

bool switch_decode(char *arg);

bool switch_verbose(char *arg);
