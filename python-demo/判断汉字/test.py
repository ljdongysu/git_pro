#coding = utf-8
import re
import os
def savetxt(srcfile,savefile):
    f = open(srcfile,'r')
    file = f.read().split()
    zhmodel = re.compile(u'[\u4e00-\u9fa5]')  #检查中文
    for i,src in enumerate(file):
        match = zhmodel.search(src)
        if match:
            savefile.write(src)
            savefile.write('\n')
    f.close()
def get_filename(fileDir):
    L = []
    F = []
    for root, dirs, files in os.walk(fileDir):
        for file in files:
            L.append(root + '/' + file)
            F.append(file)
    return L, F
def main():
    txtDir = "/txt"
    fileList, _ = get_filename(txtDir)
    resulttxt = "file1.txt"
    resultwrite = open(resulttxt,'w')
    for srctxt in fileList:
        savetxt(srctxt,resultwrite)
    resultwrite.close()


if __name__ == '__main__':
    main()

