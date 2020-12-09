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
    int priceLaundry;

    cout << "Selamat Datang di Laundry" << endl
         << "1. Tambah Pesanan" << endl
         << "2. Lihat daftar Pesanan" << endl
         << "3. Edit Pesanan" << endl
         << "4. Hapus Pesanan" << endl
         << "Silahkan Pilih Menu : ";
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

        cout << "Silahkan Masukkan Data Pakaian" << endl;
        cout << "Jumlah Pakaian     : ";
        cin >> itemNumber;
        cout << "Deskripsi Pakaian  : ";
        cin.ignore();
        getline(cin, itemDescription);
        cout << "Berat Pakaian (Kg) : ";
        cin >> itemKg;

        cout << "Masukkan Paket yang dipilih : " << endl
             << "1. Paket Kilat (1 Hari Jadi) 5000/Kg" << endl
             << "2. Paket Cepat (2 Hari Jadi) 3000 / Kg" << endl
             << "3. Paket Lambat (5 Hari Jadi) 2000 / Kg" << endl
             << "Paket Nomor [1-3] : ";

        int &variant = choice;
        cin >> variant;
        if (variant == 1) {
            priceLaundry = 5000 * itemKg;
        } else if (variant == 2) {
            priceLaundry = 3000 * itemKg;
        } else if (variant == 3) {
            priceLaundry = 2000 * itemKg;
        }

        cout << "Total Harga Adalah " << priceLaundry << endl;
    }

    return 0;
}
