#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

char *reserve_word[] = {
        "begin", "if", "then", "while", "do", "end"
};
int syn;
int kk = 0;
int k = 0;
int sum = 0;

char ch;
char input[10000];
int p_input;
char token[10];
char p_token;

struct {
    char result[12];
    char ag1[12];
    char op[12];
    char ag2[12];
}quad;

void scanner();
char * expression();
//该函数的功能是生成一个三地址语句送到四元式表中
void emit(char *result,char *ag1,char *op,char *ag2)
{
    strcpy(quad.result,result);
    strcpy(quad.ag1,ag1);
    strcpy(quad.op,op);
    strcpy(quad.ag2,ag2);

    cout << quad.result << " = "<< quad.ag1 << " " << quad.op << " " << quad.ag2 <<endl;
}



char *newtemp()
{
    char *p;
    char m[12];
    p=(char *)malloc(12);
    k++;
    itoa(k,m,10);
    strcpy(p+1,m);
    p[0]='t';
    return (p);
}
/*
 * <因子> -> ID | NUM | ( <表达式> )
 */
char *factor()
{
    char *fplace;
    fplace = (char *)malloc(12);
    strcpy(fplace, "");
    //ID = 10   NUM = 11
    if (syn == 10)
    {
        strcpy(fplace, token);     //token赋值给f_palce
        scanner();
    }
    else if(syn == 11)
    {
        itoa(sum, fplace, 10);
        scanner();
    }
    else if (syn == 27)      //'(' = 27
    {
        scanner();
        fplace = expression();
        //')' = 28
        if (syn == 28)
            scanner();
        else{
            kk = 1;
            cout << "Error! 缺少')'" << endl;
        }
    }else{
        kk = 1;
        cout << "Error! 运算符后不是常数或标识符或'('" << endl;
    }
    return fplace;
}

/*
 * <项> -> <因子> {*<因子> | /<因子>}
 */
char *term()
{
    char *tp, *ep2, *eplace, *tt;

    tp=(char *)malloc(12);
    ep2=(char *)malloc(12);
    eplace=(char *)malloc(12);
    tt=(char *)malloc(12);
    strcpy(eplace, factor());

    //'*' = 15  '/' = 16
    while (syn == 15 || syn == 16)
    {
        if (syn == 15)
            strcpy(tt, "*");
        else
            strcpy(tt, "/");

        scanner();
        strcpy(ep2, factor());
        strcpy(tp, newtemp());
        emit(tp, eplace, tt, ep2);
        strcpy(eplace, tp);

    }

    return eplace;
}

/*
 * <表达式> -> <项> {+<项> | -<项>}
 */
char *expression(){
    char *tp, *ep2, *eplace, *tt;

    tp=(char *)malloc(12);
    ep2=(char *)malloc(12);
    eplace=(char *)malloc(12);
    tt=(char *)malloc(12);
    strcpy(eplace, term());

    // '+' = 13 '-' = 14
    while (syn == 13 || syn == 14)
    {
        if (syn == 13)
            strcpy(tt, "+");
        else
            strcpy(tt, "-");

        scanner();
        strcpy(ep2, term());
        strcpy(tp, newtemp());
        emit(tp, eplace, tt, ep2);
        strcpy(eplace, tp);

    }
    return eplace;
}

/*
 * <赋值语句> -> ID:= <表达式>
 */
int statement()
{
    char *eplace, *tt;
    eplace = (char *)malloc(12);
    tt = (char *)malloc(12);
    int schain = 0;

    switch (syn)
    {
        case 10:
            strcpy(tt, token);
            scanner();
            if (syn == 18) {
                scanner();
                strcpy(eplace, expression());
                emit(tt, eplace, "", "");
                schain = 0;
            } else {
                kk = 1;
                cout << "Error! 缺少':='" << endl;
            }
            return schain;
    }
    return schain;
}

/*
 * <语句串> —> <语句> {;<语句>}
 */
int yucu()
{
    int schain = 0;
    schain = statement();
    while (syn == 26)
    {
        scanner();
        schain = statement();
    }
    return schain;
}


int lrparser()
{
    int schain = 0;
    kk = 0;
    if(syn == 1)
    {
        scanner();
        schain = yucu();
        if(syn == 6)
        {
            scanner();
            if(syn == 0 && kk == 0)
                cout<<"success!\n" <<endl;
        }
        else
        {
            if (kk != 1)
                cout<<"Error! 缺少'end'"<<endl;
            kk = 1;
        }
    }
    else
    {
        cout<<"Error! 缺少'begin'"<<endl;
        kk = 1;

    }
    return schain;
}

void remove_space_char()
{
    while (ch == ' ' || ch == '\n')
        ch = input[p_input++];
}

bool is_digit(){
    return ch >= '0' && ch <= '9';
}

bool is_letter(){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

void get_char(){
    ch = input[p_input++];
}

/*
 * 词法分析
 */
void scanner(){
    for (int i = 0; i < 8; ++i)
        token[i] = '\0';

    get_char();
    remove_space_char();

    if (is_letter())
    {
        p_token = 0;

        while (is_digit() || is_letter())
        {
            token[p_token++] = ch;
            get_char();
        }
        p_input--;
        token[p_token] = '\0';
        syn = 10;

        for (int i = 0; i < 6; ++i)
        {
            if (strcmp(token, reserve_word[i]) == 0)
            {
                syn = i + 1;
                break;
            }
        }
    }else if (is_digit())
    {
        {
            sum = 0;
            while (is_digit())
            {
                sum = sum * 10 + ch - '0';
                get_char();
            }
        }
        p_input--;
        syn = 11;
    }else{
        switch (ch)
        {
            case '+': syn = 13; token[0] = ch; break;
            case '-': syn = 14; token[0] = ch; break;
            case '*': syn = 15; token[0] = ch; break;
            case '/': syn = 16; token[0] = ch; break;
            case '=': syn = 25; token[0] = ch; break;
            case ';': syn = 26; token[0] = ch; break;
            case '(': syn = 27; token[0] = ch; break;
            case ')': syn = 28; token[0] = ch; break;
            case '#': syn = 0; token[0] = ch; break;
            case ':':
                p_token = 0;
                token[p_token++] = ch;
                get_char();
                if (ch == '=')
                {
                    token[p_token++] = ch;
                    syn = 18;
                } else{
                    syn = 17;
                    p_input--;
                }
                break;
            case '<':
                p_token = 0;
                token[p_token++] = ch;
                get_char();
                if (ch == '>')
                {
                    token[p_token++] = ch;
                    syn = 21;
                } else if (ch == '=')
                {
                    token[p_token++] = ch;
                    syn = 22;
                } else{
                    syn = 20;
                    p_input--;
                }
                break;
            case '>':
                p_token = 0;
                token[p_token++] = ch;
                get_char();
                if (ch == '=')
                {
                    token[p_token++] = ch;
                    syn = 24;
                } else{
                    syn = 23;
                    p_input--;
                }
                break;
            default:
                syn = -1;
                break;
        }
        token[p_token] = '\0';
    }
}

int main() {
    char ch_;
    do{
        scanf("%c", &ch_);
        input[p_input++] = ch_;
    }while (ch_ != '#');
    p_input = 0;
    kk = 0;
    scanner();
    lrparser();
    return 0;
}

