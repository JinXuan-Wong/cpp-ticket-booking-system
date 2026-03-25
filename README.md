# 🎟️ C++ Ticket Booking System

## 📌 Overview
This project is a console-based ticket booking system developed using C++ as part of a Year 1 Semester 1 assignment. The system simulates a real-world concert ticketing platform, allowing users to view seat availability, select seats, make payments, and generate receipts and tickets.

The system demonstrates core programming concepts such as:
- Control structures
- Functions and modular design
- Arrays and data validation
- User interaction and input handling

---

## 🎯 Features

### 🔐 User Authentication
- Login system with username and password validation
- Prevents unauthorized access

### 🪑 Seat Management System
- Two categories:
  - VIP Seats (3 × 10 layout)
  - General Seats (7 × 20 layout)
- Real-time seat availability tracking
- Reserved seats displayed in red color

### 🎟️ Ticket Ordering
- Select ticket category (VIP / General)
- Input number of tickets
- Choose specific seat codes (e.g., A1, B5)
- Prevents double booking

### 💳 Payment System
Supports multiple payment methods:
- Credit / Debit Card (with validation)
- Cash (with balance calculation)
- E-wallet

### 🧾 Receipt Generation
Displays:
- Ticket type and quantity
- Selected seats
- Total payment
- Payment method  
- Includes invoice number

### 🎫 Ticket Generation
Generates individual tickets for each seat:
- Seat number
- Price
- Queue number
- Event details

### 📊 Sales Report
Displays:
- Tickets sold (VIP & General)
- Remaining seats
- Total profit
- Number of customers  
- Includes simple text-based bar chart visualization

---

## 🏗️ System Structure

The system is designed using modular functions for better readability and maintainability.

### Key Functions:
- `login()` → Handles user authentication  
- `menu()` → Main navigation menu  
- `seatDisplay()` → Displays seating layout  
- `orderTicket()` → Core booking logic  
- `validateQuantity()` → Validates ticket quantity  
- `validateSeats()` → Validates seat selection  
- `calculate()` → Computes total cost  
- `payment()` → Handles payment processing  
- `receipt()` → Prints receipt  
- `ticket()` → Generates tickets  
- `salesReport()` → Displays system analytics  

---

## ⚙️ Technologies Used
- **Language:** C++  
- **Libraries:**
  - `<iostream>` – Input/Output  
  - `<iomanip>` – Formatting output  
  - `<string>` – String handling  
  - `<cstring>` – Character array validation  
  - `<cmath>` – Calculations  
  - `<windows.h>` – Console control (Windows only)  

---

## 📊 System Logic Highlights
- Uses 2D boolean arrays to track seat reservations:
  - `vipSeatsReserv[][]`
  - `genSeatsReserv[][]`
- Maintains global tracking variables:
  - `tickets_sold`
  - `cust_num`

Prevents:
- Overbooking  
- Invalid seat selection  
- Invalid payment input  

---

## ▶️ How to Run

### Compile:
```bash
g++ G3-WongJinXuan.cpp -o ticket_system

### Run:
```bash
./ticket_system

### Login credentials:
Username: user1  
Password: password

### 📌 Example Workflow
Login
View seat layout
Select ticket category
Choose seats
Make payment
Print receipt
Generate tickets
View sales report

### 👤 Author

Wong Jin Xuan
Bachelor of Data Science (Honours)
Tunku Abdul Rahman University of Management and Technology (TARUMT)

### 📄 License

This project is for academic purposes only.