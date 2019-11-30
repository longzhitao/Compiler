//
// Created by Lynn on 2019/11/29.
//

#ifndef C_PARSER_SCAN_H
#define C_PARSER_SCAN_H

#define _TAB_LENGTH     4    //一TAB占用的空格数
#include <iomanip>
//#define _KEY_WORD_END  "waiting for your expanding"
//关键字结束标记

void Scanner();           //函数Scaner得到源程序里的下一个单词符号
void ApartWord(char * strSource);
void Scanner_without_print();
#endif //C_PARSER_SCAN_H
