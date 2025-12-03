#include "RuleCalculator.h"

double GetG(const char** s)
{
    ON_DEBUG_PRINT("IN GetG\n");
    assert(s);
    assert(*s);

    SkipSpaces(s);

    double val = GetE(s);

    SkipSpaces(s);

    if((**s) != '\0')
    {
        ERR_PRINT("SyntaxErr\n");
        return 0;
    }
    (*s)++;

    ON_DEBUG_PRINT("OUT GetG\n");
    return val;
}
double GetE(const char** s)
{
    ON_DEBUG_PRINT("IN GetE\n");

    assert(s);
    assert(*s);

    SkipSpaces(s);

    double val = GetT(s);
    while((**s) == '+' || (**s) == '-')
    {
        double op = (**s);
        (*s)++;
        double val2 = GetT(s);
        if(op == '+') val += val2;
        else          val -= val2;
    }

    ON_DEBUG_PRINT("OUT GetE\n");
    return val;
}
double GetT(const char** s)
{
    ON_DEBUG_PRINT("IN GetT\n");

    assert(s);
    assert(*s);

    SkipSpaces(s);

    double val = GetS(s);

    SkipSpaces(s);

    while((**s) == '*' || (**s) == '/')
    {
        double op = (**s);
        (*s)++;
        double val2 = GetS(s);
        if(op == '*') val *= val2;
        else          val /= val2;
    }

    ON_DEBUG_PRINT("OUT GetT\n");
    return val;
}
double GetS(const char** s)
{
    assert(s);
    assert(*s);

    SkipSpaces(s);
    double val1 = GetP(s);
    SkipSpaces(s);

    if(**s == '^')
    {
        (*s)++;
        double val2 = GetP(s);

        val1 = pow(val1, val2);
    }

    return val1;
}
double GetP(const char** s)
{
    ON_DEBUG_PRINT("IN GetP\n");

    assert(s);
    assert(*s);

    SkipSpaces(s);

    if((**s) == '(')
    {
        ON_DEBUG_PRINT("Start '('E')'\n");
        (*s)++;

        SkipSpaces(s);

        double val = GetE(s);

        SkipSpaces(s);
        if((**s) == ')')
        {
            (*s)++;

            SkipSpaces(s);

            ON_DEBUG_PRINT("OUT GetP '('E')'\n");
            return val;
        }
        else
        {
            ERR_PRINT("SyntaxErr\n");
            return 0;
        }
    }
    else
    {
        ON_DEBUG_PRINT("OUT GetP N\n");
        return GetN(s);
    }
}
double GetN(const char** s)
{
    ON_DEBUG_PRINT("IN GetN\n");

    assert(s);
    assert(*s);

    SkipSpaces(s);

    double sign = 1;
    if(**s == '-')
    {
        sign = -1;
        (*s)++;
    }
    if(!('0'<=(**s) && (**s)<='9'))
    {
        ERR_PRINT("SyntaxErr\n");
        return 0;
    }

    double val = 0;
    while('0'<=(**s) && (**s)<='9')
    {
        val = val*10 + ((**s) - '0');
        (*s)++;
    }

    if(**s == '.')
    {
        ++*s;

        double frac_part = 0;
        double order = 1;
        while('0'<=(**s) && (**s)<='9')
        {
            frac_part += ((**s) - '0') / pow(10, order++);
            (*s)++;
        }

        val += frac_part;
    }

    ON_DEBUG_PRINT("OUT GetN\n");
    return val * sign; // TreeNodeCtor_(NUM, {.num = val}, NULL, NULL)
}
double SkipSpaces(const char** s)
{
    assert(s);
    assert(*s);

    while(isspace(**s)) ++*s;

    return 0;
}
