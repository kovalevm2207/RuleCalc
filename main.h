#ifndef RULE_CALC_MAIN_H
#define RULE_CALC_MAIN_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "color_print.h"

#ifdef DEBUG
    #define ON_DEBUG_PRINT(text) printf(ORANGE_COLOR text RESET);
#else
    #define ON_DEBUG_PRINT(text)
#endif

#define ERR_PRINT(text) printf(RED_COLOR text RESET)

const size_t ST_EXP_LEN = 5;

int GetG(const char** s);
int GetE(const char** s);
int GetT(const char** s);
int GetP(const char** s);
int GetN(const char** s);

#endif  // RULE_CALC_MAIN_H
