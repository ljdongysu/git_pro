##也可以新建一个空list，然后插入排序
def insertSort(arr:list):
    if len(arr) <= 1:
        return arr
    for i in range(1,len(arr)):
        for j in range(i):
            if arr[i] < arr[j]:
                inserLocatoin(j,i,arr)
                break
    return arr
def inserLocatoin(location,endLocation,arr):##
    value = arr[endLocation]
    for i in range(location,endLocation):
        temp = arr[i]
        arr[i] = value
        value = temp
    arr[endLocation] = value
    return arr

def main():

    a = [49,23,12,79,36,49,42,55,67,43,23,97]
    print(insertSort(a))
if __name__ == '__main__':
    main()














for i in range(10,5,-1):
    print(i)