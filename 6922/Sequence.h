#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class Sequence {
 public:
  Sequence();
  ~Sequence();
  int size();
  bool empty();
  bool find(int value);//能否找到这个value这个元素
  int &at(int pos);//返回第pos个元素
  int front(); //返回第一个字符
  int back(); //返回最后一个字符
  void insert(int value); //插入元素 value
  void insert(int pos, int value); //在pos之后插入元素value
  void clear();//变空
  void reverse(); //全部翻转
  void reverse(int fir, int las); //从哪里到哪里反转
  void replace(int value1, int value2);
  void swap(Sequence &seq2);//将类本身的序列和seq2交换
  int *a;
  int msize;
  bool mempty;
};
#endif