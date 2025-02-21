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
    uint32_t m_incount;
    uint32_t m_outcount;
    Type m_type;

public:
    static LogicGate MakeNot();
    static LogicGate MakeNand();
    static LogicGate MakeCombo(uint8_t ins, uint8_t outs);

    uint32_t inCount() const override { return m_incount; }
    uint32_t outCount() const override { return m_outcount; }
    void update() override;

    static LogicGate loadFromFile(const std::string& filename, std::unordered_map<std::string, LogicGate>& chipset);
};


class TruthTable : public Chip {
private:
    std::vector<uint32_t> m_lookup;
    uint32_t m_incount;
    uint32_t m_outcount;

public:
    static TruthTable fromChip(Chip& chip);

    std::string toString() const;

    uint32_t inCount() const override { return m_incount; }
    uint32_t outCount() const override { return m_outcount; }
    void update() override { m_outputs = m_lookup[m_inputs]; }

    static TruthTable loadFromFile(const std::string& filename);
};


struct WiredGate {
    LogicGate gate;
    std::vector<std::vector<ChipPort>> wires;
};

