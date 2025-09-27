#include "BaseAccount.hpp"

#ifndef SAVINGSACCOUNT_HPP
#define SAVINGSACCOUNT_HPP.

//added comment 

class SavingsAccount : public BaseAccount{
    public:

    // constructor: forward to BaseAccount
    SavingsAccount(const std::string& id, const AccountSettings& settings, long long opening_balance = 0)
        : BaseAccount(id, settings, opening_balance) {}

    //getter
    long long monthly_fee() const{

        return settings_.fee_flat_cents;
    }

    AccountType type() const override {
    // TODO: implement
    return AccountType::Savings;
}
};

#endif