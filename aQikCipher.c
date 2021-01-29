#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cli_switch.h"

#define empty_secret "\0"
#define default_secret "least-safe\0"

enum action {Encrypt, Decrypt};

bool verbose = false;


int encode(FILE *iptr_file, FILE *optr_file, char *secret){
  char buf;
  int secret_len = strlen(secret);
  char *new_secret = (char *)calloc(secret_len, sizeof(char));
  strncpy(new_secret, secret, secret_len);
  while(!feof(iptr_file)){
    int sec_idx;
    for(sec_idx = 0; sec_idx < secret_len; sec_idx++){
      //reading next character if present
      if(!fread(&buf, sizeof(buf), 1, iptr_file))
        break;
      if (verbose){
        printf("%c",buf);
      }
      char new_chr = (char)((int)buf + (int)secret[sec_idx]);
      new_chr = new_chr^new_secret[sec_idx];
      new_secret[sec_idx] = new_chr;
      fwrite(&new_chr, sizeof(new_chr), 1, optr_file);
    }
  }
  return 0;
}

int decode(FILE *iptr_file, FILE *optr_file, char *secret){
  char buf;
  int secret_len = strlen(secret);
  char *new_secret = (char *)calloc(secret_len, sizeof(char));
  strncpy(new_secret, secret, secret_len);
  while(!feof(iptr_file)){
    int sec_idx;
    for(sec_idx = 0; sec_idx < secret_len; sec_idx++){
      //reading next character if present
      if(!fread(&buf, sizeof(buf), 1, iptr_file))
        break;
      char new_chr = buf^new_secret[sec_idx];
      new_chr = (char)((int)new_chr - (int)secret[sec_idx]);
      new_secret[sec_idx] = buf;
      fwrite(&new_chr, sizeof(new_chr), 1, optr_file);
      if (verbose){
        printf("%c", new_chr);
      }
    }
  }
  return 0;
}

int aKrypt(enum action choice, char *input_file, char *output_file, char *secret){
  if(verbose){
    printf("%scrypting %s...\n", (choice == Encrypt ? "En" : "De"), input_file);
  }
  FILE *iptr_file, *optr_file;
  iptr_file = fopen(input_file,"rb");
  optr_file = fopen(output_file,"wb");
  //err-chk
  if (!iptr_file){
    printf("\nError: Input File reading is rasing as error.\n");
    exit(1);
  }
  if (!optr_file){
    printf("\nError: Output File writing is rasing as error.\n");
    exit(1);
  }
  if (secret = empty_secret){
      secret = default_secret;
  }
  //read-KONVERT-write
  switch(choice){
    case 0:
      encode(iptr_file, optr_file, secret);
      break;
    case 1:
      decode(iptr_file, optr_file, secret);
      break;
    default:
      printf("\nError: wrong KRYPT choice provided\n");
      exit(1);
  }
  if (verbose){
    printf("(En/De)coding finaliztion...\n");
  }
  fclose(iptr_file);
  fclose(optr_file);
  if (verbose){
    printf("(En/De)coding finished...\n");
  }
  return 0;
}


/**
Main flow for A Qik Cipher.
*/
int main(int ARGC, char *ARGV[]){
  bool it_worked = false;
  if(ARGC < 5){
    howto_use(ARGV[0]);
  }

  char *secret = ARGV[ARGC-3];
  char *input_file = ARGV[ARGC-2];
  char *output_file = ARGV[ARGC-1];
  for(int idx = 1; idx < ARGC; idx++){
      if(switch_encode(ARGV[idx])){
        aKrypt(Encrypt, input_file, output_file, secret);
        break;
      } else if(switch_decode(ARGV[idx])){
        aKrypt(Decrypt, input_file, output_file, secret);
        break;
      } else if(switch_verbose(ARGV[idx])){
        verbose = true;
      } else{
        howto_use(ARGV[0]);
        return -1;
      }
  }
  return 0;
}
