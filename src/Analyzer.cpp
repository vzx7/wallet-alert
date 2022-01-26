#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <curl/curl.h>
#include <json/value.h>
#include <json/reader.h>
#include "headers/Mailer.h"
#include "headers/constants.h"
#include "headers/BigInt.h"
#include "Wallet.cpp"
#include "headers/FileService.h"

using namespace std;


class Analyzer
{
private:
    Mailer mailer;
    Wallet *btcWallet = new Wallet(BTC);
    Wallet *ethWallet = new Wallet(ETH);
    Wallet *ltcWallet = new Wallet(LTC);

    int more;
    int less;

    struct Account {
        bool isFind;
        string address;
        string balance;
    };

    struct SetAlert {
        bool hasAlert;
        bool isDown;
    };

    static size_t callback(
            const char* in,
            size_t size,
            size_t num,
            string* out)
    {
        const size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    };

    int checkAddress(Account account, Wallet *wallet) {
        CURL *curl;
        std::string readBuffer;
        struct curl_slist *list = NULL;
        string apiKey;
        try {
            apiKey = getenv("API_BC_KEY");
        } catch(const char *msg) {
            cout << "API KEY NOT FOUND..." << endl;
        }
        curl = curl_easy_init();
        cout << "CURL START" << endl;
        if(curl) {
            string url = wallet->data.url + account.address;
            string key = "api-key: " + apiKey;
            list = curl_slist_append(list, key.c_str());
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
            // Response information.
            long httpCode(0);
            unique_ptr<std::string> httpData(new string());

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

            curl_easy_perform(curl);
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            curl_easy_cleanup(curl);

            if (httpCode == 200)
            {
                std::cout << "\nGot successful response from " << url << std::endl;
                Json::Value jsonData;
                Json::Reader jsonReader;

                if (jsonReader.parse(*httpData.get(), jsonData))
                {
                    cout << "Successfully parsed JSON data" << std::endl;
                    cout << "\nJSON data received:" << std::endl;

                    const string balance(jsonData["balance"].asString());

                    cout << "Natively parsed:" << std::endl;
                    cout << wallet->data.name << " address: " << account.address << endl;
                    cout << "Balance: " << balance << std::endl;
                    cout << endl;
                    wallet->data.lastAddress = account.address;
                    checkBalance(wallet, account.balance, balance);
                }
                else
                {
                    cout << "Could not parse HTTP data as JSON" << std::endl;
                    cout << "HTTP data was:\n" << *httpData.get() << std::endl;
                    return 1;
                }
            }
            else
            {
                std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
                return 1;
            }
        }

        return 0;
    }

    int getFreeSlot(Wallet *wallet) {
        unsigned int slot;
        for(slot = 0; slot < COUNT_ADDRESSES; slot++) {
            if (wallet->data.addresses[slot].address.empty()) {
                break;
            }
        }
        return slot;
    }

    SetAlert checkAlertForETH(string oldBalance, string newBalance) {
        SetAlert alertSet;
        BigInt intOldBalance(oldBalance);
        BigInt intNewBalance(newBalance);
        BigInt wei("1000000000000000000");
        intNewBalance = intNewBalance / wei;
        BigInt diff = intNewBalance - intOldBalance;
        BigInt tenProc = (intOldBalance/100) * 10;
        alertSet.hasAlert = false;
        if(diff >= tenProc) {
            alertSet.hasAlert = true;
            more += 1;
        } else if (diff < tenProc) {
            alertSet.hasAlert = true;
            less += 1;
        }
        alertSet.isDown = diff < 0;
        return alertSet;
    }

    void checkBalance(Wallet *wallet, string oldBalance, string newBalance)
    {
        SetAlert alertSet;
        if (wallet->data.name == "ETH") {
            alertSet = checkAlertForETH(oldBalance, newBalance);
        } else {
            unsigned long long intOldBalance = atoll(oldBalance.c_str());
            unsigned long long intNewBalance = atoll(newBalance.c_str());

            unsigned diff = intNewBalance - intOldBalance;
            unsigned int tenProc = (intOldBalance/100) * 10;
            if(diff >= tenProc) {
                alertSet.hasAlert = true;
                more += 1;
            } else if (diff < tenProc) {
                alertSet.hasAlert = true;
                less += 1;
            }
            alertSet.isDown = diff < 0;
        }

        if (alertSet.hasAlert) {
            unsigned int slot = getFreeSlot(wallet);
            wallet->data.addresses[slot].address = wallet->data.lastAddress;
            wallet->data.addresses[slot].isDown = alertSet.isDown;
            wallet->data.addresses[slot].newBalance = newBalance;
            wallet->data.addresses[slot].oldBalance = oldBalance;
        }
    };

    Account setAccount(string line) {
        unsigned int delPos = line.find("|");
        Account account;
        account.address = line.substr(0, delPos);
        account.balance = line.substr(delPos+1);
        return account;
    };

    Account getAddress(Wallet *wallet) {
        cout << "Get tne next unverified from " << wallet->data.name << "..." << endl;
        string fileName = wallet->data.name;
        string line;
        FileService fileService(fileName);
        fileService.openFile();

        Account account;
        account.isFind = false;
        while (getline(fileService.file, line))
        {
            account = setAccount(line);
            account.isFind = false;
            if ((!wallet->data.lastAddress.empty() && account.address == wallet->data.lastAddress && getline(fileService.file, line))
                    || wallet->data.lastAddress.empty()) {
                if (line.length() < 5) break;
                account = setAccount(line);
                account.isFind = true;
                break;
            }
        }
        fileService.closeFile();
        return account;
    };

    bool checkBCData(Wallet *wallet) {
        cout << "Start check for " + wallet->data.name << endl;
        if (!wallet->data.isChecked) {
            Account account = getAddress(wallet);
            if (account.isFind) {
                checkAddress(account, wallet);
            } else {
                wallet->data.isChecked = true;
            }
        }

        return wallet->data.isChecked;
    }

    string createMessage(bool isBullish, WalletData data) {
        unsigned int i = 0;
        string msg = "Blockchain " + data.name + "\n\n";
        while(!data.addresses[i].address.empty() && data.addresses[i].isDown != isBullish) {
            msg += "Address: " + data.addresses[i].address + ":\n";
            msg += "Old balance: " + data.addresses[i].oldBalance + ",\n";
            msg += "New balance: " + data.addresses[i].newBalance + ".\n";
            i++;
        }
        msg += "*********************************************************************\n\n";
        return msg;
    }

    void doAlert(bool isBullish) {
        string stage = isBullish ? "bullish" : "bearish";
        string  message = "When analyzing the balances of these addresses, it was revealed that the market is in " + stage + " stage.\n\n";
        message += createMessage(isBullish, btcWallet->data);
        message += createMessage(isBullish, ethWallet->data);
        message += createMessage(isBullish, ltcWallet->data);
        mailer.sendAlert(message);
    }

public:
    bool compareBalance()
    {
        if (
            checkBCData(btcWallet )
            && checkBCData(ethWallet )
            && checkBCData(ltcWallet )) {

            int odds = less - more;
            bool isBullish = false;
            bool isFind;

            if(odds >= 2) {
                isFind = true;
            } else if(odds <= -2) {
                isFind = true;
                isBullish = true;
            } else {
                cout << "The market is stable, nothing to worry about..." << endl;
            }
            if(isFind) {
                doAlert(isBullish);
            }
            cout << "The balance of all wallets is checked, the work is over." << endl;
            return true;
        }
        return false;
    };
};