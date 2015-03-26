/******************************************************************************

  Copyright (C), NONE

 ******************************************************************************
  File Name     : mystddef.h
  Version       : Initial Draft
  Author        : wangqunfeng
  Created       : 2014/8/19
  Last Modified :
  Description   : 自定义标准头文件 定义了基本的常用数据类型和一些简单的操作
  Function List :
***********************************History***********************************
1. wangqunfeng    2014/8/19    Create
******************************************************************************/

#ifndef _MY_STDDEF_H
#define _MY_STDDEF_H

#undef NULL
#if defined(__cplusplus)
#define NULL 0
#else
typedef enum {
    false = 0,
    true  = 1,
}bool;
#define NULL ((void *)0)
#endif

#ifndef ERROR_GENERIC
#define ERROR_GENERIC -1
#endif

#ifndef STACK_SIZE
#define STACK_SIZE -1
#endif

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned long ul;

typedef signed long long s64;
typedef signed int s32;
typedef signed short s16;
typedef signed char s8;
typedef signed long sl;

#define INT_MAX     ((int)(~0U>>1))
#define INT_MIN     (-INT_MAX -1)
#define UINT_MAX    (~0U)
#define LONG_MAX    ((long)(~0UL>>1))
#define LONG_MIN    (-LONG_MAX - 1)
#define ULONG_MAX   (~0UL)

#define STACK_MAGIC 0xdeadbeef

#define EDOM    33
#define EILSEQ  47
#define ERANGE  34

#define min(x,y) ({  \
    typeof(x) _x = (x);  \
    typeof(y) _y = (y);  \
    (void)(&_x == &_y);    \
    _x < _y ? __x : _y; })
    
#define max(x,y) ({  \
    typeof(x) _x = (x);  \
    typeof(y) _y = (y);  \
    (void)(&_x == &_y);    \
    _x > _y ? __x : _y; })
    
#define swap(x,y) ({  \
    typeof(x) _x = (x);  \
    (x) = (y);    \
    (y) = _x; })
    
#define min_t(type, x, y) \
    ({ type __x = (x); type __y = (y); __x < __y ? __x : __y ; })

#define max_t(type, x, y) \
        ({ type __x = (x); type __y = (y); __x > __y ? __x : __y ; })
        

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#define container_of(ptr, type, member) ({ \
    const typeof(((type *)0)->member) * __mptr = (ptr); \
    (type *)((char *)__mptr - offsetof(type, member)); })

#define typecheck(type, x) \
({  type __dummy; \
    typeof(x) __dummy2; \
    (void)(&__dummy == &__dummy2); \
    1; \
})

#define typecheck_fn(type, function) \
({  typeof(type) __tmp = function; \
    (void)__tmp; \
})

#ifndef prefetch
#define prefetch(x) (x)
#define prefetchw(x) (x,1)
#endif

#define LIST_POISON1 ((void *)0X00100100)
#define LIST_POISON2 ((void *)0x00200200)

#define SLIST_POISON1 LIST_POISON1
#define SLIST_POISON2 LIST_POISON2

#endif
