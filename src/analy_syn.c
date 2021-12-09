#include "../headers/analy_syn.h"

int cursor=0;

void printError(LEX_CODE code){
    printf("Erreur : %s\n",TOKEN_ERRORS[code]);
}

void test_sym(LEX_CODE code){
    if(symbols[cursor]==code){
        cursor++;
    }else {
        printError(code);
        exit(EXIT_FAILURE);
    }
}

void analy_syn(FILE *fp){
    analy_lex(fp);
    program();
}
void program(){
    test_sym(PROGRAM_TOKEN);
    test_sym(ID_TOKEN);
    test_sym(PV_TOKEN);
    block();
    test_sym(PT_TOKEN);
    test_sym(FIN_TOKEN);
}

void block(){
    consts();
    vars();
    insts();
}

void consts(){
    if(symbols[cursor]==CONST_TOKEN){
        test_sym(CONST_TOKEN);
        do{
            test_sym(ID_TOKEN);
            test_sym(EG_TOKEN);
            test_sym(NUM_TOKEN);
            test_sym(PV_TOKEN);
        }while(symbols[cursor]!=VAR_TOKEN);
    }else if(symbols[cursor]!=VAR_TOKEN){
        printError(VAR_TOKEN);
        exit(EXIT_FAILURE);
    }        
}

void vars(){
    if(symbols[cursor]==VAR_TOKEN){
        test_sym(VAR_TOKEN);
        test_sym(ID_TOKEN);
        while(symbols[cursor]!=PV_TOKEN)
        {
            test_sym(VIR_TOKEN);
            test_sym(ID_TOKEN);
        }
        test_sym(PV_TOKEN);
    }else if(symbols[cursor]!=BEGIN_TOKEN){
        printError(BEGIN_TOKEN);//TODO:
        exit(EXIT_FAILURE);
    }
}

void insts(){
    test_sym(BEGIN_TOKEN);
    inst();
    while(symbols[cursor]!=END_TOKEN){
        test_sym(PV_TOKEN);
        inst();
    }
    test_sym(END_TOKEN);
}
void inst(){
    switch(symbols[cursor]){
        case BEGIN_TOKEN: insts();break;
        case ID_TOKEN: affec();break;
        case IF_TOKEN: si();break;
        case WHILE_TOKEN : tantque();break;
        case WRITE_TOKEN: ecrire();break;
        case READ_TOKEN: lire();break;
        case END_TOKEN : break;
        default: printError(ERROR_TOKEN);exit(EXIT_FAILURE);
    }
}

void affec(){
    test_sym(ID_TOKEN);
    test_sym(AFF_TOKEN);
    expr();
}

void expr(){
    term();
    while(symbols[cursor]!=PV_TOKEN && symbols[cursor!=END_TOKEN]){
        addop();
        term();
    }
}

void term(){
    fact();
    while(symbols[cursor]!=PV_TOKEN && symbols[cursor!=END_TOKEN]){
        addop();
        term();
    }
}
 
void fact(){
    switch(symbols[cursor]){
        case ID_TOKEN: test_sym(ID_TOKEN);break;
        case NUM_TOKEN: test_sym(NUM_TOKEN);break;
        default: expr();
    }
}

void addop(){
    if(symbols[cursor]==PLUS_TOKEN||symbols[cursor]==MOINS_TOKEN){
        cursor++;
    }else{
        printError(ERROR_TOKEN);
        exit(EXIT_FAILURE);
    }
}

void si(){
    test_sym(IF_TOKEN);
    cond();
    test_sym(THEN_TOKEN);
    inst();
}

void cond(){
    expr();
    relop();
    expr();
}

void relop(){
    LEX_CODE cd = symbols[cursor]; 
    if(cd==EG_TOKEN || cd==DIFF_TOKEN ||cd == SUP_TOKEN || cd==INF_TOKEN || cd==SUPEG_TOKEN || cd==INFEG_TOKEN){
        cursor++;
    }else{
        printError(ERROR_TOKEN);
        exit(EXIT_FAILURE);
    }
}

void tantque(){
    test_sym(WHILE_TOKEN);
    cond();
    test_sym(DO_TOKEN);
    inst();
}

void ecrire(){
    test_sym(WRITE_TOKEN);
    test_sym(PO_TOKEN);
    expr();
    while(symbols[cursor]!=PF_TOKEN){
        test_sym(VIR_TOKEN);
        expr();
    }
    test_sym(PF_TOKEN);
}

void lire(){
    test_sym(READ_TOKEN);
    test_sym(PO_TOKEN);
    test_sym(ID_TOKEN);
    while(symbols[cursor]!=PF_TOKEN){
        test_sym(VIR_TOKEN);
        test_sym(ID_TOKEN);
    }
    test_sym(PF_TOKEN);
}
