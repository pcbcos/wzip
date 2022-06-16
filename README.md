# 2022辅修数据结构课程设计
## 构建
### Use GCC/Clang+CMake
```shell
git clone https://github.com/pcbcos/wzip
cd wzip
mkdir build
cmake -B build . -G "Unix Makefiles"
cmake --build build
cd bin #可执行文件所在路径
```

### Use MSVC(VS2022)+CMake
```shell
git clone https://github.com/pcbcos/wzip
cd wzip
mkdir build
cmake -B build . -G "Visual Studio 17 2022"
cmake --build build
cd bin/Debug #可执行文件所在路径
```

## 使用方法
### 压缩
```shell
wzip.exe [input filename] [output filename]
```

### 解压缩
```shell
unwzip.exe [input filename] [output filename]
```