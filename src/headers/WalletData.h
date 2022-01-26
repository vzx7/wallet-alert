//
// Created by zx on 1/26/22.
//

#ifndef WALLET_ALERT_WALLETDATA_H
#define WALLET_ALERT_WALLETDATA_H
#include <string>
#include "../headers/constants.h"
using namespace std;

struct Address {
    bool isDown;
    string address;
    string oldBalance;
    string newBalance;
};
struct WalletData {
    string name;
    string url;
    bool isChecked;
    string lastAddress;
    Address addresses[COUNT_ADDRESSES];
};
#endif //WALLET_ALERT_WALLETDATA_H
