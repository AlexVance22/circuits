#pragma once
#include "chip.h"


class nMOS : public Chip {
public:
    void setSource(bool hilo) {
        setInput(1, hilo);
    }
    void setGate(bool hilo) {
        setInput(2, hilo);
    }

    void update() override {
        const bool source = getInput(1);
        const bool gate   = getInput(2);
        outputs = (source && gate) ? 1 : 0;
    }
};

class pMOS : public Chip {
public:
    void setSource(bool hilo) {
        setInput(1, hilo);
    }
    void setGate(bool hilo) {
        setInput(2, hilo);
    }

    void update() override {
        const bool source = getInput(1);
        const bool gate   = getInput(2);
        outputs = (source && !gate) ? 1 : 0;
    }
};


class cMOSCombo : public Chip {
protected:
    Map<String, WiredChip> chips;
};


class cMOSNot : public cMOSCombo {
public:
    cMOSNot() {
        chips["A"] = WiredChip{ std::make_unique<nMOS>(), { "" } };
        chips["B"] = WiredChip{ std::make_unique<pMOS>(), { "" } };
    }
};

