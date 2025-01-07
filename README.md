# Courier Service Management System

This project is a **Courier Service Management System**, implemented in C++. It allows users and delivery personnel to interact through a platform where users can place orders, and delivery personnel can view and accept orders based on constraints like weight and profit. The system also implements algorithms for optimization and shortest-path calculation.

---

## Features

### User Features
- **Signup/Login**: Users can create accounts or log in to their existing accounts.
- **Place Orders**: Users can place orders by specifying the number of items, their weights, and the costs.
- **View Dashboard**: Users are welcomed with a personalized dashboard after login.

### Delivery Person Features
- **Signup/Login**: Delivery personnel can create accounts or log in.
- **Accept Orders**: View and accept orders based on weight constraints and profit maximization.
- **View Schedule**: View a schedule of accepted orders.
- **Optimization**: The system ensures delivery efficiency using the Knapsack algorithm and Dijkstra's algorithm.

### Optimization Algorithms
1. **Knapsack Algorithm**: Determines the maximum profit achievable given the delivery person's weight constraints.
2. **Dijkstra's Algorithm**: Finds the shortest path between delivery locations, optimizing route efficiency.

---

## File Structure

### Code Files
- **`main.cpp`**: Contains the core logic for the system.

### Data Files
- **`users.txt`**: Stores user account details.
- **`delivery.txt`**: Stores delivery personnel account details.

---

## Getting Started

### Prerequisites
- **C++ Compiler**: Ensure you have a C++ compiler (e.g., GCC, MSVC) installed.
- **Windows**: This program uses `Windows.h` for console color settings, so it is designed for Windows systems.

### Compilation and Execution
1. Open a terminal or command prompt.
2. Compile the program:
   ```bash
   g++ -o CourierService main.cpp
   ```
3. Run the program:
   ```bash
   CourierService
   ```

---

## How to Use

### 1. Main Menu
Upon launching the program, you will see:
- **Create an Account**
- **Login**
- **Quit**

### 2. Account Creation
- Select "User" or "Delivery Person."
- Provide a unique username and password.
- Delivery personnel must also specify the maximum weight their vehicle can carry.

### 3. Login
- Log in as a "User" or "Delivery Person."
- Use your registered username and password.

### 4. User Dashboard
- **Place Orders**: Specify the number of items, their weights, and costs.

### 5. Delivery Dashboard
- **View and Accept Orders**: Evaluate available orders based on profit and weight constraints.
- **View Schedule**: See accepted orders.

---

## Algorithms Used

### Rabin-Karp Algorithm
- **Purpose**: Password matching.
- **Usage**: Ensures secure login validation for users and delivery personnel.

### Knapsack Algorithm
- **Purpose**: Determines the maximum profit achievable under weight constraints.

### Dijkstra's Algorithm
- **Purpose**: Finds the shortest path between delivery locations.
- **Usage**: Optimizes delivery routes for efficiency.

---

## Example Workflow

### User
1. Create a user account.
2. Log in and place an order by specifying items, weights, and costs.
3. Log out.

### Delivery Person
1. Create a delivery person account.
2. Log in and view available orders.
3. Accept an order if it meets weight constraints and profit expectations.
4. View your schedule.

---

## Important Notes
- Ensure `users.txt` and `delivery.txt` are in the same directory as the executable.
- Passwords must be unique across all accounts.
- Delivery personnel should verify weight constraints before accepting orders.

