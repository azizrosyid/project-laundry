#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

ifstream inFile;
ofstream outFile;

int main() {
    int choice;
    string customerName;
    string customerAddress;
    string customerPhone;
    string strNumber;
    int itemNumber;
    string itemDescription;
    int itemKg;
    int variant;
    int priceLaundry;
    int timeInDay = 24 * 60 * 60;
    time_t timeOrder;
    time_t timeDone;

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
        do {
            getline(cin, customerPhone);
        } while (customerPhone.length() >= 14);

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

        cin >> variant;
        if (variant == 1) {
            priceLaundry = 5000 * itemKg;
            timeDone = timeInDay * 1;
        } else if (variant == 2) {
            priceLaundry = 3000 * itemKg;
            timeDone = timeInDay * 2;
        } else if (variant == 3) {
            priceLaundry = 2000 * itemKg;
            timeDone = timeInDay * 5;
        }

        cout << "Total Harga Adalah " << priceLaundry << endl;
        timeOrder = time(0);
        timeDone += timeOrder;

        outFile.open("laundry.txt", ios::app);
        outFile.write(reinterpret_cast<char *>(&customerName), sizeof(customerName));
        outFile.write(reinterpret_cast<char *>(&customerAddress), sizeof(customerAddress));
        outFile.write(reinterpret_cast<char *>(&customerPhone), sizeof(customerPhone));
        outFile.write(reinterpret_cast<char *>(&itemNumber), sizeof(itemNumber));
        outFile.write(reinterpret_cast<char *>(&itemDescription), sizeof(itemDescription));
        outFile.write(reinterpret_cast<char *>(&itemKg), sizeof(itemKg));
        outFile.write(reinterpret_cast<char *>(&variant), sizeof(variant));
        outFile.write(reinterpret_cast<char *>(&priceLaundry), sizeof(priceLaundry));
        outFile.write(reinterpret_cast<char *>(&timeOrder), sizeof(timeOrder));
        outFile.write(reinterpret_cast<char *>(&timeDone), sizeof(timeDone));
        outFile.close();
    } else if (choice == 2) {
        cout << "Lihat Daftar Pesanan : " << endl;
        inFile.open("laundry.txt");
        cout << setw(17) << left << "Nama" << setw(15) << "Nomor HP" << setw(8) << "Berat" << setw(10) << right << "Batas Tanggal" << endl;
        while (inFile.read(reinterpret_cast<char *>(&customerName), sizeof(customerName))) {
            inFile.read(reinterpret_cast<char *>(&customerAddress), sizeof(customerAddress));
            inFile.read(reinterpret_cast<char *>(&customerPhone), sizeof(customerPhone));
            inFile.read(reinterpret_cast<char *>(&itemNumber), sizeof(itemNumber));
            inFile.read(reinterpret_cast<char *>(&itemDescription), sizeof(itemDescription));
            inFile.read(reinterpret_cast<char *>(&itemKg), sizeof(itemKg));
            inFile.read(reinterpret_cast<char *>(&variant), sizeof(variant));
            inFile.read(reinterpret_cast<char *>(&priceLaundry), sizeof(priceLaundry));
            inFile.read(reinterpret_cast<char *>(&timeOrder), sizeof(timeOrder));
            inFile.read(reinterpret_cast<char *>(&timeDone), sizeof(timeDone));
            cout << setw(17) << left << customerName.substr(0, 15) << setw(15) << customerPhone << setw(8) << itemKg << setw(10) << right << timeDone << endl;
        }
        inFile.close();
    }
    

    return 0;
}
