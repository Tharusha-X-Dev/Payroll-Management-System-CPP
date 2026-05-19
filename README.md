# 💼 Payroll Management System (C++)

A **console-based Payroll Management System** designed for efficient salary calculation, tax deduction, error logging, and record management — all from a simple yet powerful terminal interface.

---

## 🎯 Features

- 🏷 **Generate Employee Payrolls**  
  Enter worked hours and instantly calculate monthly salaries

- 💰 **Automatic Salary & Tax Calculations**  
  Accurately applies tax-free allowances and computes deductions

- 🗂 **Employee Record Search**  
  Find and display payroll information for any employee and any month

- 📝 **Payroll History**  
  Review all payroll data across multiple months

- 📄 **File Handling**  
  Reads and writes data using clear text files (CSV-like)

- ⚠️ **Error Logging**  
  Identifies and logs invalid payroll entries for traceability

- 💾 **Report Export**  
  Save payroll outputs and error logs as text files

---

## 🛠 Technologies Used

- **C++** (Standard Library)
- STL Vectors
- File I/O Streams
- Structs & Functions
- Input Validation

---

## 📚 Concepts Demonstrated

- Modular Programming & Structured Design
- Error Handling via Logs
- Data Processing and Validation
- File I/O (Reading & Writing Text Files)
- Payroll & Tax Calculations

---

## 📁 Project Structure & Files

### **Input Files**
- `employees.txt` — Master list of employee IDs, names, and pay rates.
- `Jan25.txt`, `Feb25.txt`, `Mar25.txt`, `Apr25.txt` — Monthly employee work hours.

### **Output Files**
- `Jan25_output.txt`, etc. — Monthly payroll results (auto-generated)
- `errors.txt` — All input and processing errors logged for transparency.

---

## 🚀 How to Run

1. **Open in Visual Studio** (or compatible C++ IDE)
2. **Build** the program (ensure all `.txt` files are present)
3. **Run** the executable
4. **Follow on-screen prompts:**
   - Enter input payroll file names (e.g., `Jan25.txt`)
   - Search for employee records or view payroll history

---

## 📝 Example Functionalities

- **Payroll Generation:** Calculates each employee's gross and net salary for the chosen month, considering hours and pay rates.
- **Tax Deduction:** Applies a tax-free allowance and calculates the correct deduction automatically.
- **Record Search:** Queried by employee ID — supports month-wise or aggregate view.
- **Earnings Summary & Export:** View and save payroll histories and summaries to text files.

---

## 👨‍🎓 Author

**K.A Tharusha Lakshan Dananjaya**  
Student ID: Hidden

---

> _For demonstration and academic purposes. Contributions welcome!_
