
class Solution:
    def Rect(self,arr,i,j,number,maxR,maxC):
        # print("i,j: ",i,j," number: ",number)
        if maxR==0 or maxC == 0:
            return
        if (number%4 == 0):
            init_j = j
            while j - init_j < maxC:
                print(arr[i][j])
                j += 1
            number += 1
            self.Rect(arr, i + 1, j - 1, number, maxR - 1, maxC)
        elif (number % 4 == 1):
            init_i = i
            while i - init_i < maxR:
                print(arr[i][j])
                i += 1
            number += 1
            self.Rect(arr,i -1 ,j - 1,number,maxR,maxC-1)
        elif (number % 4 == 2):
            init_j = j
            while init_j - j < maxC:
                print(arr[i][j])
                j -= 1
            number += 1
            self.Rect(arr,i -1 ,j + 1,number,maxR -1 ,maxC)
        else:
            init_i = i
            while init_i - i < maxR:
                print(arr[i][j])
                i -= 1
            number += 1
            self.Rect(arr,i+1,j+1,number,maxR,maxC-1)

def main():
    matrix = [[1,2,3],[5,6,7],[9,10,11],[13,14,15]]
    b = Solution()
    b.Rect(matrix,0,0,0,len(matrix),len(matrix[0]))
if __name__ == '__main__':
    main()