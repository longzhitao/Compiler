#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

char *reserve_word[] = {
        "begin", "if", "then", "while", "do", "end"
};
int syn;
int kk = 0;

char ch;
char input[10000];
int p_input;
char token[10];
char p_token;

void scanner();
void expression();


/*
 * <????> -> ID | NUM | ( <????> )
 */
void factor()
{
    //ID = 10   NUM = 11
    if (syn == 10 || syn == 11)
    {
        scanner();
    }
        //'(' = 27
    else if (syn == 27)
    {
        scanner();
        expression();
        //')' = 28
        if (syn == 28)
            scanner();
        else{
            kk = 1;
            cout << "Error! 缺少')'" << endl;
        }
    }else{
        kk = 1;
        cout << "Error! 语句错误或者缺少'('" << endl;
    }
}

/*
 * <??> -> <????> {*<????> | /<????>}
 */
void term()
{
    factor();
    //'*' = 15  '/' = 16
    while (syn == 15 || syn == 16)
    {
        scanner();
        factor();
    }
}

/*
 * <????> -> <??> {+<??> | -<??>}
 */
void expression(){
    term();
    // '+' = 13 '-' = 14
    while (syn == 13 || syn == 14)
    {
        scanner();
        term();
    }
}

/*
 * <??????> -> ID:= <????>
 */
void statement()
{
    if (syn == 10)
    {
        scanner();
        if (syn == 18)
        {
            scanner();
            expression();
        } else{
            kk = 1;
            cout << "Error! 缺少':='" << endl;
        }
    } else{
        kk = 1;
        cout << "Error! 赋值语句错误" << endl;
    }
}

/*
 * <???> ??> <???> {;<???>}
 */
void yucu()
{
    statement();
    while (syn == 26)
    {
        scanner();
        statement();
    }
}


void lrparser()
{
    if(syn == 1)
    {
        scanner();
        yucu();
        if(syn == 6)
        {
            scanner();
            if(syn == 0 && kk == 0)
                cout<<"success!\n" <<endl;
        }
        else
        {
            if (kk == 0)
                cout<<"Error! 缺少'end'"<<endl;
            kk = 1;
        }
    }
    else
    {
        cout<<"Error! 缺少'begin'"<<endl;
        kk = 1;

    }
}

void remove_space_char()
{
    while (ch == ' ' || ch == 10)
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
 * ???????
 */
void scanner(){
    p_token = 0;
    get_char();
    remove_space_char();

    if (is_letter())
    {
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
        while (is_digit())
        {
            token[p_token++] = ch;
            get_char();
        }
        p_input--;
        token[p_token] = '\0';
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
                token[p_token++] = ch;
                get_char();
                if (ch == '=')
                {
                    get_char();
                    token[p_token++] = ch;
                    syn = 18;
                } else{
                    syn = 17;
                }
                p_input--;
                break;
            case '<':
                token[p_token++] = ch;
                get_char();
                if (ch == '>')
                {
                    get_char();
                    token[p_token++] = ch;
                    syn = 21;
                } else if (ch == '=')
                {
                    get_char();
                    token[p_token++] = ch;
                    syn = 22;
                } else{
                    syn = 20;
                }
                p_input--;
                break;
            case '>':
                token[p_token++] = ch;
                get_char();
                if (ch == '=')
                {
                    get_char();
                    token[p_token++] = ch;
                    syn = 24;
                } else{
                    syn = 23;
                }
                p_input--;
                break;
            default:
                syn = -1;
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