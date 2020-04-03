##选择排序
def seleteSort(arr:list):

    for i in range(len(arr)):
        index = i
        for j in range(i,len(arr)):
            if (arr[j] < arr[index]):
                index = j
        if (index != i):
            temp = arr[i]
            arr[i] = arr[index]
            arr[index] = temp
    return arr
def main():
    a = [49,23,12,79,36,49,42,55,67,43,23,97]
    seleteSort(a)
    print(a)
if __name__ == '__main__':

    main()
