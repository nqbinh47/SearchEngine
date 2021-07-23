#include "Header/str.h"
bool cmp_Info(Info &word_1, Info &word_2)
{
    return (word_1.hash_term < word_2.hash_term);
}
Str::Str()
{
    array = nullptr;
}
Str::~Str()
{
    if (array != nullptr)
        delete[] array;
}
int Str::get_number_words(string &clean_str)
{
    int size = 0;
    for (int i = 0; i < clean_str.size(); i++)
    {
        if (clean_str[i] == ' ')
        {
            size++;
        }
    }
    //more than less hehe
    size += 10;
    return size;
}
void Str::init(string &clean_str)
{
    array = new Info[get_number_words(clean_str)];
    size = 0;

    string tmp = "";
    for (int i = 0; i < clean_str.size(); i++)
    {
        if (clean_str[i] == ' ')
        {
            if (tmp.size())
                array[size++] = Info{tmp, get_hash_from_term(tmp)};
            tmp = "";
            continue;
        }
        tmp = tmp + clean_str[i];
    }
    array[size++] = Info{tmp, get_hash_from_term(tmp)};
    //
}
//need to Quick_sort
void Str::sortInfoarray()
{
    sort(array, array + size, cmp_Info);
}
int64_t Str::get_hash_from_term(string &term)
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
bool cmp(wstring &s, int i, wstring &word)
{
    if (s.size() - i < word.size())
        return false;
    if (i + word.size() < s.size() && s[i + word.size()] != L' ')
        return false;
    for (int j = 0; j < word.size(); j++)
    {
        if (s[i + j] != word[j])
            return false;
    }
    return true;
}
char Str::utf16_to_utf8(int char_value)
{
    if (0 <= char_value && char_value <= 126)
    {
        if ('A' <= char_value && char_value <= 'Z')
            return (char)(char_value + 'a' - 'A');
        else
            return (char)char_value;
    }
    switch (char_value)
    {
    case 225:
    case 224:
    case 7843:
    case 227:
    case 7841:
    case 259:
    case 7855:
    case 7857:
    case 7859:
    case 7861:
    case 7863:
    case 226:
    case 7845:
    case 7847:
    case 7849:
    case 7851:
    case 7853:
    case 193:
    case 192:
    case 7842:
    case 195:
    case 7840:
    case 258:
    case 7854:
    case 7856:
    case 7858:
    case 7860:
    case 7862:
    case 194:
    case 7844:
    case 7846:
    case 7848:
    case 7850:
    case 7852:
    {
        return 'a';
        break;
    }
    case 233:
    case 232:
    case 7867:
    case 7869:
    case 7865:
    case 234:
    case 7871:
    case 7873:
    case 7875:
    case 7877:
    case 7879:
    case 201:
    case 200:
    case 7866:
    case 7868:
    case 7864:
    case 202:
    case 7870:
    case 7872:
    case 7874:
    case 7876:
    case 7878:
    {
        return 'e';
        break;
    }
    case 417:
    case 7899:
    case 7901:
    case 7903:
    case 7905:
    case 7907:
    case 211:
    case 210:
    case 7886:
    case 213:
    case 7884:
    case 212:
    case 7888:
    case 7890:
    case 7892:
    case 7894:
    case 7896:
    case 416:
    case 7898:
    case 7900:
    case 7902:
    case 7904:
    case 7906:
    case 243:
    case 242:
    case 7887:
    case 245:
    case 7885:
    case 244:
    case 7889:
    case 7891:
    case 7893:
    case 7895:
    case 7897:
    {
        return 'o';
        break;
    }
    case 237:
    case 236:
    case 7881:
    case 297:
    case 7883:
    case 205:
    case 204:
    case 7880:
    case 296:
    case 7882:
    {
        return 'i';
        break;
    }
    case 250:
    case 249:
    case 7911:
    case 361:
    case 7909:
    case 432:
    case 7913:
    case 7915:
    case 7917:
    case 7919:
    case 7921:
    case 218:
    case 217:
    case 7910:
    case 360:
    case 7908:
    case 431:
    case 7912:
    case 7914:
    case 7916:
    case 7918:
    case 7920:
    {
        return 'u';
        break;
    }
    case 253:
    case 7923:
    case 7927:
    case 7929:
    case 7925:
    case 221:
    case 7922:
    case 7926:
    case 7928:
    case 7924:
    {
        return 'y';
        break;
    }
    case 272:
    case 273:
    {
        return 'd';
        break;
    }
    default:
        return '?';
    }
}
wstring Str::remove_by_list_of_words(wstring &raw_str, wstring listwords[], int size_listwords)
{
    //brute
    wstring res = L"";
    for (int i = 0; i < raw_str.size();)
    {
        if (raw_str[i] == ' ')
        {
            if (res[res.size() - 1] != ' ')
                res = res + L" ";
            i++;
            continue;
        }
        int step = 0;
        if (raw_str[i - 1] == L' ')
        {
            for (int j = 0; j < size_listwords; j++)
            {
                if (cmp(raw_str, i, listwords[j]))
                {
                    step = listwords[j].size();
                    break;
                }
            }
        }
        if (!step)
        {
            res = res + raw_str[i];
            step = 1;
        }
        i += step;
    }
    return res;
}
string Str::normalize_wstring(wstring &raw_str)
{
    string tmp = "";
    for (int i = 0; i < raw_str.size(); i++)
    {
        tmp = tmp + utf16_to_utf8(raw_str[i]);
    }
    return tmp;
}