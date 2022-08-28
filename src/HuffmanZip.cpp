//
// Created by wengz on 2022/5/31.
//

#include "HuffmanZip.h"

using namespace std;

auto HuffmanZip::pre(const pNode &r, code c) {
    if (!r.get()) return;
    if (r->ch == -1) {
        auto [value, len] = c;
        pre(r->left, make_pair(value << 1, len + 1));
        pre(r->right, make_pair((value << 1) | 1, len + 1));
        return;
    } else {
        dict[r->ch] = c;
        MATE.dict_size_bit += 32;
        return;
    }
}

auto HuffmanZip::GenerateHuffmanTreeFromFreq() -> void {
    assert(!this->text.empty());
    for (auto i = 0; i < 128; i++) {
        if (!freq[i]) continue;
        auto n = make_shared<Node>();
        n->ch = i;
        n->left = nullptr;
        n->right = nullptr;
        auto p = make_pair(freq[i], move(n));
        q.push(move(p));
    }
    while (q.size() != 1) {
        auto n3 = make_shared<Node>();
        n3->ch = -1;
        auto [f1, n1] = q.top();
        n3->left = n1;
        q.pop();
        auto [f2, n2] = q.top();
        n3->right = n2;
        q.pop();
        auto f3 = f1 + f2;
        q.push(make_pair(f3, n3));
    }
    HuffmanRoot = q.top().second;
    q.pop();
    pre(HuffmanRoot, make_pair(0, 0));//生成字典
}

ofstream &operator<<(ofstream &ofs, HuffmanZip& huff) {
    //先写入字典大小
    ofs.write((char *) &huff.MATE.dict_size_bit, 8);
    ofs.seekp(16);
    std::queue<pNode> q;
    if (huff.HuffmanRoot) {
        q.push(huff.HuffmanRoot);
    }
    //层次遍历,写入字典信息
    while (!q.empty()) {
        auto n = q.front();
        q.pop();
        if (n->ch != -1) {
            ofs.put(n->ch);
            ofs.write((char *) &huff.dict[n->ch].first, 2);
            ofs.write((char *) &huff.dict[n->ch].second, 1);
        }
        if (n->left) {
            q.push(n->left);
        }
        if (n->right) {
            q.push(n->right);
        }
    }
    //写入主体部分
    std::bitset<1024> bit_set;
    vector<uint64_t> s;
    s.reserve(1024 / 64);
    uint16_t space{1024};
    uint64_t sz{};
    constexpr bitset<1024> ullmask(0xFFFFFFFFFFFFFFFF);
    for (auto c: huff.text) {
        auto [cd, len] = huff.dict[c];
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
        //满了
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
    //把bit_set里剩下的输出出来
    //没有对齐64位,强制对齐
    if ((1024 - space) % 64 != 0) {
        bit_set <<= (64 - (1024 - space) % 64);
        //sz+=(64 - (1024 - space) % 64);
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
    ofs.seekp(8);
    ofs.write((char *) &sz, 8);
    huff.setZipRate((float) sz / (huff.text.length() * 8));
    return ofs;
}

void HuffmanZip::operator<<(char c) {
    freq[(size_t) c]++;
    text.push_back(c);
}

auto HuffmanZip::test() {
    while (!q.empty()) {
        auto [f, node] = q.top();
        q.pop();
        if (node->ch != '\n') {
            std::cout << f << ' ' << node->ch << '\n';
        } else {
            std::cout << f << ' ' << '\\' << 'n' << '\n';
        }
    }
}

ifstream &operator>>(ifstream &ifs, HuffmanZip &huff) {
    huff.text = "";
    char c;
    ifs >> c;
    while (ifs.good()) {
        huff << c;
        ifs >> c;
    }
    return ifs;
}

auto HuffmanZip::getZipRate() const -> float {
    return ZipRate;
}

void HuffmanZip::setZipRate(float zipRate) {
    ZipRate=zipRate;
}
