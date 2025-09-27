# FastFileToBinary

可將檔案轉換為包含二進位資料陣列的 C/C++ 標頭檔。

這個工具適用於將檔案直接嵌入到您的 C/C++ 程式中。

例如用於`ImGui`從內存中載入圖片

## 更改

此fork仓库与[Huan912/FastFileToBinary](https://github.com/Huan912/FastFileToBinary)的主要区别在于，基于Google C++ Style Guide对生成的头文件格式、内容等进行了一些优化
主要是为了满足我的个人需求，至少不要把代码搞得太乱

主要遵循以下条目 ：
- [1.2. #define 防护符](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/headers.html#define)
- [2.5. 静态和全局变量](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/scoping.html#static-and-global-variables)
- [6.12. constexpr 用法](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/others.html#constexpr)
- [7.1. 通用命名规则](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming.html#general-naming-rules)
- [7.5. 常量命名](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming.html#constant-names)
- [9.3. 空格还是制表位](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/formatting.html#id3)
- [9.14. 预处理指令](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/formatting.html#id13)
- [9.18. 水平留白](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/formatting.html#id17)

没有遵循的条目 ：
- [2.1. 命名空间](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/scoping.html#namespaces)
- [8.2. 文件注释](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/comments.html#id3)
- [8.5. 变量注释](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/comments.html#id10)

不想遵循的条目 ：
- [1.1. 自给自足的头文件](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/headers.html#self-contained-headers) “不属于头文件的文件设置为 .inc 扩展名, 并尽量避免使用.”

原仓库已经遵守的条目 ：
- [9.1. 行长度](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/formatting.html#line-length)

## 功能

- 將任何檔案轉換為 C/C++ 標頭檔（.h）
- 生成包含檔案二進位資料的 unsigned char 陣列
- 支援單次命令轉換多個檔案
- 根據輸入檔名自動生成唯一的陣列名稱
- 以十六進位格式輸出資料
- 以整潔的格式排列資料列

## 使用方法

```bash
轉換單個檔案
FastFileToBinary image.png
轉換多個檔案
FastFileToBinary image.png sound.wav data.bin
```

或是你可以直接將要轉換的檔案拖曳到 `FastFileToBinary.exe`

## 輸出格式
程式會將每個輸入檔案生成在同一個目錄的相同名稱的標頭檔。

例如：
```image.png``` → ```image.h```
```sound.wav``` → ```sound.h```

生成的標頭檔包含以下格式的陣列宣告
```cpp
unsigned char Binary_filename_data[] = {
    0xFF, 0x4A, 0x51, 0x54, ...
};
```
