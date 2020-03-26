import cv2
import os

import numpy as np


def get_filename(fileDir):
    L = []
    F = []
    for root, dirs, files in os.walk(fileDir):
        for file in files:
            L.append(root + '/' + file)
            F.append(file)
    return L, F


def imgconcat_row(imgleft,imgright):
    if (imgleft.shape[0]!=imgright.shape[0] or imgleft.shape[2] != imgright.shape[2] ):
        print(imgleft.shape)
        print(imgright.shape)
        print("other dim is not equal!")
        assert 0
    h1,w1,c1 = imgleft.shape
    h2,w2,c3 = imgright.shape
    img = np.zeros((h1,w1+w2,c),np.uint8)
    img[:,:w1,:] = imgleft
    img[:,w1:w1+w2,:] = imgright
    return img

# img = imgconcat_row(img1,img2)
# cv2.imshow("img1",img1)
# cv2.imshow("img2",img2)
# cv2.imshow("img",img)
#
# cv2.waitKey(0)
def generatefilename(referpath,quarypath,concatpath):
    filename = "refer_" + referpath.split("/")[-2]
    filename += "_quary_" + quarypath.split("/")[-2]
    filename += "_truth_" + concatpath.split("/")[-2]
    return filename
def get_truthimg(referpath,quarypath):
    truthclass = quarypath.split("/")[-2]
    rootpath = "/".join(referpath.split("/")[:-2])
    truthpath = rootpath+"/"+truthclass
    L,_ = get_filename(truthpath)

    return L[0]

def main():
    referpath = "/home/ljdong/data/dna_data/imageDataset/refer/Parasite/116/3994.jpg"
    quarypath = "/home/ljdong/data/dna_data/imageDataset/train/Parasite/132/4786.jpg"
    img1 = cv2.imread(referpath)
    img2 = cv2.imread(quarypath)

    img4 = get_truthimg(referpath,quarypath)
    img_4 = cv2.imread(img4)

    img3 = imgconcat_row(img1,img2)
    img3 = imgconcat_row(img3,img_4)
    cv2.imshow("imgreger: ",img1)
    cv2.imshow("imgquary:",img2)
    cv2.imshow("imgtruth",img_4)
    cv2.imshow("imgconcat",img3)
    print(generatefilename(referpath,quarypath,img4))
    cv2.waitKey(0)
if __name__ == '__main__':
    main()
