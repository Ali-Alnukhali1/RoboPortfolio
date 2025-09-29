#include<memory>
#include <unordered_map>
#include <vector>
#include "CheckingAccount.cpp"
#include "SavingsAccount.cpp"
using namespace std;

#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP


/**
 * @class Portfolio
 * @brief Represents a collection of heterogeneous bank accounts.
 *
 * Portfolio manages multiple accounts (Checking, Savings, etc.) and provides
 * functionality to perform transactions, transfers, and ledger-based operations
 * across all accounts. It also tracks all transaction records and can compute
 * total exposure across the portfolio.
 */
class Portfolio{

public:
    /// @brief Adds a new account to the portfolio.
    /// @param account A unique_ptr to a BaseAccount object to add.
    void add_Account(unique_ptr<BaseAccount> account);

    /// @brief Retrieves an account by its ID.
    /// @param id The string identifier of the account.
    /// @return Pointer to the BaseAccount object if found; nullptr otherwise.
    BaseAccount* get_Account(const string& id);

    /// @brief Returns the number of accounts in the portfolio.
    /// @return The count of accounts.
    int Accounts_count() const;

    // @brief Applies a batch of transactions to their respective accounts.
    /// @param txs A vector of TxRecord objects representing transactions.
    /// @note This method processes transactions and updates account balances and audit logs.
    void apply_all(const vector<TxRecord>& txs);

    /// @brief Applies transactions from ledger-style arrays.
    /// @param ids Array of account IDs.
    /// @param kinds Array of transaction kinds corresponding to each account.
    /// @param amounts Array of transaction amounts corresponding to each account.
    /// @param count The number of transactions in the arrays.
    /// @note Useful for bulk or external ledger-based transaction processing.
    void apply_from_ledger(const string ids[], const int kinds[], const long long amounts[], int count);
    
    /// @brief Transfers an amount between two accounts within the portfolio.
    /// @param tr A TransferRecord containing source ID, destination ID, amount, timestamp, and note.
    /// @note Updates balances of both accounts and logs the transaction.
    void transfer(const TransferRecord& tr);

    /// @brief Computes the total balance across all accounts.
    /// @return Sum of all account balances in the portfolio.
    long long total_exposure() const;


   private:
   std::unordered_map<std::string,std::unique_ptr<BaseAccount>> accounts_; ///< Map of account ID to account object.
   std::vector<TxRecord> records_; ///< Log of all transactions applied to the portfolio.

};

#endif