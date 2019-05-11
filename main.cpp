/*************************************
 *  ARAB_TEXT_TO_UNICODE_CONVERTER
 *  AUTHOR  :   alahem monsef
 *  EMAIL   :   m.alahem09@gmail.com
 *  VERSION :   0.1
 *  DATE    :   10-05-2019
 *
 *************************************/

#include <iostream>
//#include <cstdlib>
#include <string>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


//global variables
typedef struct arab_line_t {
    unsigned char in_byte[50];
    size_t bytes;
    uint32_t in_utf[50];
    size_t utfs;
} arab_line_t;

//pointer variables
std::ifstream ifs("arabic_test.txt");
std::wofstream  wofs("utf_code.txt");

#include "utf8.h"
#include "arabtype.h"

using namespace std;

int read_line(arab_line_t *line)
{
    //lecture fichier
    int i=0;
    while( ifs.good() )
    {
        unsigned char ch = ifs.get();
        if (ifs.good())
            line->in_byte[i] = ch;
        i++;
        if(ch == '\n')
            break;
    }
    line->bytes = i-1;
    line->in_utf[0] = 0;
    line->utfs = line->bytes*4;

}

int reverse_line(arab_line_t *line)
{
    uint32_t revsed_line[50];
    int i;
    int j = line->utfs -1;
    //copier la ligne a inverser
    for (i = 0 ; i < line->utfs ; i++) {
        revsed_line[j] = line->in_utf[i];
        j--;
    }
    for (i = 0 ; i < line->utfs ; i++) {
        //printf("rev : %x\n", revsed_line[i]);
        line->in_utf[i] = revsed_line[i]; 
    }
}

int write_line(arab_line_t *line)
{

    for( int i = 0; i < line->utfs; ++i ) {
        if (line->in_utf[i] == ' ') {
            wofs << " ";
        } else {
            wofs << "\\u" << std::hex << line->in_utf[i];
        }
    }
}

int correct(arab_line_t *line)
{
    for( int i = 0; i < line->utfs; i++ )
    {
        ///raaa
        if (line->in_utf[i] == 0xfeae)
            line->in_utf[i] = 0xfead;
        ///zaaa
        if (line->in_utf[i] == 0xfeb0)
            line->in_utf[i] = 0xfeaf;
        ///fAA
        if (line->in_utf[i] == 0xfed2)
            line->in_utf[i] = 0xfed1;
        ///qaf
        if (line->in_utf[i] == 0xfed6)
            line->in_utf[i] = 0xfed5;
        ///lam
        if (line->in_utf[i] == 0xfeee)
            line->in_utf[i] = 0xfeed;
        ///lam AKHIR
        if (line->in_utf[i] == 0xfede)
            line->in_utf[i] = 0xfedd;
        ///noun
        if (line->in_utf[i] == 0xfee6)
            line->in_utf[i] = 0xfee5;
        ///waw
        if (line->in_utf[i] == 0xfeee)
            line->in_utf[i] = 0xfeed;
        ///dal
        if (line->in_utf[i] == 0xfeaa)
            line->in_utf[i] = 0xfea9;
        ///dhal
        if (line->in_utf[i] == 0xfeac)
            line->in_utf[i] = 0xfeab;
        ///sin
        if (line->in_utf[i] == 0xfeb2)
            line->in_utf[i] = 0xfeb1;
        ///shin
        if (line->in_utf[i] == 0xfeb6)
            line->in_utf[i] = 0xfeb5;
        ///kaf
        if (line->in_utf[i] == 0xfeda)
            line->in_utf[i] = 0xfed9;
        ///mim
        if (line->in_utf[i] == 0xfee2)
            line->in_utf[i] = 0xfee1;
        ///TA FLAWL
        if (line->in_utf[i] == 0xfec3)
            line->in_utf[i] = 0xfec1;
        ///TA
        if (line->in_utf[i] == 0xfec4)
            line->in_utf[i] = 0xfec1;
        ///SAD
        if (line->in_utf[i] == 0xfeba)
            line->in_utf[i] = 0xfeb9;
        ///TA2
        if (line->in_utf[i] == 0xfe96)
            line->in_utf[i] = 0xfe95;
        ///HAMZA WAW
        if (line->in_utf[i] == 0xfe86)
            line->in_utf[i] = 0xfe85;
        ///HAMZA dadh
        if (line->in_utf[i] == 0xfec7)
            line->in_utf[i] = 0xfec5;

    }
}

int count_lines()
{
    int lines = 0;
    std::string str;
    while (! ifs.eof() ) {
        getline (ifs,str);
        lines++;
    }
    ifs.seekg (0, ifs.beg);
    return lines;
}

int main()
{
    int lines = count_lines();
    printf("lines = %d\n", lines);


    arab_line_t line;

    for (int i = 0 ; i < lines ; i++) { 
        read_line(&line);
        get_presentation_form_b(&line);
        reverse_line(&line);
        correct(&line);
        write_line(&line);
        if (i == lines-1)
            break;
        wofs << '\n';
    }

    wofs.close();
    ifs.close();

    system("pause");
    return 0;
}