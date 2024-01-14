/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) 
    {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            string pre_word = word;
            sort(word.begin(),word.end());
            //在dict里面？
                //不在
            if(dict.find(word)==dict.end())
            {
                dict[word].push_back(pre_word);
            }
                //在
            else
            {
                dict[word].push_back(pre_word);
            }
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(auto it=words.begin();it!=words.end();it++)
    {
        string word = *it;
        string pre_word = *it;
        sort(word.begin(),word.end());
        //在dict里面？
            //不在
        if(dict.find(word)==dict.end())
        {
            dict[word].push_back(pre_word);
        }
            //在
        else
        {
            dict[word].push_back(pre_word);
        }    
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string sort_word = word;
    sort(sort_word.begin(),sort_word.end());
    if(dict.find(sort_word)==dict.end())
    {
        return vector<string>();
    }
    else
    {
        return dict.find(sort_word)->second;
    }

}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    vector<vector<string>>ret;
    /* Your code goes here! */
    for(auto it=dict.begin();it!=dict.end();it++)
    {
        if(it->second.size()>=2)
            ret.push_back(it->second);
    }
    return ret;//vector<vector<string>>();
}
