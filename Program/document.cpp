#include "Header/document.h"
Document::Document()
{
    size_list_stopwords = 0;
    range_score_first = 0.015;
    range_score_second = 0.07;
    dictionary_path = ".\\Dictionary\\";
}
void Document::createIndexfile(const string &data_path)
{

    //data_path = "VanbangTV";
    // ==> train_path = "VanbangTV\\Train\\new train";

    //******INDEX FILE STRUCTURE*******

    /********************************************
    *    <SUB DIR 1 PATH><TAB><SUB DIR 1 NAME>  *
    *    <PATH FILE1.TXT>                       *
    *    <PATH FILE2.TXT>                       *
    *    ...                                    *
    *    <SUB DIR 2 PATH><TAB><SUB DIR 2 NAME>  *
    *    .....                                  *
    *********************************************/

    string train_path = data_path; //GET TRAIN DIR PATH
    const string index_path = "..\\Config\\index.txt";

    ofstream index_file(index_path);
    DIR *dh;
    struct dirent *contents;
    dh = opendir(train_path.c_str());
    if (!dh)
    {
        cout << train_path.c_str() << '\n';
        cout << "Directory not found";
        return;
    }

    int tmp = 0;
    while ((contents = readdir(dh)) != NULL) //GET SUB DIRECTORIES
    {
        string sub_dir_path = train_path + "\\" + contents->d_name;
        if (tmp >= 2)
        {
            //PRINT:  <SUB DIRECTORY PATH> <SUB DIRECTORY NAME>
            //index_file << sub_dir_path << "\t" << contents->d_name << endl;
            //OPEN SUB DIRECTORY
            DIR *sub_dh;
            struct dirent *sub_dir_contents;
            sub_dh = opendir(sub_dir_path.c_str());
            if (!sub_dh)
                cout << "Sub-directory not found\n";
            else
            {
                int tmp2 = 0;
                while ((sub_dir_contents = readdir(sub_dh)) != NULL)
                {
                    if (tmp2 >= 2)
                        //PRINT FILE PATH
                        index_file << sub_dir_path << "\\" << sub_dir_contents->d_name << endl;
                    tmp2++;
                }
                closedir(sub_dh);
            }
        }
        tmp++;
    }
    closedir(dh);
    index_file.close();
}
char Document::utf16_to_utf8(int char_value)
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
bool Document::isImportant(double score)
{
    if (score > range_score_second || score < range_score_first)
        return false;
    return true;
}
bool Document::fileisEmpty(const string &path_file)
{
    ifstream fin(path_file);
    if (!fin)
    {
        return true;
    }
    bool empty = (fin.get(), fin.eof());
    fin.close();
    return empty;
}
string Document::get_docname(const string &path_file)
{
    int i;
    for (i = path_file.size() - 1; i >= 0; i--)
    {
        if (path_file[i] == '\\')
            break;
    }
    return path_file.substr(i + 1, path_file.size() - 1 - i);
}
bool Document::filter(char char_value)
{
    if (char_value == '?' || char_value == '.' || char_value == ',' || char_value == ':' || char_value == '(' || char_value == ')' ||
        char_value == '{' || char_value == '}' || char_value == '"' || char_value == '\'' || char_value == '!' || char_value == ';' ||
        char_value == '-' || char_value == '/' || char_value == '+' || char_value == '*' || char_value == '_' || char_value == '[' ||
        char_value == ']' || char_value == '=' || char_value == '#' || char_value == '@' || char_value == '$' || char_value == '&' ||
        char_value == '|')
        return false;
    return true;
}
int Document::adddocument(const string &path_file)
{
    std::wifstream fin(path_file, std::ios::binary);
    fin.imbue(std::locale(fin.getloc(),
                          new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
    wstring raw_str = L"";
    for (wchar_t c; fin.get(c);)
    {
        if (c == 13)
        {
            //skip end line
            fin.get(c);
            if (raw_str[raw_str.size() - 1] != L' ')
                raw_str = raw_str + L' ';
            continue;
        }
        char c8 = utf16_to_utf8(c);
        if (!filter(c8))
        {
            if (raw_str[raw_str.size() - 1] != L' ')
                raw_str = raw_str + L' ';
            continue;
        }
        if ((c == L' ' && raw_str[raw_str.size() - 1] != L' ') || (c != L' '))
            raw_str = raw_str + c;
    }
    Str s;
    string clean_str;
    //remove_stop_words
    raw_str = s.remove_by_list_of_words(raw_str, list_stopwords, size_list_stopwords);
    //normalize
    clean_str = s.normalize_wstring(raw_str);
    //cout << clean_str << '\n';
    //init Info array with source: clean_str
    s.init(clean_str);
    //get term and occurence of term
    s.sortInfoarray();
    int cnt = 1;
    int tmp_size = 1;
    for (int i = 1; i < s.size; i++)
    {
        if (s.array[i].hash_term != s.array[i - 1].hash_term)
        {
            tmp_size++;
            //add term to dictionary
            addterm2dictionary(s.array[i - 1].term, s.array[i - 1].hash_term, cnt, get_docname(path_file), s.size);
            cnt = 1;
            continue;
        }
        cnt++;
    }
    addterm2dictionary(s.array[s.size - 1].term, s.array[s.size - 1].hash_term, cnt, get_docname(path_file), s.size);
    fin.close();
    return s.size;
}

bool Document::removeDoc(const string &doc_path)
{
    remove_file_in_index(doc_path);
    string doc_name = get_docname(doc_path);

    std::wifstream fin(doc_path, std::ios::binary);
    fin.imbue(std::locale(fin.getloc(),
                          new std::codecvt_utf16<wchar_t, 0x10ffff, std::codecvt_mode(std::consume_header | std::little_endian)>));
    wstring raw_str = L"";
    for (wchar_t c; fin.get(c);)
    {
        if (c == 13)
        {
            fin.get(c);
            if (raw_str[raw_str.size() - 1] != L' ')
                raw_str = raw_str + L' ';
            continue;
        }
        char c8 = utf16_to_utf8(c);
        if (!filter(c8))
        {
            if (raw_str[raw_str.size() - 1] != L' ')
                raw_str = raw_str + L' ';
            continue;
        }
        if ((c == L' ' && raw_str[raw_str.size() - 1] != L' ') || (c != L' '))
            raw_str = raw_str + c;
    }
    Str s;
    string clean_str;
    raw_str = s.remove_by_list_of_words(raw_str, list_stopwords, size_list_stopwords);
    clean_str = s.normalize_wstring(raw_str);
    s.init(clean_str);
    s.sortInfoarray();
    //cout << "Done info array\n";

    int occurence = 1;
    for (int i = 1; i < s.size; i++)
    {
        if (s.array[i].hash_term != s.array[i - 1].hash_term)
        {
            if (isImportant(occurence * 1.0 / s.size))
                removeDocByTerm(s.array[i - 1].term, doc_name);
            occurence = 1;
        }
        else
            occurence++;
    }
    if (isImportant(occurence * 1.0 / s.size))
        removeDocByTerm(s.array[s.size - 1].term, doc_name);

    fin.close();
    return true;
}

void Document::removeDocByTerm(const string &term, const string &doc_name)
{
    string term_file_path = "Dictionary\\_" + term + ".dat";

    ifstream term_file(term_file_path);
    if (!term_file)
        return;

    string term_info, doc_line, score_line;
    getline(term_file, term_info);
    getline(term_file, doc_line);

    if (doc_line == "\n")
    {
        //NO DOCS IN FILE
        term_file.close();
        remove(term_file_path.c_str());
        return;
    }

    //NOT END OF FILE
    ofstream temp_file("Dictionary\\temp.dat");
    temp_file << term_info << endl;
    /////cout << term_info << endl;
    do
    {
        getline(term_file, score_line);
        if (doc_line == doc_name)
            continue;
        //else
        temp_file << doc_line << endl
                  << score_line << endl;
        /////cout << doc_line << endl << score_line << endl;
    } while (getline(term_file, doc_line) && doc_line[0] != '\n');

    term_file.close();
    temp_file.close();

    remove(term_file_path.c_str());
    rename("Dictionary\\temp.dat", term_file_path.c_str());
}

void Document::addlist_stopwords(const string &path_file)
{
    std::wifstream fin(path_file, std::ios::binary);
    fin.imbue(std::locale(fin.getloc(),
                          new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
    wstring tmp = L"";
    wchar_t dump;
    fin.get(dump);
    for (wchar_t c; fin.get(c);)
    {
        if (c == 13)
        {
            fin.get(c);
            //A word have done
            list_stopwords[size_list_stopwords++] = tmp;
            //
            tmp = L"";
            continue;
        }
        tmp = tmp + c;
    }
    list_stopwords[size_list_stopwords++] = tmp;
    fin.close();
}
void Document::addterm2dictionary(string &term, int64_t hash_term, int occurence, const string &doc_name, int number_words_in_doc)
{
    if (term.size() == 1 && term[0] == 0)
        return;
    string name_file_term = dictionary_path + "\\_" + term + ".dat";
    double score = occurence * 1.0 / number_words_in_doc;
    if (!isImportant(score))
        return;
    if (fileisEmpty(name_file_term))
    {
        ofstream fout(name_file_term);
        fout << term << ' ' << hash_term << '\n';
        fout.close();
    }
    ofstream fout(name_file_term, ios_base::app);
    fout << doc_name << '\n'
         << score << '\n';
    fout.close();
    return;
}
int Document::countfileinindex()
{
    string path_file = "..\\Config\\index.txt ";
    ifstream fin(path_file);
    string s;
    int size = 0;
    while (getline(fin, s))
    {
        size++;
    }
    return size;
}
int Document::countfileinfolder(const string &path_file)
{
    DIR *dp;
    int cnt = 0;
    struct dirent *ep;
    dp = opendir(path_file.c_str());

    if (dp != NULL)
    {
        while (ep = readdir(dp))
            cnt++;

        (void)closedir(dp);
    }
    else
        return -1;

    return cnt;
}
