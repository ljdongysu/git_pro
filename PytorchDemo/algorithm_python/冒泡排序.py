def blobSort(arr:list):
    if len(arr)<=1:
        return arr
    for i in range(0,len(arr)):
        for j in range(1,len(arr)-i):
            if arr[j-1] > arr [j]:
                temp = arr[j]
                arr[j] = arr[j-1]
                arr[j-1] = temp
    return arr
def main():
    a = [49,23,12,79,36,49,42,55,67,43,23,97]
    blobSort(a)
    print(a)
if __name__ == '__main__':
    main()