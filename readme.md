# RoboBank Portfolio

##  Objective
The **RoboBank Portfolio** project is a practice-oriented C++ application designed to explore and apply:
- **Class inheritance** and polymorphism (e.g., `BaseAccount`, `CheckingAccount`, `SavingsAccount`).
- **Advanced C++ concepts** such as `unique_ptr`, smart memory management, and STL containers (`unordered_map`, `vector`).
- **Testing methods** using Google Test to ensure correctness of banking operations and portfolio management.
- **Docker usage** for containerizing the development and testing environment, ensuring reproducibility and portability.

This project is not intended for production-level banking software but as a **learning environment** to build confidence in modern C++ design patterns, testing, and DevOps integration.

---

## Use Cases
The **Portfolio** class models a simplified banking portfolio that can:
- **Add and manage accounts** (checking, savings, etc.) with unique IDs.
- **Perform operations** such as:
  - Deposits  
  - Withdrawals  
  - Transfers between accounts  
  - Applying transaction fees or adjustments
- **Track records** of all operations performed using transaction logs (`TxRecord`).
- **Handle bulk operations**:
  - Apply a list of transactions to multiple accounts.  
  - Process ledger-based transaction data from arrays (`apply_from_ledger`).
- **Calculate total exposure** (aggregate balance across accounts).
- **Maintain account count** and allow quick retrieval via ID lookups.

In short, the project provides a **mini banking system simulator** where multiple accounts are managed together under one portfolio, supporting both individual and batch operations.

---

## Testing
The project uses **Google Test** to validate the correctness of:
- Account creation and retrieval.
- Deposits, withdrawals, and transfers.
- Proper handling of invalid or edge-case operations.
- Portfolio-level functions (account counts, total exposure, etc.).

Run tests inside Docker:
``` bash
docker build -t robobank-portfolio -f docker/Dockerfile .
docker run --rm robobank-portfolio



