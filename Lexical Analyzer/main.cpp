#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

char input[10000];
char token[255];
int p_input;
int p_token;
char ch;

typedef struct
{
    int type_num;
    char *word;
}Word;

char *reserve_word[] = {
        "short", "if", "const", "while", "do",
        "static", "int", "float", "double", "char",
        "return", "cout", "cin", "main", "for"

};

static int RESERVE_WORD_LENGTH = 15;

Word * Scanner();

int IsReserve(){
    for (int i = 0; i < RESERVE_WORD_LENGTH; ++i) {
        if (strcmp(reserve_word[i], token) == 0)
            return i + 1;
    }
    return RESERVE_WORD_LENGTH + 1;
}

bool IsDigit(){
    return ch >= '0' && ch <= '9';
}

bool IsLetter(){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

char GetChar(){
    ch = input[p_input++];
    return ch;
}

void RemoveSpaceChar(){
    while (ch == ' ' || ch == 10)
        ch = input[p_input++];
}

void Concat(){
    token[p_token++] = ch;
    token[p_token] = '\0';
};

void Rollback(){
    p_input--;
}

void ReserveOrID(Word *word){
    while (IsLetter() || IsDigit()){
        Concat();
        GetChar();
    }
    Rollback();                             //循环中会多读取一格，故回退一格
    word->type_num = IsReserve();
    word->word = token;
}

void Number(Word *word){
    while (IsDigit()){
        Concat();
        GetChar();
    }
    Rollback();                             //循环中会多读取一格，故回退一格
    word->type_num = 20;
    word->word = token;
}


void DelimiterOrOperator(Word *word){
    switch(ch){
        case '=':                           //如果是等于号则判断下一个符号是否是'='是则操作符是'=='
            GetChar();
            if (ch == '='){
                word->type_num = 39;
                word->word = "==";
                break;
            }
            Rollback();                       //不是则回退操作符为'='
            word->type_num = 21;
            word->word = "=";
            break;
        case '+':
            word->type_num = 22;
            word->word = "+";
            break;
        case '-':
            word->type_num = 23;
            word->word = "-";
            break;
        case '*':
            word->type_num = 24;
            word->word = "*";
            break;
        case '/':
            word->type_num = 25;
            word->word = "/";
            break;
        case '(':
            word->type_num = 26;
            word->word = "(";
            break;
        case ')':
            word->type_num = 27;
            word->word = ")";
            break;
        case '[':
            word->type_num = 28;
            word->word = "[";
            break;
        case ']':
            word->type_num = 29;
            word->word = "]";
            break;
        case '{':
            word->type_num = 30;
            word->word = "{";
            break;
        case '}':
            word->type_num = 31;
            word->word = "}";
            break;
        case ',':
            word->type_num = 32;
            word->word = ",";
            break;
        case ':':
            word->type_num = 33;
            word->word = ":";
            break;
        case ';':
            word->type_num = 34;
            word->word = ";";
            break;
        case '>':
            GetChar();
            if (ch == '='){
                word->type_num = 37;
                word->word = ">=";
                break;
            } else if (ch == '>'){
                word->type_num = 41;
                word->word = ">>";
                break;
            }
            Rollback();
            word->type_num = 35;
            word->word = ">";
            break;
        case '<':
            GetChar();
            if (ch == '='){
                word->type_num = 38;
                word->word = "<=";
                break;
            } else if (ch == '<'){
                word->type_num = 42;
                word->word = "<<";
                break;
            }
            Rollback();
            word->type_num = 36;
            word->word = "<";
            break;
        case '!':
            GetChar();
            if (ch == '='){
                word->type_num = 40;
                word->word = "!=";
                break;
            }
            Rollback();
            word->type_num = -1;
            word->word = "Error";
            break;
        case '\0':
            word->type_num = 1000;
            word->word = "Over";
    }
}

bool Comments(Word *word){
    if (ch != '/')
        return false;
    else{
        GetChar();
        if (ch != '/'){
            Rollback();     //回退一格此时ch还是等于/后一个字符

            Rollback();     //再回退一格
            GetChar();      //让ch等于/
            return false;
        }
        while (ch != '\n'){
            Concat();
            GetChar();
        }
        Rollback();
        word->type_num = 1001;
        word->word = token;
        return true;
    }

}


Word *Scanner(){
    Word *word = new Word;
    word->type_num = 10;
    word->word = "";
    p_token = 0;
    GetChar();              //获得第一个字符
    RemoveSpaceChar();      //去除空格

    if (Comments(word));
    else if (IsLetter())
        ReserveOrID(word);
    else if (IsDigit())
        Number(word);
    else
        DelimiterOrOperator(word);
    return word;
}

int main() {
    int over = 1;
    Word* word;
    cout << "Read code from data.txt" << endl;
    FILE *fp;

    if ((fp = freopen("data.txt","r",stdin))==NULL){
        cout << "File Error!" << endl;
        return 0;
    } else{
        while((scanf("%[^#]s", input)) != EOF){
            p_input = 0;
            printf("Your words: \n% s \n", input);
            while (over != 1000 && over != -1){
                word = Scanner();
                if (word->type_num < 1000)
                    printf("[%d, %s]\n", word->type_num, word->word);
                over = word->type_num;
            }
        }
    }
    return 0;

}



