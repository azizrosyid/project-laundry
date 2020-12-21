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

int convertToInteger(string &tempString) {
    int resultConvert;
    stringstream tempInteger(tempString);  // inisiasi stringstream
    tempInteger >> resultConvert;          // convert str ke int
    return resultConvert;
}

string parseTime(const time_t &timestamp) {
    tm *structTime = localtime(&timestamp);
    stringstream resultString;
    resultString << structTime->tm_mday << "-" << structTime->tm_mon + 1 << "-" << structTime->tm_year + 1900;
    return resultString.str();
}

void getlineInteger(istream &file, int &result) {
    string tempString;
    getline(file, tempString, ',');
    result = convertToInteger(tempString);
}

void getlineTime(istream &file, time_t &result) {
    int tempInteger;
    getlineInteger(file, tempInteger);
    result = (time_t)tempInteger;
}

void readData(vector<Customer> &arrCustomer) {
    Customer dataCustomer;
    Laundry &dataLaundry = dataCustomer.order;
    inFile.open("laundry.txt");
    string lineString;
    while (getline(inFile, lineString)) {
        istringstream line(lineString);
        getline(line, dataCustomer.name, ',');
        getline(line, dataCustomer.address, ',');
        getline(line, dataCustomer.phone, ',');
        getlineInteger(line, dataLaundry.number);
        getline(line, dataLaundry.description, ',');
        getlineInteger(line, dataLaundry.itemKg);
        getlineInteger(line, dataLaundry.variant);
        getlineInteger(line, dataLaundry.priceLaundry);
        getlineTime(line, dataLaundry.timeOrder);
        getlineTime(line, dataLaundry.timeDone);
        arrCustomer.push_back(dataCustomer);
    }
    inFile.close();
}

void saveData(vector<Customer> &arrCustomer) {
    outFile.open("laundry.txt");
    for (int i = 0; i < arrCustomer.size(); i++) {
        Customer &dataCustomer = arrCustomer[i];
        Laundry &dataLaundry = dataCustomer.order;
        outFile << dataCustomer.name << ",";
        outFile << dataCustomer.address << ",";
        outFile << dataCustomer.phone << ",";
        outFile << dataLaundry.number << ",";
        outFile << dataLaundry.description << ",";
        outFile << dataLaundry.itemKg << ",";
        outFile << dataLaundry.variant << ",";
        outFile << dataLaundry.priceLaundry << ",";
        outFile << dataLaundry.timeOrder << ",";
        outFile << dataLaundry.timeDone << ",";
        outFile << endl;
    }
    outFile.close();
}

void showTransaction(vector<Customer> &arrCustomer, string searchValue = "") {
    cout << left << setw(5) << "No." << setw(17) << "Nama" << setw(15) << "Nomor HP" << setw(8) << "Berat" << setw(10) << right << "Batas Tanggal" << endl;
    for (int i = 0; i < arrCustomer.size(); i++) {
        if (arrCustomer[i].name.find(searchValue) != -1 || arrCustomer[i].phone.find(searchValue) != -1 || arrCustomer[i].address.find(searchValue) != -1) {
            cout << left << setw(5) << i + 1 << setw(17) << arrCustomer[i].name.substr(0, 15) << setw(15) << arrCustomer[i].phone << setw(8) << arrCustomer[i].order.itemKg << setw(10) << right << parseTime(arrCustomer[i].order.timeDone) << endl;
        }
    }
}

