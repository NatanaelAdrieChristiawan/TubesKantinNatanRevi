#include <iostream>
#include "MLL.h"

using namespace std;


int main()
{
    List DataKantin;
    createList(DataKantin);

    int pilihan = -1;   // inisialisasi awal
    string namaK, namaM, kat;
    int stok;

    // tampilkan menu pertama kali
    cout << "\n=== SISTEM MONITORING KANTIN ===" << endl;
    cout << "1. Tambah Kantin Baru" << endl;
    cout << "2. Tambah Menu ke Kantin" << endl;
    cout << "3. Lihat Semua Data" << endl;
    cout << "4. Hapus Menu" << endl;
    cout << "5. Hapus Kantin (Tutup Permanen)" << endl;
    cout << "6. Analisis Performa (Min/Max)" << endl;
    cout << "7. Lihat Menu di Kantin Tertentu" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilih: ";
    cin >> pilihan;
    cin.ignore();

    while (pilihan != 0) {

        if (pilihan == 1) {
            cout << "Nama Kantin: ";
            getline(cin, namaK);
            insertKantin(DataKantin, newKantin(namaK));
        }
        else if (pilihan == 2) {
            cout << "Masukan ke Kantin mana: ";
            getline(cin, namaK);

            if (searchKantin(DataKantin, namaK) == NULL) {
                cout << "Kantin gak ditemukan!" << endl;
            } else {
                cout << "Nama Menu: ";
                getline(cin, namaM);
                cout << "Stok: ";
                cin >> stok;
                cin.ignore();
                cout << "Kategori (Berat/Snack/Minum): ";
                getline(cin, kat);

                insertMenu(DataKantin, namaK, newMenu(namaM, stok, kat));
            }
        }
        else if (pilihan == 3) {
            showAll(DataKantin);
        }
        else if (pilihan == 4) {
            cout << "Hapus dari Kantin mana: ";
            getline(cin, namaK);
            cout << "Nama Menu yg dihapus: ";
            getline(cin, namaM);

            deleteMenu(DataKantin, namaK, namaM);
        }
        else if (pilihan == 5) {
            cout << "Nama Kantin yg mau digusur: ";
            getline(cin, namaK);

            deleteKantin(DataKantin, namaK);
        }
        else if (pilihan == 6) {
            showMinMax(DataKantin);
        }
        else if (pilihan == 7) {
            cout << "Nama Kantin: ";
            getline(cin, namaK);
            adrKantin K = searchKantin(DataKantin, namaK);
            showMenuDiKantin(K);
        }
        else {
            cout << "Pilihan salah." << endl;
        }

        // tampilkan menu lagi
        cout << "\n=== SISTEM MONITORING KANTIN ===" << endl;
        cout << "1. Tambah Kantin Baru" << endl;
        cout << "2. Tambah Menu ke Kantin" << endl;
        cout << "3. Lihat Semua Data" << endl;
        cout << "4. Hapus Menu" << endl;
        cout << "5. Hapus Kantin (Tutup Permanen)" << endl;
        cout << "6. Analisis Performa (Min/Max)" << endl;
        cout << "7. Lihat Menu di Kantin Tertentu" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();
    }

    cout << "Dadah..." << endl;
    return 0;
}
