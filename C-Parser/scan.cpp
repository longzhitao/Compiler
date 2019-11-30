//
// Created by Lynn on 2019/11/29.
//

#include "scan.h"
#include "globals.h"                            //�������Ĵʷ�ɨ�貿��

void Do_Tag(char * strSource);                  //ʶ���ʶ�����м�״̬
void Do_Digit(char * StrSource);                //ʶ�������м�״̬
void Do_EndOfTag(char * strSource);             //ʶ���ʶ�����һ��״̬
void Do_EndOfDigit(char * strSource);           //ʶ�����һ������״̬
void Do_EndOfEqual(char * strSource);           //=��==
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
void Do_EndOfEnd(char * strSource);             //'\0' Դ�������
void PrintError(int nColumn, int nRow, char chInput);   //�ʷ������������
void Scanner();
void scanner();

extern char * strSource;                        //Դ�����ַ���
int gnColumn,
        gnRow,
        gnLocate,                               //��һ���ַ��±�
        gnLocateStart;                          //��һ�����ʿ�ʼλ��

WORD uWord;                                     //����

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


void Do_Start(char * strSource)         //ʶ���һ������
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
            if(IsChar(strSource[gnLocate]))                 //��ʶ����ؼ���
            {
                Do_Tag(strSource);
            }
            else if(IsDigit(strSource[gnLocate]))           //����
            {
                uWord.value.T2 = strSource[gnLocate] - '0';
                Do_Digit(strSource);
            }
            else                                            //��������
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


void Do_Tag(char * strSource)                                       //��ʶ���м�״̬
{
    gnLocate++;
    gnRow++;
    if(IsChar(strSource[gnLocate]) || IsDigit(strSource[gnLocate])) //���ֻ���ĸ
    {
        Do_Tag(strSource);
    }
    else Do_EndOfTag(strSource);
}

void Do_Digit(char * strSource)                                     //�����м�״̬
{
    gnLocate++;
    gnRow++;
    if(IsDigit(strSource[gnLocate]))
    {
        uWord.value.T2 = uWord.value.T2 * 10                        //�ۼ�����
                         + strSource[gnLocate] - '0';
        Do_Digit(strSource);
    }
    else Do_EndOfDigit(strSource);
}

void Do_EndOfTag(char * strSource)                                  //��ʶ�����״̬
{
    int nLoop;
    uWord.syn=_SYN_ID;
    strncpy(uWord.value.T1, strSource+gnLocateStart, gnLocate-gnLocateStart);//��¼��ʶ��
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

void Do_EndOfDigit(char * strSource)    //�������״̬
{
    uWord.syn = _SYN_NUM;
}

void Do_EndOfEqual(char * strSource)    //=��==
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

void Do_EndOfLParen(char * strSource)   //��
{
    uWord.syn = _SYN_LPAREN;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfRParen(char * strSource)   //��
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

void Do_EndOfColon(char * strSource)     //��
{
    uWord.syn = _SYN_COLON;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfComma(char * strSource)  //��
{
    uWord.syn = _SYN_COMMA;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfSemicolon(char * strSource)  //��
{
    uWord.syn = _SYN_SEMICOLON;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void Do_EndOfMore(char * strSource)  //>��>=
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

void Do_EndOfEnd(char * strSource)   //����'\0',Դ�������
{
    uWord.syn = _SYN_END;
    uWord.value.T3 = strSource[gnLocate];

    gnLocate++;
    gnRow++;
}

void PrintWord(WORD uWord)          //��ӡ��Ԫ��
{

    if(uWord.syn <= _SYN_ID         //�ؼ��֡���ʶ�� ����
       || uWord.syn == _SYN_ME      //  >=
       || uWord.syn == _SYN_LE      //  <=
       || uWord.syn == _SYN_EQ)     //  ==
    {
        printf("\n%s\t               %d", uWord.value.T1, uWord.syn);
    }
    else if(uWord.syn == _SYN_NUM)  //����
    {
        printf("\n%d\t               %d", uWord.value.T2, uWord.syn);
    }
    else                            //��������
    {
        printf("\n%c\t               %d", uWord.value.T3, uWord.syn);
    }
}

void ApartWord(char * strSource)  //���������Դ����ʶ�����еĵ���
{
    gnColumn = gnRow = 1;
    gnLocate = gnLocateStart = 0;
    printf("\n�ʷ�����");
    printf("\n���ʷ���             �ֱ���");

    while(strSource[gnLocate])
    {
        Scanner();
    }
}

void Scanner()
{
    Do_Start(strSource);    //ʶ��һ������
    PrintWord(uWord);       
}


//��ӡ�ʷ�����
void PrintError(int nColumn, int nRow, char chInput)
{

    printf("\nCol:%d  Row:%d :%c", nColumn, nRow, chInput);
    printf("(δ֪����)\n");
}