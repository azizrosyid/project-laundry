#include <iomanip>
#include <iostream>
#include <limits>
#define MAX_SIZE 100
using namespace std;

string customerName[MAX_SIZE];
string customerPhone[MAX_SIZE];
int laundryKg[MAX_SIZE];
int laundryPrice[MAX_SIZE];
int length = 0;
const int pricePerKg = 3500;

void showTransaction();
void deleteElemArray(const int &);
int inputInteger(string);
void menu();
void addTransaction();
void editTransaction();
void deleteTransaction();

int main() {
    int choice;
    string userSearch;
    do {
        menu();
        choice = inputInteger("Pilih : ");
        cin.ignore();
        if (choice == 1) {
            addTransaction();
            cin.ignore();
        } else if (choice == 2) {
            showTransaction();
            cin.ignore();
        } else if (choice == 3) {
            editTransaction();
            cin.ignore();
        } else if (choice == 4) {
            deleteTransaction();
        }
    } while (choice != 0);

    return 0;
}

void showTransaction() {
    cout << "Table Daftar Pesanan : " << endl;
    cout << left << setw(5) << "No." << setw(17) << "Nama" << setw(15) << "Nomor HP" << setw(15) << "Berat (Kg)" << setw(15) << right << "Harga Laundry" << endl;
    for (int i = 0; i < length; i++) {
        cout << left << setw(5) << i + 1 << setw(17) << customerName[i].substr(0, 15) << setw(15) << customerPhone[i] << setw(15) << laundryKg[i] << setw(15) << right << laundryPrice[i] << endl;
    }
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

int inputInteger(string message) {
    int result;
    while (cout << message && !(cin >> result)) {
        cout << "Anda salah input, ulangi sampai benar " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return result;
}

void countPrice(int *itemLaundryPrice, int *itemLaundryKg) {
    int discount = 0;
    if (*itemLaundryKg > 10) {
        cout << "Anda mendapatkan diskon 10000" << endl;
        discount = 10000;
    }
    *itemLaundryPrice = *itemLaundryKg * pricePerKg - discount;
}

void menu() {
    cout << "Selamat Datang di Laundry" << endl
         << "1. Tambah Pesanan" << endl
         << "2. Lihat daftar Pesanan" << endl
         << "3. Edit Pesanan" << endl
         << "4. Hapus Pesanan" << endl
         << "0. Keluar" << endl;
}

void addTransaction() {
    cout << "Silahkan Masukkan Data Pelanggan" << endl;
    cout << "Nama       : ";
    getline(cin, customerName[length]);
    cout << "Nomor HP   : ";
    getline(cin, customerPhone[length]);

    cout << "Silahkan Masukkan Data Pakaian" << endl;
    cout << "Berat Pakaian (Kg) : ";
    laundryKg[length] = inputInteger("");
    countPrice(&laundryPrice[length], &laundryKg[length]);
    cin.ignore();

    cout << "Total Harga Adalah " << laundryPrice[length] << endl;
    length++;
}

void editTransaction() {
    int index;
    int choice;
    showTransaction();
    cout << "Pilih Data : ";
    index = inputInteger("") - 1;
    if (index >= 0 && index <= length - 1) {
        do {
            cout << "Data Yang Ingin Diubah : " << endl;
            cout << "1. Nama" << endl;
            cout << "2. Nomor HP" << endl;
            cout << "3. Berat Pakaian (Kg)" << endl;
            cout << "0. Keluar" << endl;
            choice = inputInteger("Pilih : ");
            cin.ignore();
            switch (choice) {
                case 1:
                    cout << "Nama : ";
                    getline(cin, customerName[index]);
                    break;
                case 2:
                    cout << "Nomor HP : ";
                    getline(cin, customerPhone[index]);
                    break;
                case 3:
                    cout << "Berat Pakaian (Kg) : ";
                    cin >> laundryKg[index];
                    countPrice(&laundryPrice[index], &laundryKg[index]);
                    cin.ignore();
                    cout << "Total Harga Adalah " << laundryPrice[index] << endl;
                    cin.ignore();
                    break;
                case 0:
                    break;
                default:
                    cout << "Pilihan Tidak Ada" << endl;
                    break;
            }
        } while (choice != 0);
    } else {
        cout << "Pilihan Tidak Ada" << endl;
    }
}

void deleteTransaction() {
    string strChoice;
    int choice;
    showTransaction();
    cout << "Pilih Data Yang Ingin Dihapus: ";
    choice = inputInteger("");
    if (choice >= 0 && choice <= length) {
        cout << "Apakah anda yakin ingin menghapus ? (Y/N) : ";
        cin.ignore();
        getline(cin, strChoice);
        if (toupper(strChoice[0]) == 'Y') {
            deleteElemArray(choice);
            cout << "Data Berhasil Dihapus" << endl;
        } else {
            cout << "Data Tidak Dihapus" << endl;
        }
    } else {
        cout << "Pilihan Tidak Ada" << endl;
    }
}