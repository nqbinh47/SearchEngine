#include "Header/lib.h"
#include "Header/document.h"
#include "Header/str.h"
#include "Header/linkedlist.h"
#include "Header/inverted_index.h"
#include "Header/query.h"
using namespace std;
int main()
{
    cout << "|--------------------------THERE ARE TWO OPTIONS FOR SEARCHING----------------------------------------------------|\n"
         << "|      \t[1] LOADING ALL METADATA TO SEARCH                                                                        |\n"
         << "|         \t *Recommend to search a large amount of queries, it will not reload but it takes a bit time       |\n"
         << "|      \t[2] LOADING NECESSARY METEDATA TO SEARCH                                                                  |\n"
         << "|         \t *Recommend to search an individual query                                                         |\n"
         << "|-----------------------------------------------------------------------------------------------------------------|\n";
    cout << "ENTER YOUR CHOICE [1 or 2]:     ";
    int option_load;
    cin >> option_load;
    cout << "\t----------LOADING DATA----------\n";
    Document I;
    int cnt_file = I.countfileinfolder("Dictionary\\");
    int total_file = I.countfileinindex();
    Inverted_index Invid(cnt_file, total_file);
    if (option_load == 1)
        Invid.build_Inverted_index("Dictionary\\");
    cout << "DONE\n";

    while (true)
    {
        system("cls");
        cin.clear();
        fflush(stdin);

        //GET LIST OF TERMS

        string word[1005];
        int nWord = 0;
        string tmp;
        cout << "\t-------------ENTER QUERY PHRASE (<= 1000 WORDS)-------------\n";
        cin.ignore(0);
        getline(cin, tmp);
        size_t sstart = 0, send = tmp.size() - 1;

        while (tmp[sstart] == ' ' || !I.filter(tmp[sstart]))
            sstart++;
        while (tmp[send] == ' ' || !I.filter(tmp[send]))
            send--;

        for (size_t i = sstart; i <= send; i++)
        {
            if (!I.filter(tmp[i]) || tmp[i] == ' ')
            {
                if (tmp[i + 1] != ' ' && I.filter(tmp[i + 1]))
                    nWord++;
            }
            else if ('A' <= tmp[i] && tmp[i] <= 'Z')
                word[nWord] = word[nWord] + (char)(tmp[i] + 'a' - 'A');
            else
                word[nWord] = word[nWord] + tmp[i];
        }
        nWord++;
        ///
        ///
        cout << "\t-------------ENTER NUMBER OF DOCS (BETWEEN 10 AND 100)-------------\n\t\t\t\t\t";
        int nDoc;
        cin >> nDoc;
        cout << "---------------------------------------------------------------------\n";
        if (nDoc >= 100)
            nDoc = 100;
        else if (nDoc <= 10)
            nDoc = 10;
        if (option_load == 2)
            Invid.build_Instant_Inverted_index("Dictionary\\", word, nWord);
        Invid.query(word, nWord, nDoc);
        Invid.view_topN_doc(nDoc);
        cout << "---------------------------------------------------------------------\n";

        ///
        bool done = false;
        while (!done)
        {
            cout << "\t\t|-----------------------------------------|\n"
                 << "\t\t|      \t*ENTER YOUR CHOICE:               |\n"
                 << "\t\t| -2   \tEXIT PROGRAM                      |\n"
                 << "\t\t| -1   \tSEARCH ANOTHER PHRASE             |\n"
                 << "\t\t|  0   \tVIEW SEARCH RESULT                |\n"
                 << "\t\t| 1-" << nDoc << "\tVIEW DOC NUMBER ...               |\n"
                 << "\t\t|-----------------------------------------|\n";
            int choice;
            cin >> choice;
            cout << "---------------------------------------------------------------------\n";

            while (choice < -2 || choice > nDoc)
            {
                cout << "\t\t|-----------------------------------------|\n"
                     << "\t\t|      \t**WRONG CHOICE!                   |\n"
                     << "\t\t|      \t*PLEASE RE-ENTER YOUR CHOICE:     |\n"
                     << "\t\t| -2   \tEXIT PROGRAM                      |\n"
                     << "\t\t| -1   \tSEARCH ANOTHER PHRASE             |\n"
                     << "\t\t|  0   \tVIEW SEARCH RESULT                |\n"
                     << "\t\t| 1-" << nDoc << "\tVIEW DOC NUMBER ...               |\n"
                     << "\t\t|-----------------------------------------|\n";
                cin >> choice;
                cout << "---------------------------------------------------------------------\n";
            }

            switch (choice)
            {
            case -2:
            {
                return 0;
                break;
            }
            case -1:
            {
                done = true;
                break;
            }
            case 0:
            {
                Invid.view_topN_doc(nDoc);
                cout << "---------------------------------------------------------------------\n";
                break;
            }
            default:
            {
                Invid.view_nth_doc(choice, word, nWord);
                cout << "---------------------------------------------------------------------\n";
                continue;
            }
            }
        }
    }
}