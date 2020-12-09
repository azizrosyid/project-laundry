#include <iostream>
using namespace std;

int main() {
    int choice;
    string customerName;
    string customerAddress;
    string customerPhone;
    int itemNumber;
    string itemDescription;
    int itemKg;

    cout << "Selamat Datang di Laundry" << endl;
    cout << "1. Tambah Pesanan" << endl;
    cout << "2. Lihat daftar Pesanan" << endl;
    cout << "3. Edit Pesanan" << endl;
    cout << "4. Hapus Pesanan" << endl;
    cout << "Silahkan Pilih Menu : ";
    cin >> choice;

    if (choice == 1) {
        cout << "Silahkan Masukkan Data Pelanggan" << endl;
        cin.ignore();
        cout << "Nama       : ";
        getline(cin, customerName);
        cout << "Alamat     : ";
        getline(cin, customerAddress);
        cout << "Nomor HP   : ";
        getline(cin, customerPhone);

        cout << "Silahkan Masukkan Data Pakaian"<<endl;
        cout << "Jumlah Pakaian     : ";
        cin >> itemNumber;
        cout << "Deskripsi Pakaian  : ";
        cin.ignore();
        getline(cin,itemDescription);
        cout << "Berat Pakaian (Kg) : ";
        cin >> itemKg;
    }

    return 0;
}
