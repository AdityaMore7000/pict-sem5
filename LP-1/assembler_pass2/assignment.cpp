#include <iostream>
#include <fstream>
#include <sstream>
#include<string.h>
#include <vector>

class TableRow {
public:
    std::string symbol;
    int address;
    int index;

    TableRow(const std::string& symbol, int address) : symbol(symbol), address(address) {}

    TableRow(const std::string& symbol, int address, int index) : symbol(symbol), address(address), index(index) {}

    int getIndex() {
        return index;
    }

    void setIndex(int newIndex) {
        index = newIndex;
    }

    std::string getSymbol() {
        return symbol;
    }

    void setSymbol(const std::string& newSymbol) {
        symbol = newSymbol;
    }

    int getAddress() {
        return address;
    }

    void setAddress(int newAddress) {
        address = newAddress;
    }
};

class Pass2 {
public:
    std::vector<TableRow> SYMTAB, LITTAB;

    Pass2() {
        SYMTAB = std::vector<TableRow>();
        LITTAB = std::vector<TableRow>();
    }

    void readTables() {
        std::ifstream br;
        std::string line;
        try {
            br.open("sym.txt");
            while (std::getline(br, line)) {
                std::istringstream iss(line);
                std::string symbol, addressStr, indexStr;
                iss >> indexStr >> symbol >> addressStr;
                SYMTAB.emplace_back(symbol, std::stoi(addressStr), std::stoi(indexStr));
            }
            br.close();
            br.open("lit.txt");
            while (std::getline(br, line)) {
                std::istringstream iss(line);
                std::string symbol, addressStr, indexStr;
                iss >> indexStr >> symbol >> addressStr;
                LITTAB.emplace_back(symbol, std::stoi(addressStr), std::stoi(indexStr));
            }
            br.close();
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void generateCode(const std::string& filename) {
        readTables();
        std::ifstream br(filename);
        std::ofstream bw("output.txt");
        std::string line, code;
        while (std::getline(br, line)) {
            std::istringstream iss(line);
            std::vector<std::string> parts;
            std::string part;
            while (iss >> part) {
                parts.push_back(part);
            }
            if (parts[0].find("AD") != std::string::npos || parts[0].find("DL,02") != std::string::npos) {
                bw << "\n";
                continue;
            } else if (parts.size() == 2) {
                if (parts[0].find("DL") != std::string::npos) {
                    parts[0] = parts[0].substr(parts[0].find_first_of("0123456789"));
                    if (std::stoi(parts[0]) == 1) {
                        int constant = std::stoi(parts[1]);
                        code = "00\t0\t" + std::to_string(constant) + "\n";
                        bw << code;
                    }
                } else if (parts[0].find("IS") != std::string::npos) {
                    int opcode = std::stoi(parts[0].substr(parts[0].find_first_of("0123456789")));
                    if (opcode == 10) {
                        if (parts[1].find("S") != std::string::npos) {
                            int symIndex = std::stoi(parts[1].substr(parts[1].find_first_of("0123456789")));
                            code = std::to_string(opcode) + "\t0\t" + std::to_string(SYMTAB[symIndex - 1].getAddress()) + "\n";
                            bw << code;
                        } else if (parts[1].find("L") != std::string::npos) {
                            int symIndex = std::stoi(parts[1].substr(parts[1].find_first_of("0123456789")));
                            code = std::to_string(opcode) + "\t0\t" + std::to_string(LITTAB[symIndex - 1].getAddress()) + "\n";
                            bw << code;
                        }
                    }
                }
            } else if (parts.size() == 1 && parts[0].find("IS") != std::string::npos) {
                int opcode = std::stoi(parts[0].substr(parts[0].find_first_of("0123456789")));
                code = std::to_string(opcode) + "\t0\t" + std::to_string(0) + "\n";
                bw << code;
            } else if (parts[0].find("IS") != std::string::npos && parts.size() == 3) {
                int opcode = std::stoi(parts[0].substr(parts[0].find_first_of("0123456789")));
                int regcode = std::stoi(parts[1]);
                if (parts[2].find("S") != std::string::npos) {
                    int symIndex = std::stoi(parts[2].substr(parts[2].find_first_of("0123456789")));
                    code = std::to_string(opcode) + "\t" + std::to_string(regcode) + "\t" + std::to_string(SYMTAB[symIndex - 1].getAddress()) + "\n";
                    bw << code;
                } else if (parts[2].find("L") != std::string::npos) {
                    int symIndex = std::stoi(parts[2].substr(parts[2].find_first_of("0123456789")));
                    code = std::to_string(opcode) + "\t" + std::to_string(regcode) + "\t" + std::to_string(LITTAB[symIndex - 1].getAddress()) + "\n";
                    bw << code;
                }
            }
        }
        bw.close();
        br.close();
    }
};

int main() {
    Pass2 pass2;
    try {
        pass2.generateCode("input.txt");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
