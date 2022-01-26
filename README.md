# wallet-alert
## Goal of the project
Alert for sharp fluctuations in the balance of the largest wallets of the leading cryptocurrencies.

- [List of requirements](docs/requirements.md) - List of requirements;
- [Functionality](docs/functionality.md) - Description of the functionality of the project;
- [UML](docs/UML.md) - Project UML diagrams;

The application is being developed for the linux (64) operating system. Perhaps later the ability to compile for other operating systems will be added.
## Build application 
### CMake options
```asm
//Flags used by the CXX compiler during all build types.
CMAKE_CXX_FLAGS:STRING=-std=c++14 -pthread -fconcepts-ts -lcurl -ljsoncpp
```

### Location of resource files
Resource files must be located along the path:
```bash
$HOME/wallet_alert/resources/{BTC ETH LTC date addresses}
```
- *BTC, ETH, LTC* - Files containing lists of wallets in the format: adresses|balance;
- *date* - Date of last analysis of wallets;
- *addresses* Mailing List
