//
// Created by zx on 1/24/22.
//

#include "headers/BcType.h"
#include "headers/WalletData.h"
#include "headers/constants.h"
using namespace std;

class Wallet {
private:
    BcType bcType;

    void setWalletData() {
        switch (bcType) {
            case BTC:
                data.name = BTC_NAME;
                data.url = "https://btcbook.nownodes.io/api/v2/address/";
                break;
            case ETH:
                data.name = ETH_NAME;
                data.url = "https://eth-blockbook.nownodes.io/api/v2/address/";
                break;
            case LTC:
                data.name = LTC_NAME;
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
