#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

std::string extractFileName(const std::string& filePath)
{
    size_t pos = filePath.find_last_of("/\\");
    return filePath.substr(pos + 1);
}

std::string generateArrayName(const std::string& inputFileName)
{
    std::string fileName = extractFileName(inputFileName);
    size_t pos = fileName.find_last_of('.');
    std::string baseName = (pos == std::string::npos) ? fileName : fileName.substr(0, pos);
    std::string arrayName = "Binary_" + baseName + "_data";
    return arrayName;
}

std::string generateOutputFileName(const std::string& inputFileName)
{
    std::string fileName = extractFileName(inputFileName);
    size_t pos = fileName.find_last_of('.');
    std::string baseName = (pos == std::string::npos) ? fileName : fileName.substr(0, pos);
    std::string outputFileName = baseName + ".h";
    return outputFileName;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file1> <file2> ..." << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) 
    {
        std::ifstream inputFile(argv[i], std::ios::binary);
        if (!inputFile)
        {
            std::cerr << "Error opening input file: " << argv[i] << std::endl;
            continue;
        }

        std::string outputFileName = generateOutputFileName(argv[i]);
        std::ofstream outputFile(outputFileName);
        if (!outputFile)
        {
            std::cerr << "Error creating output file: " << outputFileName << std::endl;
            inputFile.close();
            continue;
        }

        inputFile.seekg(0, std::ios::end);
        size_t fileSize = inputFile.tellg();
        inputFile.seekg(0, std::ios::beg);

        std::string arrayName = generateArrayName(argv[i]);
        outputFile << "unsigned char " << arrayName << "[" << fileSize << "] = {\n\t";
        char buffer;
        size_t count = 0;
        while (inputFile.read(&buffer, 1))
        {
            outputFile << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (0xFF & static_cast<unsigned int>(buffer));

            count++;
            if (!inputFile.eof()) {
                outputFile << ", ";
                if (count % 12 == 0) {
                    outputFile << "\n\t";
                }
            }
        }

        outputFile << "\n};\n";

        inputFile.close();
        outputFile.close();

        std::cout << "Converted: " << argv[i] << " => " << outputFileName << std::endl;
    }
    return 0;
}