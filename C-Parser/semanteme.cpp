//
// Created by Lynn on 2019/11/29.
//

#include "semanteme.h"
#include"scan.h"

QUATERNION * pQuad;                                         //四元组
int nSuffix,nNXQ,ntc,nfc;                                   //变量的ID
extern WORD uWord;
extern int gnColumn, gnRow, gnLocate, gnLocateStart;
char * strSource;                                           //源程序
char * Expression();
char * Term();
char * Factor();
void   Statement_Block(int * nChain);

void LocateError(int nColumn,int nRow)                      //定位语法错误
{
    printf("\nCol:%d  Row:%d:", nColumn+1, nRow);
}

void error(char *strError)                                  //输出扫描错误
{
    LocateError(gnColumn,gnRow);
    printf("%s",strError);
}

void Match(int syn,char *strError)                          //判断当前识别的单词是否需要的单词，不是报错，否则扫描下一个单词
{
    if(syn==uWord.syn)Scanner();
    else error(strError);
}

void gen(char *op,char *argv1,char *argv2,char *result)     //生成一个四元式
{
    sprintf(pQuad[nNXQ].op,op);
    sprintf(pQuad[nNXQ].argv1,argv1);
    sprintf(pQuad[nNXQ].argv2,argv2);
    sprintf(pQuad[nNXQ].result,result);
    nNXQ++;
}

void PrintQuaternion()              //打印一个四元式数组
{
    int nLoop;
    for (nLoop=1; nLoop < nNXQ; nLoop++){
        printf("\n  %d:\t%s \t%s \t%s \t%s \n",
               nLoop,pQuad[nLoop].op,pQuad[nLoop].argv1,
               pQuad[nLoop].argv2,pQuad[nLoop].result);
    }
}

char * Newtemp()             //临时变量
{
    char * strTempID = (char *)malloc(MAXLENGTH);
    sprintf(strTempID,"T%d",++nSuffix);
    return strTempID;
}

int merge(int p1, int p2)         //合并p1和p2
{
    int p, nResult;

    if(p2 == 0)nResult = p1;
    else{
        nResult = p = p2;
        while(atoi(pQuad[p].result)){
            p=atoi(pQuad[p].result);
            sprintf(pQuad[p].result,"%s",p1);
        }
    }
    return nResult;
}

void bp(int p,int t)         //将t加入到p为头节点的四元式链
{
    int w, q = p;
    while(q){
        w = atoi(pQuad[q].result);
        sprintf(pQuad[q].result,"%d",t);
        q = w;
    }
}

char * Expression()
{
    char opp[MAXLENGTH], * eplace, eplace1[MAXLENGTH], eplace2[MAXLENGTH];
    eplace=(char *)malloc(MAXLENGTH);

    strcpy(eplace1, Term());
    strcpy(eplace,eplace1);

    while(uWord.syn == _SYN_PLUS || uWord.syn == _SYN_MINUS){ //    + -
        sprintf(opp,"%c",uWord.value.T3);
        Scanner();

        strcpy(eplace2, Term());
        strcpy(eplace, Newtemp());

        gen(opp, eplace1, eplace2, eplace);
        strcpy(eplace1, eplace);
    }
    return eplace;
}

char * Term(void)
{
    char opp[2], * eplace1, * eplace2, * eplace;
    eplace = eplace1 = Factor();

    while(uWord.syn == _SYN_TIMES || uWord.syn == _SYN_DIVIDE){ //   * /
        sprintf(opp, "%c", uWord.value.T3);
        Scanner();
        eplace2 = Factor();
        eplace = Newtemp();
        gen(opp, eplace1, eplace2, eplace);
        eplace1 = eplace;
    }
    return eplace;
}

char * Factor(void)
{
    char * eplace = (char *)malloc(MAXLENGTH);
    if(uWord.syn == _SYN_ID || uWord.syn == _SYN_NUM)
    {
        if(uWord.syn == _SYN_ID)
            sprintf(eplace, "%s", uWord.value.T1);
        else
            sprintf(eplace, "%d", uWord.value.T2);
        Scanner();

    }
    else
    {
        Match(_SYN_LPAREN, "(");
        eplace = Expression();
        Match(_SYN_RPAREN, ")");
    }
    return eplace;
}

