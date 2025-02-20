//
// Created by Bryan on 2/19/2025.
//

#include <conio.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// cifrado monoalfabético por sustitución

string frequency(const string &message) {
    unordered_map<char, int> map;

    for (char e: message)
        if (isalpha(e)) {
            e = toupper(e);
            map[e]++;
        }

    vector<pair<char, int>> freq(map.begin(), map.end());

    sort(freq.begin(), freq.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    string result;
    for (const auto &e: freq)
        result += e.first;

    return result;
}

string decrypt_message(const string &message, const string &freq_lang) {
    string code = frequency(message);
    string decrypt;

    if (code.size() != freq_lang.size())
        throw range_error("The sizes don't match.");

    for (char e: message) {
        char key;
        if (isalpha(e)) {
            auto it = find(code.begin(), code.end(), toupper(e));

            if (it == code.end())
                throw out_of_range("The character doesn't exist.");

            auto index = distance(code.begin(), it);

            key = freq_lang[index];
        } else
            key = e;

        decrypt += key;
    }

    return decrypt;
}

int main() {

    auto message = "Bgc-bfufb tegaedppqna ql aggv zge xof tegaedppfe'l \n"
                   "lgjb. \n"
                   "Xof adpf vflqanfe logjbvn'x hf pdwqna d cgebv qn \n"
                   "coqro xof tbdkfe ql mjlx d lpdbb tdex. Xof tbdkfe QL \n"
                   "XOF HGLL; qx'l kgje vjxk xg fnxfexdqn oqp ge ofe. \n"
                   "Zgrjl ql d pdxxfe gz vfrqvqna codx xoqnal kgj def \n"
                   "ngx agqna xg vg. \n"
                   "Xof rglx gz dvvqna d zfdxjef qln'x mjlx xof xqpf qx \n"
                   "xdwfl xg rgvf qx. Xof rglx dblg qnrbjvfl xof \n"
                   "dvvqxqgn gz dn ghlxdrbf xg zjxjef fstdnlqgn. Xof \n"
                   "xeqrw ql xg tqrw xof zfdxjefl xodx vgn'x zqaox fdro \n"
                   "gxofe. - Mgon Rdepdrw. \n"
                   "(ccc.adpdljxed.rgp/uqfc/nfcl/234346?utkjpvbjr) \n"
                   "(ccc.hedqnkijgxf.rgp/ijgxfl/djxogel/m/mgon_rdepdrw.o\n"
                   " xpb)";

    auto result = decrypt_message(message, "TEOAISRHNUCMDLGWFPYKJBVQX");

    cout << result << endl;

    _getch();
    return 0;
}