//
// Created by zx on 1/24/22.
//

#include "headers/bc_type.h"
#include "structs/wallet_data.cpp"
using namespace std;

class Wallet {
private:
    BcType bcType;

    void setWalletData() {
        switch (bcType) {
            case BTC:
                data.name = "BTC";
                data.url = "https://btcbook.nownodes.io/api/v2/address/";
                break;
            case ETH:
                data.name = "ETH";
                data.url = "https://eth-blockbook.nownodes.io/api/v2/address/";
                break;
            case LTC:
                data.name = "LTC";
                data.url = "https://ltcbook.nownodes.io/api/v2/address/";
                break;
        }
        data.isChecked = false;
    }
public:
    Wallet(BcType type) {
        bcType = type;
        setWalletData();
    }
    WalletData data;
};
