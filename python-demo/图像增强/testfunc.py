# coding=utf-8
# cv2解决绘制中文乱码

import cv2
import numpy
from PIL import Image, ImageDraw, ImageFont


def cv2ImgAddText(img, text, left, top, textColor=(255,255,255), textSize=1):
    if (isinstance(img, numpy.ndarray)):  # 判断是否OpenCV图片类型
        img = Image.fromarray(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    # 创建一个可以在给定图像上绘图的对象
    draw = ImageDraw.Draw(img)
    # 字体的格式
    fontStyle = ImageFont.truetype('NotoSansCJK-Bold.ttc', textSize, encoding="utf-8")
    draw.text((left, top), text, textColor, font=fontStyle)
    # 转换回OpenCV格式
    return cv2.cvtColor(numpy.asarray(img), cv2.COLOR_RGB2BGR)

def LoadPutTxt(txtFile):
    files = open(txtFile)
    putTxt = []
    for line in files:
        putTxt.append(line)
    return putTxt
import random
if __name__ == '__main__':
    a = 0
    b = 0
    c = 0
    for i in range(1000):
        randomRa = random.randint(1,4)
        print(randomRa)
        if randomRa == 1:
            a += 1
        elif randomRa == 2:
            b += 1
        else:
            c += 1
    print(a/1000,b/1000,c/1000)
    ss = "abc\n\nd"
    print(ss.rstrip())
    print(1)
    print(min([1,2],[2,0]))
    putTxt = LoadPutTxt("lrc")
    text = putTxt[random.randint(0,len(putTxt)-1)]
    img = cv2.imread('/home/ljdong/PycharmProjects/transform/image/1_1.jpg')
    text = text.rstrip('\n')
    print(text)
    print("a")
    print("b")
    text.rstrip()
    for i in range(1000):
        img = cv2ImgAddText(img, text, 10, 10, (255,255, 255), 10)

    cv2.imshow('show', img)

    cv2.waitKey(0)