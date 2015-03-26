/******************************************************************************

  Copyright (C), NONE

 ******************************************************************************
  File Name     : myallege.h
  Version       : Initial Draft
  Author        : wangqunfeng
  Created       : 2014/8/19
  Last Modified :
  Description   : ���Բ���֧��
  Function List :
              allege    ~ ���ʽ��ֵ�������
              allegemem ~ �ڴ��������
              allegefile~ �ļ���������
***********************************History***********************************
1. wangqunfeng    2014/8/19    Create
******************************************************************************/

#ifndef _MY_ALLEGE_H
#define _MY_ALLEGE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

inline void allege_error(int val, const char *msg)
{
    if(val)
    {
        fprintf(stderr, "error: %s\n\r", msg);
    #ifdef NDEBUG
        exit(1);
    #endif
    }
}

#define allege(expr, msg) \
{   allege_error((expr) ? 1 : 0, msg); \
    assert(expr); \
}
#define allegemem(expr) \
    allege(expr, "out of memory");

#define allegefile(expr) \
    allege(expr, "could not open file");

#endif
