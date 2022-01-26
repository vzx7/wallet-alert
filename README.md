# wallet-alert
**Attention!!!** 
This application is under development. And yet does not fulfill all the declared functions.
You can take part in the development! Dare)!

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
- **BTC, ETH, LTC** - Files containing lists of wallets in the format: address|balance;
- **date** - Date of last analysis of wallets;
- **addresses** - Mailing List
### Environment variables
The application works with two variables:
$HOME and $API_BC_KEY. The first one stores the path to your home directory. The second must be added via:
```bash
export $API_BC_KEY=yourKey
```
Where is the **yourKey**, this is your api key from the resource https://nownodes.io/.

## Denial of responsibility
You may use this application at your own risk. You and only you are responsible for any problems caused in connection with the use of this code and the application itself.