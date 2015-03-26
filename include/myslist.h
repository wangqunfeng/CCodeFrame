/******************************************************************************

  Copyright (C), NONE

 ******************************************************************************
  File Name     : myslist.h
  Version       : Initial Draft
  Author        : wangqunfeng
  Created       : 2014/8/19
  Last Modified :
  Description   : ���������֧��
  Function List :
              INIT_SLIST_HEAD    ~ ����һ����ʼ��������ͷ
              __slist_add        ~ ��ָ���ڵ������½ڵ�
              slist_add_head     ~ �����Ԫ�ص�����ͷ��
              slist_add_tail     ~ �����Ԫ�ص�����β��
              slist_del          ~ ɾ���ڵ�,��ָ����ɾ�ڵ������ͷ
              __slist_del        ~ ɾ��ָ���ڵ����Ľڵ�
              slist_empty        ~ ���������Ƿ��
              slist_invert       ~ ����ת
              slist_is_last      ~ ���Խڵ��Ƿ����һ���ڵ�
              slist_is_valid     ~ ���Խڵ��Ƿ���Ч(���ǿ�)
***********************************History***********************************
1. wangqunfeng    2014/8/19    Create
******************************************************************************/

#ifndef _MY_SLIST_H
#define _MY_SLIST_H

#include <mystddef.h>

struct slist_head {
    struct slist_head *next;
};

