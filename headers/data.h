#ifndef DATA_H
#define DATA_H

#include<stdio.h>
#include<stdio.h>
#include<string.h>

char curr_char;
FILE *fp;

typedef enum {
    ID_TOKEN,
    NUM_TOKEN,
    ERROR_TOKEN,
    PV_TOKEN,
    PT_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    VIR_TOKEN,
    AFF_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    EG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    FIN_TOKEN,
    STRING_TOKEN,
    PROGRAM_TOKEN,
    CONST_TOKEN,
    BEGIN_TOKEN,
    END_TOKEN,
    IF_TOKEN,
    THEN_TOKEN,
    WHILE_TOKEN,
    DO_TOKEN,
    READ_TOKEN,
    WRITE_TOKEN,
    VAR_TOKEN
} LEX_CODE;

extern const char* TOKEN_NAMES[];
extern const char* TOKEN_ERRORS[];
typedef struct {
    LEX_CODE code;
    char keyword[20];
}LANGUAGE_KEYWORD;

extern const LANGUAGE_KEYWORD pascal_keywords[];
extern const int number_of_keywords;
LEX_CODE curr_sym;

LEX_CODE symbols[255];

LEX_CODE last_keyword;

typedef enum { //Type de symbole
    VAR_TYPE,
    CONST_TYPE,
    PROGRAM_TYPE
} SYM_TYPE;

typedef struct { //Type de tableau d'identifiants
    char* value;
    SYM_TYPE type;
} IDS_ARR_TYPE;

IDS_ARR_TYPE IDS_ARR[100];

int ids_arr_cursor;

#endif
