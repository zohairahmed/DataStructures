/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        for (unsigned j = 0; j < words.size(); j++){
          auto w = file_word_maps[i].find(words[j]);
          if (w != file_word_maps[i].end()){
            w->second++;
          }
          else {
            file_word_maps[i][words[j]] = 1;
          }
        }
        /* Your code goes here! */
    }
}

void CommonWords::init_common()
{
    for (unsigned i = 0; i < file_word_maps.size(); i++){
      for (std::pair<string, unsigned> p : file_word_maps[i]){
        auto w = file_word_maps[i].find(p.first);
        if (w != file_word_maps[i].end()){
          common[w->first]++;
        }
        else {
          common[w->first] = 1;
        }
      }
    }
    /* Your code goes here! */
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    for (std::pair<string, unsigned> p : common){
      if (p.second == file_word_maps.size()){
        bool nTimes = true;
        for (unsigned j = 0; j < file_word_maps.size() && nTimes; j++){
          if (file_word_maps[j].at(p.first) < n){
            nTimes = false;
          }
        }
        if (nTimes)
          out.push_back(p.first);
      }
    }
    /* Your code goes here! */
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
