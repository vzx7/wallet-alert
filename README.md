# wallet-alert
## Goal of the project
Alert for sharp fluctuations in the balance of the largest wallets of the leading cryptocurrencies.

- [List of requirements](docs/requirements.md) - List of requirements;
- [Functionality](docs/functionality.md) - Description of the functionality of the project;
- [UML](docs/UML.md) - Project UML diagrams;

## CMake options
```asm
//Flags used by the CXX compiler during all build types.
CMAKE_CXX_FLAGS:STRING=-std=c++14 -pthread -fconcepts-ts -lcurl -ljsoncpp
```