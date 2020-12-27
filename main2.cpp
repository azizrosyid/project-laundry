#include <iomanip>
#include <iostream>
#define MAX_SIZE 100
using namespace std;

string customerName[MAX_SIZE];
string customerPhone[MAX_SIZE];
int laundryKg[MAX_SIZE];
int laundryPrice[MAX_SIZE];
int length = 0;

void showTransaction(const string &searchValue = "") {
    cout << left << setw(5) << "No." << setw(17) << "Nama" << setw(15) << "Nomor HP" << setw(15) << "Berat (Kg)" << setw(15) << right << "Harga Laundry" << endl;
    for (int i = 0; i < length; i++) {
        if (customerName[i].find(searchValue) != -1 || customerPhone[i].find(searchValue) != -1) {
            cout << left << setw(5) << i + 1 << setw(17) << customerName[i].substr(0, 15) << setw(15) << customerPhone[i] << setw(15) << laundryKg[i] << setw(15) << right << laundryPrice[i] << endl;
        }
    }
}

void swapElemArray(const int &index1, const int &index2) {
    swap(customerName[index1], customerName[index2]);
    swap(customerPhone[index1], customerPhone[index2]);
    swap(laundryKg[index1], laundryKg[index2]);
    swap(laundryPrice[index1], laundryPrice[index2]);
}

void deleteElemArray(const int &choice) {
    for (int i = choice - 1; i < length; i++) {
        customerName[i] = customerName[i + 1];
        customerPhone[i] = customerPhone[i + 1];
        laundryKg[i] = laundryKg[i + 1];
        laundryPrice[i] = laundryPrice[i + 1];
    }
    length--;
}

void sortingArray(const int &mode) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (mode == 1) {
                if (customerName[j] > customerName[j + 1]) {
                    swapElemArray(j, j + 1);
                }
            } else if (mode == 2) {
                if (laundryPrice[j] > laundryPrice[j + 1]) {
                    swapElemArray(j, j + 1);
                }
            }
        }
    }
}

int main() {
    const int pricePerKg = 3500;
    int choice;
    string choiceStr;
    string userSearch;
    do {
        cout << "Selamat Datang di Laundry" << endl
             << "1. Tambah Pesanan" << endl
             << "2. Lihat daftar Pesanan" << endl
             << "3. Edit Pesanan" << endl
             << "4. Hapus Pesanan" << endl
             << "0. Keluar" << endl
             << "Silahkan Pilih Menu : ";
        // TODO validasi disini
        cin >> choice;
        if (choice == 1) {
            cout << "Silahkan Masukkan Data Pelanggan" << endl;
            cin.ignore();
            cout << "Nama       : ";
            getline(cin, customerName[length]);
            do {
                cout << "Nomor HP   : ";
                getline(cin, customerPhone[length]);
            } while (customerPhone[length].length() >= 14);

            cout << "Silahkan Masukkan Data Pakaian" << endl;
            cout << "Berat Pakaian (Kg) : ";
            // TODO validasi disini
            cin >> laundryKg[length];
            laundryPrice[length] = laundryKg[length] * pricePerKg;
            cin.ignore();
            
            cout << "Total Harga Adalah " << laundryPrice[length] << endl;
            length++;
            cin.ignore();
        } else if (choice == 2) {
            cout << "Table Daftar Pesanan : " << endl;
            showTransaction();
            do {
                cout << "Fitur : " << endl
                     << "1. Cari Data" << endl
                     << "2. Urutkan data" << endl
                     << "99. Keluar" << endl
                     << "Pilih : ";
                cin >> choice;
                if (choice == 1) {
                    cout << "Masukkan Nama / Nomor HP : ";
                    cin.ignore();
                    getline(cin, userSearch);
                    showTransaction(userSearch);
                } else if (choice == 2) {
                    cout << "1. Nama " << endl
                         << "2. Harga" << endl
                         << "Urutkan berdasarkan [1-2] : ";
                    // TODO tambahkan validasi
                    cin >> choice;
                    sortingArray(choice);
                    showTransaction();
                }
            } while (choice != 99);
        } else if (choice == 3) {
            cout << "Table Daftar Pesanan" << endl;
            showTransaction();
            cout << "Pilih Data : ";
            cin >> choice;
            do {
                cout << "Data Yang Ingin Diubah : " << endl;
                cout << "1. Nama" << endl;            
                cout << "2. Nomor HP" << endl;                                
                cout << "3. Berat Pakaian (Kg)" << endl;
                cout << "99. Keluar" << endl;
                cout << "Pilih Data : ";
                cin >> choice;
                cin.ignore();
                if (choice == 1) {
                    cout << "Nama : ";
                    getline(cin, customerName[choice - 1]);
                } else if (choice == 2) {
                    cout << "Nomor HP : ";
                    getline(cin, customerPhone[choice - 1]);
                } else if (choice == 3) {
                    cout << "Berat Pakaian (Kg) : ";
                    cin >> laundryKg[choice - 1]);
                    laundryPrice[choice - 1] = laundryKg[choice - 1] * pricePerKg;
                    cin.ignore();
                    cout << "Total Harga Adalah " << laundryPrice[choice - 1] << endl;
                    cin.ignore();
                }
        } while (choice != 99)
        } else if (choice == 4) {
            cout << "Table Daftar Pesanan" << endl;
            showTransaction();
            cout << "Pilih Data Yang Ingin Dihapus: ";
            cin >> choice;
            cout << "Apakah anda yakin ingin menghapus ? (Y/N) : ";
            cin.ignore();
            getline(cin, choiceStr);
            if (toupper(choiceStr[0]) == 'Y') {
                deleteElemArray(choice);
                cout << "Data Berhasil Dihapus" << endl;
            }
        }
    } while (choice != 99);

    return 0;
}
