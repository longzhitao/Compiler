//
// Created by Lynn on 2019/11/29.
//

#include "scan.h"
#include "globals.h"                            //分析器的词法扫描部分

void Do_Tag(char * strSource);                  //识别标识符的中间状态
void Do_Digit(char * StrSource);                //识别数字中间状态
void Do_EndOfTag(char * strSource);             //识别标识符最后一个状态
void Do_EndOfDigit(char * strSource);           //识别最后一个数字状态
void Do_EndOfEqual(char * strSource);           //=，==
void Do_EndOfPlus(char * strSource);            //+
void Do_EndOfSubtraction(char * strSource);     //-
void Do_EndOfMultiply(char * strSource);        //*
void Do_EndOfDivide(char * strSource);          // /
void Do_EndOfLParen(char * strSource);          //(
void Do_EndOfRParen(char * strSource);          //)
void Do_EndOfLeftBracket1(char * strSource);    //[
void Do_EndOfRightBracket1(char * strSource);   //]
void Do_EndOfLeftBracket2(char * strSource);    //{
void Do_EndOfRightBracket2(char * strSource);   //}
void Do_EndOfColon(char * strSource);           //:
void Do_EndOfComma(char * strSource);           //,
void Do_EndOfSemicolon(char * strSource);       //;
void Do_EndOfMore(char * strSource);            //>,>=
void Do_EndOfLess(char * strSource);            //<,<=
void Do_EndOfEnd(char * strSource);             //'\0' 源程序结束
void PrintError(int nColumn, int nRow, char chInput);   //词法分析错误输出
void Scanner();
void scanner();

extern char * strSource;                        //源程序字符串
int gnColumn,
        gnRow,
        gnLocate,                               //下一个字符下标
        gnLocateStart;                          //下一个单词开始位置

WORD uWord;                                     //单词

char * KEY_WORDS[20] = {"main","int","char","if","else","for",
                        "while","void","bool","string","this",
                        "double","public","private","new","true",
                        "false","print","null","class"};

int IsDigit(char chInput)
{
    if (chInput<='9' && chInput>='0')return 1;
    else return 0;
}

int IsChar(char chInput)
{
    if ((chInput<='z' && chInput>='a')
        ||(chInput<='Z' && chInput>='A'))
        return 1;
    else return 0;
}


void Do_Start(char * strSource)         //识别第一个单词
{
    gnLocateStart = gnLocate;
    switch(strSource[gnLocate]){
        case '+':Do_EndOfPlus(strSource);                break;
        case '-':Do_EndOfSubtraction(strSource);         break;
        case '*':Do_EndOfMultiply(strSource);            break;
        case '/':Do_EndOfDivide(strSource);              break;
        case '(':Do_EndOfLParen(strSource);              break;
        case ')':Do_EndOfRParen(strSource);              break;
        case '[':Do_EndOfLeftBracket1(strSource);        break;
        case ']':Do_EndOfRightBracket1(strSource);       break;
        case '{':Do_EndOfLeftBracket2(strSource);        break;
        case '}':Do_EndOfRightBracket2(strSource);       break;
        case ':':Do_EndOfColon(strSource);               break;
        case ',':Do_EndOfComma(strSource);               break;
        case ';':Do_EndOfSemicolon(strSource);           break;
        case '>':Do_EndOfMore(strSource);                break;
        case '<':Do_EndOfLess(strSource);                break;
        case '=':Do_EndOfEqual(strSource);               break;
        case '\0':Do_EndOfEnd(strSource);                break;
        default:
            if(IsChar(strSource[gnLocate]))                 //标识符或关键字
            {
                Do_Tag(strSource);
            }
            else if(IsDigit(strSource[gnLocate]))           //数字
            {
                uWord.value.T2 = strSource[gnLocate] - '0';
                Do_Digit(strSource);
            }
            else                                            //其他符号
            {
                if(strSource[gnLocate] != ' '
                   && strSource[gnLocate] != '\t'
                   && strSource[gnLocate] != '\n'
                   && strSource[gnLocate] != '\r')
                {
                    PrintError(gnColumn, gnRow, strSource[gnLocate]);
                }
                if(strSource[gnLocate] == '\n'
                   || strSource[gnLocate] == '\r')
                {
                    gnColumn++;
                    gnRow = 1;
                }
                else if(strSource[gnLocate] == '\t')
                {
                    gnColumn += _TAB_LENGTH;
                }
                else gnRow++;

                gnLocate++;

                Do_Start(strSource);
            }
            break;
    }
}


void Do_Tag(char * strSource)                                       //标识符中间状态
{
    gnLocate++;
    gnRow++;
    if(IsChar(strSource[gnLocate]) || IsDigit(strSource[gnLocate])) //数字或字母
    {
        Do_Tag(strSource);
    }
    else Do_EndOfTag(strSource);
}

void Do_Digit(char * strSource)                                     //整数中间状态
{
    gnLocate++;
    gnRow++;
    if(IsDigit(strSource[gnLocate]))
    {
        uWord.value.T2 = uWord.value.T2 * 10                        //累加数字
                         + strSource[gnLocate] - '0';
        Do_Digit(strSource);
    }
    else Do_EndOfDigit(strSource);
}

