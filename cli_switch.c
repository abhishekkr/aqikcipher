/*
 * Implementation for cli_switch.h
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cli_switch.h"


void howto_use(char *mynameis){
  printf("A Qik Cipher\n\n~ Syntax:\n\n");
  printf("./%s [-v] encode secret-string original.file encrypted.file\n\n", mynameis);
  printf("./%s [-v] decode secret-string decrypted.file decrypted.file\n", mynameis);
  exit(1);
}

bool match(char *arg, char *maybe){
  if(strncmp(arg, maybe, strlen(maybe)) == 0){
    return true;
  }
  return false;
}

bool switch_encode(char *arg){
    if (match(arg, "encode") || match(arg, "-e")){
        return true;
    }
    return false;
}

bool switch_decode(char *arg){
    if (match(arg, "decode") || match(arg, "-d")){
        return true;
    }
    return false;
}

bool switch_verbose(char *arg){
    if (match(arg, "verbose") || match(arg, "-v")){
        return true;
    }
    return false;
}
