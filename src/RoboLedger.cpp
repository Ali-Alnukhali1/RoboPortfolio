#include "RoboLedger.hpp"
#include "robocalculator.hpp"



using namespace std;

#define MAX_ID_LEN 50
int find_account(const unique_ptr<char[]> ac_account_id[], int ac_count, const char account_id[]){
    for(int i = 0;i<ac_count;i++){
        if(strcmp(ac_account_id[i].get(),account_id) == 0){
            return i;
        }
    }
    return -1;
}


int find_or_create_account(unique_ptr<char[]> ac_account_id[], long long ac_balance[],
                           int ac_capacity,int& ac_count, const char account_id[]){

        int i = find_account(ac_account_id,ac_count,account_id);
        if(i != -1) return i; //account found

        if(ac_count >= ac_capacity){
           // cannot add new account
           return -1;  // signal failure
            }

        ac_account_id[ac_count] = make_unique<char[]>(MAX_ID_LEN); //use unique ptr
        strcpy(ac_account_id[ac_count].get(),account_id); //copy the new id to the acounts array
        ac_balance[ac_count] = 0;
        return ac_count++;
}
void apply_one_transaction(unique_ptr<char[]> ac_account_id[], long long ac_balance[],
                           int ac_capacity,int& ac_count, const char account_id[],
                           int tx_type, long long amount){

    int index = find_or_create_account(ac_account_id,ac_balance,ac_capacity,ac_count,account_id);
    if (index == -1) {
        cout << "Error: could not find/create account." << endl;
        return;
}

    switch(tx_type){
        //Deposit
        case 0:
            apply_deposit(ac_balance[index], amount);

            break;

        //Withdrawl
        case 1:
            apply_withdrawal(ac_balance[index], amount);

             break;

        //Fee
        case 2:
            apply_fee(ac_balance[index],amount);

            break;

        //Intrest
        case 3:
            cout<<"not yet implmented"<<endl;
        break;

        //Transfer in
        case 4:
              apply_deposit(ac_balance[index], amount);

         break;

        //Transfer out
        case 5:
            apply_withdrawal(ac_balance[index], amount);

         break;

    default: 
            cout << "Invalid operation, try again." << endl;
    }

    
}

void apply_all_transactions(const char* tx_account_id[], int tx_type[], int tx_amount_cents[],
                            int tx_count,unique_ptr<char[]> ac_account_id[],long long ac_balance[],
                            int ac_capacity, int& ac_count){

    for(int i = 0;i<tx_count;i++){
        apply_one_transaction(
            ac_account_id,       // account array
            ac_balance,          // balance array
            ac_capacity,         // max accounts
            ac_count,            // number of accounts
            tx_account_id[i],    // account ID for this transaction
            tx_type[i],          // transaction type
            tx_amount_cents[i]   // transaction amount
        );
    }
}

long long balance_of(unique_ptr<char[]> ac_account_id[],
               long long ac_balance[], int ac_count,
               const char account_id[]){


    int index = find_account(ac_account_id,ac_count,account_id);
    if (index == -1) {
        cout << "Error: Account not Found" << endl;
        return 0;
    }
        return ac_balance[index];
}

void print_bank_summary(int tx_type[], int tx_amount_cents[],
                        int tx_count, long long ac_balance[],
                        int ac_count,
                        int& out_total_deposits,
                        int& out_total_withdrawals,
                        int& out_total_fees,
                        int& out_total_interest,
                        int& out_net_exposure){

     // Initialize totals
    out_total_deposits = 0;
    out_total_withdrawals = 0;
    out_total_fees = 0;
    out_total_interest = 0;
    out_net_exposure = 0;

    for(int i = 0;i<tx_count;i++){
           switch(tx_type[i]) {
            case 0: // Deposit
            case 4: // TransferIn
                out_total_deposits += tx_amount_cents[i];
                break;
            case 1: // Withdrawal
            case 5: // TransferOut
                out_total_withdrawals += tx_amount_cents[i];
                break;
            case 2: // Fee
                out_total_fees += tx_amount_cents[i];
                break;
            case 3: // Interest
                out_total_interest += tx_amount_cents[i];
                break;
        }
    }

    
    for(int i = 0;i<ac_count;i++){
        out_net_exposure += ac_balance[i];
    }
    
    
    cout<<"==========Bank Summary=========="<<endl;
    cout<<"Total Deposits: "<<out_total_deposits<<endl;
    cout<<"Total Withdrals: "<<out_total_withdrawals<<endl;
    cout<<"Total Fees: "<<out_total_fees<<endl;
    cout<<"Total Intrestes: "<<out_total_interest<<endl;
    cout<<"Net Exposure: "<<out_net_exposure<<endl;
                            

}

// helper functions
void list_all_accounts(){
    cout<<"in list_all_accounts()"<<endl;

}

