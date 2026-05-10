#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class ConsoleUI {
public:
    static constexpr const char* RESET   = "\033[0m";
    static constexpr const char* BOLD    = "\033[1m";
    static constexpr const char* RED     = "\033[31m";
    static constexpr const char* GREEN   = "\033[32m";
    static constexpr const char* YELLOW  = "\033[33m";
    static constexpr const char* BLUE    = "\033[34m";
    static constexpr const char* MAGENTA = "\033[35m";
    static constexpr const char* CYAN    = "\033[36m";
    static constexpr const char* WHITE   = "\033[37m";

    static void printHeader(string title) {
        cout << CYAN << BOLD << "\n+" << string(50, '-') << "+" << RESET << endl;
        int padding = (50 - title.length()) / 2;
        cout << CYAN << BOLD << "|" << RESET << string(padding, ' ') << YELLOW << BOLD << title << RESET << string(50 - padding - title.length(), ' ') << CYAN << BOLD << "|" << RESET << endl;
        cout << CYAN << BOLD << "+" << string(50, '-') << "+" << RESET << endl;
    }

    static void printSuccess(string msg) {
        cout << GREEN << BOLD << " [OK] " << RESET << msg << endl;
    }

    static void printError(string msg) {
        cout << RED << BOLD << " [ERROR] " << RESET << msg << endl;
    }

    static void printWarning(string msg) {
        cout << YELLOW << BOLD << " [WARN] " << RESET << msg << endl;
    }

    static void printMenuOption(int num, string text) {
        if (num == 0) {
            cout << RED << BOLD << " [" << num << "] " << RESET << text << endl;
        } else {
            cout << CYAN << BOLD << " [" << num << "] " << RESET << text << endl;
        }
    }

    static void printTableRow2(string col1, int w1, string col2, int w2) {
        cout << CYAN << " | " << RESET 
             << left << setw(w1) << col1 << CYAN << " | " << RESET 
             << left << setw(w2) << col2 << CYAN << " |" << RESET << endl;
    }

    static void printTableRow3(string col1, int w1, string col2, int w2, string col3, int w3) {
        cout << CYAN << " | " << RESET 
             << left << setw(w1) << col1 << CYAN << " | " << RESET 
             << left << setw(w2) << col2 << CYAN << " | " << RESET 
             << left << setw(w3) << col3 << CYAN << " |" << RESET << endl;
    }

    static void printTableRow4(string col1, int w1, string col2, int w2, string col3, int w3, string col4, int w4) {
        cout << CYAN << " | " << RESET 
             << left << setw(w1) << col1 << CYAN << " | " << RESET 
             << left << setw(w2) << col2 << CYAN << " | " << RESET 
             << left << setw(w3) << col3 << CYAN << " | " << RESET 
             << left << setw(w4) << col4 << CYAN << " |" << RESET << endl;
    }
    
    static void printTableRow5(string col1, int w1, string col2, int w2, string col3, int w3, string col4, int w4, string col5, int w5) {
        cout << CYAN << " | " << RESET 
             << left << setw(w1) << col1 << CYAN << " | " << RESET 
             << left << setw(w2) << col2 << CYAN << " | " << RESET 
             << left << setw(w3) << col3 << CYAN << " | " << RESET 
             << left << setw(w4) << col4 << CYAN << " | " << RESET 
             << left << setw(w5) << col5 << CYAN << " |" << RESET << endl;
    }

    static void printTableLine(int totalWidth) {
        cout << CYAN << " +" << string(totalWidth, '-') << "+" << RESET << endl;
    }

    static void printProductTableHeader() {
        printTableLine(75);
        printTableRow5("ID", 5, "PRODUCTO", 20, "CATEGORIA", 15, "PRECIO", 15, "STOCK", 8);
        printTableLine(75);
    }

    static void printProductTableFooter() {
        printTableLine(75);
    }

    static void printSupplierTableHeader() {
        printTableLine(85);
        printTableRow5("ID", 5, "PROVEEDOR", 20, "EMAIL", 25, "PAIS", 12, "CATEGORIA", 12);
        printTableLine(85);
    }

    static void printSupplierTableFooter() {
        printTableLine(85);
    }

    static string formatPrice(double price) {
        string str = to_string(price);
        return "S/. " + str.substr(0, str.find('.') + 3);
    }

    static void printCardHeader(string title) {
        cout << MAGENTA << " +====================================================+" << RESET << endl;
        int padding = (50 - title.length()) / 2;
        cout << MAGENTA << " | " << RESET << string(padding, ' ') << YELLOW << BOLD << title << RESET << string(50 - padding - title.length(), ' ') << MAGENTA << " |" << RESET << endl;
        cout << MAGENTA << " +====================================================+" << RESET << endl;
    }

    static void printCardField(string key, string value) {
        cout << MAGENTA << " | " << RESET << left << setw(15) << key << ": " << setw(33) << value << MAGENTA << "|" << RESET << endl;
    }

    static void printCardFooter() {
        cout << MAGENTA << " +====================================================+" << RESET << endl;
    }
};


