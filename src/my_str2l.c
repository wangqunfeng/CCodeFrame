#include <mystddef.h>
#include <myallege.h>
#include <stdio.h>

long my_str2l(const char *nptr, char **endptr, int base)
{
    ul result = 0;
    long sign = 1;
    /* ���˵���ʼ�Ŀո� */
    while(isspace(*nptr))
        ++nptr;
    /* ��ȡ������Ϣ */
    if(*nptr == '-')
    {
        sign = -1; 
        ++nptr;
    }
    /* ���û��ָ��x���ƣ��������ʼ�ַ��жϽ��� */
    if(base == 0)
    {
        if(*nptr == '0' &&(nptr[1] == 'x' || nptr[1] == 'X'))
        {
            nptr +=2;
            base = 16;
        }
        else if(*nptr == '0')
        {
            nptr++;
            base = 8;
        }
        else
            base = 10;
    }
    /* ���Խ��ƴ����޴��� */
    allege((base>=2 && base<=36), "invalid base");

    /* ѭ�����������ַ������ۼӵ������ */
    while(*nptr != '\0' && 
          ((*nptr>='0' && *nptr<('0'+base)) || (tolower(*nptr)>='a' && tolower(*nptr)<('a'+ base - 10))))
    {
        if(tolower(*nptr)>='a')
        {
            result = result * base + (tolower(*nptr) - 'a' + 10);
        }
        else
        {
            result = result * base + (*nptr -'0');
        }
        nptr++;
    }
    /* ��������ʶָ�� */
    if(NULL != endptr)
        *endptr = (char *)nptr;

    return result * sign;
}


int main()
{
    char arr[20];
    scanf("%s",arr);
    printf("%s, parse result: %ld\n\r",arr, my_str2l(arr, NULL, 0));
    return 0;
}
