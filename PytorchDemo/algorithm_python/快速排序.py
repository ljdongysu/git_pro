# ##error：1.陷入死循环，没有判断调用递归条件，2.low和high自减自增没判断low<high导致之后的low>high，3.掉头时候赋值没判断low<high还是值的问题导致掉头，4.掉头时候的自增自减5.先面两个参考方法
######### error: 第二次看发现判断递归条件出现问题，没有正确判断递归条件，切没进行确定为+-1

# def quick_sort(self, value_list):
#     """
#     快速排序
#     :param value_list: 无序列表
#     :return:
#     """
#     low = 0
#     high = len(value_list) - 1
#     self.__qsort(value_list, low, high)
#     sorted_list = value_list
#     return sorted_list
#
# def __qsort(self, val_list, low, high):
#     """
#     快速排序辅助函数
#     :param val_list: 无序列表
#     :param low: 低位
#     :param high: 高位
#     :return:
#     """
#     if low >= high:
#         return
#     pivot_key = low
#     tmp_low = pivot_key
#     tmp_high = high
#     while low < high:  # 分成一边比轴（pivot）大，一边比轴（pivot）小的顺序
#         while low < high:
#             if val_list[high] < val_list[pivot_key]:
#                 tmp = val_list[high]
#                 val_list[high] = val_list[pivot_key]
#                 val_list[pivot_key] = tmp
#                 pivot_key = high
#                 break  # 发生交换后，就换方向
#             else:
#                 high -= 1
#         while low < high:
#             if val_list[low] > val_list[pivot_key]:
#                 tmp = val_list[low]
#                 val_list[low] = val_list[pivot_key]
#                 val_list[pivot_key] = tmp
#                 pivot_key = low
#                 break  # 发生交换后，就换方向
#             else:
#                 low += 1
#     self.__qsort(val_list, tmp_low, pivot_key - 1)
#     self.__qsort(val_list, pivot_key + 1, tmp_high)
def fastSort(arr:list):
    low = 0
    high = len(arr)-1
    flag = 0
    fastLocationSort(arr,low,high,flag)
    return arr


def fastLocationSort(arr,low,high,flag):
    temp = arr[flag]
    flagLow = low
    flagHigh = high
    while(low < high):
        print(arr)
        while(arr[high] > temp and low < high):
            high -= 1
        if(low < high):
            arr[low] = arr[high]
            low += 1
        print(arr,"up: ",low,high)

        while(arr[low] < temp and low < high):
            low += 1
        if (low < high):
            arr[high] = arr[low]
            high -= 1
        print(arr,"down: ",low,high)

    print("first: ",arr)
    arr[high] = temp
    print(arr,flagLow,flagHigh,high)
    print("flag: ",flagHigh,flagLow,flag,high)

    if(flagLow<high-1):
        fastLocationSort(arr,flagLow,high-1,flagLow)
    if (flagHigh>high+1):
        fastLocationSort(arr,high+1,flagHigh,high+1)
def main():
    a = [49,23,12,79,36,49,42,55,67,43,23,97]
    #[12, 23, 23, 36, 42, 43, 49, 49, 55, 67, 79, 97]
    fastSort(a)
    print(a)
if __name__ == '__main__':
    main()