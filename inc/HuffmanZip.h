//
// Created by wengz on 2022/5/31.
//

#ifndef WZIP_HUFFMANZIP_H
#define WZIP_HUFFMANZIP_H

#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <memory>
#include <bitset>
#include "datatypes.h"
#include <cassert>

using namespace std;

class HuffmanZip {
private:

    auto pre(const pNode &r, code c);

public:

    HuffmanZip() {
        freq.resize(128, 0);
        text = "";
    };

    friend ofstream &operator<<(ofstream &ofs, HuffmanZip &huff);

    friend ifstream &operator>>(ifstream &ifs, HuffmanZip &huff);

    auto GenerateHuffmanTreeFromFreq() -> void;

    void operator<<(char c);

    auto test();

    auto getZipRate() const->float;

    void setZipRate(float zipRate);

private:
    vector<uint32_t> freq;

    priority_queue<iPair, vector<iPair>, std::greater<>> q;

    string text;

    code dict[128]{};

    float ZipRate{};

    metadata MATE{};

    pNode HuffmanRoot;
};


#endif //WZIP_HUFFMANZIP_H
