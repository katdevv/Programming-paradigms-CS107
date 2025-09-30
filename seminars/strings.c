#include <stdio.h>
#include <stdlib.h>

int _strcmp(const char *s1, const char *s2) {
  int i = 0;
  while(s1[i] != '\0' && s2[i] != '\0') {
    if(s1[i] != s2[i]) return s1[i] - s2[i];
    i++;
  }
    return s1[i] - s2[i];
}

char *_strcpy(char *dest, const char *src)
{
    int i = 0;
    while(src[i] != 0) {
      dest[i] = src[i];
      i++;
    }
    dest[i] = '\0';
    return dest;
}

size_t _strlen(const char *s)
{
    int i = 0;
    while(s[i] != '\0') i++;
    return i;
}

char *_strcat(char *dest, const char *src)

{
    int len = _strlen(dest);
    _strcpy(dest + len, src);
    return dest;
}

char *_strdup(const char *s)
{
    int len = _strlen(s);
    char* p = malloc((len + 1) * sizeof(char));
    return _strcpy(p, s);
}

void *_memset(void *s, int c, size_t n)
{
    for (int i = 0; i < n; i++){
       *((int*)s + i) = c;
    }
    return s;
}

char *ConcatStrings(const char *first, const char *second)
{
  int strLen = _strlen(first);
  int strLen2 = _strlen(second);
  char* p = malloc((strLen + strLen2 + 1)* sizeof(char));
  for (int i = 0; i < strLen; i++){
    p[i] = first[i];
  }
  for (int i = 0; i <= strLen2; i++){
    p[i + strLen] = second[i];
  }
  return p;
}

int main()
{
    // strcmp
    printf("strcmp:\n");
    char *s1 = "abcde";
    char *s2 = "abcdd";
    int strcmpRes = _strcmp(s1, s2);
    if (strcmpRes > 0)
    {
        printf("    s1: %s is greater than s2: %s by %d\n", s1, s2, strcmpRes);
    }
    else if (strcmpRes < 0)
    {
        printf("    s1: %s is less than s2: %s by %d\n", s1, s2, strcmpRes);
    }
    else
    {
        printf("    s1: %s is equal to s2: %s\n", s1, s2);
    }
    printf("\n");

    printf("strcmp:\n");
    char *s1_1 = "abcde";
    char *s2_2 = "bcde";
    int strcmpRes_2 = _strcmp(s1_1, s2_2);
    if (strcmpRes_2 > 0)
    {
        printf("    s1: %s is greater than s2: %s by %d\n", s1, s2, strcmpRes_2);
    }
    else if (strcmpRes_2 < 0)
    {
        printf("    s1: %s is less than s2: %s by %d\n", s1, s2, strcmpRes_2);
    }
    else
    {
        printf("    s1: %s is equal to s2: %s\n", s1_1, s2_2);
    }
    printf("\n");

    // strcpy
    printf("strcpy:\n");
    char buffer[50];
    char *strToCopy = "abcde";
    printf("    function returns: %s\n", _strcpy(buffer, strToCopy));
    printf("    buffer string after function call: %s\n", buffer);
    printf("\n");

    // strlen
    printf("strlen:\n");
    char *s3 = "Programming";
    char *s4 = "Paradigms";
    printf("    s3: %s len is %zu\n", s3, _strlen(s3));
    printf("    s4: %s len is %zu\n", s4, _strlen(s4));
    printf("\n");

    // strcat
    printf("strcat:\n");
    char buffer2[50];
    _strcpy(buffer2, "Start ");

    printf("    function returns: %s\n", _strcat(buffer2, "First"));
    printf("    function returns: %s\n", _strcat(buffer2, " Second"));
    printf("    function returns: %s\n", _strcat(buffer2, " Third"));
    printf("    buffer2 after function calls: %s\n", buffer2);
    printf("\n");

    // strdup
    printf("strdup:\n");
    char *originStr = "Strdup First Example";
    char *newStr = _strdup("Strdup First Example");
    printf("    newStr: %s\n", newStr);
    printf("    originStr value address is %p\n", (void *)originStr);
    printf("    newStr value address is %p\n", (void *)newStr);
    printf("\n");

    // memset
    printf("memset:\n");
    char memsetBuffer[50];
    _memset((void *)memsetBuffer, 'A', 40);
    printf("    buffer after memset call: %s\n", memsetBuffer);

    // concat
    char *string1 = "abc";
    char *string2 = "de";
    char *result = ConcatStrings(string1, string2);
    printf("string1: %s\n", string1);
    printf("string2: %s\n", string2);
    printf("result: %s\n", result);
    printf("addresses (can't be the same):\n");
    printf("1: %p, 2: %p, r: %p\n", string1, string2, result);
}