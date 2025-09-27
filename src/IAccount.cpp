
#ifndef IACCOUNT_HPP
#define IACCOUNT_HPP

#include <string>
#include <vector>
using namespace std;

//Data Types 

//Enumerations
enum AccountType {Checking = 0,
                  Savings = 1};
enum TxKind {Deposit = 0,
             Withdrawal = 1,
             Fee = 2,
             Interest = 3,
             TransferIn = 4,
             TransferOut =5};

//Structs
struct AccountSettings {
    AccountType type;
    double apr;
    long long fee_flat_cents;

};

struct TxRecord{
    TxKind kind;
    long long amount_cents;
    long long timestamp;
    string note;
    string account_id;
};

struct TransferRecord {
        string from_id;

        string to_id;
        long long amount_cents;
        long long timestamp;
        string note;
};

class IAccount {
    public:
        //Identity & metadata:
        virtual  string id() const = 0;
        virtual  AccountType type() const = 0;
        virtual  double apr() const = 0;
        //State:
        virtual long long balance_cents() const = 0;
        virtual int audit_size() const = 0;
        virtual const vector<TxRecord>& audit_data() const = 0;

        virtual void apply(const TxRecord& tx) = 0;

        virtual ~IAccount() = default;

};

#endif // IACCOUNT_HPP