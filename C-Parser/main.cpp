#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include "globals.h"
#include "semanteme.h"
using namespace std;


int main() {
    char ch_;

    vector<char> vector_ch;                         //保存用户输入
    while (true)
    {
        scanf("%c",&ch_);                   //输入一个字符
        if (ch_ == '#')                             //如果不是#存入vector
            break;
        vector_ch.push_back(ch_);
    }
    vector_ch.push_back('\0');                      //加入结束符

    gnRow = gnColumn = gnLocate = gnLocateStart = 0;//代码位置初始化
    char *char_array = new char[vector_ch.size()];  //为了给strSource传参

    for (int j = 0; j < vector_ch.size(); ++j) {    //将vector传给char_array
            char_array[j] = vector_ch[j];
    }

    strSource = char_array;                         //char_array传给strSource

    lrparse();                                      //调用
    return 0;
}