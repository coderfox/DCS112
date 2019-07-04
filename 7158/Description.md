# [algorithm]解码

## Description
Linda是中山大学16级软工的新生。她跟John经常通信，但她不喜欢直接把信息发给John，而是把信息通过一个规则转换后再发给John，这让John很郁闷。她的规则如下：如果字符x出现的n次，则将这几个连在一起的字符表示为xn，例如aaa->a3。为了能读取Linda的信息，聪明的你可以帮John解码吗？

## Input
一个字符串S，表示Linda发给John的信息，数字表示字符出现次数N；测试数据有多组，S为x时，表示结束。

## Output
一个字符串T，表示解码后的信息
## Sample Input
```
a3
go12gle
x
```
## Sample Output
```
aaa
goooooooooooogle
```
