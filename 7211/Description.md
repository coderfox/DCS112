# [Exception] 课件例2

实现三个函数 `f1(int), f2(int), f3(int)`，其中`f1`调用`f2`，`f2`调用`f3`。具体要求如下：

1. 每个函数`fi`在最后均会打印 `End of fi`，其中`i=1,2,3`
2. 对于`f3`，形参为1,2,3时分别抛出如下类型错误：
	- 1：抛出`double`类型错误
	- 2：抛出`float`类型错误
	- 3：抛出`int`类型错误
3. 对于`f2`，用于捕捉来自`f3`的`int`和`float`类型的错误，并打印`A float exception occurred!--from f2`或者`An int exception occurred!--from f2`
4. 对于`f1`，用于捕捉来自未被`f2`捕捉`double`类型的错误，并打印`A double exception occurred!--from f1`

# input

# output
```
End of f3
End of f2
End of f1
A double exception occurred!--from f1
End of f1
A float exception occurred!--from f2
End of f2
End of f1
An int exception occurred!--from f2
End of f2
End of f1
End of main
```