/*****************************************************************************
 FunctionName : INIT_SLIST_HEAD
 Description  : ��ʼ������ͷ
 Input        : struct slist_head *head  ~ ����ͷָ��
 Caution      : 
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline void INIT_SLIST_HEAD(struct slist_head *head)
{
    head->next = NULL;
}

/*****************************************************************************
 FunctionName : SLIST_HEAD
 Description  : ��̬������ʼ��������ͷ
 Input        : name  ~ �����������ͷ��������
 Caution      : ����ֱ��ʹ��SLIST_HEAD_INIT()
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define SLIST_HEAD_INIT() { NULL }
#define SLIST_HEAD(name) \
    struct slist_head name = SLIST_HEAD_INIT()

/*****************************************************************************
 FunctionName : slist_entry
 Description  : ��ȡ����ڵ�ṹ�����
 Input        : ptr     ~ ������ָ��
                type    ~ ��������������
                member  ~ ������ָ���ڽڵ�ṹ�еĳ�Ա��
 Caution      : 
 Return       : ����ڵ�ṹ��ָ��
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_entry(ptr, type, member) \
    (NULL != (ptr) ? container_of((ptr), type, member) : NULL)

/*****************************************************************************
 FunctionName : slist_next
 Description  : ��ȡ��������һ���ڵ�ָ��
 Input        : ptr ~ ����ǰ�ڵ�ָ�� 
 Caution      : ptr��ֹ��NULL
 Return       : ��������һ���ڵ�ָ��
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_next(ptr) ((ptr)->next)

/*****************************************************************************
 FunctionName : slist_entry_next
 Description  : ���ݵ�ǰ�ڵ������ṹ��ָ���ȡ��һ���ڵ������ṹ��ָ��
 Input        : pos     ~ �����������ṹ��ָ��
                type    ~ ������ṹ����������
                member  ~ ������ָ���ڽڵ�ṹ�еĳ�Ա��
 Caution      : pos��ֹ��NULL
 Return       : ��������һ�ڵ������ṹ��ָ��
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_entry_next(pos, type, member) \
    slist_entry((pos)->member.next, type, member)

/*****************************************************************************
 FunctionName : slist_next_safe
 Description  : ��ȡ��������һ���ڵ�ָ��~��ȫ�ӿ�
 Input        : ptr ~ ����ǰ�ڵ�ָ�� 
 Caution      : 
 Return       : ��������һ���ڵ�ָ��
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_next_safe(pos) ((NULL !=(pos)) ? (pos)->next : NULL)

/*****************************************************************************
 FunctionName : slist_entry_next_safe
 Description  : ���ݵ�ǰ�ڵ������ṹ��ָ���ȡ��һ���ڵ������ṹ��ָ��~��ȫ�ӿ�
 Input        : pos     ~ �����������ṹ��ָ��
                type    ~ ������ṹ����������
                member  ~ ������ָ���ڽڵ�ṹ�еĳ�Ա��
 Caution      : 
 Return       : ��������һ�ڵ������ṹ��ָ��
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_entry_next_safe(pos, type, member) \
    ((NULL != (pos)) ? slist_entry((pos)->member.next, type, member) : NULL)

static inline void __slist_add(struct slist_head *n, struct slist_head *prev)
{
    n->next = prev->next;
    prev->next = n;
}

/*****************************************************************************
 FunctionName : slist_add_head
 Description  : ������ͷ����ӽڵ�
 Input        : struct slist_head *n     ~ ����ӽڵ�ָ��
                struct slist_head *head  ~ ����ͷָ��
 Caution      : head��ֹ��NULL
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline void slist_add_head(struct slist_head *n, struct slist_head *head)
{
    __slist_add(n, head);
}

/*****************************************************************************
 FunctionName : slist_add_tail
 Description  : ������β����ӽڵ�
 Input        : struct slist_head *n     ~ ����ӽڵ�ָ��
                struct slist_head *head  ~ ����ͷָ��
 Caution      : head��ֹ��NULL
 Return       : static
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline void slist_add_tail(struct slist_head *n, struct slist_head *head)
{
    while(head->next && (head = head->next));
    __slist_add(n, head);
}

static inline void __slist_del(struct slist_head *prev)
{
    prev->next = prev->next->next;
}

/*****************************************************************************
 FunctionName : slist_del
 Description  : ������ɾ���ڵ�
 Input        : struct slist_head *n     ~ ��ɾ�ڵ�ָ��
                struct slist_head *head  ~ ����ͷָ��
 Caution      : head��n��ֹ��NULL
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline void slist_del(struct slist_head *n, struct slist_head *head)
{
    while(NULL != head->next && head->next != n && (head = head->next));
    if(head && head->next)
        __slist_del(head);
    n->next = SLIST_POISON1;
}

/*****************************************************************************
 FunctionName : slist_is_valid
 Description  : �ж������нڵ��Ƿ���Ч
 Input        : const struct slist_head *n  ~ ����ڵ�ָ��
 Caution      : 
 Return       : 0/non0 ~ ��Ч/��Ч
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline int slist_is_valid(const struct slist_head *n)
{
    return n != NULL; 
}

/*****************************************************************************
 FunctionName : slist_is_last
 Description  : �ж��Ƿ����������һ���ڵ�
 Input        : const struct slist_head *n  ~ ����ڵ�ָ��
 Caution      : 
 Return       : 0/non0 ~ ��/��
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline int slist_is_last(const struct slist_head *n)
{
    return n->next == NULL; 
}

/*****************************************************************************
 FunctionName : slist_empty
 Description  : �ж������Ƿ�Ϊ��
 Input        : const struct slist_head *head  ~ ����ͷָ��
 Caution      : 
 Return       : 0/non0 ~ �ǿ�/��
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline int slist_empty(const struct slist_head *head)
{
    return head->next == NULL;
}

/*****************************************************************************
 FunctionName : slist_invert
 Description  : ����ת����
 Input        : struct slist_head *head  ~ ����ͷָ��
 Caution      : head��ֹ��NULL
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline void slist_invert(struct slist_head *head)
{
    struct slist_head *pos, *n, *temp;
    for(pos = head->next, n = slist_next_safe(pos);
        pos != NULL & n != NULL;
        pos = n, n = temp)
    {
        temp = n->next;
        n->next = pos;
    }

    if(head->next != NULL)
        head->next->next = NULL;
    head->next = pos;
}

/*****************************************************************************
 FunctionName : slist_for_each
 Description  : ��������forѭ��
 Input        : pos   ~ ��α�:�ڵ�ָ��
                head  ~ ����ͷָ��
 Caution      : head��ֹ��NULL
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_for_each(pos, head) \
    for((pos) = slist_next(head); (pos) != NULL; (pos) = slist_next(pos))

/*****************************************************************************
 FunctionName : slist_for_each_safe
 Description  : ��������forѭ��~��ȫ�ӿ�
 Input        : ptr   ~ ��α�:�ڵ�ָ��
                n     ~ ��ʱ�α�:�ڵ�ָ�룬�ڱ�����������ʱʹ��
                head  ~ ����ͷָ��
 Caution      : 
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_for_each_safe(ptr, n, head) \
    for((ptr) = slist_next_safe(head), (n) = slist_next_safe(ptr); \
        (ptr) != NULL; \
        (ptr) = (n), (n) = slist_next_safe(ptr))

/*****************************************************************************
 FunctionName : slist_for_each_entry
 Description  : ���������ϵ����нṹ��
 Input        : pos     ~ ��α�:�ڵ����ڽṹ��ָ��
                head    ~ ����ͷָ��
                member  ~ ������ָ���ڽڵ�ṹ�еĳ�Ա��
 Caution      : head��ֹ��NULL
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_for_each_entry(pos, head, member) \
    for((pos) = slist_entry(slist_next(head), typeof(*(pos)), member); \
        ((pos) != NULL) &&prefetch((pos)->member.next), (pos) != NULL; \
        (pos) = slist_entry_next(pos, typeof(*(pos)), member))

/*****************************************************************************
 FunctionName : slist_for_each_entry_safe
 Description  : ���������ϵ����нṹ�� ~ ��ȫ�ӿ�
 Input        : pos     ~ ��α�:�ڵ����ڽṹ��ָ��
                  n     ~ ��ʱ�α�:�ڵ����ڽṹ��ָ�룬�ڱ�����������ʱʹ��
                head    ~ ����ͷָ��
                member  ~ ������ָ���ڽڵ�ṹ�еĳ�Ա��
 Caution      : 
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_for_each_entry_safe(pos, n, head, member) \
    for((pos) = slist_entry(slist_next_safe(head), typeof(*(pos)), member), \
        (n) = slist_entry_next_safe(pos, typeof(*(pos)), member); \
        (pos) != NULL; \
        (pos) = (n), (n) = slist_entry_next_safe(pos, typeof(*(pos)), member))
        
#endif

