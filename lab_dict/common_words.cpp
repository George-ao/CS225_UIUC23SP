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

std::string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        IsPunct());
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
        /* Your code goes here! */
        for(size_t j =0;j<words.size();j++)
        {
            if(file_word_maps[i].find(words[j])==file_word_maps[i].end())
            {
                file_word_maps[i].emplace(words[j],1);
                continue;
            }
            file_word_maps[i][words[j]]++;
        }
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
    for(size_t i=0; i<file_word_maps.size(); i++)
    {
        for(map<string, unsigned int>::iterator it=file_word_maps[i].begin();it!=file_word_maps[i].end();it++)
        {
            //word not in common before
            if(common.find(it->first)==common.end())
            {
                common[it->first]  = it->second;
            }
            //find word and renew when new value is smaller
            else
            {
                if(common[it->first]>it->second)
                {
                    common[it->first] = it->second;
                }
            }
        }
    }
    //check the common because some words do not exists in every file
    for(auto it=common.begin();it!=common.end();it++)
    {
        //in every file
        for(size_t i=0; i<file_word_maps.size(); i++)
        {
            if(file_word_maps[i].find(it->first)==file_word_maps[i].end())
            {
                common[it->first] = 0;
                break;
            }
        }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */


    // for(size_t i=0; i<common.size(); i++)
    // {
        //vector<string> words = file_to_vector(filenames[i]);
        for(auto it=common.begin();it!=common.end();it++)
        {
            // not smaller than n
            if(it->second>=n)
            {
                out.push_back(it->first);
            }
        }
    // }
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
