#include "../headers/analy_syn.h"

int cursor=0;

void printError(LEX_CODE code){
    printf("Error in line %d: %s\n",symbols[cursor-1].line,TOKEN_ERRORS[code]);
}

void test_sym(LEX_CODE code){
    if(symbols[cursor].token==code){
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
    if(symbols[cursor].token==CONST_TOKEN){
        test_sym(CONST_TOKEN);
        do{
            test_sym(ID_TOKEN);
            test_sym(EG_TOKEN);
            test_sym(NUM_TOKEN);
            test_sym(PV_TOKEN);
        }while(symbols[cursor].token!=VAR_TOKEN);
    }else if(symbols[cursor].token!=VAR_TOKEN){
        printError(VAR_TOKEN);
        exit(EXIT_FAILURE);
    }        
}

void vars(){
    if(symbols[cursor].token==VAR_TOKEN){
        test_sym(VAR_TOKEN);
        test_sym(ID_TOKEN);
        while(symbols[cursor].token!=PV_TOKEN)
        {
            test_sym(VIR_TOKEN);
            test_sym(ID_TOKEN);
        }
        test_sym(PV_TOKEN);
    }else if(symbols[cursor].token!=BEGIN_TOKEN){
        printError(BEGIN_TOKEN);//TODO:
        exit(EXIT_FAILURE);
    }
}

void insts(){
    test_sym(BEGIN_TOKEN);
    inst();
    while(symbols[cursor].token!=END_TOKEN){
        test_sym(PV_TOKEN);
        inst();
    }
    test_sym(END_TOKEN);
}
void inst(){
    switch(symbols[cursor].token){
        case BEGIN_TOKEN: insts();break;
        case ID_TOKEN: affec();break;
        case IF_TOKEN: si();break;
        case WHILE_TOKEN : tantque();break;
        case WRITE_TOKEN: ecrire();break;
        case READ_TOKEN: lire();break;
        case END_TOKEN : break;
        case PV_TOKEN: break;
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
    LEX_CODE cur_sym_tok = symbols[cursor].token;
    while(cur_sym_tok!=VIR_TOKEN && cur_sym_tok!=PF_TOKEN
    && !(cur_sym_tok==EG_TOKEN || cur_sym_tok==DIFF_TOKEN ||cur_sym_tok == SUP_TOKEN || cur_sym_tok==INF_TOKEN || cur_sym_tok==SUPEG_TOKEN || cur_sym_tok==INFEG_TOKEN)){
        addop();
        term();
    }
}

void term(){
    fact();
    while(symbols[cursor].token!=PV_TOKEN && symbols[cursor].token!=END_TOKEN){
        multop();
        term();
    }
}
 
void fact(){//TODO: fix
    switch(symbols[cursor].token){
        case ID_TOKEN: test_sym(ID_TOKEN);break;
        case NUM_TOKEN: test_sym(NUM_TOKEN);break;
        default: expr();
    }
}

void addop(){
    if(symbols[cursor].token==PLUS_TOKEN||symbols[cursor].token==MOINS_TOKEN){
        cursor++;
    }else{
        printError(ERROR_TOKEN);
        exit(EXIT_FAILURE);
    }
}
void multop(){
    if(symbols[cursor].token==MULT_TOKEN||symbols[cursor].token==DIV_TOKEN){
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
    LEX_CODE cd = symbols[cursor].token; 
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
    while(symbols[cursor].token!=PF_TOKEN){
        test_sym(VIR_TOKEN);
        expr();
    }
    test_sym(PF_TOKEN);
}

void lire(){
    test_sym(READ_TOKEN);
    test_sym(PO_TOKEN);
    test_sym(ID_TOKEN);
    while(symbols[cursor].token!=PF_TOKEN){
        test_sym(VIR_TOKEN);
        test_sym(ID_TOKEN);
    }
    test_sym(PF_TOKEN);
}
