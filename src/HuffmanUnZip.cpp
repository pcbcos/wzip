//
// Created by wengz on 2022/5/31.
//

#include "HuffmanUnZip.h"
using std::make_shared;
inline bool getBit(uint64_t data, uint8_t pos) {
    return (data >> (64 - pos)) & 1;
}


ifstream &operator>>(ifstream &ifs, HuffmanUnZip &unZip) {
    ifs.read((char *) &unZip.MATE.dict_size_bit, 8);
    ifs.read((char *) &unZip.MATE.zipped_text_size_bit, 8);
    uint16_t dict_count = unZip.MATE.dict_size_bit / 32;//每个条目32位 4字节
    assert((dict_count > 0) && (unZip.MATE.dict_size_bit % 32 == 0));
    packed_dict_code tmp{};
    auto r = make_shared<Node>();
    r->ch = -1;
    r->right = nullptr;
    r->left = nullptr;
    pNode &root = unZip.HuffmanRoot;//取一个引用，简化一下表达
    root = move(r);//移动
    for (auto i = 0; i < dict_count; i++) {
        ifs.read((char *) &tmp, sizeof(tmp));//读入一个字典项
        //建树
        auto tmp_node = make_shared<Node>();
        pNode pre;
        tmp_node->ch = tmp.ch;
        int deep;
        for (pre = root, deep = tmp.len; deep > 1; deep--) {
            if (((tmp.data >> (deep - 1)) & 1) == 0) {
                if (pre->left == nullptr) {
                    pre->left = make_shared<Node>();
                    pre->left->ch = -1;
                    pre->left->left = nullptr;
                    pre->left->right = nullptr;
                }
                pre = pre->left;
            } else {
                if (pre->right == nullptr) {
                    pre->right = make_shared<Node>();
                    pre->right->ch = -1;
                    pre->right->left = nullptr;
                    pre->right->right = nullptr;
                }
                pre = pre->right;
            }
        }
        if ((tmp.data & 1) == 0) {
            pre->left = tmp_node;
        } else {
            pre->right = tmp_node;
        }
    }//树建完了
    auto pass = unZip.MATE.zipped_text_size_bit / 64;
    if (unZip.MATE.zipped_text_size_bit % 64) {
        pass++;
    }
    pNode ptr = unZip.HuffmanRoot;
    uint64_t len = unZip.MATE.zipped_text_size_bit;
    for (; pass > 0 && len > 0; pass--) {
        uint64_t data{};
        ifs.read((char *) &data, 8);
        for (auto i = 1; i <= 64 && len > 0; i++, len--) {
            if (getBit(data, i) == 0) {
                ptr = ptr->left;
            } else {
                ptr = ptr->right;
            }
            if (ptr->ch != -1) {
                unZip.text.push_back(ptr->ch);
                ptr = unZip.HuffmanRoot;
            }
        }
    }
    return ifs;
}

ofstream &operator<<(ofstream &ofs, const HuffmanUnZip &unZip) {
    ofs<<unZip.text;
    return ofs;
}
