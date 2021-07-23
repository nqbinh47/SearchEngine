#ifndef INVERTED_INDEX_H_INCLUDED
#define INVERTED_INDEX_H_INCLUDED
#include "lib.h"
#include "str.h"
#include "linkedlist.h"
struct Info_doc //in4 for document
{
    string doc_name;
    double score;
};
struct Info_ht //in4 for hash_table
{
    string term;
    int hash_term;
    List<Info_doc> list_document;
};
struct Info_qr
{
    string doc_name;
    int termdocs; //number documents have term
    int term_id;
    double score;
};
struct Inverted_index
{
    Info_doc *result;
    int result_size; ////---------NEW--------////
    Info_ht *hash_table;
    int size, totaldocs;
    Inverted_index(int new_size, int new_totaldocs);
    ~Inverted_index(); ////-------CHANGED------////
    void build_Inverted_index(const string &file_path);
    void build_Instant_Inverted_index(const string &file_path, string term[], int number_terms);
    List<Info_doc> *find_doc_by_term(const string &term);
    void gen_TFIDFvector(double vector_doc[], int size_vector, int totaldocs, int termdocs[]);
    double similarity(double vector_doc[], double vector_query[], int size_vector);
    void query(string term[], int number_terms, int N); ////-------CHANGED------////
    void view_topN_doc(int N);                          ////-------CHANGED------////
    bool view_nth_doc(int n, string word[], int nWord); ////---------NEW--------////
};
string get_path_by_name(const string &doc_name); ////---------NEW--------////
bool cmp_ht(Info_ht a, Info_ht b);
bool cmp_doc(Info_doc a, Info_doc b);
bool cmp_qr(Info_qr a, Info_qr b);
template <class T>
void Sort(T a[], int n, bool (*cmp)(T, T));
#endif // INVERTED_INDEX_H_INCLUDED
