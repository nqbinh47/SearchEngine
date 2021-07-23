#include "Header/document.h"
#include "Header/index.h"
#include "Header/lib.h"
using namespace std;
bool remove_file_in_index(const std::string &file_name)
{
    ifstream f_index("..\\Config\\index.txt");
    ofstream f_tmp("..\\Config\\tmp.txt");

    if (!f_index || !f_tmp)
    {
        if (f_index)
            f_index.close();
        if (f_tmp)
            f_tmp.close();
        return 0;
    }

    string buffer;
    bool found = false;
    while (getline(f_index, buffer))
    {
        if (buffer == file_name)
            found = true;
        else
            f_tmp << buffer << endl;
        buffer = "";
    }

    f_index.close();
    f_tmp.close();

    remove("..\\Config\\index.txt");
    rename("..\\Config\\tmp.txt", "..\\Config\\index.txt");

    return found;

    //find and remove path_file in index.txt
    //return true if success else false
}
bool add_file_to_index(const std::string &path_file, int level)
{
    Document I;
    I.addlist_stopwords("..\\Config\\stopwords.txt");
    ofstream f_index("..\\Config\\index.txt", ios::app);
    if (!f_index)
    {
        cout << "LOG: failed to open index.txt\n";
        return false;
    }

    switch (level)
    {
    case 0:
    { //level == 0 => add file    EX: path_file = "file.txt"
        f_index << path_file << endl;
        I.adddocument(path_file);
        break;
    }
    case 1:
    { //level == 1 => add folder/**   EX: path_file = "AMNHAC"
        DIR *dir_pointer = opendir(path_file.c_str());
        dirent *file_pointer;

        if (!dir_pointer)
        {
            cout << "LOG: failed to open directory" << path_file << endl;
            return false;
        }

        cout << "Adding folder " << path_file << "to metadata\n";
        int tmp = 0;
        while ((file_pointer = readdir(dir_pointer)) != nullptr)
        {
            if (tmp >= 2)
            {
                string path = path_file + '\\' + file_pointer->d_name;
                f_index << path << endl;
                I.adddocument(path);
            }

            tmp++;
        }
        break;
    }
    case 2:
    { //level == 2 => add folder/sub_folders/**   EX: path_file = "VanBanTV_Train"
        DIR *dir = opendir(path_file.c_str()), *sub_dir;
        dirent *dir_content, *sub_dir_content;

        if (!dir)
        {
            cout << "LOG: failed to open directory" << path_file << endl;
            return false;
        }

        int tmp = 0;
        while ((dir_content = readdir(dir)) != nullptr)
        {
            if (tmp >= 2)
            {
                string sub_dir_path = path_file + '\\' + dir_content->d_name;
                //OPEN SUB DIR

                sub_dir = opendir(sub_dir_path.c_str());
                if (!sub_dir)
                {
                    cout << "LOG: failed to open sub directory" << sub_dir_path << endl;
                    return false;
                }

                cout << "Adding folder " << sub_dir_path << " to metadata\n";
                int sub_tmp = 0;
                while ((sub_dir_content = readdir(sub_dir)) != nullptr)
                {
                    if (sub_tmp >= 2)
                    {
                        string path = sub_dir_path + '\\' + sub_dir_content->d_name;
                        f_index << path << endl;
                        I.adddocument(path);
                    }

                    sub_tmp++;
                }

                closedir(sub_dir);
            }

            tmp++;
        }

        closedir(dir);
        break;
    }
    }
    //writing(append to index.txt) and update(non rebuild) the dictionary( reference at function[int Document::adddocument(const string &path_file)] in DOCUMENT.H)

    f_index.close();
    return true;
}
bool clear()
{
    ofstream f_index("..\\Config\\index.txt", ios::trunc);
    if (!f_index)
        return false;
    f_index.close();

    DIR *dir = opendir("Dictionary");
    dirent *content;

    if (!dir)
    {
        cout << "LOG: cannot open Dictionary\n";
        return false;
    }

    int tmp = 0;
    while ((content = readdir(dir)) != nullptr)
    {
        if (tmp >= 2)
        {
            string path = "Dictionary\\";
            path = path + content->d_name;
            remove(path.c_str());
        }

        tmp++;
    }

    closedir(dir);
    return true;
    //clear all in index and dictionary
}

bool remove_file_from_metadata(const std::string &file_path, int level)
{
    Document I;
    I.addlist_stopwords("..\\Config\\stopwords.txt");

    switch (level)
    {
    case 0:
    { //REMOVE 1 TEXT FILE
        I.removeDoc(file_path);
        break;
    }
    case 1:
    {
        DIR *dir;
        dirent *dir_content;
        dir = opendir(file_path.c_str());

        if (!dir)
        {
            cout << "LOG: cannot open dir " << file_path << endl;
            return false;
        }

        int tmp = 0;
        while ((dir_content = readdir(dir)) != nullptr)
        {
            if (tmp >= 2)
            {
                string doc_path = file_path + '\\' + dir_content->d_name;
                I.removeDoc(doc_path);
            }
            tmp++;
        }

        closedir(dir);
        break;
    }
    case 2:
    {
        DIR *dir, *sub_dir;
        dirent *dir_content, *sub_dir_content;

        dir = opendir(file_path.c_str());
        if (!dir)
        {
            cout << "LOG: cannot open dir " << file_path << endl;
            return false;
        }

        int tmp = 0;
        while ((dir_content = readdir(dir)) != nullptr)
        {

            if (tmp >= 2)
            {
                cout << "Removing dir " << dir_content->d_name << endl;
                string sub_dir_path = file_path + '\\' + dir_content->d_name;

                sub_dir = opendir(sub_dir_path.c_str());
                if (!sub_dir)
                {
                    cout << "Cannot open dir " << dir_content->d_name << endl;
                    continue;
                }

                int tmp2 = 0;
                while ((sub_dir_content = readdir(sub_dir)) != nullptr)
                {
                    if (tmp2 >= 2)
                    {
                        string doc_path = sub_dir_path + '\\' + sub_dir_content->d_name;
                        I.removeDoc(doc_path);
                    }
                    tmp2++;
                }
                closedir(sub_dir);
            }
            tmp++;
        }

        closedir(dir);
        break;
    }
    }
    return true;
}

int main_index()
{
    //Document I;
    //.createIndexfile("..\\File\\VanBanTV_train");
}