void Condition(int * etc, int * efc)
{
    char opp[3], * eplace1, * eplace2;
    char strTemp[4];

    eplace1 = Expression();
    if(uWord.syn <= _SYN_NE && uWord.syn >= _SYN_LG)
    {
        switch(uWord.syn)
        {
            case _SYN_LT:
            case _SYN_LG:
                sprintf(opp, "%c", uWord.value.T3);
                break;
            default:
                sprintf(opp, "%s", uWord.value.T1);
                break;
        }
        Scanner();
        eplace2 = Expression();
        * etc = nNXQ;
        * efc = nNXQ+1;
        sprintf(strTemp, "J%s", opp);
        gen(strTemp, eplace1, eplace2, "0");
        gen("JMP", "", "", "0");
    }
    else error("(关系运算符错误)");
}

void Statement(int * nChain)    //语句分析函数
{
    char strTemp[MAXLENGTH], eplace[MAXLENGTH];
    int nChainTemp, nWQUAD;
    switch(uWord.syn)
    {
        case _SYN_ID:
            strcpy(strTemp, uWord.value.T1);
            Scanner();
            Match(_SYN_ASSIGN, "=");
            strcpy(eplace, Expression());
            Match(_SYN_SEMICOLON, ";");
            gen("=", eplace, "", strTemp);
            * nChain = 0;
            break;
        case _SYN_IF:
            Match(_SYN_IF, "if");
            Match(_SYN_LPAREN, "(");
            Condition(&ntc, &nfc);
            bp(ntc, nNXQ);
            Match(_SYN_RPAREN, ")");
            Statement_Block(&nChainTemp);
            * nChain = nfc;
            break;
        case _SYN_ELSE:
            Match(_SYN_ELSE, "else");
            Statement_Block(&nChainTemp);
            * nChain = 0;
            break;
        case _SYN_WHILE:
            Match(_SYN_WHILE, "while");
            nWQUAD=nNXQ;
            Match(_SYN_LPAREN, "(");
            Condition(&ntc, &nfc);
            bp(ntc, nNXQ);
            Match(_SYN_RPAREN, ")");
            Statement_Block(&nChainTemp);
            bp(nChainTemp, nWQUAD);
            sprintf(strTemp, "%d", nWQUAD);
            gen("JMP", "", "", strTemp);
            * nChain = nfc;
            break;
        case _SYN_INT:
            Match(_SYN_INT,"int");
            while(uWord.syn != 36)
            {
                Scanner();
            }
            Match(_SYN_SEMICOLON,";");
            gen("SMT","","","");
            * nChain = 0;
            break;
        case _SYN_CHAR:
            Match(_SYN_CHAR,"char");
            while(uWord.syn != 36)
            {
                Scanner();
            }
            Match(_SYN_SEMICOLON,";");
            gen("SMT","","","");
            * nChain = 0;
            break;
        default:
        {
            error("(无法识别的语句!)");
            while(uWord.syn != 2
                  && uWord.syn != 3
                  && uWord.syn != 4
                  && uWord.syn != 5
                  && uWord.syn != 7)
            {
                Scanner();
            }
            * nChain = 0;
        }
    }
    return;
}

void Statement_Sequence(int * nChain) // nChain语句串分析函数
{
    Statement(nChain);
    while(uWord.syn == _SYN_ID
          || uWord.syn == _SYN_INT
          || uWord.syn == _SYN_CHAR
          || uWord.syn == _SYN_IF
          || uWord.syn == _SYN_ELSE
          || uWord.syn == _SYN_WHILE){  //id if while
        bp(* nChain, nNXQ);
        Statement(nChain);
    }
    bp(* nChain, nNXQ);
    return;
}

void Statement_Block(int * nChain) //语句块分析函数
{
    Match(_SYN_LEFTBRACKET2, "{");
    Statement_Sequence(nChain);
    Match(_SYN_RIGHTBRACKET2, "}"); //)
}

void Parse(void)
{
    int nChain;
    Scanner();
    Match(_SYN_MAIN, "main");
    Match(_SYN_LPAREN, "(");
    Match(_SYN_RPAREN, ")");
    Statement_Block(&nChain);      //语句块分析函数
    if(uWord.syn != _SYN_END){
        printf("源程序异常结束");
    }

    printf("序列号\n");
    printf("op     arg1    arg2    result");

    PrintQuaternion();

}

void lrparse(void)           //语义语法分析函数
{
    pQuad=(QUATERNION*)malloc(strlen(strSource)*sizeof(QUATERNION));
    nSuffix = 0;
    nfc = ntc = nNXQ = 1;

    ApartWord(strSource);
    gnColumn = gnRow = 0;
    gnLocate = gnLocateStart = 0;
    Parse();
}