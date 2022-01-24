#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <curl/curl.h>
#include <json/value.h>
#include <json/reader.h>
#include "headers/mailer.h"
#include "wallet.cpp"

using namespace std;

const string API_KEY = getenv("API_BC_KEY");

class Analyzer
{
private:
    Mailer mailer;

    Wallet *btcWallet = new Wallet(BTC);
    Wallet *ethWallet = new Wallet(ETH);
    Wallet *ltcWallet = new Wallet(LTC);

    int more;
    int less;

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

    int checkAddress(string address, Wallet *wallet) {
        CURL *curl;
        CURLcode res;
        std::string readBuffer;
        struct curl_slist *list = NULL;

        curl = curl_easy_init();
        cout << "CURL START" << endl;
        if(curl) {
            string url = wallet->data.url + address;
            string key = "api-key: " + API_KEY;
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
                    cout << wallet->data.name << " address: " << address << endl;
                    cout << "Balance: " << balance << std::endl;
                    cout << endl;
                    wallet->data.lastAddress = address;
                    // TODO
                    checkBalance(balance, balance);
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

    void checkBalance(string oldBalance, string newBalance)
    {
        int intOldBalance = atoi(newBalance.c_str());
        int intNewBalance = atoi(oldBalance.c_str());
        int diff = intNewBalance - intOldBalance;
        if(diff >= (intOldBalance - (intOldBalance * 0.15))) {
            more += 1;
        } else if (diff < (intOldBalance - (intOldBalance * 0.15))) {
            less += 1;
        }
    };

    string getAddress(Wallet *wallet) {

        cout << "Get tne next unverified from " << wallet->data.name << "..." << endl;
        string file_path = "./resource/" + wallet->data.name;
        ifstream file;
        bool isFind = false;

        file.open(file_path);
        if (!file)
        {
            throw "ERROR: The file currency list was not opened!";
        }

        string address;
        while (getline(file, address))
        {
            if ((!wallet->data.lastAddress.empty() && address == wallet->data.lastAddress && getline(file, address))
                    || wallet->data.lastAddress.empty()) {
                isFind = true;
                break;
            }
        }
        if (isFind) {
            return address;
        }

        return "";
    };

    bool checkBCData(Wallet *wallet) {
        cout << "Start check for " + wallet->data.name << endl;
        if (!wallet->data.isChecked) {
            string address = getAddress(wallet);
            cout << address << endl;
            if (!address.empty()) {
                checkAddress(address, wallet);
            } else {
                wallet->data.isChecked = true;
            }
        }

        return wallet->data.isChecked;
    }

public:
    bool compareBalance()
    {
        if (checkBCData(btcWallet ) && checkBCData(ethWallet ) && checkBCData(ltcWallet )) {
            if(more - less > 3) {
                // do something
            }
            cout << "The balance of all wallets is checked, the work is over." << endl;
            return true;
        }
        return false;
    };
};