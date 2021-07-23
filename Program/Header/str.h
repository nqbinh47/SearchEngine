#pragma once
#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED
#include "lib.h"
#include "document.h"
using namespace std;
struct Info
{
    string term;
    int64_t hash_term;
};
bool cmp_Info(Info &word_1, Info &word_2);
struct Str
{
    Info *array;
    int size;
    Str();
    ~Str();
    int get_number_words(string &clean_str);
    void init(string &clean_str);
    void sortInfoarray();
    int64_t get_hash_from_term(string &term);
    char utf16_to_utf8(int char_value);
    wstring remove_by_list_of_words(wstring &raw_str, wstring listwords[], int size_listwords);
    string normalize_wstring(wstring &raw_str);
};
#endif // STR_H_INCLUDED