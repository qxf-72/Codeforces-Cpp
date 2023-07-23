/*
    BigIntTiny类：https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/math/BigIntTiny.cpp
        - BigIntTiny类利用vector<int>存储数位，同时实现了压位，将4位压缩为1位存储
        - 具体操作方面，实现了大数之间的<,>,==,!=,<=,>=,*,/,%的操作
        - 在具体测试时，发现除法操作时间消耗极高，在需要进行除法操作时建议使用BigInt_simplest类
*/


/*
    BigInt_simplest类：https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/math/BigInt_simplest.cpp
        - 利用数组int [] 存储数位
        - 实现了大数和int的乘法，大数和int的除法，大数和int的<操作
        - 只能进行正数的运算
*/

