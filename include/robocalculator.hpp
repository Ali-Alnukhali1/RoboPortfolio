#ifndef ROBOCALCULATOR_HPP
#define ROBOCALCULATOR_HPP

#include <iostream>
#include <map>
#include <string>
using namespace std;

// user functions
void apply_deposit(long long& current_balance, long long deposit_amount);
void apply_withdrawal(long long& current_balance, long long withdrawl_amount);

double simple_interest(int base, double apr, int days, int day_count_basis);
double compound_interest(int principal,double apr, int years, int compounds_per_year);

// convert currency
double convert_currency(int amount, string from_currency, string to_currency);

// helper functions
double percent_of(int amount, double rate);
bool validate_rate (double rate);
bool validate_non_negative (double amount);
void apply_fee(long long& current_balance, long long fee_amount);

#endif