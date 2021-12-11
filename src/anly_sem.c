#include "../headers/analy_sem.h"

int find_in_id_array(char* id){//returns element's index if found and -1 otherwise
    int i;
    for(i=0;i<ids_arr_cursor;i++){
        if (strcmp(IDS_ARR[i].value,id)==0){
            return i;
        }
    }
    return -1;
}

void add_to_id_array(char* id){
    switch(last_keyword){
        case PROGRAM_TOKEN:
            add_program(id);
            break;
        case CONST_TOKEN:
            add_const(id);
            break;
        case VAR_TOKEN:
            add_var(id);
            break;
        case BEGIN_TOKEN: //if last keyword is begin then the current id represent an assignment. 
            validate_assignment(id);
            break;
    }
}

void add_program(char* id){
    //we don't check if id already exist in ids table because program always comes first (checked by analy_syn)
    IDS_ARR[ids_arr_cursor]=(IDS_ARR_TYPE){id,VAR_TYPE};
    ids_arr_cursor++;
}

void add_const(char* id){
    if(find_in_id_array(id)==-1){
        IDS_ARR[ids_arr_cursor]=(IDS_ARR_TYPE){id,CONST_TYPE};
        ids_arr_cursor++;
    }else{
        //TODO: raise error : multiple definitions .
        char* msg="multiple definitions of ";
        strcat(msg,id);
        printSemError(msg);
        exit(EXIT_FAILURE);
    }
}

void add_var(char* id){
    if(find_in_id_array(id)==-1){
        IDS_ARR[ids_arr_cursor]=(IDS_ARR_TYPE){id,VAR_TYPE};
        ids_arr_cursor++;
    }else{
        //TODO: raise error : multiple definitions .
        char* msg="multiple definitions of ";
        strcat(msg,id);
        printSemError(msg);
        exit(EXIT_FAILURE);
    }
}

void validate_assignment(char* id){
    int index = find_in_id_array(id);
    char* msg="";
    if(index==-1){
        //TODO: raise error : didn't find a declaration .
        strcat(msg,"didn't find a declaration of ");
        strcat(msg,id);
        printSemError(msg);
        exit(EXIT_FAILURE);
    }else if(IDS_ARR[index].type==CONST_TYPE){
        //TODO: raise error : const value can't be changed .
        printSemError("const value can't be changed");
        
        exit(EXIT_FAILURE);
    }else if(IDS_ARR[index].type==CONST_TYPE){
        //TODO: raise error : program id can't be used as variable.
        printSemError("program id can't be used as variable"); 
        exit(EXIT_FAILURE);
    }
}

void printSemError(char* msg){
    printf("Error : %s\n",msg);
}