#include"../headers/analy_syn.h"

int main(){
    fp = fopen("/media/hamza/windows/Users/Asus/Ensias/S3/COMPILA/TP/compilateur Pascal/pascal.p","r");
    if(fp == NULL) {
      perror("Error in opening file");
      return -1;
    }
    analy_syn(fp);
    printf("BRAVO: le programme est correcte!!!");
    fclose(fp);
    return 0;
}