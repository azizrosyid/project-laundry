#include <stdlib.h>

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// declare class for i/o file
ifstream inFile;
ofstream outFile;

struct Laundry {
    int number;
    string description;
    int itemKg;
    int variant;
    int priceLaundry;
    time_t timeOrder;
    time_t timeDone;
};
struct Customer {
    string name;
    string address;
    string phone;
    Laundry order;
};

// declare vector for struct Customer
vector<Customer> arrCustomer;

// declare variable global
string customerName;
string customerAddress;
string customerPhone;
int itemNumber;
string itemDescription;
int itemKg;
int variant;
int priceLaundry;
time_t timeOrder;
time_t timeDone;

void convertToInteger(string &tempString, int &resultConvert) {
    stringstream tempInteger(tempString);  // inisiasi stringstream
    tempInteger >> resultConvert;          // convert str ke int
}

string parseTime(const time_t &timestamp) {
    tm *structTime = localtime(&timestamp);
    stringstream ss;
    ss << structTime->tm_mday << "-" << structTime->tm_mon + 1 << "-" << structTime->tm_year + 1900;
    return ss.str();
}

void readData() {
    string tempString;
    inFile.open("laundry.txt");
    while (getline(inFile, customerName)) {
        getline(inFile, customerAddress);
        getline(inFile, customerPhone);
        getline(inFile, tempString);
        convertToInteger(tempString, itemNumber);
        getline(inFile, itemDescription);
        getline(inFile, tempString);
        convertToInteger(tempString, itemKg);
        getline(inFile, tempString);
        convertToInteger(tempString, variant);
        getline(inFile, tempString);
        convertToInteger(tempString, priceLaundry);
        getline(inFile, tempString);
        const char *tempTimeOrder = tempString.c_str();
        timeOrder = (time_t)strtol(tempTimeOrder, NULL, 10);
        getline(inFile, tempString);
        const char *tempTimeDone = tempString.c_str();
        timeDone = (time_t)strtol(tempTimeDone, NULL, 10);

        Laundry order = {
            itemNumber,
            itemDescription,
            itemKg,
            variant,
            priceLaundry,
            timeOrder,
            timeDone};

        Customer customer = {
            customerName,
            customerAddress,
            customerPhone,
            order};

        arrCustomer.push_back(customer);
    }
    inFile.close();
}

void saveData() {
    outFile.open("laundry.txt");
    for (int i = 0; i < arrCustomer.size(); i++) {
        Laundry &saveOrder = arrCustomer[i].order;
        outFile << arrCustomer[i].name << endl;
        outFile << arrCustomer[i].address << endl;
        outFile << arrCustomer[i].phone << endl;
        outFile << saveOrder.number << endl;
        outFile << saveOrder.description << endl;
        outFile << saveOrder.itemKg << endl;
        outFile << saveOrder.variant << endl;
        outFile << saveOrder.priceLaundry << endl;
        outFile << saveOrder.timeOrder << endl;
        outFile << saveOrder.timeDone << endl;
    }
    outFile.close();
}

void showTransaction(string searchValue = "") {
    cout << left << setw(5) << "No." << setw(17) << "Nama" << setw(15) << "Nomor HP" << setw(8) << "Berat" << setw(10) << right << "Batas Tanggal" << endl;
    for (int i = 0; i < arrCustomer.size(); i++) {
        if (!searchValue.empty()) {
            if (arrCustomer[i].name == searchValue || arrCustomer[i].phone == searchValue || arrCustomer[i].address == searchValue) {
                cout << left << setw(5) << i + 1 << setw(17) << arrCustomer[i].name.substr(0, 15) << setw(15) << arrCustomer[i].phone << setw(8) << arrCustomer[i].order.itemKg << setw(10) << right << parseTime(arrCustomer[i].order.timeDone) << endl;
            }
        } else if (searchValue.empty()) {
            cout << left << setw(5) << i + 1 << setw(17) << arrCustomer[i].name.substr(0, 15) << setw(15) << arrCustomer[i].phone << setw(8) << arrCustomer[i].order.itemKg << setw(10) << right << parseTime(arrCustomer[i].order.timeDone) << endl;
        }
    }
}

