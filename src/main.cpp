#include <iostream>
#include "Portfolio.hpp"
#include "SavingsAccount.cpp"
#include "CheckingAccount.cpp"

using namespace std;

int main() {

    AccountSettings chk_settings{Checking,0.0, 150};   // 0% APR, 150 fee
    AccountSettings sav_settings{Savings,0.05, 0};    // 5% APR, no fee
   
    //1. create portfolio
    Portfolio portfolio;

    // add accounts
    portfolio.add_Account(make_unique<CheckingAccount>("CHK-001", chk_settings, 0));
    portfolio.add_Account(make_unique<SavingsAccount>("SAV-010", sav_settings, 500000));

    cout << "Test[1] Portfolio has " << portfolio.Accounts_count() << " accounts." << endl;
    cout << "Test[1] Total exposure: " << portfolio.total_exposure() << " cents" << endl;

    // 2. Apply transactions (vector path)
    vector<TxRecord> txs;
    txs.push_back({TxKind::Deposit,    100000, 1, "Initial deposit", "CHK-001"});
    txs.push_back({TxKind::Withdrawal, 25000,  2, "ATM withdrawal","CHK-001"});
    txs.push_back({TxKind::Fee,        1500,   3, "Monthly fee", "CHK-001"});

    portfolio.apply_all(txs);

    auto chk1 = portfolio.get_Account("CHK-001");
    cout << "Test[2] CHK-001 balance after deposit/withdraw/fee: "
         << chk1->balance_cents() << endl;// (expected 73500)

    
    // 3. Savings interest
    auto sav = portfolio.get_Account("SAV-010");
    sav->post_simple_interest(31, 365, 4, "Monthly interest", "SAV-010");

    cout << "Test[3] SAV-010 balance after interest: "
         << sav->balance_cents() << endl;// (expected 502123)

    // 4. Transfer between accounts
    TransferRecord tr{"SAV-010", "CHK-001", 30000, 5, "Transfer to checking"};
    portfolio.transfer(tr);

    cout << "Test[4] CHK-001 balance after transfer: " << chk1->balance_cents() << endl;
    cout << "Test[4] SAV-010 balance after transfer: " << sav->balance_cents() << endl;

     // 5. Apply transactions (Ledger path)
    const string ids[]     = {"CHK-001", "CHK-002", "SAV-010"};
    const int kinds[]      = {(TxKind::Fee),
                              (TxKind::Deposit),
                              (TxKind::Withdrawal)};
    const long long amts[] = {30000, 30000, 123};

    portfolio.add_Account(make_unique<CheckingAccount>("CHK-002", chk_settings, 0));
    portfolio.apply_from_ledger(ids, kinds, amts, 3);

    cout << "Test[5] CHK-001 balance: " << portfolio.get_Account("CHK-001")->balance_cents() << endl;// (expected 73500)
    cout << "Test[5] CHK-002 balance: " << portfolio.get_Account("CHK-002")->balance_cents()<< endl;//  (expected 30000)
    cout << "Test[5] SAV-010 balance: " << portfolio.get_Account("SAV-010")->balance_cents() << endl;// (expected 472000)


        return 0;
}
