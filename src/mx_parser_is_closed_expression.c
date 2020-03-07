#include "parser.h"

int mx_is_opening(int i, char *s, int count_slash) {
    char *opening_chars[] = {"\"", "\'", "$(", "${", "`", "(", NULL};
    int length[] = {1, 1, 2, 2, 1, 1};
    int len = 6;

    for (int j = 0; j < len; j++)
        if (count_slash % 2 == 0) // все слеши погашены
            if (strncmp( s + i, opening_chars[j], length[j]) == 0)
                return j;
    return -1;
}

int mx_is_closing(int i, char *s, int count_slash) {
    char *closing_chars[] = {"\"", "\'", ")", "}", "`", ")", NULL};
    int length[] = {1, 1, 1, 1, 1, 1};
    int len = 6;

    for (int j = 0; j < len; j++)
        if (count_slash % 2 == 0) // все слеши погашены
            if (strncmp( s + i, closing_chars[j], length[j]) == 0)
                return j;
    return -1;

}

bool mx_is_closed_expression(char *s) {
    int len = strlen(s);
    int count_slash = 0;
    bool flag = true;
    int index = -1;

    for (int i = 0; i < len; i++) {
        if (s[i] == '\\')
            count_slash++;
        else {
            if (flag) {
                int id = mx_is_opening(i, s, count_slash);
                if (id > -1) {
                    flag = false;
                    index = id;
                }
            }
            else {
                int id = mx_is_closing(i, s, count_slash);
                if (id > -1 && id == index) {
                    flag = true;
                    index = -1;
                }
            }
            count_slash = 0;
        }
    }
//    if (!flag) {
//        mx_printstr("Odd number of quotes.\n");
//    }
    return flag;
}

//#include <assert.h>
//int main(void) {
//    printf("test mx_is_closed_expression\n");
////    char *ss = "\\\\'H";
////    bool r = mx_is_closed_expression(ss);
//    char *s[] = { " 'hello' ", "\\'hello ", " \\\\'hello", "\\\\\\'hello",
//                  " 'hello' ", "'hello\\' ", " 'hello\\\\'", "'hello\\\\\\'",
//                  " 'hello' ", " 'hello ",  " \"hello\" ", " hel\"lo ",
//                  " ${hello}", "${hello",   "  $(hello)",  "$(hello",
//                  "  $hello",  "  hello ",  " `hello` ",   " hello` ",
//                  "  ~",       " ~name"  ,
//                  NULL};
//    bool test[] = {true, true, false, true,
//                   true, false, true, false,
//                   true, false, true,  false,
//                   true, false, true,  false,
//                   true, true, true,  false,
//                   true, true,
//                     NULL};
//    for (int i = 0; s[i]; i++) {
//         bool res = mx_is_closed_expression(s[i]);
//         printf("test %d\n", i+1);
//         assert(res == test[i]);
//    }
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}
