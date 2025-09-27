#include<memory>
#include <unordered_map>
#include <vector>
#include "CheckingAccount.cpp"
#include "SavingsAccount.cpp"
using namespace std;

#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

class Portfolio{

    public:
    //getters
    void add_Account(unique_ptr<BaseAccount> account);
    BaseAccount* get_Account(const string& id);
    int Accounts_count() const;

    //functions
    void apply_all(const vector<TxRecord>& txs);
    void apply_from_ledger(const string ids[], const int kinds[], const long long amounts[], int count);
    void transfer(const TransferRecord& tr);
    long long total_exposure() const;


   private:
   std::unordered_map<std::string,std::unique_ptr<BaseAccount>> accounts_;
   std::vector<TxRecord> records_;

};

#endif