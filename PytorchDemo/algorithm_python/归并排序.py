##归并排序需要多看实现过程  error：1.不知道怎么分而置之，不知道怎么将整个数组分为单个一组，需要left，mid，right三个判断好，其中middle需要+1才能防止无限递归 2.合并条件需要多个变量控制条件

def mergeSort(arr:list):
    left = 0
    right = len(arr) -1
    devSort(arr,left,right)

def mergeArray(array,left,middle,right):

    temp = array.copy()
    t1 = left
    t2 = middle + 1
    start = left
    while (t1 <= middle and right >= t2):
        if (array[t1] < array[t2]):
            temp[start] = array[t1]
            t1 += 1
        else:
            temp[start] = array[t2]
            t2 += 1
        start += 1
    print("while: ",array)
    print("while: ",temp)
    print("start: ",start)


    while t1 <= middle:
        temp[start] = array[t1]
        t1 += 1
        start += 1
    while right >= t2:
        temp[start] = array[t2]
        t2 += 1
        start += 1
    for i in range(left,right+1):
        array[i] = temp[i]
    print(left,middle,right)
    print(array)
    print("\n\n")

def devSort(arr:list,left,right):
    if left < right:
        middle = (right + left) // 2
        if middle > left:
            devSort(arr,left,middle)
        if right > middle + 1:
            devSort(arr,middle+1,right)
        mergeArray(arr,left,middle,right)


a = [49,23,12,79,36,49,42,55,67,43,23,97]
mergeSort(a)
print(a)
