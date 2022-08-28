//
// Created by wengz on 2022/8/28.
//
#include <iostream>
#include <fstream>
#include "EqLenUnZip.h"

auto main(int argc, const char *argv[])->int{
    assert(("需要提供输入文件和输出文件路径",argc==3));
    ifstream ifs;
    ifs.open(argv[1], std::ios::binary);
    EqLenUnZip uw;
    ifs >> uw;
    ifs.close();

    ofstream ofs;
    ofs.open(argv[2]);
    ofs << uw;
    ofs.close();

    return 0;
}