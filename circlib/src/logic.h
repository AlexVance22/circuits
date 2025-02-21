#pragma once
#include "chip.h"
#include <unordered_map>


struct WiredGate;

class LogicGate : public Chip {
public:
    enum class Type {
        Not,
        Nand,
        Combo
    };

private:
    std::unordered_map<std::string, WiredGate> chips;
    std::vector<std::vector<ChipPort>> ins;
    Type m_type;
    std::string m_typename;

public:
    static LogicGate MakeNot();
    static LogicGate MakeNand();
    static LogicGate MakeCombo(uint8_t ins, uint8_t outs);

    static LogicGate loadFromFile(const std::string& filename, std::unordered_map<std::string, LogicGate>& chipset);
    void saveToFile(const std::string& filename);

    const std::string& getTypeName() { return m_typename; }

    void update() override;
};


class TruthTable : public Chip {
private:
    std::vector<uint32_t> m_lookup;

public:
    static TruthTable fromChip(Chip& chip);
    static TruthTable loadFromFile(const std::string& filename);

    std::string toString() const;

    void update() override { m_outputs = m_lookup[m_inputs]; }
};


struct WiredGate {
    LogicGate gate;
    std::vector<std::vector<ChipPort>> wires;
};

