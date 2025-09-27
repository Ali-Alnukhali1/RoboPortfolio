#include "Portfolio.hpp"
using namespace std;

void Portfolio::add_Account(unique_ptr<BaseAccount> account) {
    // TODO: insert into accounts_ using account->id() as key
    if(!account) return;

    accounts_[account->id()] = move(account);
    
}

BaseAccount* Portfolio::get_Account(const string& id) {
    // TODO: look up in accounts_, return raw pointer or nullptr
    auto it = accounts_.find(id);
    if(it!=accounts_.end()){
        return it->second.get();
    }
    return nullptr;

}

int Portfolio::Accounts_count() const {
    // TODO: return accounts_.size()
    return static_cast<int> (accounts_.size());
}

void Portfolio::apply_all(const vector<TxRecord>& txs) {
    // TODO: iterate over txs, dispatch each to the matching account->apply()
    // also record tx in records_
    for (const auto& tx: txs){
        BaseAccount* acc = get_Account(tx.account_id);
        if(acc){
            acc->apply(tx); //apply record
            records_.push_back(tx); //append record
        }else{
                        cout << "Account '" << tx.account_id << "' doesn't exist.\n";

        }
    }

}

void Portfolio::apply_from_ledger(const string ids[],
                                  const int kinds[],
                                  const long long amounts[],
                                  int count) {
    // TODO: loop through parallel arrays, build TxRecord for each, and call apply_all()
    vector<TxRecord> txs;
    txs.reserve(count);

    for(int i =0 ;i<count;i++){
        TxRecord tx;
        tx.account_id = ids[i];
        tx.kind = static_cast<TxKind>(kinds[i]);
        tx.amount_cents = amounts[i];
        tx.timestamp = i;
        tx.note = "from ledger";
        txs.push_back(tx); //push the record
    }

    apply_all(txs); //apply all records
}

void Portfolio::transfer(const TransferRecord& tr) {
    // TODO: withdraw from src account, deposit to dst account,
    // add TxRecords for TransferOut and TransferIn
    BaseAccount* src = get_Account(tr.from_id);
    BaseAccount* dst = get_Account(tr.to_id);

    if(src && dst){

        TxRecord out;
        out.account_id = tr.from_id;
        out.kind = TxKind::TransferOut;
        out.amount_cents = tr.amount_cents;
        out.timestamp = tr.timestamp;
        out.note = tr.note;
        src->apply(out);
        records_.push_back(out);

        TxRecord in;
        in.account_id = tr.to_id;
        in.kind = TxKind::TransferIn;
        in.amount_cents = tr.amount_cents;
        in.timestamp = tr.timestamp;
        in.note = tr.note;
        dst->apply(in);
        records_.push_back(in);
    }
}

long long Portfolio::total_exposure() const {
    // TODO: accumulate balances from all accounts and return sum

    long long total = 0;
    for(const auto& [id,acc]:accounts_){
        total +=acc->balance_cents();
    }
    return total;
}
