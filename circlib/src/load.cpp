#include "logic.h"
#include <fstream>
#include <iostream>


LogicGate LogicGate::loadFromFile(const std::string& filename, std::unordered_map<std::string, LogicGate>& chipset) {
    std::ifstream stream(filename);

    std::string junk;
    uint32_t count;
    stream >> junk >> count;
    for (uint32_t i = 0; i < count; i++) {
        std::string chip;
        stream >> chip;
        if (chipset.find(chip) == chipset.end()) {
            chipset[chip] = LogicGate::loadFromFile("res/" + chip + ".chip", chipset);
        }
    }

    std::string name;
    uint32_t i, o;
    stream >> name >> i >> o;

    LogicGate result = LogicGate::MakeCombo((uint8_t)i, (uint8_t)o);

    for (uint32_t j = 0; j < i; j++) {
        uint32_t splits;
        stream >> splits;
        std::vector<ChipPort> wires;
        for (uint32_t s = 0; s < splits; s++) {
            std::string c;
            uint32_t p;
            stream >> c >> p;
            wires.push_back({ c, (uint8_t)p });
        }
        result.ins.push_back(wires);
    }

    uint32_t chipcount;
    stream >> chipcount;

    for (uint32_t j = 0; j < chipcount; j++) {
        std::string id, type;
        stream >> id >> type;
        if (type == "NOT") {
            uint32_t splits;
            stream >> splits;
            std::vector<ChipPort> wires;
            for (uint32_t s = 0; s < splits; s++) {
                std::string c;
                uint32_t p;
                stream >> c >> p;
                wires.push_back({ c, (uint8_t)p });
            }
            result.chips[id] = WiredGate{ LogicGate::MakeNot(), { wires } };
        } else if (type == "NAND") {
            uint32_t splits;
            stream >> splits;
            std::vector<ChipPort> wires;
            for (uint32_t s = 0; s < splits; s++) {
                std::string c;
                uint32_t p;
                stream >> c >> p;
                wires.push_back({ c, (uint8_t)p });
            }
            result.chips[id] = WiredGate{ LogicGate::MakeNand(), { wires } };
        } else {
            const LogicGate& g = chipset.at(type);
            std::vector<std::vector<ChipPort>> wires;
            for (uint8_t k = 0; k < g.outCount(); k++) {
                uint32_t splits;
                stream >> splits;
                std::vector<ChipPort> w;
                for (uint32_t s = 0; s < splits; s++) {
                    std::string c;
                    uint32_t p;
                    stream >> c >> p;
                    w.push_back(ChipPort{ c, (uint8_t)p });
                }
                wires.push_back(w);
            }
            result.chips[id] = WiredGate{ g, std::move(wires) };
        }
    }

    return result;
}

void LogicGate::saveToFile(const std::string& filename) {
    std::ofstream stream(filename);

}


static size_t intpow(size_t base, size_t exp) {
    size_t res = 1;
    for (size_t i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}


TruthTable TruthTable::loadFromFile(const std::string& filename) {
    std::ifstream stream(filename);

    std::string name;
    uint32_t i, o;
    stream >> name >> i >> o;

    TruthTable result = TruthTable();
    const size_t rows = intpow(2, i);
    result.m_lookup.resize(rows);
    for (size_t j = 0; j < rows; j++) {
        uint32_t out = 0;
        for (uint32_t k = 0; k < o; k++) {
            bool bit;
            stream >> bit;
            out |= (uint32_t)1 << (o - k - 1);
        }
        result.m_lookup[j] = out;
    }

    return result;
}

