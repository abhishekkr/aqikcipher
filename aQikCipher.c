#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int encode(FILE *iptr_file, FILE *optr_file, char *secret){
  char buf;
  int secret_len = strlen(secret);
  char *new_secret = (char *)calloc(secret_len, sizeof(char));
  strncpy(new_secret,secret,secret_len);
  while(!feof(iptr_file)){
    int sec_idx;
    for(sec_idx=0; sec_idx<secret_len; sec_idx++){
      //reading next character if present
      if(!fread(&buf,sizeof(buf),1,iptr_file))
        break;
      printf("%c",buf);
      char new_chr = (char)((int)buf+(int)secret[sec_idx]);
      new_chr = new_chr^new_secret[sec_idx];
      new_secret[sec_idx]=new_chr;
      fwrite(&new_chr, sizeof(new_chr),1,optr_file);
    }
  }
  return 0;
}

int decode(FILE *iptr_file, FILE *optr_file, char *secret){
  char buf;
  int secret_len = strlen(secret);
  char *new_secret = (char *)calloc(secret_len, sizeof(char));
  strncpy(new_secret,secret,secret_len);
  while(!feof(iptr_file)){
    int sec_idx;
    for(sec_idx=0; sec_idx<secret_len; sec_idx++){
      //reading next character if present
      if(!fread(&buf,sizeof(buf),1,iptr_file))
        break;
      char new_chr = buf^new_secret[sec_idx];
      new_chr = (char)((int)new_chr-(int)secret[sec_idx]);
      new_secret[sec_idx]=buf;
      fwrite(&new_chr, sizeof(new_chr),1,optr_file);
      printf("%c",new_chr);
    }
  }
  return 0;
}

int aKrypt(int choice, char *input_file, char *output_file, char *secret){
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
  if (secret = "\0"){
      secret = "least-safe\0";
  }
  //read-KONVERT-write
  switch(choice){
    case 1:
      encode(iptr_file, optr_file, secret);
      break;
    case 2:
      decode(iptr_file, optr_file, secret);
      break;
    default:
      printf("\nError: wrong KRYPT choice provided\n");
      exit(1);
  }
  printf("(En/De)coding finaliztion...\n");
  fclose(iptr_file);
  fclose(optr_file);
  printf("(En/De)coding finished...\n");
  return 0;
}

void wrong_syntax(){
  printf("Wrong Syntax\n\n[] Encypting Syntax:\n");
  printf("./acrypt encode secret-string original.file encrypted.file\n\n");
  printf("./acrypt decode secret-string decrypted.file decrypted.file\n");
  exit(1);
}


/**
./acrypt encode original.file encrypted.file
./acrypt decode decrypted.file decrypted.file
*/
int main(int ARGC, char *ARGV[]){
  if(ARGC!=5){
    wrong_syntax();
  }
  if(strncmp(ARGV[1], "encode", 6)){
    printf("Encrypting initializtion...\n");
    aKrypt(1, ARGV[3], ARGV[4], ARGV[2]);
  }
  else if(strncmp(ARGV[1], "decode", 6)){
    printf("Decrypting initializtion...\n");
    aKrypt(2, ARGV[3], ARGV[4], ARGV[2]);
  }
  else{
    wrong_syntax();
  }
  return 0;
}
