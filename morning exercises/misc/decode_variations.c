#include <stdio.h>
#include <stdlib.h>

const int decodeVariations(const char *S)
{
 
  int len = strlen(S);
  int ret = 0;
  
  if (len == 0)
    return 0;
  if (len == 1)
    return 1;
  
  ret = 1;
  int prev_ret = 1;
  int prev_prev_ret = 1;

  for (int i = 1; i < len; ++i)
  {
    if ((int)S[i] - 48 < 0 || (int)S[i] - 48 > 9)
      return 0;
    
    char buf[3];
    sprintf(buf, "%c%c", S[i-1], S[i]);
    int k = atoi(buf);
    
    ret = prev_ret;
    
    if (k <= 26 && k >= 10)
      ret += prev_prev_ret;
    
    prev_prev_ret = prev_ret;
    prev_ret = ret;
  }
  
  return ret;
}

int main() 
{
	return 0;
}
