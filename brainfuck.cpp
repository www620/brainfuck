#include <cstdio>
#include <fstream>
using namespace std;

#define maxcodelen 100000
#define maxtapelen 100000
char code[maxcodelen], tape[maxtapelen], *p = tape + maxtapelen / 2;
int paired[maxcodelen / 2], stack[maxcodelen / 2], top = 0, codelen = 0, last_input;

void input_code_and_pair_brackets(char quit_char)
{
    for (char ch = getchar(); ch != quit_char; ch = getchar())
    {
        if (ch == '[')
            stack[top++] = codelen;
        else if (ch == ']')
        {
            if (top == 0)
                fprintf(stderr, "PairBracketsError\n");
            top--;
            paired[stack[top]] = codelen;
            paired[codelen] = stack[top];
        }
        code[codelen++] = ch;
    }
}

void run_code()
{
    freopen("CON", "r", stdin);
    for (int i = 0; i < codelen; i++)
    {
        switch (code[i])
        {
        case '+':
            ++*p;
            break;
        case '-':
            --*p;
            break;
        case '>':
            ++p;
            break;
        case '<':
            --p;
            break;
        case ',':
            last_input = *p = getchar();
            break;
        case '.':
            putchar(*p);
            break;
        case '[':
            if (!*p)
                i = paired[i];
            break;
        case ']':
            if (*p)
                i = paired[i];
            break;
//        case '#':
//            for (char *pi = p - 10;  pi <= p + 10;  pi++)
//                printf("\n%c%4d %#d %c", pi == p ? '-' : ' ', pi - tape, int(*pi), *pi);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        printf("BrainFuck 0.1\n\n");
        while (1)
        {
            last_input = '\n';
            printf(">>> ");
            input_code_and_pair_brackets('\n');
            while (top)
            {
                printf("... ");
                input_code_and_pair_brackets('\n');
            }
            run_code();
            if (last_input != '\n')
                for (char ch = getchar(); ch != '\n'; ch = getchar())
                    ;
            codelen = 0;
        }
    }
    else if (freopen(argv[1], "r", stdin) == NULL)
    {
        fprintf(stderr, "ReadFileError\n");
    }
    else
    {
        input_code_and_pair_brackets(EOF);
        run_code();
    }
    //    system("pause");
}
