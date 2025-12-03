#ifndef RULE_CALC_MAIN_H
#define RULE_CALC_MAIN_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "color_print.h"

#ifdef DEBUG
    #define ON_DEBUG_PRINT(text) fprintf(stderr, ORANGE_COLOR text RESET);
#else
    #define ON_DEBUG_PRINT(text)
#endif

#define ERR_PRINT(text) fprintf(stderr, RED_COLOR text RESET)

const size_t ST_EXP_LEN = 5;

double GetG(const char** s);
double GetE(const char** s);
double GetT(const char** s);
double GetS(const char** s);
double GetP(const char** s);
double GetN(const char** s);
double SkipSpaces(const char** s);

#endif  // RULE_CALC_MAIN_H
