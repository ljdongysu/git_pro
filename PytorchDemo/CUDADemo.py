# import torchvision
# import torch
# x = torch.cuda.FloatTensor(1)
# print(x.get_device())
# y = torch.FloatTensor(1).cuda()
# print(y.get_device())
# with torch.cuda.device(0):
#     a = torch.cuda.FloatTensor(1)
#     print(a.get_device())
#     b = torch.FlaotTensor(1).cuda()
##==========================

import torch
cuda = torch.device('cuda')
x_cpu = torch.empty(2)
x_gpu = torch.empty(2,device=cuda)
x_cpu_long = torch.empty(2,dtype=torch.int64)
print(x_cpu)
print(x_gpu)
print(x_cpu_long)
y_cpu = x_cpu.new_full([3,2],fill_value=0.3)
print(y_cpu)
y_gpu = x_gpu.new_full([3,2],fill_value=-5)
print(y_gpu)
y_cpu_long = x_cpu_long.new_tensor([[1,2,3]])
print(y_cpu_long)

z_cpu = torch.ones_like(x_cpu)
z_gpu = torch.zeros_like(x_gpu)
print(z_cpu)
print(z_gpu)
