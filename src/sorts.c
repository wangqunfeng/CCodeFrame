#include <mystddef.h>
#include <myslist.h>
#include <myarray.h>
#include <stdio.h>
#include <malloc.h>

static ssize_t sort_quick_partition(t_array arr[], ssize_t low, ssize_t high)
{
    t_array key = arr[low];
    while(low < high)
    {
        while(low < high && arr[high]>=key)
            high--;
        arr[low] = arr[high];
        while(low < high && arr[low]<=key)
            low++;
        arr[high] = arr[low];
    }
    arr[low] = key;
    return low;
}

/*****************************************************************************
 FunctionName : sort_quick
 Description  : 快速排序算法
 Input        : t_array arr[]  
                ssize_t low     
                ssize_t high    
 Caution      : 
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/19    Create
*****************************************************************************/
void sort_quick(t_array arr[], ssize_t low, ssize_t high)
{
    ssize_t mid;
    if(low<high)
    {
        mid = sort_quick_partition(arr, low,high);
        sort_quick(arr,low, mid - 1);
        sort_quick(arr, mid+1, high);
    }
}

/*****************************************************************************
 FunctionName : sort_bubble
 Description  : 冒泡排序
 Input        : t_array arr[]  
                ssize_t sz      
 Caution      : 
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/20    Create
*****************************************************************************/
void sort_bubble(t_array arr[], ssize_t sz)
{
    ssize_t i,j;
    for(i=0; i<sz; ++i)
    {
        for(j=0; j<sz-1-i; ++j)
        {
            if(arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

/*****************************************************************************
 FunctionName : sort_select
 Description  : 选择排序
 Input        : t_array arr[]  
                ssize_t sz      
 Caution      : 
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/20    Create
*****************************************************************************/
void sort_select(t_array arr[], ssize_t sz)
{
    ssize_t i,j;
    for(i=0;i<sz-1;++i)
    {
        for(j=i+1;j<sz;++j)
        {
            if(arr[j] < arr[i])
                swap(arr[i], arr[j]);
        }
    }
}

/*****************************************************************************
 FunctionName : sort_insert
 Description  : 直接插入排序
 Input        : t_array arr[]  
                ssize_t sz      
 Caution      : 
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/20    Create
*****************************************************************************/
void sort_insert(t_array arr[], ssize_t sz)
{
    ssize_t i,j;
    t_array temp;
    for(i=0;i<sz-1;++i)
    {
        j = i+1;
        temp = arr[j];
        while(j-1 >= 0 && temp<arr[j-1])
        {
            arr[j] = arr[j-1];
            --j;
        }
        arr[j] = temp;
    }
}

void __sort_merge(t_array arr[], ssize_t low, ssize_t split, ssize_t high, t_array arr_temp[])
{
    ssize_t k,l,r;
    k = l = low;
    r = split + 1;
    while(l<=split && r<=high)
    {
        if(arr[l] < arr[r])
        {
            arr_temp[k++] = arr[l++];
        }
        else
        {
            arr_temp[k++] = arr[r++];
        }
    }
    
    /* 处理边界情况，右侧已复制完 */
    while(l <= split)
        arr_temp[k++] = arr[l++];
    /* 处理边界情况，左侧已复制完 */
    while(r <= high)
        arr_temp[k++] = arr[r++];
    
    array_copy(arr, arr_temp, low, high);
}

void _sort_merge(t_array arr[], ssize_t low, ssize_t high, t_array arr_temp[])
{
    ssize_t mid;
    if(low < high)
    {
        mid = (low + high)/2;
        _sort_merge(arr, low, mid, arr_temp);
        _sort_merge(arr, mid+1, high, arr_temp);
        __sort_merge(arr, low, mid, high, arr_temp);
    }
}

/*****************************************************************************
 FunctionName : sort_merge
 Description  : 两路归并排序
 Input        : t_array arr[]  
                ssize_t sz     
 Caution      : 
 Return       : 
***********************************History***********************************
 wangqunfeng    2014/8/20    Create
*****************************************************************************/
void sort_merge(t_array arr[], ssize_t sz)
{
    t_array *arr_temp = (t_array *)malloc(sz * sizeof(t_array));
    if(NULL == arr_temp)
        return;
    _sort_merge(arr, 0, sz - 1, arr_temp);
    free(arr_temp);
}

void sort_heap_adjust_min_heap(t_array arr[], ssize_t pos, ssize_t len)
{
    t_array temp, child;
    for(temp = arr[pos]; 2*pos + 1 <= len; pos = child)
    {
        child = 2 * pos + 1;
        if(child < len && arr[child] < arr[child + 1])
            child ++;
        if(arr[child] > temp)
            arr[pos] = arr[child];
        else
            break;
    }
    arr[pos] = temp;
}

void sort_heap_min(t_array arr[], ssize_t sz)
{
    ssize_t i;
    for(i=sz/2-1;i>=0;--i)
        sort_heap_adjust_min_heap(arr, i, sz-1);
    for(i=sz-1;i>=0;--i)
    {
        swap(arr[0], arr[i]);
        sort_heap_adjust_min_heap(arr, 0, i-1);
    }
}


int main()
{
    /* 随机数组生成测试 */
    t_array arr[24],arr2[24];
    array_random(arr,24);
    array_copy(arr2, arr, 0,24-1);
    
    printf("orginal array\n\r");
    array_printf(arr,24, 8, "%4d");
    sort_heap_min(arr, 24);
    array_printf(arr,24, 8, "%4d");

    array_copy(arr, arr2, 0,24-1);
    array_printf(arr,24, 8, "%4d");
    sort_bubble(arr, 24);
    printf("after sort bubble\n\r");
    array_printf(arr,24, 8, "%4d");
/*    
    array_copy(arr, arr2, 0,24-1);
    printf("orginal array\n\r");
    array_printf(arr,24, 8, "%4d");
    sort_select(arr, 24);
    printf("after sort select\n\r");
    array_printf(arr,24, 8, "%4d");

    array_copy(arr, arr2, 0,24-1);
    printf("orginal array\n\r");
    array_printf(arr,24, 8, "%4d");
    sort_quick(arr, 0, 24-1);
    printf("after sort quick\n\r");
    array_printf(arr,24, 8, "%4d");
    
    array_copy(arr, arr2, 0,24-1);
    printf("orginal array\n\r");
    array_printf(arr,24, 8, "%4d");
    sort_insert(arr, 24);
    printf("after sort insert\n\r");
    array_printf(arr,24, 8, "%4d");
   
    array_copy(arr, arr2, 0,24-1);
    printf("orginal array\n\r");
    array_printf(arr,24, 8, "%4d");
    sort_merge(arr, 24);
    printf("after sort merge\n\r");
    array_printf(arr,24, 8, "%4d");
   */ 
    return 0;
}

