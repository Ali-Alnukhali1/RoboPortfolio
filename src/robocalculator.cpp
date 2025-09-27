#include "robocalculator.hpp"
#include <cmath>   // for pow, round, floor

// user functions
void apply_deposit(long long& current_balance, long long deposit_amount) {
    current_balance += deposit_amount;
}

void apply_withdrawal(long long& current_balance, long long withdrawl_amount) {
    current_balance -= withdrawl_amount;
}

double simple_interest(int base, double apr, int days, int day_count_basis) {
    double raw_interest = ((double)(base)) * apr * ((double)days/day_count_basis);
    return raw_interest;
}

double compound_interest(int principal,double apr, int years, int compounds_per_year) {
    double raw_interest = principal * pow(1+(apr/compounds_per_year), (compounds_per_year * years)-1);
    return raw_interest;
}

double convert_currency(int amount, string from_currency, string to_currency) {
    double new_currency_amount = -1;

    map<string,double> fx_table ={
        {"USD", 1.0},
        {"SAR", 3.75},
        {"EUR", 0.85},
        {"EGP", 48.05},
        {"RUB", 83.70},
    };

    if (fx_table.count(from_currency) == 0 || (fx_table.count(to_currency) == 0)) {
        cout<<"Error: Unknown currency"<<endl;
    } else {
        new_currency_amount = (amount/fx_table[from_currency]) * fx_table[to_currency];
    }
    return new_currency_amount;
}

// helper functions
double percent_of(int amount, double rate) {
    double raw_percent = amount * rate;
    return raw_percent;
}

bool validate_rate (double rate) {
    if(rate < 0 || rate > 1){ 
        cout<<"invalid rate"<<endl;
        return false;
    }
    return true;
}

bool validate_non_negative (double amount) {
    if(amount < 0){ 
        cout<<"error: the amount is negative"<<endl;
        return false;
    }
    return true;
}

void apply_fee(long long& current_balance, long long fee_amount) {
    current_balance -= fee_amount;
}
