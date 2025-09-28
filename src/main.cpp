#include <iostream>
#include "Portfolio.hpp"
#include "SavingsAccount.cpp"
#include "CheckingAccount.cpp"
#include <gtest/gtest.h>

using namespace std;

int main(int argc,char **argv) {

     testing::InitGoogleTest(&argc,argv);

     return RUN_ALL_TESTS();
}

TEST(Portfolio_test, add_account) {
    AccountSettings chk_settings{Checking,0.0, 150};  
    AccountSettings sav_settings{Savings,0.05, 0};   
    
    Portfolio portfolio;
    portfolio.add_Account(make_unique<CheckingAccount>("CHK-001", chk_settings, 0));
    portfolio.add_Account(make_unique<SavingsAccount>("SAV-010", sav_settings, 0));

    ASSERT_EQ(portfolio.Accounts_count(), 2);
}

TEST(Portfolio_test, deposit_and_withdrawal) {
    AccountSettings chk_settings{Checking,0.0, 150};
    Portfolio portfolio;

    portfolio.add_Account(make_unique<CheckingAccount>("CHK-001", chk_settings, 0));

    vector<TxRecord> txs;
    txs.push_back({TxKind::Deposit,    100000, 1, "Initial deposit", "CHK-001"});
    txs.push_back({TxKind::Withdrawal, 25000,  2, "ATM withdrawal", "CHK-001"});
    txs.push_back({TxKind::Fee,        1500,   3, "Monthly fee",    "CHK-001"});

    portfolio.apply_all(txs);

    auto chk1 = portfolio.get_Account("CHK-001");
    ASSERT_EQ(chk1->balance_cents(), 73500);
}

TEST(Portfolio_test, apply_from_ledger) {
    AccountSettings chk_settings{Checking,0.0, 150};  
    AccountSettings sav_settings{Savings,0.05, 0};   
    
    Portfolio portfolio;

 //Apply transactions (Ledger path)
    const string ids[]     = {"CHK-001", "CHK-002", "SAV-010"};
    const int kinds[]      = {(TxKind::Deposit),
                              (TxKind::Deposit),
                              (TxKind::Deposit)};
    const long long amts[] = {30000, 50000, 100000};

    portfolio.add_Account(make_unique<CheckingAccount>("CHK-001", chk_settings, 0));
    portfolio.add_Account(make_unique<CheckingAccount>("CHK-002", chk_settings, 0));
    portfolio.add_Account(make_unique<SavingsAccount>("SAV-010", sav_settings, 0));
    portfolio.apply_from_ledger(ids, kinds, amts, 3);

    ASSERT_EQ(portfolio.get_Account("CHK-001")->balance_cents(),30000);
    ASSERT_EQ(portfolio.get_Account("CHK-002")->balance_cents(),50000);
    ASSERT_EQ(portfolio.get_Account("SAV-010")->balance_cents(),100000);

}

