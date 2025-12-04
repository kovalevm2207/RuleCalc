#include "RuleCalculator.h"

int main()
{
    char* user_exp = NULL;
    size_t st_size = ST_EXP_LEN;
    ssize_t n_pos = getline(&user_exp, &st_size, stdin);
    user_exp[n_pos - 1] = '\0';

    const char* s = user_exp;
    double ans = GetG(&s, user_exp);
    printf("Your ans = %lg\n", ans);

    free(user_exp);
    return 0;
}
