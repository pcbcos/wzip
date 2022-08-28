//
// Created by wengz on 2022/6/16.
//
#include <cassert>
#include <fstream>
#include "datatypes.h"
#include "EqLenZip.h"
#include <iomanip>

using std::ifstream;

auto main(int argc, const char *argv[]) -> int {
    assert(("需要提供输入文件和输出文件路径", argc == 3));
    EqLenZip eqLenZip;
    ifstream ifs;
    ifs.open(argv[1], ifstream::in);
    ifs.unsetf(std::ios::skipws);
    ifs >> eqLenZip;
    ifs.close();

    std::ofstream ofs;
    ofs.open(argv[2], std::ios::binary);
    ofs << eqLenZip;
    ofs.close();

    std::cout << "Compression Rate=" << std::setprecision(4) << setiosflags(std::ios::showpoint)
              << (float) eqLenZip.getZipRate() * 100 << std::endl;
    return 0;
}