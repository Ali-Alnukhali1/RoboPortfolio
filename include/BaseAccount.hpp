#include "IAccount.hpp"
#include "robocalculator.hpp"
#include "RoboLedger.hpp"
#include <vector>

#ifndef BASEACCOUNT_HPP
#define BASEACCOUNT_HPP

class BaseAccount: public IAccount{
    public:
        //API Constructor
        BaseAccount(const string& id, const AccountSettings& settings,
                long long opening_balance_cents = 0) :
                  id_(id), 
                  settings_(settings), 
                  balance_cents_(opening_balance_cents){}
       virtual ~BaseAccount() = default;
        //Getters
        string id() const override { return id_; }
        virtual AccountType type() const = 0;
        double apr() const { return settings_.apr; }
        long long balance_cents() const override{return balance_cents_;};
        int audit_size() const override { return static_cast<int>(audit_.size()); }
        const vector<TxRecord>& audit_data() const override { return audit_; }

        //Operations
        void deposit(long long amount_cents, long long ts,
                     const string note, string account_id) ;
        
        void withdraw(long long amount_cents, long long ts,
                      const string note, string account_id);

        void charge_fee(long long fee_cents, long long ts,
                        const string note, string account_id);

        void post_simple_interest(int days, int basis, long long ts,
                                  const string note, string account_id);

        void apply(const TxRecord& tx);

    protected:
        string id_;
        AccountSettings settings_;
        long long balance_cents_;
        vector<TxRecord> audit_;

        void record (TxKind kind, long long amount, long long ts,
                     string note, string account_id);

};

#endif