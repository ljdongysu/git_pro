import csv
import os
import shutil
def main():
    rootDir = '/home/ljdong/data/dna_data/视频版权检测算法/train-184/'
    sourceDIr = "/home/ljdong/data/dna_data/视频版权检测算法/train/"
    with open('test.csv','r') as f1:
        reader = csv.reader(f1)
        print(type(reader))
        i = 0

        for row in reader:
            if i == 0:
                i += 1
                continue

            if not os.path.exists(rootDir+row[2]):
                os.mkdir(rootDir+row[2])
            source = sourceDIr + row[0] + '.mp4'
            target = rootDir + row[2]
            if not os.path.exists(source):
                print(source)
                assert 0
            shutil.copy(source, target)
            print(source,target)

def main1():
    rootDir = '/home/ljdong/data/dna_data/视频版权检测算法/train-184/'
    i = 0
    for root,dirs,files in os.walk(rootDir):
        for name in files:

            i += 1
            print(name)
    print(i)
def main2():
    L = []
    with open('train.csv','r') as f1:
        reader = csv.reader(f1)
        print(type(reader))
        i = 0

        for row in reader:
            if i ==0 :
                i += 1
                continue
            print(row[2])

            print(type(row[2]))
            if row[2] not in L:
                L.append(row[2])
        print(len(L))
if __name__ == '__main__':
    main2()



