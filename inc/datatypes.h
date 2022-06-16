//
// Created by wengz on 2022/5/31.
//

#ifndef WZIP_DATATYPES_H
#define WZIP_DATATYPES_H
#include <memory>

typedef struct Node Node;
typedef std::shared_ptr<Node> pNode;
typedef std::pair<uint32_t, pNode> iPair;
typedef std::pair<uint16_t, uint8_t> code; //first存储最长16位编码,second存储长度
typedef struct metadata metadata;
typedef struct packed_dict_code packed_dict_code;
#ifdef __GNUC__
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif


struct Node {
    char ch;
    pNode left;
    pNode right;
};

PACK(struct metadata {
    uint64_t dict_size_bit;
    uint64_t zipped_text_size_bit;
});

PACK(struct packed_dict_code{
    char ch;
    uint16_t data;
    uint8_t len;
});
#endif //WZIP_DATATYPES_H
