#include "SavingsAccount.hpp"

long long SavingsAccount::monthly_fee() const {
    return settings_.fee_flat_cents;
}

AccountType SavingsAccount::type() const {
    return AccountType::Savings;
}