#include "parser.h"

static void helper1(int id, bool *flag, int *index);
static void helper2(int id, bool *flag, int *index);
static int mx_is_closing(int i, char *s, int count_slash);
static int mx_is_opening(int i, char *s, int count_slash);

bool mx_is_closed_expression(char *s) {
    int count_slash = 0;
    bool flag = true;
    int index = -1;

    for (int i = 0; s[i]; i++) {
        if (s[i] == '\\')
            count_slash++;
        else {
            if (flag) {
                helper1(mx_is_opening(i, s, count_slash), &flag, &index);
            }
            else {
                helper2(mx_is_closing(i, s, count_slash), &flag, &index);
            }
            count_slash = 0;
        }
    }
    return flag;
}

static void helper1(int id, bool *flag, int *index) {
    if (id > -1) {
        *flag = false;
        *index = id;
    }
}

static void helper2(int id, bool *flag, int *index) {
    if (id > -1 && id == *index) {
        *flag = true;
        *index = -1;
    }
}

static int mx_is_opening(int i, char *s, int count_slash) {
    char *opening_chars[] = {"\"", "\'", "$(", "${", "`", "(", NULL};
    int length[] = {1, 1, 2, 2, 1, 1};
    int len = 6;

    for (int j = 0; j < len; j++)
        if (count_slash % 2 == 0) // все слеши погашены
            if (strncmp( s + i, opening_chars[j], length[j]) == 0)
                return j;
    return -1;
}

static int mx_is_closing(int i, char *s, int count_slash) {
    char *closing_chars[] = {"\"", "\'", ")", "}", "`", ")", NULL};
    int length[] = {1, 1, 1, 1, 1, 1};
    int len = 6;

    for (int j = 0; j < len; j++)
        if (count_slash % 2 == 0) // все слеши погашены
            if (strncmp( s + i, closing_chars[j], length[j]) == 0)
                return j;
    return -1;

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
//                  " $(hello)", " $(hello ",
//                  NULL};
//    bool test[] = {true, true, false, true,
//                   true, false, true, false,
//                   true, false, true,  false,
//                   true, false, true,  false,
//                   true, true, true,  false,
//                   true, true,
//                   true, false,
//                     NULL};
//    for (int i = 0; s[i]; i++) {
//         bool res = mx_is_closed_expression(s[i]);
//         printf("test %d\n", i+1);
//         assert(res == test[i]);
//    }
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush");
//    return 0;
//}