void Do_EndOfTag(char * strSource)                                  //标识符最后状态
{
    int nLoop;
    uWord.syn=_SYN_ID;
    strncpy(uWord.value.T1, strSource+gnLocateStart, gnLocate-gnLocateStart);//记录标识符
    uWord.value.T1[gnLocate-gnLocateStart] = '\0';
    nLoop = 0;

    while(strcmp(KEY_WORDS[nLoop], "class") != 0)
    {
        if(! strcmp(KEY_WORDS[nLoop], uWord.value.T1))
        {
            uWord.syn = nLoop + 1;
            break;
        }
        nLoop++;
    }
}

void Do_EndOfDigit(char * strSource)    //数字最后状态
{
    uWord.syn = _SYN_NUM;
}

void Do_EndOfEqual(char * strSource)    //=，==
{
    if(strSource[gnLocate+1] != '=')
    {
        uWord.syn = _SYN_ASSIGN;
        uWord.value.T3 = strSource[gnLocate];
    }
    else                               //==
    {
        gnLocate++;
        gnRow++;
        uWord.syn = _SYN_EQ;
        strcpy(uWord.value.T1, "==");
    }
    gnLocate++;
    gnRow++;
}

void Do_EndOfPlus(char * strSource)   //+
{
    uWord.syn = _SYN_PLUS;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfSubtraction(char * strSource)  //-
{
    uWord.syn = _SYN_MINUS;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfMultiply(char * strSource)   //*
{
    uWord.syn = _SYN_TIMES;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfDivide(char * strSource)    ///
{
    uWord.syn = _SYN_DIVIDE;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfLParen(char * strSource)   //（
{
    uWord.syn = _SYN_LPAREN;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfRParen(char * strSource)   //）
{
    uWord.syn = _SYN_RPAREN;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfLeftBracket1(char * strSource)    //[
{
    uWord.syn = _SYN_LEFTBRACKET1;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfRightBracket1(char * strSource)  //]
{
    uWord.syn = _SYN_RIGHTBRACKET1;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfLeftBracket2(char * strSource)  //{
{
    uWord.syn = _SYN_LEFTBRACKET2;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfRightBracket2(char * strSource) //}
{
    uWord.syn = _SYN_RIGHTBRACKET2;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfColon(char * strSource)     //：
{
    uWord.syn = _SYN_COLON;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfComma(char * strSource)  //，
{
    uWord.syn = _SYN_COMMA;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfSemicolon(char * strSource)  //；
{
    uWord.syn = _SYN_SEMICOLON;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfMore(char * strSource)  //>，>=
{
    if(strSource[gnLocate+1] != '=') //>
    {
        uWord.syn = _SYN_LG;
        uWord.value.T3 = strSource[gnLocate];
    }
    else              //>=
    {
        gnLocate++;
        gnRow++;
        uWord.syn = _SYN_ME;
        strcpy(uWord.value.T1, ">=");
    }
    gnLocate++;
    gnRow++;
}

void Do_EndOfLess(char * strSource)  //<,<=
{
    if(strSource[gnLocate+1] != '=') //<
    {
        uWord.syn = _SYN_LT;
        uWord.value.T3 = strSource[gnLocate];
    }
    else   //<=
    {
        gnLocate++;
        gnRow++;
        uWord.syn = _SYN_LE;
        strcpy(uWord.value.T1, "<=");
    }
    gnLocate++;
    gnRow++;
}

void Do_EndOfEnd(char * strSource)   //读到'\0',源程序结束
{
    uWord.syn = _SYN_END;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void PrintWord(WORD uWord)          //打印二元组
{

    if(uWord.syn <= _SYN_ID         //关键字、标识符 错误
       || uWord.syn == _SYN_ME      //  >=
       || uWord.syn == _SYN_LE      //  <=
       || uWord.syn == _SYN_EQ)     //  ==
    {
        printf("\n%s\t               %d", uWord.value.T1, uWord.syn);
    }
    else if(uWord.syn == _SYN_NUM)  //数字
    {
        printf("\n%d\t               %d", uWord.value.T2, uWord.syn);
    }
    else                            //其他符号
    {
        printf("\n%c\t               %d", uWord.value.T3, uWord.syn);
    }
}

void ApartWord(char * strSource)  //根据输入的源程序识别所有的单词
{
    gnColumn = gnRow = 1;
    gnLocate = gnLocateStart = 0;
    printf("\n词法分析");
    printf("\n单词符号             种别码");

    while(strSource[gnLocate])
    {
        Scanner();
    }
}

void Scanner()
{
    Do_Start(strSource);    //识别一个单词
    PrintWord(uWord);       
}


//打印词法错误
void PrintError(int nColumn, int nRow, char chInput)
{

    printf("\nCol:%d  Row:%d :%c", nColumn, nRow, chInput);
    printf("(未知单词)\n");
}