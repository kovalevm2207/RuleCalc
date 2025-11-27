#include  "main.h"

int main()
{
    char* user_exp = NULL;
    size_t st_size = ST_EXP_LEN;
    size_t n_pos = getline(&user_exp, &st_size, stdin);
    user_exp[n_pos - 1] = '\0';

    const char* s = user_exp;
    int ans = GetG(&s);
    printf("Your ans = %d\n", ans);

    free(user_exp);
    return 0;
}

int GetG(const char** s)
{
    ON_DEBUG_PRINT("IN GetG\n");
    assert(s);
    assert(*s);

    int val = GetE(s);
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

    int val = GetP(s);
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

    if((**s) == '(')
    {
        ON_DEBUG_PRINT("Start '('E')'\n");
        (*s)++;
        int val = GetE(s);
        if((**s) == ')')
        {
            (*s)++;

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

    int val = 0;
    while('0'<=(**s) && (**s)<='9')
    {
        val = val*10 + ((**s) - '0');
        (*s)++;
    }
    ON_DEBUG_PRINT("OUT GetN\n");

    return val;
}
