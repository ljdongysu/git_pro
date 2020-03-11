import torch
import torch.nn as nn
import torchvision
import torch.optim as optim
from torch.autograd import Variable

# ##=====================
# x = Variable(torch.randn(5,5))
# y = Variable(torch.randn(5,5))
# z = Variable(torch.randn(5, 5), requires_grad=True)
# a = x + y
# print(a.requires_grad)
# b = a + z
# print(b.requires_grad)
#
# ##===============
# model = torchvision.models.resnet18(pretrained=True)
# for param in model.parameters():
#     param.require_grad = False
# model.fc = nn.Linear(512,100)
# optimizer = optim.SGD(model.fc.parameters(),lr=1e-2,momentum=0.9)

##=================  #UserWarning: volatile was removed and now has no effect. Use `with torch.no_grad():` instead.  no a
regulart_input = Variable(torch.randn(64,3,5,5))
# volatile_input = Variable(torch.randn(5,5),volatile=True)
volatile_input = Variable(torch.randn(64,3,5, 5), volatile=True)
model = torchvision.models.resnet18(pretrained=True)
print(model(regulart_input).requires_grad)
print(model(regulart_input).volatile)
print(model(regulart_input).grad_fn)
with torch.no_grad():
    print(model(volatile_input).requires_grad)
    print(model(volatile_input).volatile)
    print(model(volatile_input).grad_fn)
