#ifndef SEM_H
#define SEM_H

#include<stdio.h>
#include<stdlib.h>
#include "data.h"

int find_in_id_array(char* id);
void add_to_id_array(char* id);
void add_const(char* id);
void add_var(char* id);
void add_program(char* id);
void validate_assignment(char* id);
void printSemError(char* msg);

#endif