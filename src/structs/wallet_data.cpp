#include <string>
using namespace std;

struct Address {
    string address;
    int old_balance;
    int new_balance;
};
struct WalletData {
    string name;
    string url;
    bool isChecked;
    string lastAddress;
    Address addresses[30];
};