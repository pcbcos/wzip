#include <iostream>
#include <fstream>
#include "HuffmanZip.h"

#include <iomanip>

using std::ifstream, std::ofstream;


auto main(int argc, const char *argv[]) -> int {

    assert(("需要提供输入文件和输出文件路径", argc == 3));
    HuffmanZip w;

    ifstream ifs;
    ifs.open(argv[1], ifstream::in);
    ifs.unsetf(ios::skipws);//不跳过回车和空格符号
    ifs >> w;
    ifs.close();
    w.GenerateHuffmanTreeFromFreq();


    ofstream ofs;
    ofs.open(argv[2], ios::binary);
    ofs << w;//写二进制文件
    ofs.close();

    std::cout << "Compression Rate=" << setprecision(4) << setiosflags(std::ios::showpoint)
              << (float) w.getZipRate() * 100 << std::endl;


    return 0;

}