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