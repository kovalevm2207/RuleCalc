#include <stdio.h>

const char* s = "1000-(3*2+1)+0$";

int GetG(void);
int GetE(void);
int GetT(void);
int GetP(void);
int GetN(void);

int GetG(void)
{
    int val = GetE();
    if(*s != '$')
    {
        printf("SyntaxErr\n");
        return 0;
    }
    s++;
    return val;
}

int GetE(void)
{
    int val = GetT();
    while(*s == '+' || *s == '-')
    {
        int op = *s;
        s++;
        int val2 = GetT();
        if(op == '+') val += val2;
        else          val -= val2;
    }
    return val;
}

int GetT(void)
{
    int val = GetP();
    while(*s == '*' || *s == '/')
    {
        int op = *s;
        s++;
        int val2 = GetP();
        if(op == '*') val *= val2;
        else          val /= val2;
    }
    return val;
}

int GetP(void)
{
    if(*s == '(')
    {
        s++;
        int val = GetE();
        if(*s == ')')
        {
            s++;
            return val;
        }
        else
        {
            printf("SyntaxErr\n");
            return 0;
        }
    }
    else return GetN();
}

int GetN()
{
    int val = 0;
    while('0'<=*s && *s<='9')
    {
        val = val*10 + (*s - '0');
        s++;
    }
    return val;
}

int main()
{
    int ans = GetG();
    printf("Your ans = %d\n", ans);
    return 0;
}
