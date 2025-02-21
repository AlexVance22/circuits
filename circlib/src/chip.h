#pragma once
#include <cstdint>
#include <string>


class Chip {
protected:
    uint32_t m_inputs = 0;
    uint32_t m_outputs = 0;

    bool getInput(uint8_t port);
    bool getClock();
    void setOutput(uint8_t port, bool hilo);

    virtual void update() = 0;

public:
    virtual uint32_t inCount() const = 0;
    virtual uint32_t outCount() const = 0;

    void setInput(uint8_t port, bool hilo);
    void setInputs(uint32_t all);
    void setClock(bool hilo);
    bool getOutput(uint8_t port) const;
    uint32_t getOutputs() const;
};


struct ChipPort {
    std::string chip;
    uint8_t port;
};

