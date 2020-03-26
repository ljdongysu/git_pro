def dec1(func):
    print("1111")

    def one():
        print("2222")
        func()
        print("3333")

    return one


def dec2(func):
    print("aaaa")

    def two():
        print("bbbb")
        func()
        print("cccc")

    return two


@dec1
@dec2
def test():
    print("test test")

print("wwwwwwwwwwwwww")
test()



#### 执行结果：
aaaa
1111
wwwwwwwwwwwwww
2222
bbbb
test test
cccc
3333

## 23-26行是装载装饰器的过程，相当于执行test=dect1(dect2(test))，此时先执行dect2(test)，结果是输出aaaa、将func指向函数test、并返回函数two，然后执行dect1(two)，结果是输出1111、将func指向函数two、并返回函数one，然后进行赋值，用函数替代了函数名test。29行则是实际调用被装载的函数，这时实际上执行的是函数one，运行到func()时执行函数two，再运行到func()时执行未修饰的函数test。
