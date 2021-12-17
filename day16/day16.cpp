#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bits/stdc++.h>
#include "../util/helpers.h"

struct Packet
{
    int type;
    int version;
    vector<Packet> SubPackets;
    ulong value;
    bool valSet = false;

    /** @brief Get the Value. If it's not set, calculate it. */
    ulong getValue() {
        if (!valSet) { calcValue(); }
        return value;
    }

    void calcValue() {
        if (valSet) { return; }
        switch (type)
        {
        case 0: // SUM
            value = 0;
            for (Packet p : SubPackets) {
                value += p.getValue();
            }
            valSet = true;
            break;
        case 1: // PRODUCT
            for (size_t i = 0; i < SubPackets.size(); i++) {
                if (i == 0) {
                    value = SubPackets.at(0).getValue();
                } else {
                    value *= SubPackets.at(i).getValue();
                }
            }
            valSet = true;
            break;
        case 2: // MIN
            {
            ulong min_val = ULONG_MAX;
            for (Packet p : SubPackets) {
                if (p.getValue() < min_val) {
                    min_val = p.getValue();
                }
            }
            value = min_val;
            valSet = true;
            break;
            }
        case 3: // MAX
            {
            ulong max_val = 0;
            for (Packet p : SubPackets) {
                if (p.getValue() > max_val) {
                    max_val = p.getValue();
                }
            }
            value = max_val;
            valSet = true;
            break;
            }
        case 5: // >
            if (SubPackets.at(0).getValue() > SubPackets.at(1).getValue()) {
                value = 1;
            } else {
                value = 0;
            }
            valSet = true;
            break;
        case 6: // <
            if (SubPackets.at(0).getValue() < SubPackets.at(1).getValue()) {
                value = 1;
            } else {
                value = 0;
            }
            valSet = true;
            break;
        case 7: // ==
            if (SubPackets.at(0).getValue() == SubPackets.at(1).getValue()) {
                value = 1;
            } else {
                value = 0;
            }
            valSet = true;
            break;
        default:
            cout << "Error: Could not calculate value! Type = " << type << endl;
            break;
        }
    }
};

Packet decodeOperator(string *bin);

/**
 * @brief Decodes a found literal string 
 *        and removes the literal bin code from the input string.
 */
Packet decodeLiteral(string *bin) {
    Packet literal;
    literal.version = bitset<3>(bin->substr(0, 3)).to_ulong();
    literal.type = 4;

    // Cut out the now used information
    *bin =  bin->substr(6);

    // Calculate the value
    string val = "";
    while (true) {
        if ((*bin)[0] == '0') {
            val += bin->substr(1,4);
            *bin = bin->substr(5);
            break;
        }
        val += bin->substr(1,4);
        *bin = bin->substr(5);
    }
    literal.value = stoul(val, nullptr, 2);
    literal.valSet = true;
    return literal;
}

/** @brief Decodes a found operator-packetlist with length bit 1 */
vector<Packet> decodeLengthType1(string *bin) {
    int packets = bitset<11>(bin->substr(0, 11)).to_ulong();
    vector<Packet> pp;
    *bin = bin->substr(11);
    for (int i = 0; i < packets; i++) {
        if (bin->substr(3,3) == "100") {
            pp.push_back(decodeLiteral(bin));
        } else {
            pp.push_back(decodeOperator(bin));
        }
    }

    return pp;
}

/** @brief Decodes a found operator-packetlist with length bit 0 */
vector<Packet> decodeLengthType0(string *bin) {
    int length = bitset<15>(bin->substr(0, 15)).to_ulong();
    vector<Packet> pp;
    string subCode = bin->substr(15, length);
    
    *bin = bin->substr(15 + length);
    while (subCode.find_first_of('1') != subCode.npos) {
        if (subCode.substr(3,3) == "100") {
            pp.push_back(decodeLiteral(&subCode));
        } else {
            pp.push_back(decodeOperator(&subCode));
        }
    }

    return pp;
}

/** @brief Decodes a found operator */
Packet decodeOperator(string *bin) {
    Packet op;
    op.version = bitset<3>(bin->substr(0, 3)).to_ulong();
    op.type    = bitset<3>(bin->substr(3, 3)).to_ulong();

    bool lengthType = ((*bin)[6] == '1');
    *bin = bin->substr(7);
    op.SubPackets = (lengthType) ? decodeLengthType1(bin) : decodeLengthType0(bin);

    return op;
}

/** @brief Sums up the version numbers of Packet p and it's subpackets */
int getVersionSum(Packet *p) {
    int s = p->version;
    if (p->type != 4) {
        for (Packet pp : p->SubPackets) {
            s += getVersionSum(&pp);
        }
    }
    return s;
}

int task1(Packet *p) {
    return getVersionSum(p);
}

ulong task2(Packet *p) {
    return p->getValue();
}

int main() {
    // First, decode the string from hexadecimal into binary
    string bin = "";
    std::ifstream is("input");
    for (string s; getline(is, s);) {
        bin += hexadecimal_to_binary(s);
    }
    // Now parse the packet
    Packet p;
    if (bin.substr(3,3) == "100") {
        p = decodeLiteral(&bin);
    } else {
        p = decodeOperator(&bin);
    }
    cout << "Task 1: " << task1(&p) << endl;
    cout << "Task 2: " << task2(&p) << endl;
    return 0;
}