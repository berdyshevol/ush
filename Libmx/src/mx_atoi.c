#include "libmx.h"

int mx_atoi(const char *str) {
  int i = 0, n = 0, sign = 1;
  if(str[0] == 0) return 0;
  while(mx_isspace(str[i])) i++;
  if(str[i] == '-') {
    sign = -1;
    i++;
  }
  if(str[i] == '+') i++;
  while (mx_isdigit(str[i])) { 
    n = (n * 10) + (str[i] - '0');
    i++;
  }
  return n * sign;
}
