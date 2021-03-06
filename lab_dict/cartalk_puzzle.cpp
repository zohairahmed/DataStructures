/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            // cout << word << endl;
            if (word.size() > 2){
              string word1 = word.substr(1);
              string word2 = word.substr(0,1) + word.substr(2);
              // std::transform(word.begin(), word.end(), word.begin(), ::toupper);
              // std::transform(word1.begin(), word1.end(), word1.begin(), ::toupper);
              // std::transform(word2.begin(), word2.end(), word2.begin(), ::toupper);
              if (d.homophones(word, word1) && d.homophones(word, word2))
                ret.push_back(std::make_tuple(word, word1, word2));
            }
        }
    }
    /* Your code goes here! */
    return ret;
}
