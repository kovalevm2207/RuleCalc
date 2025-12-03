#ifndef RULE_CALC_MAIN_H
#define RULE_CALC_MAIN_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "color_print.h"

#ifdef DEBUG
    #define ON_DEBUG_PRINT(text) fprintf(stderr, ORANGE_COLOR text RESET);
#else
    #define ON_DEBUG_PRINT(text)
#endif

#define ERR_PRINT(text) fprintf(stderr, RED_COLOR text RESET)

const size_t ST_EXP_LEN = 5;
const size_t ST_W_LEN = 5;


double GetG(const char** s);
double GetE(const char** s);
double GetT(const char** s);
double GetS(const char** s);
double GetF(const char** s);
double GetP(const char** s);
double GetN(const char** s);
char*  GetW(const char** s);
double SkipSpaces(const char** s);
size_t CheckLen(char** word, size_t word_len, const size_t letter);
double cotan(double val);
double ctanh(double val);

const struct
{
    const char* const name;
    double (*action)(double val);
} func[] ={
    {"sin",   sin},
    {"cos",   cos},
    {"tan",   tan},
    {"ctan",  cotan},
    {"ln",    log},
    {"lg",    log10},
    {"sqrt",  sqrt},
    {"sinh",  sinh},
    {"cosh",  cosh},
    {"tanh",  tanh},
    {"ctanh", ctanh},
    {"asin",  asin},
    {"acos",  acos},
    {"atan",  atan}
};

const size_t FUNC_NUM = sizeof(func)/sizeof(func[0]);

#endif  // RULE_CALC_MAIN_H
