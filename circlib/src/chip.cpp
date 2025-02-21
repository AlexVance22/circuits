#include "chip.h"


bool Chip::getInput(uint8_t port) {
    return (m_inputs & ((uint32_t)1 << port)) ? true : false;
}

bool Chip::getClock() {
    return getInput(31);
}

void Chip::setOutput(uint8_t port, bool hilo) {
    m_outputs ^= (m_outputs & ((uint32_t)1 << port));
    m_outputs |= (uint32_t)hilo << port;
}


void Chip::setInput(uint8_t port, bool hilo) {
    m_inputs ^= (m_inputs & ((uint32_t)1 << port));
    m_inputs |= (uint32_t)hilo << port;
    update();
}

void Chip::setInputs(uint32_t all) {
    m_inputs = all;
    update();
}

void Chip::setClock(bool hilo) {
    setInput(31, hilo);
}

bool Chip::getOutput(uint8_t port) const {
    return (m_outputs & ((uint32_t)1 << port)) ? true : false;
}

uint32_t Chip::getOutputs() const {
    return m_outputs;
}

