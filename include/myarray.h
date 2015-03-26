/******************************************************************************

  Copyright (C), NONE

 ******************************************************************************
  File Name     : myarray.h
  Version       : Initial Draft
  Author        : wangqunfeng
  Created       : 2014/8/19
  Last Modified :
  Description   : �������֧�� ֧�ֶ�ά����
  Function List :
              array_cp      ~ ��������
              array_printf  ~ ��ӡ����
              array_random  ~ ����������� Caution:����Ԫ����Ŀ����ʱ���ã���ʱ
***********************************History***********************************
1. wangqunfeng    2014/8/19    Create
******************************************************************************/
#include <mystddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*****************************************************************************
 MacroName                  Description
 t_array                    ����Ԫ����������
 ARRAY_MAX_RAND_NUM         Ҫ���ɵ���������
 ARRAY_MIN_RAND_NUM         Ҫ���ɵ���С�����
 ARRAY_RAND_TIMEDELAY       �����������ʱ��϶��С(��λ:ms)
 ������� 
 CONFIG_ARRAY_RAND_FLOAT    �ж���: ����Ԫ������Ϊ��������
                            �޶���: ����Ԫ������Ϊ��������
 ARRAY_MAX_RAND_NUM_FLOAT   Ҫ���ɵ�������������
 ARRAY_MIN_RAND_NUM_FLOAT   Ҫ���ɵ���С���������
 
 CONFIG_ARRAY_RAND_FLOAT_PRECIOUS
                            ���㾫�ȣ���10����������ʾ������:
                            10��ʾ��ȷ��0.1,1000��ʾ��ȷ��0.001
*****************************************************************************/
typedef float t_array;

#define ARRAY_MAX_RAND_NUM 1024
#define ARRAY_MIN_RAND_NUM 1
#define ARRAY_RAND_TIMEDELAY 1

#define ARRAY_MAX_RAND_NUM_FLOAT 99.999
#define ARRAY_MIN_RAND_NUM_FLOAT 0.001
#define CONFIG_ARRAY_RAND_FLOAT_PRECIOUS 1000

#ifndef  CONFIG_ARRAY_RAND_FLOAT
/* ���ø���������� */
#define CONFIG_ARRAY_RAND_FLOAT
#endif

/*****************************************************************************
 FunctionName : __get_miliseconds
 Description  : ������ϵͳ���������ĺ�����
 Input        : None
 Caution      : 
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/19    Create
*****************************************************************************/
static inline ul __get_miliseconds()
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

/*****************************************************************************
 FunctionName : array_random
 Description  : �����������
 Input        : void * array_addr  ~ �����׵�ַ
                size_t sz          ~ �����С
 Caution      : ���ڸ����������ݣ�������������������
                  CONFIG_ARRAY_RAND_FLOAT          ~ �������Ԫ���Ƿ�Ϊ��������
                  CONFIG_ARRAY_RAND_FLOAT_PRECIOUS ~ ���㾫�� 1000��ʾ3λС��
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline void array_random(void * array_addr, size_t sz)
{
    size_t i;
    t_array *arr = (t_array*)array_addr;
    for(i = 0; i< sz; ++i)
    {
        usleep(ARRAY_RAND_TIMEDELAY * 1000);
        srand(__get_miliseconds());
#ifdef CONFIG_ARRAY_RAND_FLOAT
        arr[i] = (rand() % (u32)(ARRAY_MAX_RAND_NUM_FLOAT * CONFIG_ARRAY_RAND_FLOAT_PRECIOUS - \
                  ARRAY_MIN_RAND_NUM_FLOAT * CONFIG_ARRAY_RAND_FLOAT_PRECIOUS) + CONFIG_ARRAY_RAND_FLOAT_PRECIOUS) * \
                  1.0 / CONFIG_ARRAY_RAND_FLOAT_PRECIOUS + ARRAY_MIN_RAND_NUM_FLOAT;
#else
        arr[i] = rand() % (ARRAY_MAX_RAND_NUM - ARRAY_MIN_RAND_NUM + 1) + ARRAY_MIN_RAND_NUM;
#endif
    }
}

/*****************************************************************************
 FunctionName : array_printf
 Description  : ��ӡ���鵽�ն�
 Input        : void * array_addr  ~ �����׵�ַ
                size_t sz          ~ �����С
                col                ~ ÿ����ʾ�����ݸ���
                fmt                ~ ��ʽ����
 Caution      : 
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline void array_printf(void * array_addr, size_t sz, size_t col, const char *fmt)
{
    size_t i;
    t_array *arr = (t_array*)array_addr;
    printf("array @ %p\n\r", arr);
    for(i = 0; i < sz; ++i)
    {
        printf(fmt, arr[i]);
        if((i+1) % col == 0)
            printf("\n\r");
        else
            printf(", ");
    }
    printf("\n\r");
}

/*****************************************************************************
 FunctionName : array_cp
 Description  : ��������
 Input        : t_array dst[]  ~ Ŀ����������
                t_array src[]  ~ Դ��������
                size_t start   ~ ��ʼ���������±�
                size_t end     ~ �������������±�
 Caution      : ����start���벻С��end
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/19    Create
*****************************************************************************/
static inline void array_cp(t_array dst[], t_array src[], size_t start, size_t end)
{
    for(; start < end; ++start)
    {
        dst[start] = src[start];
    }
}
