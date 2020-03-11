# import torch.nn.functional as F
# F.cross_entropy(x,target) == F.nll_loss(F.log_softmax(x),target) # 即F.cross_entropy(x,target) 等价于 F.log_softmax(x) + F.nll_loss(x1,target)
# F.log_softmax(x) == torch.log(F.softmax(x))
import torch
import torch.nn.functional as F

input = torch.tensor([[1.,1.],[1.0,5.0]])
target = torch.tensor([0,1])

loss1 = F.cross_entropy(input,target)
input1 = F.log_softmax(input)
# print("soft(input): ",torch.softmax(input))
print("soft(input): ",F.softmax(input))
print("log(soft(input)): ",torch.log(F.softmax(input)))
print("input1: ",input1)
print(input)
print("log: ",torch.log(input))
print("input1: {},target: {}".format(input1,target))
loss2 = F.nll_loss(input1,target)

print(" [F.cross_entropy()]:{},   [F.nll_loss() + F.log_softmax()]:{}".format(loss1,loss2))
# print(f)
# print(torch.pow(f,2))


