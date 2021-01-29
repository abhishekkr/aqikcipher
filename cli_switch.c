/*
 * Implementation for cli_switch.h
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cli_switch.h"

bool verbose = false;


bool match(char *arg, char *maybe){
  if(strncmp(arg, maybe, strlen(maybe)) == 0){
    return true;
  }
  return false;
}

bool switch_encode(char *arg){
    if (match(arg, "encode") || match(arg, "-e")){
        printf(">e>>>> true for %s  %d\n", arg, match(arg, "encode"));
        printf(">e>>>> true for %s  %d\n", arg, strncmp(arg, "encode", strlen("encode")));
        return true;
    }
        printf(">e>>>> false for %s\n", arg);
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
