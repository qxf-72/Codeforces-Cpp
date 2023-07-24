## 基本介绍

`Tire`的本质，就是利用字符串之间的公共前缀，将重复的前缀合并在一起，其结构如下：

![Tire结构图](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/picture/Tire_1.png)

树中存储着一些单词的所有字母，每个节点代表一个字母，其中可以另外保存一些状态，比如是否有单词以该字母为结尾。

