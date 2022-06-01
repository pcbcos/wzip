//
// Created by wengz on 2022/5/31.
//
#include <iostream>
#include <fstream>
#include "HuffmanUnZip.h"


auto main(int argc, const char *argv[]) -> int {
    ifstream ifs;
    ifs.open(argv[1], ios::binary);
    HuffmanUnZip uw;
    ifs >> uw;
    ifs.close();

    ofstream ofs;
    ofs.open(argv[2]);
    ofs << uw;
    ofs.close();


    return 0;
}