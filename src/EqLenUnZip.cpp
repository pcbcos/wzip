//
// Created by wengz on 2022/6/16.
//

#include "EqLenUnZip.h"

inline bool getBits(uint64_t data, uint8_t pos) {

    return (data >> (64 - pos)) & 1;
}

ifstream &operator>>(ifstream &ifs, EqLenUnZip &unZip) {
    ifs.read((char *) &unZip.MATE.dict_size_bit, 8);
    ifs.read((char *) &unZip.MATE.zipped_text_size_bit, 8);
    uint16_t dict_count = unZip.MATE.dict_size_bit / 32;
    assert((dict_count > 0) && (unZip.MATE.dict_size_bit % 32 == 0));
    packed_dict_code tmp{};

    for (int i = 0; i < dict_count; i++) {
        ifs.read((char *) &tmp, sizeof(tmp));
        unZip.dict[tmp.ch].first = tmp.data;
        unZip.dict[tmp.ch].second = tmp.len;
        unZip.inv_dict[tmp.data]=tmp.ch;
    }
    unZip.length = tmp.len;
    auto pass = unZip.MATE.zipped_text_size_bit / 64;
    if (unZip.MATE.zipped_text_size_bit % 64) {
        pass++;
    }
    uint16_t key{};
    uint8_t l{};
    uint64_t len = unZip.MATE.zipped_text_size_bit;
    for (; pass > 0 && len > 0; pass--) {
        uint64_t data{};
        ifs.read((char *) &data, 8);
        for (auto i = 1; i <= 64 && len > 0; i++, len--) {
            key <<= 1;
            key += getBits(data, i);
            l++;
            if (l == unZip.length) {
                l = 0;
                unZip.text.push_back(unZip.inv_dict[key]);
                key = 0;
            }
        }
    }

    return ifs;
}

ofstream &operator<<(ofstream &ofs, const EqLenUnZip &unZip) {
    ofs << unZip.text;
    return ofs;
}
