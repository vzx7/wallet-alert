# Functionality

- The application is a console server application, and is intended to run continuously in the background.
- The application must check the balances of the largest wallets of the three leading cryptocurrencies: BTC, ETH, BNB. 10 addresses from each blockchain.
- At startup, the application must accept a list of email addresses to send out. You need to provide a flag to rewrite the list of addresses. It is possible to expand the parameters passed to the application.
- Wallet addresses must be pre-selected or obtained by polling services that can return the addresses of such wallets. (it is not yet clear which method to choose).
- Wallet balance must be saved either in a text file or in a database (depending on the deadline). The balance is written to the database every Monday at 15:00 UTC
- After receiving the balance, the program should check the balance with the previous saved one and, if the balance has decreased by 15%, we save the sign in the counter of negative signs.
- If the purse is replenished by more than 10% we also save, now a positive sign in another counter of positive signs variable.
- After bypassing all wallets, we check the counters of negative and positive signs. Compare them (the comparison algorithm is in the process of refinement):
    - If negative - positive >= 2 - send a bearish market alert;
    - If negative - positive < 2 & >= 0 - there is nothing to worry about, a correction is observed;
    - If negative – positive < 0 – it is necessary to send an alert about bullish sentiment in the market;
- After completion of the bypass, we reset the counters and wait for the time of the next bypass of wallets.
- The application must be available for completion from the console.
- Once a week we send a list of wallet balances to the specified email addresses.
- Once a year (December 31) we optimize the database of wallet balances, clear all balance changes for the past year, leaving only the balances of the first Mondays of the month.