#include "Header/document.h"
using namespace std;
int main()
{
    Document I;
    I.addlist_stopwords("..\\Config\\stopwords.txt");
    ifstream fin("..\\Config\\index.txt");
    cout << "==========EXTRACTING METADATA FROM INDEX.TXT==========\n1%\n";
    int prev = 0, cnt_file = 0, amount = I.countfileinindex();
    string path;
    while (getline(fin, path))
    {
        I.adddocument(path);
        cnt_file++;
        int percent = cnt_file * 100 / amount;
        if (percent != prev && percent % 5 == 0)
        {
            cout << percent << "%\n";
        }
        prev = cnt_file * 100 / amount;
        if (cnt_file == amount)
            break;
    }
    cout << "COMPLETE!!\n";
    fin.close();
}
