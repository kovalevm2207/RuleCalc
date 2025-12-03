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

    int val = GetT(s);
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
        int op = (**s);
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
    double val1 = GetF(s);
    SkipSpaces(s);

    if(**s == '^')
    {
        (*s)++;
        double val2 = GetF(s);

        val1 = pow(val1, val2);
    }

    return val1;
}
double GetF(const char** s)
{
    assert(s);
    assert(*s);

    SkipSpaces(s);

    char* word = GetW(s);
    double val = GetP(s);

    if(word)
    {
        for(size_t i = 0; i < FUNC_NUM; i++)
        {
            if(strcmp(word, func[i].name) == 0)
            {
                return func[i].action(val);
            }
        }
        ERR_PRINT("SyntaxErr\n");
        return 0;
    }

    return val;
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
char*  GetW(const char** s)
{
    assert(s);
    assert(*s);

    char* word = (char*) calloc(ST_W_LEN, sizeof(char));
    assert(word && "mem alloc err (calloc)");

    size_t letter = 0;
    size_t word_len = ST_W_LEN;

    SkipSpaces(s);
    while(('A' <= (**s) && (**s) <= 'Z') ||
          ('a' <= (**s) && (**s) <= 'z'))
    {
        word[letter++] = **s;
        (*s)++;

        word_len = CheckLen(&word, word_len, letter);
        assert(word_len);
    }
    if(letter == 0)
    {
        free(word);
        return NULL;
    }

    while(('A' <= (**s) && (**s) <= 'Z') ||
          ('a' <= (**s) && (**s) <= 'z') ||
          ('0' <= (**s) && (**s) <= '9') ||
          (**s) == '_')
    {
        word[letter++] = **s;
        (*s)++;

        word_len = CheckLen(&word, word_len, letter);
        assert(word_len);
    }

    word[letter] = '\0';

    return word;
}
double SkipSpaces(const char** s)
{
    assert(s);
    assert(*s);

    while(isspace(**s)) ++*s;

    return 0;
}
size_t CheckLen(char** word, size_t word_len, const size_t letter)
{
    assert(word);
    assert(*word);
    assert(letter <= word_len);

    if(letter == word_len)
    {
        char* new_word = (char*) realloc(*word, (word_len * 2) * sizeof(char));
        assert(new_word);
        *word = new_word;
        memset(*word + word_len, 0, word_len);
        word_len *= 2;
    }

    return word_len;
}
double cotan(double val)
{
    return 1/tan(val);
}
double ctanh(double val)
{
    return 1/tanh(val);
}
