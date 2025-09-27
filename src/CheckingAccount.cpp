#include "BaseAccount.hpp"

#ifndef CHECKINGACCOUNT_HPP
#define CHECKINGACCOUNT_HPP
class CheckingAccount : public BaseAccount{
    public:
     CheckingAccount(const std::string& id, const AccountSettings& settings, long long opening_balance = 0)
        : BaseAccount(id, settings, opening_balance) {}

    //getter
    long long monthly_fee() const {

        return settings_.fee_flat_cents;
    }

    AccountType type() const override{
    // TODO: implement
    return AccountType::Checking;
}
};

#endif