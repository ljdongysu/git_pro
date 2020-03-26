# encoding:utf-8
import cv2
import random
import numpy as np
import os
from PIL import Image, ImageDraw, ImageFont



CROP_CETER = 1
CROP_RANDOM = 2
logoSizeRatio = 0.15
logoDisYRatio = 0.05
subImageRatio = 0.3
logoPast = 1
subImagePast = 0
lineSize = 15
firstCropRatio = 0.1

def FileName(fileDir):
    L = []
    for root, dirs, files in os.walk(fileDir):
        for file in files:
            L.append(root + '/' + file)
    return L

class transform(object):
    def __init__(self, cropHeight, cropWidth, textFile:str = None, logoDir:str = None):
        self.cropHeight = cropHeight
        self.cropWidth = cropWidth
        self.FuncProbability = [1,1,1,1,1,1,1,1,1]
        # self.FuncProbability = [0.5,0.5,0.5,1,0.5,0.5,0.5,0.5,0.5]

        self.firstLeftRatio = random.uniform(0,1)
        self.firstTopRatio = random.uniform(0,1)
        self.firstRightRatio = random.uniform(0,1)
        self.firstBottomRatio = random.uniform(0,1)

        self.resizeRatioMin = 0.9
        self.resizeRatioMax = 1.1

        self.cropType = random.randint(1,3)
        self.cropLeft = random.uniform(0,1)
        self.cropTop = random.uniform(0,1)

        self.blackRandom = random.uniform(0, 0.2)
        self.rotationRandom = random.randint(0, 360)
        self.resizeRatoi = random.uniform(self.resizeRatioMin,self.resizeRatioMax)

        self.putTxt = self.LoadPutTxt(textFile)
        self.putTxtLeft = random.uniform(0, 0.5)
        self.putTxtTop = random.uniform(0.8, 0.9)
        self.randomTxtSize = random.uniform(0.5,1)
        self.randomTxt = self.putTxt[random.randint(0,len(self.putTxt)-1)]

        self.pastTop = random.uniform(0,1)
        self.pastLeft = random.uniform(0,1)

        self.logoList = FileName(logoDir)
        self.randomLogo = self.logoList[random.randint(0, len(self.logoList) - 1)]
        self.pastDown = random.randint(0,1)

        self.randomH = random.uniform(0.95,1.05)
        self.randomS = random.uniform(0.95,1.05)
        self.randomL = random.uniform(0.95,1.05)

        self.flipRandom = random.randint(0, 2)
        self.logoRatio = 0.5

    def RandomParameter(self):

        self.firstLeftRatio = random.uniform(0,1)
        self.firstTopRatio = random.uniform(0,1)
        self.firstRightRatio = random.uniform(0,1)
        self.firstBottomRatio = random.uniform(0,1)

        self.cropType = random.randint(1,3)
        self.cropLeft = random.uniform(0,1)
        self.cropTop = random.uniform(0,1)

        self.blackRandom = random.uniform(0, 0.2)
        self.rotationRandom = random.randint(0, 360)
        self.resizeRatoi = random.uniform(self.resizeRatioMin,self.resizeRatioMax)

        self.putTxtLeft = random.uniform(0, 0.5)
        self.putTxtTop = random.uniform(0.8, 0.9)
        self.randomTxtSize = random.uniform(0.5,1)
        self.randomTxt = self.putTxt[random.randint(0,len(self.putTxt)-1)]

        self.pastTop = random.uniform(0,1)
        self.pastLeft = random.uniform(0,1)

        self.randomLogo = self.logoList[random.randint(0, len(self.logoList) - 1)]
        self.pastDown = random.randint(0,1)

        self.randomH = random.uniform(0.95,1.05)
        self.randomS = random.uniform(0.95,1.05)
        self.randomL = random.uniform(0.95,1.05)

        self.flipRandom = random.randint(0, 2)

    def LoadPutTxt(self,txtFile):
        files = open(txtFile)
        putTxt = []
        for line in files:
            putTxt.append(line)
        return putTxt

    def BlackBound(self, img):
        heightBound = int(self.blackRandom * img.shape[0])
        widthBound = int(self.blackRandom * img.shape[1])
        resizeHeight = img.shape[0] - 2 * heightBound
        resizeWidth = img.shape[1] - 2 * widthBound
        image = cv2.resize(img, (resizeWidth,resizeHeight))
        image = cv2.copyMakeBorder(image, heightBound, heightBound,widthBound, widthBound, cv2.BORDER_CONSTANT, value=0)
        return image

    def Rotation(self, img):
        image = cv2.getRotationMatrix2D(((img.shape[1] - 1) / 2.0, (img.shape[0] - 1) / 2.0), self.rotationRandom, 1)
        img = cv2.warpAffine(img, image, (img.shape[1], img.shape[0]))
        return img

    def FirstCrop(self, img):
        left = int(self.firstLeftRatio * firstCropRatio * img.shape[0])
        top = int(self.firstTopRatio * firstCropRatio * img.shape[1])
        right = int((1 - self.firstRightRatio * firstCropRatio) * img.shape[0])
        bottom = int((1 - self.firstBottomRatio * firstCropRatio) * img.shape[1])
        image = img[left:right,top:bottom,:]
        return image

    def Resize(self, img):
        image = cv2.resize(img, (int(self.cropHeight * self.resizeRatoi), int(self.cropWidth * self.resizeRatoi)))
        return image

    def CropResize(self,img):
        if (img.shape[0] < self.cropHeight or img.shape[1] < self.cropWidth):
            maxRatio = max(self.cropHeight / img.shape[0], self.cropWidth / img.shape[1])
            cropHeight = int(maxRatio * img.shape[0])
            cropWeight = int(maxRatio * img.shape[1])
            cropHeight = max(224,cropHeight)
            cropWeight = max(224,cropWeight)
            img = cv2.resize(img,(cropWeight,cropHeight))

        width = img.shape[1] - self.cropWidth
        height = img.shape[0] - self.cropHeight
        return width,height,img

    def Crop(self, img):
        width, height,img = self.CropResize(img)
        if(self.cropType == CROP_CETER):
            left = width//2
            top = height//2
            img = img[top:top+self.cropHeight,left:left+self.cropWidth]

        elif(self.cropType == CROP_RANDOM):
            left = int(self.cropLeft * width)
            top = int(self.cropTop * height)
            img = img[top:top+self.cropHeight,left:left+self.cropWidth]

        else:
            return cv2.resize(img,(self.cropWidth, self.cropHeight))

        return img

    def PutTxt(self, img):
        if(len(self.putTxt) < 1):
            print("Add txt need a txt file when this class inited!\n")
            assert (0)
        image = self.ImgAddText(img, self.randomTxt, int(self.putTxtLeft * img.shape[1]),int(self.putTxtTop * img.shape[0]))
        return image

    def ImgAddText(self, img, text, left, top, textColor=(255, 255, 255), textSize = lineSize):
        meanLightness = np.mean(0.299 * img[left:,:,2] + 0.587 * img[left:,:,1] + 0.114 * img[left:,:,0])
        if(meanLightness > 127):
            textColor = (0,0,0)
        if (isinstance(img, np.ndarray)):  # 判断是否OpenCV图片类型
            img = Image.fromarray(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
        draw = ImageDraw.Draw(img)
        fontStyle = ImageFont.truetype('NotoSansCJK-Bold.ttc', textSize, encoding="utf-8")
        text = text.rstrip('\n')
        draw.text((left, top), text, textColor, font=fontStyle)
        return cv2.cvtColor(np.asarray(img), cv2.COLOR_RGB2BGR)

    def Logo(self, img):
        if(len(self.logoList) < 1):
            print("Add logo need a dir include logo images when this class inited!\n")
            assert (0)
        logo = cv2.imread(self.randomLogo)
        logo = cv2.resize(logo, (int(img.shape[1] * logoSizeRatio), int(img.shape[0] * logoSizeRatio)))
        image = self.Past(img, logo, logoPast)
        return image

    def SubImage(self, img):
        subImage = cv2.resize(img, (int(img.shape[1] * subImageRatio), int(img.shape[0] * subImageRatio)))
        image = self.Past(img, subImage, subImagePast)
        return image

    def Past(self,image, pastImg,flag):
        imagePast = image.copy()
        pastImgHeight = pastImg.shape[0]
        pastImgWidth = pastImg.shape[1]
        left = int(self.pastLeft * (image.shape[1] - pastImgWidth))
        top = 0
        if(flag == logoPast):
            if(self.pastDown):
                top = int(logoDisYRatio * self.pastTop * image.shape[0])
            else:
                top = int((1 - logoDisYRatio * self.pastTop) * image.shape[0]) - pastImgHeight
        else:
            if(self.pastDown):
                top = image.shape[0] - pastImgHeight
        imagePast[top:top + pastImgHeight, left:left + pastImgWidth] = pastImg[:, :]
        return imagePast

    def AdjustHLS(self, img):
        image = cv2.cvtColor(img, cv2.COLOR_BGR2HLS)
        image[:,:,0] = np.minimum(image[:,:,0] * self.randomH, 255)
        image[:,:,1] = np.minimum(image[:,:,1] * self.randomL, 255)
        image[:,:,2] = np.minimum(image[:,:,2] * self.randomS, 255)
        image = cv2.cvtColor(image,cv2.COLOR_HLS2BGR)
        return image

    def Flip(self, img):
        cv2.flip(img, self.flipRandom - 1, img)
        return img

    def Run(self,img, funcList:list):
        for f in funcList:
            img = f(img)
        return img

    def FuncList(self):
        logoProbility = random.uniform(0,1)
        if logoProbility > self.logoRatio :
            funcList = [self.FirstCrop, self.BlackBound, self.Resize, self.Rotation, self.Crop, self.AdjustHLS, self.PutTxt, self.Logo,
                         self.Flip]
        else:
            funcList = [self.FirstCrop, self.BlackBound, self.Resize, self.Rotation, self.Crop, self.AdjustHLS, self.PutTxt, self.SubImage,
                         self.Flip]
        return funcList

    def RandomFunction(self, images:list):
        size = len(self.FuncProbability)
        randomList = [random.uniform(0,1) for _ in range(size)]
        funcAll = self.FuncList()

        funcList = []
        select = [r <= f for r, f in zip(randomList, self.FuncProbability)]
        for i, s in enumerate(select):
            if(s):
                funcList.append(funcAll[i])
        imageList = []
        self.RandomParameter()
        for image in images:
            imageList.append(self.Run(image,funcList))
        return imageList

def main():
    root = "image"
    file = FileName(root)
    imageList = []
    for i in range(24):
        img = cv2.imread(file[i])
        imageList.append(img)
    textFile = "lrc"
    logoDir = "/home/ljdong/code/qt/dna_data/image/image_center"
    transformImages = transform(224,224,textFile,logoDir)
    images = transformImages.RandomFunction(imageList)
    for i in range(len(images)):
        cv2.imshow("abc",images[i])
        cv2.waitKey(0)

if __name__ == '__main__':
    main()