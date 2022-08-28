//
// Created by wengz on 2022/6/16.
//


#include "EqLenZip.h"
#include "fstream"
#include "cmath"

using namespace std;

std::ofstream &operator<<(std::ofstream &ofs, const EqLenZip &eqzip) {

    //先写入字典大小
    ofs.write((char *) &eqzip.MATE.dict_size_bit, 8);
    //写入压缩后的文本大小
    ofs.write((char *) &eqzip.MATE.zipped_text_size_bit, 8);
    //写入字典
    for (auto c: eqzip.kind) {
        ofs.put(c);
        ofs.write((char *) (&(eqzip.dict[c].first)), 2);
        ofs.write((char *) (&(eqzip.dict[c].second)), 1);
    }
    //写入主体部分
    std::bitset<1024> bit_set;
    vector<uint64_t> s;
    s.reserve(1024 / 64);
    uint16_t space{1024};
    uint64_t sz{};
    constexpr bitset<1024> ullmask(0xFFFFFFFFFFFFFFFF);
    for (auto c: eqzip.text) {
        auto [cd, len] = eqzip.dict[c];
        sz += len;
        code res{};
        if (len <= space) {
            bit_set <<= len;
            bit_set |= cd;
            space -= len;
        } else {
            bit_set <<= space;
            bit_set |= (cd >> (len - space));
            res.first = cd & ((1 << (len - space)) - 1);
            res.second = len - space;
            space = 0;
        }
        if (space == 0) {
            for (auto i = 0; i < 1024 / 64; i++) {
                s.push_back((bit_set & ullmask).to_ullong());
                bit_set >>= 64;
            }
            bit_set.reset();
            while (!s.empty()) {
                uint64_t i = s.back();
                ofs.write((char *) &i, 8);
                s.pop_back();
            }
            bit_set |= res.first;
            space = 1024 - res.second;
            res = {0, 0};
        }
    }
    if ((1024 - space) % 64 != 0) {
        bit_set <<= (64 - (1024 - space) % 64);
        space -= (64 - (1024 - space) % 64);
    }
    auto count = (1024 - space) / 64;//计算剩余的64位单元
    //压栈
    for (auto i = 0; i < count; i++) {
        s.push_back((bit_set & ullmask).to_ullong());
        bit_set >>= 64;
    }
    bit_set.reset();//清0
    while (!s.empty()) {
        uint64_t i = s.back();
        ofs.write((char *) &i, 8);//输出
        s.pop_back();
    }
    space = 1024;

    return ofs;

}

std::ifstream &operator>>(ifstream &ifs, EqLenZip &eqzip) {
    eqzip.text = "";
    char c;
    ifs >> c;
    while (ifs.good()) {
        eqzip << c;
        ifs >> c;
    }
    eqzip.GenerateDict();
    return ifs;
}

void EqLenZip::operator<<(char c) {
    text.push_back(c);
    kind.insert(c);
}

void EqLenZip::test() {
    for (auto c: kind) {
        std::cout << c << '\n';
    }
    uint8_t len = ceil(std::log2(kind.size()));
    std::cout << (int) len;
}

void EqLenZip::operator<<(std::string_view str) {
    for (auto c: str) {
        (*this) << c;
    }
}

void EqLenZip::GenerateDict() {
    uint8_t len = ceil(std::log2(kind.size()));
    uint16_t code = 0;
    for (char c: kind) {
        dict[c].first = code;
        dict[c].second = len;
        code++;
    }
    MATE.dict_size_bit = kind.size() * 32;
    MATE.zipped_text_size_bit = text.size() * len;
}


