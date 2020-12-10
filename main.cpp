#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

ifstream inFile;
ofstream outFile;

int stringToInteger(string &strConvert) {
    int result;
    stringstream stringToInteger(strConvert);
    stringToInteger >> result;
    return result;
}

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
    int timeDone;

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
        outFile << customerName << "|" << customerAddress << "|";
        outFile << customerPhone << "|" << itemNumber << "|";
        outFile << itemDescription << "|" << itemKg << "|";
        outFile << variant << "|" << priceLaundry << "|";
        outFile << timeOrder << "|" << timeDone << endl;
        outFile.close();
    } else if (choice == 2) {
        cout << "Lihat Daftar Pesanan : " << endl;
        inFile.open("laundry.txt");
        string strFile;
        cout << setw(17) << left << "Nama" << setw(15) << "Nomor HP" << setw(8) << "Berat" << setw(10) << right << "Batas Tanggal" << endl;
        while (!inFile.eof()) {
            getline(inFile, strFile);
            if (strFile.empty()) {
                break;
            }
            vector<int> delimeter;
            for (int i = 0; i < 9; i++) {
                if (i == 0) {
                    delimeter.push_back(strFile.find('|'));
                } else if (i != 0) {
                    delimeter.push_back(strFile.find('|', delimeter[i - 1] + 1));
                }
            }

            customerName = strFile.substr(0, delimeter[0]);
            customerAddress = strFile.substr(delimeter[0] + 1, delimeter[1] - delimeter[0] - 1);
            customerPhone = strFile.substr(delimeter[1] + 1, delimeter[2] - delimeter[1] - 1);

            strNumber = strFile.substr(delimeter[2] + 1, delimeter[3] - delimeter[2] - 1);
            itemNumber = stringToInteger(strNumber);

            itemDescription = strFile.substr(delimeter[3] + 1, delimeter[4] - delimeter[3] - 1);
            string strItemKg = strFile.substr(delimeter[4] + 1, delimeter[5] - delimeter[4] - 1);
            itemKg = stringToInteger(strNumber);

            strNumber = strFile.substr(delimeter[5] + 1, delimeter[6] - delimeter[5] - 1);
            variant = stringToInteger(strNumber);

            strNumber = strFile.substr(delimeter[6] + 1, delimeter[7] - delimeter[6] - 1);
            priceLaundry = stringToInteger(strNumber);

            strNumber = strFile.substr(delimeter[7] + 1, delimeter[8] - delimeter[7] - 1);
            timeOrder = stringToInteger(strNumber);

            strNumber = strFile.substr(delimeter[8] + 1);
            timeDone = stringToInteger(strNumber);

            time_t rawTime = timeDone;
            struct tm *timeinfo;
            timeinfo = localtime(&rawTime);

            cout << setw(17) << left << customerName.substr(0, 15) << setw(15) << customerPhone << setw(8) << strItemKg.append(" Kg") << setw(10) << right << timeDone << endl;

            // cout << customerName << endl;
            // cout << customerAddress << endl;
            // cout << customerPhone << endl;
            // cout << itemNumber << endl;
            // cout << itemDescription << endl;
            // cout << itemKg << endl;
            // cout << variant << endl;
            // cout << priceLaundry << endl;
            // cout << timeOrder << endl;
            // cout << timeDone << endl;
        }
    }

    return 0;
}
