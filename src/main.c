#include"../headers/analy_syn.h"

int main(int argc, char *argv[]){
    if (argc<2){
      printf("no file specified");
      return -1; 
    }else{
      fp = fopen(argv[1],"r");
      //fp = fopen("./tests/test0.p","r");
      if(fp == NULL) {
        perror("Error in opening file");
        return -1;
      }
      analy_syn(fp);
      printf("BRAVO: le programme est correcte!!!");
      fclose(fp);
      return 0; 
    }
}