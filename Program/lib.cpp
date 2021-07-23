#include "Header/lib.h"
int64_t hash_fr_term(const string &term)
{
    int base = 37;
    int64_t tmp = 0;
    for (int i = 0; i < term.size(); i++)
    {
        int _tmp;
        if (term[i] >= '0' && term[i] <= '9')
            _tmp = 27 + term[i] - '0';
        else
            _tmp = term[i] - 'a' + 1;
        tmp = tmp * base + _tmp;
    }
    return tmp;
}