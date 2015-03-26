#include <mystddef.h>
#include <stdio.h>
const char *my_strstr(const char *haystack, const char *needle)
{
    const char *pos,*sub;
    if(NULL == haystack)
        return (NULL == needle) ? haystack : NULL;

again:
    sub = needle;
    while(*haystack && *haystack != *sub)
        ++haystack;
    pos = haystack;
    while(*haystack && *sub)
        if(*haystack == *sub)
            haystack++,sub++;
        else
            goto again;
    return (*sub=='\0') ? pos : NULL;
}

int main()
{
    char *s1 = "haha";
    char *s2 = "ha ap hahaello";
    printf("%s\n\r", my_strstr(s2, s1));
    return 0;
}


