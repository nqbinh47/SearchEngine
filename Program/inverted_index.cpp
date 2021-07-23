#include "Header/inverted_index.h"
#include "Header/str.h"
bool cmp_ht(Info_ht a, Info_ht b)
{
    return (a.hash_term <= b.hash_term);
}
bool cmp_doc(Info_doc a, Info_doc b)
{
    return (a.score >= b.score);
}
Inverted_index::Inverted_index(int new_size, int new_totaldocs)
{
    size = new_size;
    totaldocs = new_totaldocs;
    hash_table = new Info_ht[size];
}
Inverted_index::~Inverted_index()
{
    if (hash_table)
        delete[] hash_table;
    if (result) //----CHANGED
        delete[] result;
}
//need to the add instant search feature
void Inverted_index::build_Inverted_index(const string &file_path) // this is build all then search feature
{
    DIR *dh;
    struct dirent *contents;
    dh = opendir(file_path.c_str());
    if (!dh)
        return;
    int id = 0, pre = 0;
    while ((contents = readdir(dh)) != NULL) //GET SUB DIRECTORIES
    {
        if (strlen(contents->d_name) < 3)
            continue;

        string file_term_name = contents->d_name;
        string sub_path = file_path + file_term_name;
        ifstream fin(sub_path);
        if (!fin)
        {
            //error
            continue;
        }
        string term, doc_name;
        int hash_term;
        double score = 0.1;
        fin >> term >> hash_term;
        hash_table[id].term = term;
        hash_table[id].hash_term = hash_term;
        fin.ignore();
        while (getline(fin, doc_name) && (fin >> score))
        {
            hash_table[id].list_document.AddHead(Info_doc{doc_name, score});
            fin.ignore();
        }
        id++;
        // if(id > 50) break;
        // /*TEXT*/
        // if(id * 100 / size != pre)
        // {
        //     cout << id * 100 / size << "%\n";
        // }
        // pre = id * 100 / size;
        /*TEXT*/
        fin.close();
    }
    size = id;
    closedir(dh);
    //sort
    Sort(hash_table, size, cmp_ht);
    return;
}
void Inverted_index::build_Instant_Inverted_index(const string &file_path, string term[], int number_terms)
{
    int id = 0, pre = 0;
    for (int i = 0; i < number_terms; i++)
    {
        int t_id = 0;
        char sub_path[205];
        const char *tmp = term[i].c_str();
        for (int j = 0; j < file_path.size(); j++)
            sub_path[t_id++] = file_path[j];
        sub_path[t_id++] = '_';
        for (int j = 0; j < strlen(tmp); j++)
            sub_path[t_id++] = tmp[j];
        sub_path[t_id++] = '.';
        sub_path[t_id++] = 'd';
        sub_path[t_id++] = 'a';
        sub_path[t_id++] = 't';
        sub_path[t_id++] = '\0';
        ifstream fin(sub_path);
        if (!fin)
        {
            //cout << sub_path << ' ' << "ERROR\n";
            //error
            continue;
        }
        //cout << sub_path << ' ' << "OPEN SUCCESSFULLY\n";
        string term, doc_name;
        int hash_term;
        double score = 0.1;
        fin >> term >> hash_term;
        hash_table[id].term = term;
        hash_table[id].hash_term = hash_term;
        fin.ignore();
        while (getline(fin, doc_name) && (fin >> score))
        {
            //cout << doc_name << ' ' << score << '\n';
            hash_table[id].list_document.AddHead(Info_doc{doc_name, score});
            fin.ignore();
        }
        id++;
        fin.close();
    }
    size = id;
    //cout << "SIZE " << size << ' ' << id << '\n';
    //sort
    Sort(hash_table, size, cmp_ht);
    return;
}
List<Info_doc> *Inverted_index::find_doc_by_term(const string &term)
{
    //find term in hash_table
    int l = 0, r = size - 1;
    List<Info_doc> *res = nullptr;
    int64_t hash_term = hash_fr_term(term);
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (hash_table[mid].hash_term <= hash_term)
        {
            if (hash_table[mid].hash_term == hash_term)
            {
                res = &hash_table[mid].list_document;
            }
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return res;
}
bool cmp_qr(Info_qr a, Info_qr b)
{
    if (a.doc_name == b.doc_name)
        return (a.term_id <= b.term_id);
    return (a.doc_name < b.doc_name);
}
//need set include string and occurence
void Inverted_index::query(string term[], int number_terms, int N = 10) //term is uniQue
{
    if (result)          /*  CHANGED    */
        delete[] result; /*  DELETE PREVIOUS RESULT  */

    int *termdocs = new int[number_terms];
    int total_size = 0;
    for (int i = 0; i < number_terms; i++)
    {
        List<Info_doc> *li = find_doc_by_term(term[i]);
        //mix all lists
        if (li)
        {
            total_size += li->size;
            termdocs[i] = li->size;
        }
        else
        {
            termdocs[i] = 0;
        }
    }
    Info_qr *mixli = new Info_qr[total_size];
    int id = 0;
    for (int i = 0; i < number_terms; i++)
    {
        List<Info_doc> *li = find_doc_by_term(term[i]);
        //mix all lists
        if (li)
        {
            //travelsal in each list to add
            for (Node<Info_doc> *cursor = (li->head)->next; cursor != nullptr; cursor = cursor->next)
            {
                mixli[id++] = Info_qr{(cursor->data).doc_name, li->size, i, (cursor->data).score};
                //cout << (cursor->data).doc_name << ' ' << (cursor->data).score << '\n';
            }
        }
    }
    /*VECTOR*/
    //create_vector_doc, vector_query
    double *vector_doc = new double[number_terms];
    double *vector_query = new double[number_terms];
    //set vector_query
    //***************************************************************************************************//
    for (int i = 0; i < number_terms; i++)
        vector_query[i] = 1.0 / number_terms;
    gen_TFIDFvector(vector_query, number_terms, totaldocs, termdocs);
    /*VECTOR*/
    Sort(mixli, total_size, cmp_qr);
    Info_doc *top_docs = new Info_doc[total_size];
    int _id = 0;
    for (int i = 0; i < total_size;)
    {
        //reset vector to 0
        for (int j = 0; j < number_terms; j++)
            vector_doc[j] = 0;

        string name = mixli[i].doc_name;
        while (i < total_size && mixli[i].doc_name == name)
        {
            vector_doc[mixli[i].term_id] = mixli[i].score;
            i++;
        }
        //gen_vector_TFIDF
        gen_TFIDFvector(vector_doc, number_terms, totaldocs, termdocs);
        //similarity
        //cout << similarity(vector_doc, vector_query, number_terms) << '\n';
        top_docs[_id++] = Info_doc{name, similarity(vector_doc, vector_query, number_terms)};
    }
    Sort(top_docs, _id, cmp_doc);
    //view_topN_doc(top_docs, min(_id, N));
    if (mixli)
        delete[] mixli;
    if (vector_doc)
        delete[] vector_doc;
    if (vector_query)
        delete[] vector_query;
    if (termdocs)
        delete[] termdocs;
    result = top_docs;        /*     CHANGED     */
    result_size = total_size; /*  STORE RESULT   */
    //if (top_docs)
    //delete[] top_docs;
    return;
}

void Inverted_index::view_topN_doc(int N)
{ //CHANGED
    if (N <= 0)
        return;
    if (N > result_size)
        N = result_size;

    cout << "\tTOP " << N << " DOCUMENTS \n";

    for (int i = 0; i < N; i++)
    {
        cout << '#' << i + 1 << '\t' << result[i].doc_name << ' ' << result[i].score << '\n';
    }

    return;
}
void Inverted_index::extract_doc_to_file(int N)
{
    ofstream fout("logdoc.txt");
    fout << N << '\n';
    for (int i = 0; i < N; i++)
    {
        fout << result[i].doc_name << '\n';
        fout << result[i].score << '\n';
    }
    fout.close();
}
bool Inverted_index::view_nth_doc(int n, string word[], int nWord)
{ //NEW
    if (n > result_size || n <= 0)
        return false;
    string file_name = result[n - 1].doc_name;
    string file_path = get_path_by_name(file_name);
    cout << "\t-------------VIEWING DOC " << file_name << "-------------\n";
    std::wifstream fin(file_path, std::ios::binary);
    if (!fin)
    {
        cout << "LOG: Cannot open file " << file_path << endl;
        return false;
    }
    fin.imbue(std::locale(fin.getloc(),
                          new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
    wchar_t dump;
    fin.get(dump);
    string normalized_string;
    Str s;
    for (wchar_t c; fin.get(c);)
    {
        normalized_string = normalized_string + s.utf16_to_utf8(c);
    }
    normalized_string += ' ';
    //cout << normalized_string << endl;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //-----HIGHLIGHT TEXT USING COLOR - WORKS ON WINDOWS ONLY
    for (size_t i = 0; i < normalized_string.size(); i++)
    {
        if ((normalized_string[i] >= '0' && normalized_string[i] <= '9') || (normalized_string[i] >= 'a' && normalized_string[i] <= 'z'))
        {

            if (i > 0 && normalized_string[i - 1] != ' ')
            {
                cout << normalized_string[i];
                continue;
            }
            bool match;
            for (int j = 0; j < nWord; j++)
            {
                if (i + word[j].size() <= normalized_string.size())
                {
                    //compare
                    match = true;
                    for (size_t t = 0; t < word[j].size(); t++)
                    {
                        if (word[j][t] != normalized_string[i + t])
                        {
                            match = false;
                            break;
                        }
                    }
                    //highlight
                    char next_char = normalized_string[i + word[j].size()];
                    if (match && !((next_char >= '0' && next_char <= '9') || (next_char >= 'a' && next_char <= 'z')))
                    { //SECOND CONDITION: EXACT MATCH

                        SetConsoleTextAttribute(hConsole, 10);
                        cout << word[j]; /*  TEXT HIGHLIGHTED HERE  */
                        SetConsoleTextAttribute(hConsole, 7);

                        i += word[j].size() - 1;
                        break;
                    }
                    //
                }
            }

            if (!match)
                cout << normalized_string[i];
        }
        else
        {
            cout << normalized_string[i];
        }
    }

    SetConsoleTextAttribute(hConsole, 7);
    fin.close();
    return true;
}

void Inverted_index::gen_TFIDFvector(double vector_doc[], int size_vector, int totaldocs, int termdocs[])
{
    for (int i = 0; i < size_vector; i++)
    {
        double IDF = 1 + log(totaldocs * 1.0 / (termdocs[i] + 1));
        double tmp = vector_doc[i] * IDF;
        //cout << vector_doc[i] << '\n';
        //cout << "WORD " << i << ' ' << termdocs[i] << ' ' << IDF << ' ' << vector_doc[i] << ' ' << vector_doc[i] * IDF << '\n';
        vector_doc[i] = tmp;
    }
    return;
}
double Inverted_index::similarity(double vector_doc[], double vector_query[], int size_vector)
{
    double dot_product = 0, len_vector_doc = 0, len_vector_query = 0;
    for (int i = 0; i < size_vector; i++)
    {
        dot_product += vector_doc[i] * vector_query[i];
        len_vector_doc += vector_doc[i] * vector_doc[i];
        len_vector_query += vector_query[i] * vector_query[i];
    }
    len_vector_doc = sqrt(len_vector_doc);
    len_vector_query = sqrt(len_vector_query);
    return dot_product / (len_vector_doc * len_vector_query);
}

string get_path_by_name(const string &doc_name)
{ //------NEW
    ifstream f_index("..\\Config\\index.txt");
    if (!f_index)
        return "";

    string line;
    while (getline(f_index, line))
    {
        if (line.size() < doc_name.size())
            continue;
        size_t size_dif = line.size() - doc_name.size();

        bool match = true;
        for (size_t i = 0; i < doc_name.size(); i++)
        {
            if (doc_name[i] != line[size_dif + i])
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            f_index.close();
            return line;
        }
    }

    f_index.close();
    return "";
}

template <class T>
int partition(T arr[], int low, int high, bool (*cmp)(T, T))
{
    T pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (cmp(arr[j], pivot))
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
template <class T>
void quickSort(T arr[], int low, int high, bool (*cmp)(T, T))
{
    if (low < high)
    {
        int pi = partition(arr, low, high, cmp);
        quickSort(arr, low, pi - 1, cmp);
        quickSort(arr, pi + 1, high, cmp);
    }
}
template <class T>
void Sort(T arr[], int n, bool (*cmp)(T, T))
{
    quickSort(arr, 0, n - 1, cmp);
}
