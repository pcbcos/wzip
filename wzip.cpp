#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <memory>
#include <bitset>
#include "HuffmanZip.h"
#include "datatypes.h"

using namespace std;


auto main(int argc, const char *argv[]) -> int {
    HuffmanZip w;

    ifstream ifs;
    ifs.open(argv[1], ifstream::in);
    ifs.unsetf(ios::skipws);
    ifs >> w;
    ifs.close();
    w.GenerateHuffmanTreeFromFreq();


    ofstream ofs;
    ofs.open(argv[2], ios::binary);
    ofs << w;//写二进制文件
    ofs.close();

    return 0;

}