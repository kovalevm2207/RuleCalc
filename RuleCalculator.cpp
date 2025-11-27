#include "RuleCalculator.h"

int GetG(const char** s)
{
    ON_DEBUG_PRINT("IN GetG\n");
    assert(s);
    assert(*s);

    SkipSpaces(s);

    int val = GetE(s);

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
int GetE(const char** s)
{
    ON_DEBUG_PRINT("IN GetE\n");

    assert(s);
    assert(*s);

    SkipSpaces(s);

    int val = GetT(s);
    while((**s) == '+' || (**s) == '-')
    {
        int op = (**s);
        (*s)++;
        int val2 = GetT(s);
        if(op == '+') val += val2;
        else          val -= val2;
    }

    ON_DEBUG_PRINT("OUT GetE\n");
    return val;
}
int GetT(const char** s)
{
    ON_DEBUG_PRINT("IN GetT\n");

    assert(s);
    assert(*s);

    SkipSpaces(s);

    int val = GetP(s);

    SkipSpaces(s);

    while((**s) == '*' || (**s) == '/')
    {
        int op = (**s);
        (*s)++;
        int val2 = GetP(s);
        if(op == '*') val *= val2;
        else          val /= val2;
    }

    ON_DEBUG_PRINT("OUT GetT\n");
    return val;
}
int GetP(const char** s)
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

        int val = GetE(s);
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
int GetN(const char** s)
{
    ON_DEBUG_PRINT("IN GetN\n");

    assert(s);
    assert(*s);

    SkipSpaces(s);

    int val = 0;
    while('0'<=(**s) && (**s)<='9')
    {
        val = val*10 + ((**s) - '0');
        (*s)++;
    }

    ON_DEBUG_PRINT("OUT GetN\n");
    return val;
}
int SkipSpaces(const char** s)
{
    assert(s);
    assert(*s);

    while(isspace(**s)) ++*s;

    return 0;
}
