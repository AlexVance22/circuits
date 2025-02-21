#include "mscmptest/asserts.h"

#include "logic.h"


void test_logical_not();
void test_logical_nand();
void test_logical_and();
void test_logical_or();
void test_logical_nor();
void test_logical_xor();
void test_truth_tables();


int main() {
    test(test_logical_not)
    test(test_logical_nand)
    test(test_logical_and)
    test(test_logical_or)
    test(test_logical_nor)
    test(test_logical_xor)
    test(test_truth_tables)
}


void test_logical_not() {
    auto NOT = LogicGate::MakeNot();

    NOT.setInputs(0b0);
    assert_eq(NOT.getOutputs(), 0b1);
    NOT.setInputs(0b1);
    assert_eq(NOT.getOutputs(), 0b0);
}

void test_logical_nand() {
    auto NAND = LogicGate::MakeNand();

    NAND.setInputs(0b00);
    assert_eq(NAND.getOutputs(), 0b01);
    NAND.setInputs(0b10);
    assert_eq(NAND.getOutputs(), 0b01);
    NAND.setInputs(0b01);
    assert_eq(NAND.getOutputs(), 0b01);
    NAND.setInputs(0b11);
    assert_eq(NAND.getOutputs(), 0b00);
}

void test_logical_and() {
    auto set = std::unordered_map<std::string, LogicGate>{};
    auto AND = LogicGate::loadFromFile("res/AND.chip", set);

    AND.setInputs(0b00);
    assert_eq(AND.getOutputs(), 0b00);
    AND.setInputs(0b10);
    assert_eq(AND.getOutputs(), 0b00);
    AND.setInputs(0b01);
    assert_eq(AND.getOutputs(), 0b00);
    AND.setInputs(0b11);
    assert_eq(AND.getOutputs(), 0b01);
}

void test_logical_or() {
    auto set = std::unordered_map<std::string, LogicGate>{};
    auto OR = LogicGate::loadFromFile("res/OR.chip", set);

    OR.setInputs(0b00);
    assert_eq(OR.getOutputs(), 0b00);
    OR.setInputs(0b10);
    assert_eq(OR.getOutputs(), 0b01);
    OR.setInputs(0b01);
    assert_eq(OR.getOutputs(), 0b01);
    OR.setInputs(0b11);
    assert_eq(OR.getOutputs(), 0b01);
}

void test_logical_nor() {
    auto set = std::unordered_map<std::string, LogicGate>{};
    auto NOR = LogicGate::loadFromFile("res/NOR.chip", set);

    NOR.setInputs(0b00);
    assert_eq(NOR.getOutputs(), 0b01);
    NOR.setInputs(0b10);
    assert_eq(NOR.getOutputs(), 0b00);
    NOR.setInputs(0b01);
    assert_eq(NOR.getOutputs(), 0b00);
    NOR.setInputs(0b11);
    assert_eq(NOR.getOutputs(), 0b00);
}

void test_logical_xor() {
    auto set = std::unordered_map<std::string, LogicGate>{};
    auto XOR = LogicGate::loadFromFile("res/XOR.chip", set);

    XOR.setInputs(0b00);
    assert_eq(XOR.getOutputs(), 0b00);
    XOR.setInputs(0b10);
    assert_eq(XOR.getOutputs(), 0b01);
    XOR.setInputs(0b01);
    assert_eq(XOR.getOutputs(), 0b01);
    XOR.setInputs(0b11);
    assert_eq(XOR.getOutputs(), 0b00);
}

void test_truth_tables() {
}

