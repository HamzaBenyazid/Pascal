#ifndef SYN_H
#define SYN_H

#include"data.h"
#include"analy_lex.h"



void analy_syn(FILE *fp);
void program();
void block();
void consts();
void vars();
void insts();
void inst();
void affec();
void si();
void tantque();
void ecrire();
void lire();
void cond();
void relop();
void expr();
void addop();
void term();
void multop();
void fact();
void id();
void num();
void chiffre();
void lettre();

#endif