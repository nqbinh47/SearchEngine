#ifndef INDEX_H_INCLUDED
#define INDEX_H_INCLUDED
#include <string>

bool remove_file_in_index(const std::string &file_name);
bool add_file_to_index(const std::string &path_file, int level);
bool remove_file_from_metadata(const std::string &file_path, int level); //-------NEW-------//
bool clear();
int main_index();

#endif // INDEX_H_INCLUDED
