#ifndef ROBOLEDGER_HPP
#define ROBOLEDGER_HPP

#include <iostream>
#include<cstring>
#include <memory>

using namespace std;

/* Finds the i of a target account ID within the accounts array.
 Inputs:
   ac_account_id[] : array of C-strings holding all account IDs,
                     the function actually receives is a pointer to the first element
   ac_count        : number of valid accounts in the array
   account_id      : target account ID to search for (C-string)
 Output:
   Returns the i (0..ac_count-1) if found, otherwise -1
*/ 
//dosent change anything so it should be const
int find_account(const unique_ptr<char[]> ac_account_id[], int ac_count, const char account_id[]);


int find_or_create_account(unique_ptr<char[]> ac_account_id[], long long ac_balance[],
                           int ac_simple_interestcapacity,int& ac_count, const char account_id[]);

void apply_one_transaction(unique_ptr<char[]> ac_account_id[],
                           long long ac_balance[],
                           int ac_capacity,
                           int& ac_count,
                           const char account_id[],
                           int tx_type,
                           long long amount);

void apply_all_transactions(const char* tx_account_id[], int tx_type[], int tx_amount_cents[],
                            int tx_count,unique_ptr<char[]> ac_account_id[],long long ac_balance[],
                            int ac_capacity, int& ac_count);

long long balance_of(unique_ptr<char[]> ac_account_id[],
               long long ac_balance[], int ac_count,
               const char account_id[]);

void print_bank_summary(int tx_type[], int tx_amount_cents[],
                        int tx_count, long long ac_balance[],
                        int ac_count, int& out_total_deposits,
                        int& out_total_withdrawals,
                        int& out_total_fees,
                        int& out_total_interest,
                        int& out_net_exposure);

// helper functions
void list_all_accounts();

#endif // ROBOLEDGER_HPP
