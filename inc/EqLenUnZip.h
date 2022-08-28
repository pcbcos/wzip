//
// Created by wengz on 2022/6/16.
//

#ifndef WZIP_EQLENUNZIP_H
#define WZIP_EQLENUNZIP_H

#include "datatypes.h"
#include "fstream"
#include <cassert>
#include <map>

using std::ifstream, std::ofstream, std::string,std::map;

class EqLenUnZip {
public:
    EqLenUnZip() { text = ""; };
    friend ifstream &operator>>(ifstream& ifs,EqLenUnZip& unZip);
    friend ofstream &operator<<(ofstream& ofs,const EqLenUnZip& unZip);

private:
    string text;
    code dict[128]{};
    std::map<uint16_t ,char> inv_dict{};
    metadata MATE{};
    uint8_t length;//每个字符压缩后存储的长度

};


#endif //WZIP_EQLENUNZIP_H
