####脚本功能
 - 1.根据以``数字x_数字y``命名的图像，将`x`作为类别区分图像
  - 2.对查询图像和库存图像进行匹配，得到准确率
#### 依赖库
 - CUDA10.0+
 - TensorRT6.0.1.5
 - opencv3.4.0
#### 运行
 - 将主函数的三个变量分别赋值``referDir：库存文件夹``，``trainDir：查询文件夹``，``modelNet：TensorRT模型``
#### 注意事项
 - 需要满足以下要求
     - 确保图像所在文件加的名字为图像的类别
     - 库存文件夹和查询文件夹中仅可存文件夹，但文件夹命名无要求(不能与上一条冲突)
   - 宏定义``CLASS_IMAGE``作用
     - 将`dirname`中图像进行分类，即脚本功能1