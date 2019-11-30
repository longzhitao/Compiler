//
// Created by Lynn on 2019/11/27.
//

#ifndef C_PARSER_GLOBALS_H
#define C_PARSER_GLOBALS_H

#include <string.h>

//单词种别码
#define _SYN_MAIN           1
#define _SYN_INT            2
#define _SYN_CHAR           3
#define _SYN_IF             4
#define _SYN_ELSE           5
#define _SYN_FOR            6
#define _SYN_WHILE          7
#define _SYN_VOID           8
#define _SYN_BOOL           9
#define _SYN_STRING        10
#define _SYN_THIS          11
#define _SYN_DOUBLE        12
#define _SYN_PUBLIC        13
#define _SYN_PRIVATE       14
#define _SYN_NEW           15
#define _SYN_TRUE          16
#define _SYN_FALSE         17
#define _SYN_PRINT         18
#define _SYN_NULL          19
#define _SYN_CLASS         20
//以上为关键字的种别码

#define _SYN_ID            21           //标识符的单词种别符
#define _SYN_NUM           22           //整数的单词种别符

#define _SYN_ASSIGN        23           //=
#define _SYN_PLUS          24           //+
#define _SYN_MINUS         25           //-
#define _SYN_TIMES         26           //*
#define _SYN_DIVIDE        27           // /
#define _SYN_LPAREN        28           //(
#define _SYN_RPAREN        29           //)
#define _SYN_LEFTBRACKET1  30           //[
#define _SYN_RIGHTBRACKET1 31           //]
#define _SYN_LEFTBRACKET2  32           //{
#define _SYN_RIGHTBRACKET2 33           //}
#define _SYN_COMMA         34           //,
#define _SYN_COLON         35           //:
#define _SYN_SEMICOLON     36           //;

#define _SYN_LG            37           //>
#define _SYN_LT            38           //<
#define _SYN_ME            39           //>=
#define _SYN_LE            40           //<=
#define _SYN_EQ            41           //==
#define _SYN_NE            42           // !=
#define _SYN_END           1000         //源程序结束标志

#define _SYN_ERROR         -1           //error

#define MAXLENGTH          255          //一行允许字符个数

union WORDCONTENT{                      //存放单词内容的联合
    char T1[MAXLENGTH];
    int  T2;
    char T3;
};

typedef struct WORD{                    //单词二元组
    int syn;
    union WORDCONTENT value;
}WORD;



extern char * strSource;
extern char * strFileName;
extern int gnRow,gnColumn,gnLocate,gnLocateStart;


#endif //C_PARSER_GLOBALS_H
