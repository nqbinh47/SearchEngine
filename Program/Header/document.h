#pragma once
#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED
#include "lib.h"
#include "str.h"
#include "index.h"
using namespace std;
//need update filter
//need lowercase rieng => add_document
struct Document
{
    double range_score_first, range_score_second;
    wstring list_stopwords[3005];
    int size_list_stopwords;
    string dictionary_path;
    Document();
    void createIndexfile(const string &path_file);
    char utf16_to_utf8(int char_value);
    bool isImportant(double score);
    bool fileisEmpty(const string &path_file);
    string get_docname(const string &path_file);
    bool filter(char char_value);
    int adddocument(const string &path_file);
    bool removeDoc(const string &doc_path);                           //-------NEW-------//
    void removeDocByTerm(const string &term, const string &doc_name); //-------NEW-------//
    void addlist_stopwords(const string &path_file);
    void addterm2dictionary(string &term, int64_t hash_term, int occurence, const string &doc_name, int number_words_in_doc);
    int countfileinindex();
    int countfileinfolder(const string &path_file);
};
#endif // DOCUMENT_H_INCLUDED
