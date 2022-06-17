//
// Created by wengz on 2022/6/16.
//

#ifndef WZIP_EQLENZIP_H
#define WZIP_EQLENZIP_H

#include "datatypes.h"
#include <vector>
#include <set>
#include <iostream>
#include <bitset>

class EqLenZip {
public:
    EqLenZip() {
        text="";
    };

    friend std::ofstream& operator<<(std::ofstream& ofs,const EqLenZip& eqzip);

    friend std::ifstream & operator>>(std::ifstream& ifs,EqLenZip& Eqzip);

    void operator<<(char c);

    void operator<<(std::string_view str);

    void test();
private:
    void GenerateDict();
private:

    std::set<char> kind;//出现过的字符

    std::string text;//文本总体

    code dict[128]{};//生成的字典

    metadata MATE{};//元数据



};


#endif //WZIP_EQLENZIP_H
