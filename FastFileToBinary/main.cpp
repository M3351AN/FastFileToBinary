import std;

std::string extractFileName(const std::string& filePath) {
  size_t pos = filePath.find_last_of("/\\");
  return filePath.substr(pos + 1);
}

std::string GenerateArrayName(const std::string& input_file_name) {
  std::string file_name = extractFileName(input_file_name);
  size_t pos = file_name.find_last_of('.');
  std::string base_name =
      (pos == std::string::npos) ? file_name : file_name.substr(0, pos);
  std::string pascal_name;
  bool capitalize = true;
  for (char c : base_name) {
    if (std::isalnum(static_cast<unsigned char>(c))) {
      if (capitalize) {
        pascal_name.push_back(static_cast<char>(std::toupper(c)));
        capitalize = false;
      } else {
        pascal_name.push_back(static_cast<char>(std::tolower(c)));
      }
    } else {
      capitalize = true;
    }
  }
  std::string array_name = "k" + pascal_name + "RawData";
  return array_name;
}

std::string generateOutputFileName(const std::string& inputFileName) {
  std::string fileName = extractFileName(inputFileName);
  size_t pos = fileName.find_last_of('.');
  std::string baseName =
      (pos == std::string::npos) ? fileName : fileName.substr(0, pos);
  std::string outputFileName = baseName + ".h";
  return outputFileName;
}

std::string GenerateHeaderGuardName(const std::string& input_file_name) {
  std::string file_name = extractFileName(input_file_name);
  size_t pos = file_name.find_last_of('.');
  std::string base_name =
      (pos == std::string::npos) ? file_name : file_name.substr(0, pos);
  std::string header_guard_name;
  header_guard_name.reserve(base_name.size() + 3);
  for (char c : base_name) {
    if (std::isalnum(static_cast<unsigned char>(c))) {
      header_guard_name.push_back(static_cast<char>(std::toupper(c)));
    } else {
      header_guard_name.push_back('_');
    }
  }
  header_guard_name += "_H_";
  return header_guard_name;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <file1> <file2> ..." << std::endl;
    return 1;
  }

  for (int i = 1; i < argc; ++i) {
    std::ifstream inputFile(argv[i], std::ios::binary);
    if (!inputFile) {
      std::cerr << "Error opening input file: " << argv[i] << std::endl;
      continue;
    }

    std::string outputFileName = generateOutputFileName(argv[i]);
    std::ofstream outputFile(outputFileName);
    if (!outputFile) {
      std::cerr << "Error creating output file: " << outputFileName
                << std::endl;
      inputFile.close();
      continue;
    }

    inputFile.seekg(0, std::ios::end);
    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    std::string header_guard_name = GenerateHeaderGuardName(argv[i]);

    outputFile << "#pragma once\n";  // non-standard but widely supported
    outputFile << "#ifndef\x20" << header_guard_name << "\n"
               << "#define\x20" << header_guard_name << "\n\n";
    outputFile << "namespace rawdata {\n";
    std::string arrayName = GenerateArrayName(argv[i]);
    outputFile << "inline static constexpr unsigned char " << arrayName << "["
               << fileSize << "] = {\n\x20\x20";
    char buffer;
    size_t count = 0;
    while (inputFile.read(&buffer, 1)) {
      outputFile << "0x" << std::hex << std::uppercase << std::setw(2)
                 << std::setfill('0')
                 << (0xFF & static_cast<unsigned int>(buffer));

      count++;
      if (!inputFile.eof()) {
        if (count % 12 == 0) {
          outputFile << ",\n\x20\x20";
        } else {
          outputFile << ",\x20";
        }
      }
    }

    outputFile << "\n};\n";
    outputFile << "} // namespace rawdata\n\n";
    outputFile << "#endif\x20\x20//\x20" << header_guard_name << "\n";
    inputFile.close();
    outputFile.close();

    std::cout << "Converted: " << argv[i] << " => " << outputFileName
              << std::endl;
  }
  return 0;
}