void showDetailTransaction(vector<Customer> &arrCustomer, int indexVector) {
    Customer &dataCustomer = arrCustomer[indexVector - 1];
    Laundry &dataLaundry = dataCustomer.order;
    cout << "Detail Customer" << endl;
    cout << "Nama       : " << dataCustomer.name << endl;
    cout << "Alamat     : " << dataCustomer.address << endl;
    cout << "Nomor HP   : " << dataCustomer.phone << endl;
    cout << "Detail Pesanan" << endl;
    cout << "Jumlah Pakaian     : " << dataLaundry.number << endl;
    cout << "Deskripsi Pakaian  : " << dataLaundry.description << endl;
    cout << "Berat Pakaian (Kg) : " << dataLaundry.itemKg << endl;
    cout << "Pilihan Paket      : " << dataLaundry.variant << endl;
    cout << "Total Harga        : " << dataLaundry.priceLaundry << endl;
    cout << "Tanggal Order      : " << parseTime(dataLaundry.timeOrder) << endl;
    cout << "Deadline Laundry   : " << parseTime(dataLaundry.timeDone) << endl;
}

int main() {
    vector<Customer> arrCustomer;
    int choice;
    string choiceStr;
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

    readData(arrCustomer);

    if (choice == 1) {
        cout << "Silahkan Masukkan Data Pelanggan" << endl;
        cin.ignore();
        cout << "Nama       : ";
        getline(cin, dataCustomer.name);
        cout << "Alamat     : ";
        getline(cin, dataCustomer.address);
        do {
            cout << "Nomor HP   : ";
            getline(cin, dataCustomer.phone);
        } while (dataCustomer.phone.length() >= 14);

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
            dataLaundry.priceLaundry = 3000 * dataLaundry.itemKg;
            dataLaundry.timeDone = timeInDay * 2;
        } else if (dataLaundry.variant == 3) {
            dataLaundry.priceLaundry = 2000 * dataLaundry.itemKg;
            dataLaundry.timeDone = timeInDay * 5;
        }
        cout << "Total Harga Adalah " << dataLaundry.priceLaundry << endl;
        dataLaundry.timeOrder = time(0);
        dataLaundry.timeDone += dataLaundry.timeOrder;
        arrCustomer.push_back(dataCustomer);
        saveData(arrCustomer);
    } else if (choice == 2) {
        cout << "Table Daftar Pesanan : " << endl;
        showTransaction(arrCustomer);
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
                showTransaction(arrCustomer, userSearch);
            } else if (choice == 2) {
                cout << "Masukkan Nomor Pesanan : ";
                cin >> choice;
                showDetailTransaction(arrCustomer, choice);
            }
        } while (choice != 0);
    } else if (choice == 3) {
        cout << "Table Daftar Pesanan" << endl;
        showTransaction(arrCustomer);
        cout << "Pilih Data : ";
        cin >> choice;
        showDetailTransaction(arrCustomer, choice);
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
                    arrCustomer[choice - 1].order.timeDone = timeInDay * 1;
                } else if (arrCustomer[choice - 1].order.variant == 2) {
                    arrCustomer[choice - 1].order.priceLaundry = 3000 * arrCustomer[choice - 1].order.itemKg;
                    arrCustomer[choice - 1].order.timeDone = timeInDay * 2;
                } else if (arrCustomer[choice - 1].order.variant == 3) {
                    arrCustomer[choice - 1].order.priceLaundry = 2000 * arrCustomer[choice - 1].order.itemKg;
                    arrCustomer[choice - 1].order.timeDone = timeInDay * 5;
                }

                cout << "Total Harga Adalah " << arrCustomer[choice - 1].order.priceLaundry << endl;
                arrCustomer[choice - 1].order.timeDone += arrCustomer[choice - 1].order.timeOrder;
            }
            saveData(arrCustomer);
        } while (choice != 0);
    } else if (choice == 4) {
        cout << "Table Daftar Pesanan" << endl;
        showTransaction(arrCustomer);
        cout << "Pilih Data Yang Ingin Dihapus: ";
        cin >> choice;
        showDetailTransaction(arrCustomer, choice);
        cout << "Apakah anda yakin ingin menghapus ? (Y/N) : ";
        cin.ignore();
        getline(cin, choiceStr);
        if (toupper(choiceStr[0]) == 'Y') {
            arrCustomer.erase(arrCustomer.begin() + choice);
            saveData(arrCustomer);
            cout << "Data Berhasil Dihapus" << endl;
        }
    }
    return 0;
}
