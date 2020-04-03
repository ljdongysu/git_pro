##error:1.不知道如何建立多个空[]，2.没想到直接得到最大数字的位数做循环3.看了https://www.cnblogs.com/sfencs-hcy/p/10616446.html才会写的
def radixSort(arr:list):
    maxNumber = max(arr)
    Num = len(str(maxNumber))
    for i in range(1,Num+1):
        bucket = [[] for _ in range(10)]
        for j in arr:
            bucket[j//(pow(10,i-1))%10].append(j)
        arr = []
        for j in bucket:
            for k in j:
                arr.append(k)
    return arr

if __name__ == "__main__":
    array = [49,23,12,79,36,49,42,55,67,43,23,97]
    print(array)
    array = radixSort(array)
    print("堆排序最终结果:", array)