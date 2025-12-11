#include <iostream>
#include "MLL.h"

using namespace std;

int main()
{
    List DataKantin;
    createList(DataKantin);

    int pilihan;
    string namaK, namaM, kat;
    int stok;

    do {
        cout << "\n=== SISTEM MONITORING KANTIN ===" << endl;
        cout << "1. Tambah Kantin Baru" << endl;
        cout << "2. Tambah Menu ke Kantin" << endl;
        cout << "3. Lihat Semua Data" << endl;
        cout << "4. Hapus Menu" << endl;
        cout << "5. Hapus Kantin (Tutup Permanen)" << endl;
        cout << "6. Analisis Performa (Min/Max)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore(); // Bersihin buffer enter biar getline gak error

        switch(pilihan) {
        case 1:
            cout << "Nama Kantin: ";
            getline(cin, namaK);
            insertKantin(DataKantin, newKantin(namaK));
            break;
        case 2:
            cout << "Masukan ke Kantin mana: ";
            getline(cin, namaK);
            // Cek dulu kantinnya ada gak, biar user gak capek ngetik menu kalo kantinnya gada
            if (searchKantin(DataKantin, namaK) == NULL) {
                cout << "Kantin gak ditemukan!" << endl;
            } else {
                cout << "Nama Menu: "; getline(cin, namaM);
                cout << "Stok: "; cin >> stok;
                cin.ignore();
                cout << "Kategori (Berat/Snack/Minum): "; getline(cin, kat);
                insertMenu(DataKantin, namaK, newMenu(namaM, stok, kat));
            }
            break;
        case 3:
            showAll(DataKantin);
            break;
        case 4:
            cout << "Hapus dari Kantin mana: "; getline(cin, namaK);
            cout << "Nama Menu yg dihapus: "; getline(cin, namaM);
            deleteMenu(DataKantin, namaK, namaM);
            break;
        case 5:
            cout << "Nama Kantin yg mau digusur: "; getline(cin, namaK);
            deleteKantin(DataKantin, namaK);
            break;
        case 6:
            showMinMax(DataKantin);
            break;
        case 0:
            cout << "Dadah..." << endl;
            break;
        default:
            cout << "Pilihan salah." << endl;
        }
    } while (pilihan != 0);

    return 0;
}