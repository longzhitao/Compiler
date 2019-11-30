//
// Created by Lynn on 2019/11/28.
//

#include <stdio.h>
#include "scan.h"
#include "globals.h"

void Do_Tag(char *str);                 //识别标识符中间状态
void Do_Digit(char *str);               //识别数字的中间状态
void Do_EndOfTag(char *str);            //识别标识符最后的一个状态
void Do_EndOfDigit(char *str);          //识别数字的最后一个状态
void Do_EndOfEqual(char *str);
void Do_EndOfPlus(char *str);           // +
void Do_EndOfSubtraction(char *str);    // -
void Do_EndOfMultiply(char *str);
void Do_EndOfDivide(char *str);
void Do_EndOfLParen(char *str);
void Do_EndOfRParen(char *str);
void Do_EndOfLeftBracketMid(char *str); //
void Do_EndOfRightBracketMid(char *str);//
void Do_EndOfLeftBracketBig(char *str);
void Do_EndOfRightBracketBig(char *str);
void Do_EndOfColon(char *str);
void Do_EndOfComma(char *str);
void Do_EndOfSemicolon(char *str);
void Do_EndOfGreat(char *str);
void Do_EndOfLess(char *str);
void Do_EndOfEnd(char *str);
void PrintError(int nColumn, int nRow, char ch_Input);
void Scanner(void);

extern char *str;
extern FILE *fw;
int gnColumn,
    gnRow,
    gnLocate,
    gnLocateStart;
Word uWord;

char * Key_Words[20] = {
        "main", "int", "char", "if", "else",
        "for", "while", "void", _key_word_end
};

int IsDigit(char ch_Input){
    if (ch_Input <= '9' && ch_Input >= '0')
        return 1;
    else
        return 0;
}

int IsChar(char ch_Input){
    if ((ch_Input >= 'a' && ch_Input <= 'z')
    || (ch_Input >= 'A' && ch_Input <= 'Z'))
        return 1;
    else
        return 0;
}

void Do_Start(char *str){
    gnLocateStart = gnLocate;
    switch (str[gnLocate]){
        case '+':Do_EndOfPlus(str);             break;
        case '-':Do_EndOfSubtraction(str);      break;
        case '*':Do_EndOfMultiply(str);         break;
        case '/':Do_EndOfDivide(str);           break;
        case '(':Do_EndOfLParen(str);           break;
        case ')':Do_EndOfRParen(str);           break;
        case '[':Do_EndOfLeftBracketMid(str);   break;
        case ']':Do_EndOfRightBracketMid(str);  break;
        case '{':Do_EndOfLeftBracketBig(str);   break;
        case '}':Do_EndOfRightBracketBig(str);  break;
        case ':':Do_EndOfColon(str);            break;
        case ',':Do_EndOfComma(str);            break;
        case ';':Do_EndOfSemicolon(str);        break;
        case '>':Do_EndOfGreat(str);            break;
        case '<':Do_EndOfLess(str);             break;
        d

    }
}