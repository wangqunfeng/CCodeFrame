/******************************************************************************

  Copyright (C), NONE

 ******************************************************************************
  File Name     : myarray.h
  Version       : Initial Draft
  Author        : wangqunfeng
  Created       : 2014/8/19
  Last Modified :
  Description   : 数组操作支持 支持多维数组
  Function List :
              array_cp      ~ 拷贝数组
              array_printf  ~ 打印数组
              array_random  ~ 生成随机数组 Caution:数组元素数目超大时慎用，耗时
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
 t_array                    数组元素数据类型
 ARRAY_MAX_RAND_NUM         要生成的最大随机数
 ARRAY_MIN_RAND_NUM         要生成的最小随机数
 ARRAY_RAND_TIMEDELAY       随机生成数延时间隙大小(单位:ms)
 浮点控制 
 CONFIG_ARRAY_RAND_FLOAT    有定义: 数组元素类型为浮点类型
                            无定义: 数组元素类型为整数类型
 ARRAY_MAX_RAND_NUM_FLOAT   要生成的最大随机浮点数
 ARRAY_MIN_RAND_NUM_FLOAT   要生成的最小随机浮点数
 
 CONFIG_ARRAY_RAND_FLOAT_PRECIOUS
                            浮点精度，以10的整数倍表示，例如:
                            10表示精确到0.1,1000表示精确到0.001
*****************************************************************************/
typedef float t_array;

#define ARRAY_MAX_RAND_NUM 1024
#define ARRAY_MIN_RAND_NUM 1
#define ARRAY_RAND_TIMEDELAY 1

#define ARRAY_MAX_RAND_NUM_FLOAT 99.999
#define ARRAY_MIN_RAND_NUM_FLOAT 0.001
#define CONFIG_ARRAY_RAND_FLOAT_PRECIOUS 1000

#ifndef  CONFIG_ARRAY_RAND_FLOAT
/* 启用浮点随机功能 */
#define CONFIG_ARRAY_RAND_FLOAT
#endif

/*****************************************************************************
 FunctionName : __get_miliseconds
 Description  : 返回自系统开机以来的毫秒数
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
 Description  : 生成随机数组
 Input        : void * array_addr  ~ 数组首地址
                size_t sz          ~ 数组大小
 Caution      : 对于浮点类型数据，请配置以下两个变量
                  CONFIG_ARRAY_RAND_FLOAT          ~ 随机数组元素是否为浮点类型
                  CONFIG_ARRAY_RAND_FLOAT_PRECIOUS ~ 浮点精度 1000表示3位小数
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
 Description  : 打印数组到终端
 Input        : void * array_addr  ~ 数组首地址
                size_t sz          ~ 数组大小
                col                ~ 每行显示的数据个数
                fmt                ~ 格式控制
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
 Description  : 拷贝数组
 Input        : t_array dst[]  ~ 目的数组名称
                t_array src[]  ~ 源数组名称
                size_t start   ~ 起始拷贝数组下标
                size_t end     ~ 结束拷贝数组下标
 Caution      : 传入start必须不小于end
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
