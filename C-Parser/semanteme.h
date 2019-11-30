//
// Created by Lynn on 2019/11/29.
//

#ifndef C_PARSER_SEMANTEME_H
#define C_PARSER_SEMANTEME_H

#include "globals.h"

//四元组的结构
typedef struct QUAD{
    char op[MAXLENGTH];       //操作符
    char argv1[MAXLENGTH];    //第一个操作数
    char argv2[MAXLENGTH];    //第二个操作数
    char result[MAXLENGTH];   //运算结果
}QUATERNION;

void lrparse(void);           //语法语义分析主函数
#endif //C_PARSER_SEMANTEME_H
