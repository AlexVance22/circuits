#include "logic.h"


LogicGate LogicGate::MakeNot() {
    LogicGate gate;
    gate.m_type = Type::Not;
    gate.m_incount = 1;
    gate.m_outcount = 1;
    return gate;
}

LogicGate LogicGate::MakeNand() {
    LogicGate gate;
    gate.m_type = Type::Nand;
    gate.m_incount = 2;
    gate.m_outcount = 1;
    return gate;
}

LogicGate LogicGate::MakeCombo(uint8_t ins, uint8_t outs) {
    LogicGate gate;
    gate.m_type = Type::Combo;
    gate.m_incount = ins;
    gate.m_outcount = outs;
    return gate;
}


void LogicGate::update() {
    if (m_type == Type::Not) {
        setOutput(0, !getInput(0));
        return;
    }
    if (m_type == Type::Nand) {
        setOutput(0, !(getInput(0) && getInput(1)));
        return;
    }

    uint8_t i = 0;
    for (const auto& in : ins) {
        for (const auto& split : in) {
            chips[split.chip].gate.setInput(split.port, getInput(i));
        }
        i++;
    }

    for (size_t j = 0; j < chips.size(); j++) {
        for (auto& [_, chip] : chips) {
            i = 0;
            for (const auto& wire : chip.wires) {
                for (const auto& split : wire) {
                    if (split.chip == "_") {
                        setOutput(split.port, chip.gate.getOutput(i));
                    } else {
                        chips[split.chip].gate.setInput(split.port, chip.gate.getOutput(i));
                    }
                }
                i++;
            }
        }
    }
}



static size_t intpow(size_t base, size_t exp) {
    size_t res = 1;
    for (size_t i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

static int isBitSet(size_t num, uint8_t bit) {
    auto temp = num & ((size_t)1 << bit);
    return temp > 0 ? 1 : 0;
}


TruthTable TruthTable::fromChip(Chip& chip) {
    TruthTable res;
    const size_t height = intpow(2, chip.inCount());
    res.m_incount = chip.inCount();
    res.m_outcount = chip.outCount();
    res.m_lookup.resize(height);
    for (size_t i = 0; i < height; i++) {
        chip.setInputs((uint32_t)i);
        res.m_lookup[i] = chip.getOutputs();
    }
    return res;
}


std::string TruthTable::toString() const {
    std::string result = "";
    for (size_t i = 0; i < m_lookup.size(); i++) {
        for (size_t x = 0; x < m_incount; x++) {
            result += std::to_string(isBitSet(i, (uint8_t)x)) + " ";
        }
        result += "| ";
        for (size_t x = 0; x < m_outcount; x++) {
            result += std::to_string(isBitSet(m_lookup[i], (uint8_t)x)) + " ";
        }
        result += "\n";
    }
    return result;
}

