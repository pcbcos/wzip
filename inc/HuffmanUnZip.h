//
// Created by wengz on 2022/5/31.
//

#ifndef WZIP_HUFFMANUNZIP_H
#define WZIP_HUFFMANUNZIP_H

#include "datatypes.h"
#include "fstream"
#include <cassert>

using std::ifstream,std::ofstream,std::string;

class HuffmanUnZip {
public:
    HuffmanUnZip() { text = ""; };

    friend ifstream &operator>>(ifstream &ifs, HuffmanUnZip &unZip);

    friend ofstream &operator<<(ofstream &ofs, const HuffmanUnZip &unZip);

private:
    string text;
    code dict[128]{};

    metadata MATE{};

    pNode HuffmanRoot;
};


#endif //WZIP_HUFFMANUNZIP_H
