//
// Created by wengz on 2022/6/16.
//
#include "datatypes.h"
#include "EqLenZip.h"


auto main() -> int {
    EqLenZip eqLenZip;
    eqLenZip << "abcdefgh";
    eqLenZip.test();
    return 0;
}