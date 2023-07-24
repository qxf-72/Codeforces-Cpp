## 基本介绍

`Tire`的本质，就是利用字符串之间的公共前缀，将重复的前缀合并在一起，其结构如下：

![Tire结构图](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/picture/Tire_1.png)

树中存储着一些单词的所有字母，每个节点代表一个字母，其中可以另外保存一些状态，比如是否有单词以该字母为结尾。可用于高效判断一个字符串是否存在于一组字符串集合中，或者作为字符串集合中某个字符串的前缀。



## 模板代码

### [`Tire`](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/string/Trie.cpp)类



## 相关题目

[208.实现 Trie (前缀树)](https://leetcode.cn/problems/implement-trie-prefix-tree/)

[1032.字符流](https://leetcode.cn/problems/stream-of-characters/)

