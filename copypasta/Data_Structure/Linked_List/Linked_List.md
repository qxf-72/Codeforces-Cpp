## 基本介绍

链表是一种用于存储数据的数据结构，通过如链条一般的指针来连接元素。它的特点是插入与删除数据十分方便，但寻找与读取数据的表现欠佳。

<br/>

C++标准库中有单链表和双向链表的实现，这里主要介绍链表相关的算法。

<br/>
<br/>

## 目录索引

[Floyd判圈算法](#Floyd判圈算法)

[Floyd判圈算法求环的起点](#Floyd判圈算法求环的起点)

<br/>
<br/>

<div id="Floyd判圈算法">

## Floyd判圈算法

<div>

> Floyd判圈算法(Floyd Cycle Detection Algorithm)，又称龟兔赛跑算法(Tortoise and Hare Algorithm)，是一个可以在有限状态机、迭代函数或者链表上判断是否存在环，求出该环的起点与长度的算法。该算法据高德纳称由美国科学家罗伯特-弗洛伊德发明。

该算法可以在不使用常量空间的情况下，使用线性的时间来判断链表是否存在环。主要依赖两个快慢指针——fast、slow。fast指针一次走两步，slow指针一次走一步，如果存在环，两者必定会相遇。

```c++
bool hasCycle(ListNode *head) {
    if (!head)
        return false;
    ListNode *slow = head, *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow)
            return true;
    }
    return false;
}
```

相关题目：

[141. 环形链表](https://leetcode.cn/problems/linked-list-cycle/)

<br/>
<br/>

<div id="Floyd判圈算法求环的起点">

## Floyd判圈算法求环的起点

<div>

Floyd判圈算法能够判断链表中是否存在环，但是如果要求环的起点呢？此时快慢指针相遇节点不一定是起点节点。

[环形链表 II（双指针法，清晰图解）](https://leetcode.cn/problems/linked-list-cycle-ii/solutions/12616/linked-list-cycle-ii-kuai-man-zhi-zhen-shuang-zhi-/)

由上面文章的推导可以知，此时slow指针再走a（链表中非环部分长度）步就能回到环的起点，此时只需要增加一个指针p指向头部，和slow指针一起移动知道相遇即可。

```c++
ListNode *detectCycle(ListNode *head) {
    if (!head)
        return nullptr;
    ListNode *fast = head, *slow = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            ListNode *p = head;
            while (p != slow) {
                p = p->next;
                slow = slow->next;
            }
            return p;
        }
    }
    return nullptr;
}
```

相关题目：

[142. 环形链表 II](https://leetcode.cn/problems/linked-list-cycle-ii/)





