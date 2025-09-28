#include "BaseAccount.hpp"

// Operations
void BaseAccount::deposit(long long amount_cents, long long ts, string note, string account_id) {
    // TODO: implement
    apply_deposit(balance_cents_, amount_cents);
    record(Deposit,amount_cents,ts, note,account_id);
}

void BaseAccount::withdraw(long long amount_cents, long long ts, string note, string account_id) {
    // TODO: implement
    apply_withdrawal(balance_cents_, amount_cents);
    record(Withdrawal,amount_cents,ts, note,account_id);
}
void BaseAccount::post_simple_interest(int days, int basis, long long ts, string note, string account_id) {
    // TODO: implement

    int base = static_cast<int>(balance_cents_);
 
    double interest = simple_interest(base,
                              settings_.apr,
                              days,
                              basis);
    long long newInterest = static_cast<long long>(interest);

    record(Interest,newInterest,ts, note,account_id);

    balance_cents_ += newInterest;
}

void BaseAccount::apply(const TxRecord& tx) {
    // TODO: implement
        switch(tx.kind){
        case TxKind::Deposit: 
            apply_deposit(balance_cents_, tx.amount_cents);
        break;
        case TxKind::Withdrawal:  
            apply_withdrawal(balance_cents_, tx.amount_cents);
            break;
        case TxKind::Fee:
            apply_fee(balance_cents_, tx.amount_cents);
            break;
        case TxKind::Interest:
                //apply intreset
            break;
        default:
            // Optional: handle unknown kinds
            std::cerr << "Unknown transaction kind!\n";
            break;
        }

        record(tx.kind, tx.amount_cents, tx.timestamp, tx.note, tx.account_id);
}

// Private helper
void BaseAccount::record(TxKind kind, long long amount, long long ts, string note,  string account_id) {
    // TODO: implement
        audit_.push_back({kind, amount, ts, note, account_id});
}
