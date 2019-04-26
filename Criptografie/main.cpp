#include <iostream>
#include <cstdlib>
#include <string.h>
#include <map>
#include <fstream>
#include "Huffman.h"
using namespace std;

char* getFileContent(char* path);
map<char, int> getSentenceFrequence(char* sentence);
map<char, float> calculateFrequency(map<char, int> w, int length);


char* getFileContent(char* path)
{
    ifstream file(path, ifstream::in);
    char* line = new char[5000];
    char* content = new char[50000];
    while( !file.eof() )
    {
        file>>line;
        strcat(content, line);
    }
    file.close();
    return content;
}

map<char,int> getSentenceFrequence(char* sentence)
{
    map<char,int> w;

    for(int i = 0; i < strlen(sentence); i++)
    {
        if(isalpha(sentence[i]))
            w[sentence[i]] = 0;
    }


    for(int i = 0; i <  strlen(sentence); i++)
    {
        if( isalpha(sentence[i]) )
            w[sentence[i]]++;
    }
    return w;
}

map<char,float> calculateFrequency( map<char,int> w, int length)
{
    map<char,float> freq;
    for(map<char,int>::iterator it = w.begin(); it != w.end(); ++it)
    {
        freq[it->first] = (float)it->second/length;
    }
    return freq;
}

int main()
{
    ofstream result("result.txt");
    char* content = getFileContent( "text.txt" );

    map<char,int> ww;
    ww = getSentenceFrequence( content );
    result << "Frecvente : " << endl;
    for(map<char,int>::iterator it = ww.begin(); it != ww.end(); ++it)
    {
        result << it->first << " " << it->second << endl;
    }
    result << endl;
    result << "Distributia: " << endl;
    map<char, float> freq = calculateFrequency(ww, strlen(content));
    for(map<char,float>::iterator it = freq.begin(); it != freq.end(); ++it)
    {
        result << it -> first << " " << it->second << endl;
    }

    int index = 0;
    char* letters = new char[ ww.size() ];
    int* frequence = new int[ ww.size() ];

    for(map<char, int>::iterator it = ww.begin(); it != ww.end(); ++it)
    {
        letters[index] = it->first;
        frequence[index] = it->second;
        index++;
    }

    result << endl;
    codes = new char*[ww.size()];
    for(int i = 0; i < ww.size(); i++)
        codes[i] =  new char[100];

    HuffmanCodes(letters, frequence, ww.size());

    result << "Coduri : " << endl;
    map<char, string> message_to_code;
    for(int i = 0; i < ww.size(); i++)
    {
        message_to_code[ letters[i] ] = codes[i];
        result << letters[i] << " : " << message_to_code[ letters[i] ] << endl;
    }
    result << endl;

    char* compressed = new char[50000];
    result << "Mesaj compresat: " << endl;
    char* code[50];
    for(int i = 0; i < strlen(content); i++)
    {
        for(map<char,string>::iterator it = message_to_code.begin(); it != message_to_code.end(); ++it)
        {
            if( content[i] == it->first)
                result << it->second;
        }
    }

    map<string, char> code_to_message;
    for(int i = 0; i < ww.size(); i++)
    {
        code_to_message[ codes[i] ] = letters[i];
    }

    result << endl;
    result << endl;
    result << "Mesaj decompresat: " << endl;
    for(int i = 0; i < strlen(content); i++)
    {
        for(map<char,string>::iterator it = message_to_code.begin(); it != message_to_code.end(); ++it)
        {
            for(map<string,char>::iterator it2 = code_to_message.begin(); it2 != code_to_message.end(); ++it2)
            {
                if( content[i] == it->first && it->first == it2->second)
                {
                    result << it2->second;
                }
            }
        }
    }
    result.close();
    return 0;
}
