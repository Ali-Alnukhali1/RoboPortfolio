#include <iostream>
#include "Portfolio.hpp"
#include "SavingsAccount.hpp"
#include "CheckingAccount.hpp"
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

TEST(Portfolio_test, transfer_between_accounts) {
    AccountSettings chk_settings{Checking,0.0, 0};  
    AccountSettings sav_settings{Savings,0.05, 0};   
    
    Portfolio portfolio;
    portfolio.add_Account(make_unique<CheckingAccount>("CHK-001", chk_settings, 50000));
    portfolio.add_Account(make_unique<SavingsAccount>("SAV-010", sav_settings, 20000));

    TransferRecord tr{"CHK-001", "SAV-010", 15000, 10, "Transfer to savings"};
    portfolio.transfer(tr);

    ASSERT_EQ(portfolio.get_Account("CHK-001")->balance_cents(), 35000);
    ASSERT_EQ(portfolio.get_Account("SAV-010")->balance_cents(), 35000);
}

TEST(Portfolio_test, total_exposure) {
    AccountSettings chk_settings{Checking,0.0, 0};  
    AccountSettings sav_settings{Savings,0.05, 0};   
    
    Portfolio portfolio;
    portfolio.add_Account(make_unique<CheckingAccount>("CHK-001", chk_settings, 40000));
    portfolio.add_Account(make_unique<SavingsAccount>("SAV-010", sav_settings, 60000));

    ASSERT_EQ(portfolio.total_exposure(), 100000);
}

TEST(Account_test, post_interest) {
    AccountSettings sav_settings{Savings, 0.10, 0}; // 10% APR  
    SavingsAccount sav("SAV-010", sav_settings, 100000); // $1000

    sav.post_simple_interest(365, 365, 1, "Yearly interest", "SAV-010");

    // Should add 10% interest = 10000
    ASSERT_EQ(sav.balance_cents(), 110000);
}

TEST(Account_test, audit_trail_records) {
    AccountSettings chk_settings{Checking,0.0, 0};  
    CheckingAccount chk("CHK-001", chk_settings, 0);

    chk.deposit(10000, 1, "Deposit 1", "CHK-001");
    chk.withdraw(5000, 2, "Withdraw 1", "CHK-001");

    ASSERT_EQ(chk.audit_size(), 2);
    ASSERT_EQ(chk.audit_data().at(0).kind, TxKind::Deposit);
    ASSERT_EQ(chk.audit_data().at(1).kind, TxKind::Withdrawal);
}

TEST(Portfolio_test, get_non_existent_account) {
    AccountSettings chk_settings{Checking,0.0, 0};  
    Portfolio portfolio;
    portfolio.add_Account(make_unique<CheckingAccount>("CHK-001", chk_settings, 1000));

    ASSERT_EQ(portfolio.get_Account("UNKNOWN"), nullptr);
}

TEST(Account_test, charge_fee) {
    AccountSettings chk_settings{Checking,0.0, 200};  
    CheckingAccount chk("CHK-001", chk_settings, 50000);

    chk.charge_fee(200, 1, "Maintenance fee", "CHK-001");

    ASSERT_EQ(chk.balance_cents(), 49800);
}


//ASSERT_FALSE

TEST(Portfolio_test, add_account_wrong) {
    AccountSettings chk_settings{Checking,0.0, 150};  
    AccountSettings sav_settings{Savings,0.05, 0};   
    
    Portfolio portfolio;
    portfolio.add_Account(make_unique<CheckingAccount>("CHK-001", chk_settings, 0));
    portfolio.add_Account(make_unique<SavingsAccount>("SAV-010", sav_settings, 0));
    portfolio.add_Account(make_unique<CheckingAccount>("CHK-001", chk_settings, 0));


    ASSERT_FALSE(portfolio.Accounts_count()== 3);
}

TEST(Portfolio_test, deposit_negative) {
    AccountSettings chk_settings{Checking,0.0, 100000};
    Portfolio portfolio;

    portfolio.add_Account(make_unique<CheckingAccount>("CHK-001", chk_settings, 0));

    vector<TxRecord> txs;
    txs.push_back({TxKind::Deposit,    -10000, 1, "Negative deposit", "CHK-001"});

    portfolio.apply_all(txs);

    auto chk1 = portfolio.get_Account("CHK-001");
    ASSERT_FALSE(chk1->balance_cents() == 90000);
}

TEST(Portfolio_test, withdraw_negative) {
    AccountSettings chk_settings{Checking,0.0, 100000};
    Portfolio portfolio;

    portfolio.add_Account(make_unique<CheckingAccount>("CHK-001", chk_settings, 0));

    vector<TxRecord> txs;
    txs.push_back({TxKind::Withdrawal,    -10000, 1, "Negative Withdrawl", "CHK-001"});

    portfolio.apply_all(txs);

    auto chk1 = portfolio.get_Account("CHK-001");
    ASSERT_FALSE(chk1->balance_cents() == 90000);
}

TEST(Portfolio_test, Fee_negative) {
    AccountSettings chk_settings{Checking,0.0, 100000};
    Portfolio portfolio;

    portfolio.add_Account(make_unique<CheckingAccount>("CHK-001", chk_settings, 0));

    vector<TxRecord> txs;
    txs.push_back({TxKind::Fee,    -10000, 1, "Negative Fee amount", "CHK-001"});

    portfolio.apply_all(txs);

    auto chk1 = portfolio.get_Account("CHK-001");
    ASSERT_FALSE(chk1->balance_cents() == 90000);
}
