#include "CheckingAccount.hpp"


long long CheckingAccount::monthly_fee() const {
    return settings_.fee_flat_cents;
}

AccountType CheckingAccount::type() const {
    return AccountType::Checking;
}