#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include "globals.h"
#include "semanteme.h"
using namespace std;

void bk(char ch,int w)
{
    for(int i=0;i<80;i++)
        putchar(ch);
}



long int countchar(char *str)
{
    FILE *fp;
    long int count=0;
    //gets(str);
    fp=fopen(str,"r");
    if(fp==NULL)
    {
        putchar('\n');
        bk('*',81);
        printf("\n\t\tSorry,There isn't the file %s at presnt path!\n",str);
        bk('*',81);
        return -1;
    }
    while(!feof(fp))
    {
        fgetc(fp);
        count++;
    }
    fclose(fp);
    return count;
}

int main() {
//    char str1[81], sourcefilename[30], resultfilename[30], *new_arry;
//    long int len;
//    FILE *fp;
//
//
//    puts("Input the source file name:");
//    gets(sourcefilename);
//    if((len=countchar(sourcefilename))!=-1)
//    {
//        new_arry=new char[len];
//        puts("Input the result file name:");
//        gets(resultfilename);
//        strFileName = resultfilename;
//        fp = fopen(sourcefilename,"r");
//        new_arry[0]='\0';
//        while(!feof(fp))
//        {
//            fgets(str1,80,fp);
//            puts(str1);
//            strcat(new_arry,str1);
//        }
//        fclose(fp);
//        gnRow = gnColumn = gnLocate = gnLocateStart=0;
//        strSource=new_arry;
//
//        lrparse();
//        delete new_arry;
//    }
    char ch_;

    vector<char> vector_ch;
    while (true)
    {
        scanf("%c",&ch_);
        if (ch_ == '#')
            break;
        vector_ch.push_back(ch_);
    }
    gnRow = gnColumn = gnLocate = gnLocateStart = 0;
    char *char_array = new char[vector_ch.size()];

    for (int j = 0; j < vector_ch.size(); ++j) {
            char_array[j] = vector_ch[j];
    }

    strSource = char_array;

    int i = 0;
    for (i = 0; i < vector_ch.size(); ++i) {
        cout << strSource[i];
    }
    strSource[i+1] = '\0';

    lrparse();
    return 0;
}