void showDetailTransaction(int indexVector) {
    Laundry &detailOrder = arrCustomer[indexVector - 1].order;
    cout << "Detail Customer" << endl;
    cout << "Nama       : " << arrCustomer[indexVector - 1].name << endl;
    cout << "Alamat     : " << arrCustomer[indexVector - 1].address << endl;
    cout << "Nomor HP   : " << arrCustomer[indexVector - 1].phone << endl;
    cout << "Detail Pesanan" << endl;
    cout << "Jumlah Pakaian     : " << detailOrder.number << endl;
    cout << "Deskripsi Pakaian  : " << detailOrder.description << endl;
    cout << "Berat Pakaian (Kg) : " << detailOrder.itemKg << endl;
    cout << "Pilihan Paket      : " << detailOrder.variant << endl;
    cout << "Total Harga        : " << detailOrder.priceLaundry << endl;
    cout << "Tanggal Order      : " << parseTime(detailOrder.timeOrder) << endl;
    cout << "Deadline Laundry   : " << parseTime(detailOrder.timeDone) << endl;
}

int main() {
    int choice;
    int timeInDay = 24 * 60 * 60;
    string userSearch;
    Customer dataCustomer;

    cout << "Selamat Datang di Laundry" << endl
         << "1. Tambah Pesanan" << endl
         << "2. Lihat daftar Pesanan" << endl
         << "3. Edit Pesanan" << endl
         << "4. Hapus Pesanan" << endl
         << "Silahkan Pilih Menu : ";
    cin >> choice;

    readData();

    if (choice == 1) {
        cout << "Silahkan Masukkan Data Pelanggan" << endl;
        cin.ignore();
        cout << "Nama       : ";
        getline(cin, dataCustomer.name);
        cout << "Alamat     : ";
        getline(cin, dataCustomer.address);
        cout << "Nomor HP   : ";
        do {
            getline(cin, dataCustomer.phone);
        } while (customerPhone.length() >= 14);

        Laundry &dataLaundry = dataCustomer.order;
        cout << "Silahkan Masukkan Data Pakaian" << endl;
        cout << "Jumlah Pakaian     : ";
        cin >> dataLaundry.number;
        cout << "Deskripsi Pakaian  : ";
        cin.ignore();
        getline(cin, dataLaundry.description);
        cout << "Berat Pakaian (Kg) : ";
        cin >> dataLaundry.itemKg;

        cout << "Masukkan Paket yang dipilih : " << endl
             << "1. Paket Kilat (1 Hari Jadi) 5000/Kg" << endl
             << "2. Paket Cepat (2 Hari Jadi) 3000 / Kg" << endl
             << "3. Paket Lambat (5 Hari Jadi) 2000 / Kg" << endl
             << "Paket Nomor [1-3] : ";

        cin >> dataLaundry.variant;
        if (dataLaundry.variant == 1) {
            dataLaundry.priceLaundry = 5000 * dataLaundry.itemKg;
            dataLaundry.timeDone = timeInDay * 1;
        } else if (dataLaundry.variant == 2) {
            priceLaundry = 3000 * itemKg;
            dataLaundry.timeDone = timeInDay * 2;
        } else if (dataLaundry.variant == 3) {
            priceLaundry = 2000 * itemKg;
            dataLaundry.timeDone = timeInDay * 5;
        }
        cout << "Total Harga Adalah " << dataLaundry.priceLaundry << endl;
        dataLaundry.timeOrder = time(0);
        dataLaundry.timeDone += dataLaundry.timeOrder;
        arrCustomer.push_back(dataCustomer);
        saveData();
    } else if (choice == 2) {
        cout << "Table Daftar Pesanan : " << endl;
        showTransaction();
        do {
            cout << "Fitur : " << endl
                 << "1. Cari Data" << endl
                 << "2. Lihat detail data" << endl
                 << "0. Keluar" << endl
                 << "Pilih : ";
            cin >> choice;
            if (choice == 1) {
                cout << "Masukkan Nama / Nomor HP / Alamat : ";
                cin.ignore();
                getline(cin, userSearch);
                showTransaction(userSearch);
            } else if (choice == 2) {
                cout << "Masukkan Nomor Pesanan : ";
                cin >> choice;
                showDetailTransaction(choice);
            }
        } while (choice != 0);
    } else if (choice == 3) {
        cout << "Table Daftar Pesanan" << endl;
        showTransaction();
        cout << "Pilih Data : ";
        cin >> choice;
        showDetailTransaction(choice);
        do {
            cout << "Data Yang Ingin Diubah : " << endl;
            cout << "1. Nama" << endl;
            cout << "2. Alamat" << endl;
            cout << "3. Nomor HP" << endl;
            cout << "4. Jumlah Pakaian" << endl;
            cout << "5. Deskripsi Pakaian" << endl;
            cout << "6. Berat Pakaian (Kg)" << endl;
            cout << "7. Pilihan Paket" << endl;
            cout << "0. Keluar" << endl;
            cout << "Pilih Data : ";
            cin >> choice;
            cin.ignore();
            if (choice == 1) {
                cout << "Nama : ";
                getline(cin, arrCustomer[choice - 1].name);
            } else if (choice == 2) {
                cout << "Alamat : ";
                getline(cin, arrCustomer[choice - 1].address);
            } else if (choice == 3) {
                cout << "Nomor HP : ";
                getline(cin, arrCustomer[choice - 1].phone);
            } else if (choice == 4) {
                cout << "Jumlah Pakaian : ";
                cin >> arrCustomer[choice - 1].order.number;
            } else if (choice == 5) {
                cout << "Deskripsi Pakaian : ";
                getline(cin, arrCustomer[choice - 1].order.description);
            } else if (choice == 6) {
                cout << "Berat Pakaian (Kg) : ";
                cin >> arrCustomer[choice - 1].order.itemKg;
            } else if (choice == 7) {
                cout << "Masukkan Paket yang dipilih : " << endl
                     << "1. Paket Kilat (1 Hari Jadi) 5000/Kg" << endl
                     << "2. Paket Cepat (2 Hari Jadi) 3000 / Kg" << endl
                     << "3. Paket Lambat (5 Hari Jadi) 2000 / Kg" << endl
                     << "Paket Nomor [1-3] : ";
                cin >> arrCustomer[choice - 1].order.variant;
                if (arrCustomer[choice - 1].order.variant == 1) {
                    arrCustomer[choice - 1].order.priceLaundry = 5000 * arrCustomer[choice - 1].order.itemKg;
                    timeDone = timeInDay * 1;
                } else if (arrCustomer[choice - 1].order.variant == 2) {
                    arrCustomer[choice - 1].order.priceLaundry = 3000 * arrCustomer[choice - 1].order.itemKg;
                    timeDone = timeInDay * 2;
                } else if (arrCustomer[choice - 1].order.variant == 3) {
                    arrCustomer[choice - 1].order.priceLaundry = 2000 * arrCustomer[choice - 1].order.itemKg;
                    timeDone = timeInDay * 5;
                }

                cout << "Total Harga Adalah " << arrCustomer[choice - 1].order.priceLaundry << endl;
                arrCustomer[choice - 1].order.timeDone = arrCustomer[choice - 1].order.timeOrder + timeDone;
            }
            saveData();
        } while (choice != 0);
    } else if (choice == 4) {
        cout << "Table Daftar Pesanan" << endl;
        showTransaction();
        cout << "Pilih Data Yang Ingin Dihapus: ";
        cin >> choice;
        arrCustomer.erase(arrCustomer.begin() + choice);
        saveData();
    }
    return 0;
}
