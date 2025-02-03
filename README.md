# FastFileToBinary

可將檔案轉換為包含二進位資料陣列的 C/C++ 標頭檔。

這個工具適用於將檔案直接嵌入到您的 C/C++ 程式中。

例如用於`ImGui`從內存中載入圖片

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
