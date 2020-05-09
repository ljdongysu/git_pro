##区分官方dataset与自写dataset的载入图像区别，自己在入用opencv且需要将Normalize换rg通道

from torchvision import datasets, transforms
import torch
import cv2
from torch.utils import data

__imagenet_stats = {'mean': [0.485, 0.456, 0.406],
                    'std': [0.229, 0.224, 0.225]}
# __imagenet_stats = {'mean': [0.406, 0.456, 0.485],
#                     'std': [0.225, 0.224, 0.229]}


def inception_preproccess(input_size, normalize=__imagenet_stats):
    return transforms.Compose([
        # transforms.RandomResizedCrop(input_size),
        # transforms.RandomHorizontalFlip(),
        transforms.Resize((input_size,input_size)),
        transforms.ToTensor(),
        transforms.Normalize(**normalize)
    ])


def scale_crop(input_size, scale_size=None, normalize=__imagenet_stats):
    t_list = [
        transforms.CenterCrop(input_size),
        transforms.ToTensor(),
        transforms.Normalize(**normalize),
    ]
    if scale_size != input_size:
        t_list = [transforms.Resize(scale_size)] + t_list

    return transforms.Compose(t_list)

def get_transform(augment=True, input_size=224):
    normalize = __imagenet_stats
    scale_size = int(input_size / 0.875)
    if augment:
        return inception_preproccess(input_size=input_size, normalize=normalize)
    else:
        return scale_crop(input_size=input_size, scale_size=scale_size, normalize=normalize)

class DataSetTest(data.Dataset):
    def __init__(self, imageListFile, officalTransform=None):
        file = open(imageListFile,'r')
        self.imagesPath = file.read().split()
        file.close()
        self.officalTransform = officalTransform

    def __getitem__(self, item):
        image = cv2.imread(self.imagesPath[item])
        image = self.officalTransform(self.forTorch(image))
        image = image[(2,1,0),:,:]
        return image, int(self.imagesPath[item].split('/')[-2])
    def __len__(self):
        return len(self.imagesPath)

    def forTorch(self, image):
        print(image.shape)
        print(image.transpose(2, 0, 1).shape)
        return torch.from_numpy(image.transpose(2, 0, 1))

def main():
    train_data = datasets.ImageFolder(root="/home/ubuntu/ljdong/image/",
                                      transform=get_transform(input_size=224))
    train_loader = torch.utils.data.DataLoader(train_data, batch_size=64, shuffle=False,
                                               pin_memory=True)
    for i in train_data:
        print(i)
        print(i[0].shape)

    normalize = transforms.Normalize(mean=[0.406, 0.456, 0.485],
                                     std=[0.225, 0.224,0.229])
    #
    #
    # normalize = transforms.Normalize(mean=[0.485, 0.456, 0.406],
    #                                  std=[0.229, 0.224, 0.225])

    quaryDataloader = DataSetTest("/home/ubuntu/ljdong/test.txt",transforms.Compose([
        transforms.ToPILImage(),
        transforms.Resize((224,224)),
        transforms.ToTensor(),
        normalize,
        # transforms.Normalize(**normalize)
        # transforms.Lambda(lambda x: x.mul(255))
    ]))

    for i in quaryDataloader:
        print(i)
        print(i[0].shape)

if __name__ == '__main__':
    main()
