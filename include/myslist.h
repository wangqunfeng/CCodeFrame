/******************************************************************************

  Copyright (C), NONE

 ******************************************************************************
  File Name     : myslist.h
  Version       : Initial Draft
  Author        : wangqunfeng
  Created       : 2014/8/19
  Last Modified :
  Description   : 单链表操作支持
  Function List :
              INIT_SLIST_HEAD    ~ 创建一个初始化的链表头
              __slist_add        ~ 向指定节点后添加新节点
              slist_add_head     ~ 添加新元素到链表头部
              slist_add_tail     ~ 添加新元素到链表尾部
              slist_del          ~ 删除节点,需指定待删节点和链表头
              __slist_del        ~ 删除指定节点后面的节点
              slist_empty        ~ 测试链表是否空
              slist_invert       ~ 链表反转
              slist_is_last      ~ 测试节点是否最后一个节点
              slist_is_valid     ~ 测试节点是否有效(即非空)
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
 Description  : 初始化链表头
 Input        : struct slist_head *head  ~ 链表头指针
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
 Description  : 静态创建初始化的链表头
 Input        : name  ~ 欲定义的链表头变量名称
 Caution      : 请勿直接使用SLIST_HEAD_INIT()
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define SLIST_HEAD_INIT() { NULL }
#define SLIST_HEAD(name) \
    struct slist_head name = SLIST_HEAD_INIT()

/*****************************************************************************
 FunctionName : slist_entry
 Description  : 获取链表节点结构体入口
 Input        : ptr     ~ 链表结点指针
                type    ~ 链表结点数据类型
                member  ~ 链表结点指针在节点结构中的成员名
 Caution      : 
 Return       : 链表节点结构体指针
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_entry(ptr, type, member) \
    (NULL != (ptr) ? container_of((ptr), type, member) : NULL)

/*****************************************************************************
 FunctionName : slist_next
 Description  : 获取链表中下一个节点指针
 Input        : ptr ~ 链表当前节点指针 
 Caution      : ptr禁止传NULL
 Return       : 链表中下一个节点指针
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_next(ptr) ((ptr)->next)

/*****************************************************************************
 FunctionName : slist_entry_next
 Description  : 根据当前节点所属结构体指针获取下一个节点所属结构体指针
 Input        : pos     ~ 链表结点所属结构体指针
                type    ~ 链表结点结构体数据类型
                member  ~ 链表结点指针在节点结构中的成员名
 Caution      : pos禁止传NULL
 Return       : 链表中下一节点所属结构体指针
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_entry_next(pos, type, member) \
    slist_entry((pos)->member.next, type, member)

/*****************************************************************************
 FunctionName : slist_next_safe
 Description  : 获取链表中下一个节点指针~安全接口
 Input        : ptr ~ 链表当前节点指针 
 Caution      : 
 Return       : 链表中下一个节点指针
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_next_safe(pos) ((NULL !=(pos)) ? (pos)->next : NULL)

/*****************************************************************************
 FunctionName : slist_entry_next_safe
 Description  : 根据当前节点所属结构体指针获取下一个节点所属结构体指针~安全接口
 Input        : pos     ~ 链表结点所属结构体指针
                type    ~ 链表结点结构体数据类型
                member  ~ 链表结点指针在节点结构中的成员名
 Caution      : 
 Return       : 链表中下一节点所属结构体指针
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
 Description  : 在链表头部添加节点
 Input        : struct slist_head *n     ~ 待添加节点指针
                struct slist_head *head  ~ 链表头指针
 Caution      : head禁止传NULL
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
 Description  : 在链表尾部添加节点
 Input        : struct slist_head *n     ~ 待添加节点指针
                struct slist_head *head  ~ 链表头指针
 Caution      : head禁止传NULL
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
 Description  : 链表中删除节点
 Input        : struct slist_head *n     ~ 待删节点指针
                struct slist_head *head  ~ 链表头指针
 Caution      : head、n禁止传NULL
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
 Description  : 判断链表中节点是否有效
 Input        : const struct slist_head *n  ~ 链表节点指针
 Caution      : 
 Return       : 0/non0 ~ 无效/有效
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline int slist_is_valid(const struct slist_head *n)
{
    return n != NULL; 
}

/*****************************************************************************
 FunctionName : slist_is_last
 Description  : 判断是否链表中最后一个节点
 Input        : const struct slist_head *n  ~ 链表节点指针
 Caution      : 
 Return       : 0/non0 ~ 否/是
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline int slist_is_last(const struct slist_head *n)
{
    return n->next == NULL; 
}

/*****************************************************************************
 FunctionName : slist_empty
 Description  : 判断链表是否为空
 Input        : const struct slist_head *head  ~ 链表头指针
 Caution      : 
 Return       : 0/non0 ~ 非空/空
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
static inline int slist_empty(const struct slist_head *head)
{
    return head->next == NULL;
}

/*****************************************************************************
 FunctionName : slist_invert
 Description  : 链表反转操作
 Input        : struct slist_head *head  ~ 链表头指针
 Caution      : head禁止传NULL
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
 Description  : 遍历链表for循环
 Input        : pos   ~ 活动游标:节点指针
                head  ~ 链表头指针
 Caution      : head禁止传NULL
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/18    Create
*****************************************************************************/
#define slist_for_each(pos, head) \
    for((pos) = slist_next(head); (pos) != NULL; (pos) = slist_next(pos))

/*****************************************************************************
 FunctionName : slist_for_each_safe
 Description  : 遍历链表for循环~安全接口
 Input        : ptr   ~ 活动游标:节点指针
                n     ~ 临时游标:节点指针，在遍历过程中临时使用
                head  ~ 链表头指针
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
 Description  : 遍历链表上的所有结构体
 Input        : pos     ~ 活动游标:节点所在结构体指针
                head    ~ 链表头指针
                member  ~ 链表结点指针在节点结构中的成员名
 Caution      : head禁止传NULL
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
 Description  : 遍历链表上的所有结构体 ~ 安全接口
 Input        : pos     ~ 活动游标:节点所在结构体指针
                  n     ~ 临时游标:节点所在结构体指针，在遍历过程中临时使用
                head    ~ 链表头指针
                member  ~ 链表结点指针在节点结构中的成员名
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

