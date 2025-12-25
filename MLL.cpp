#include "MLL.h"

// IS List L belum terdefinisi
// LS Pointer first(L) bernilai nullptr
void createList(List &L) {
    first(L) = nullptr;
}

// IS Belum terdapat node kantin baru di memori.
// LS Mengembalikan address P yang berisi data kantin, next=nullptr, firstMenu=nullptr
adrKantin newKantin(string nama) {
    adrKantin P = new elmKantin;
    info(P).namaKantin = nama;
    next(P) = nullptr;
    child(P) = nullptr; // Awal dibuat, kantin belum punya menu (anak)
    return P;
}

// IS Belum terdapat node menu baru di memori.
// FS Mengembalikan address P yang berisi data menu, next = nullptr
adrMenu newMenu(string nama, int stok, string kat) {
    // Minta jatah memori buat menu baru
    adrMenu P = new elmMenu;
    info(P).namaMenu = nama;
    info(P).stok = stok;
    info(P).kategori = kat;
    next(P) = nullptr;
    return P;
}

// IS List L mungkin kosong atau sudah berisi beberapa kantin.
// FS Node kantin P berhasil ditambahkan sebagai elemen terakhir
void insertKantin(List &L, adrKantin P) {
    // Pakai Insert Last supaya urutannya sesuai input
    if (first(L) == nullptr) {
        // Kalau list masih kosong, ini jadi kantin pertama
        first(L) = P;
    } else {
        // Kalau udah ada isinya, jalan dulu sampai ujung
        adrKantin Q = first(L);
        while (next(Q) != nullptr) {
            Q = next(Q);
        }
        // Sambungin yang baru di belakang
        next(Q) = P;
    }
}
// IS L terdefinisi nama terdefinisi
// FS Mengembalikan alamat kantin jika ketemu , nullptr jika tidak
adrKantin searchKantin(List L, string nama) {
    adrKantin P = first(L);
    adrKantin hasil = nullptr;
    bool ketemu = false;

    while (P != nullptr && !ketemu) {
        if (info(P).namaKantin == nama) {
            hasil = P;
            ketemu = true;
        } else {
            P = next(P);
        }
    }

    return hasil;
}

// IS L terdefinisi, nama terdefinisi
// FS Jika ketemu kantin dan seluruh menu dihapus, jika tidak, tidak terjadi apa apa
void deleteKantin(List &L, string nama) {
    adrKantin P = first(L);
    adrKantin prev = nullptr;
    bool ketemu = false;

    while (P != nullptr && !ketemu) {
        if (info(P).namaKantin == nama) {
            ketemu = true;
        } else {
            prev = P;
            P = next(P);
        }
    }

    if (ketemu) {
        // hapus semua menu
        adrMenu M = child(P);
        while (M != nullptr) {
            adrMenu hapus = M;
            M = next(M);
            delete hapus;
        }

        if (P == first(L)) {
            first(L) = next(P);
        } else {
            next(prev) = next(P);
        }
        delete P;
        cout << "Kantin " << nama << " dan seluruh menunya berhasil dihapus." << endl;
    } else {
        cout << "Kantin " << nama << " gak ketemu, batal hapus." << endl;
    }
}

// --- BAGIAN MENU (CHILD) ---

// IS L terdefinisi, namaKantin terdefinisi P sudah teralokasi
// FS Jika kantin ditemukan P ditambahkan di akhir

void insertMenu(List &L, string namaKantin, adrMenu P) {
    // Cari dulu kantinnya ada gak?
    adrKantin K = searchKantin(L, namaKantin);

    if (K == nullptr) {
        cout << "Waduh, Kantin " << namaKantin << " gak ada." << endl;
    } else {
        // Masukin menu ke dalam list child milik Kantin K
        // Kita pakai Insert Last juga biar rapi
        if (child(K) == nullptr) {
            child(K) = P;
        } else {
            adrMenu Q = child(K);
            while (next(Q) != nullptr) {
                Q = next(Q);
            }
            next(Q) = P;
        }
    }
}

// IS L terdefinisi
// LS Menampilkan seluruh data kantin beserta menunya
void showAll(List L) {
    adrKantin K = first(L);

    if (K != nullptr) {

        // Loop Parent (Kantin)
        while (K != nullptr) {
            cout << "[" << info(K).namaKantin << "]" << endl;

            // Loop Child (Menu)
            adrMenu M = child(K);
            if (M != nullptr) {
                while (M != nullptr) {
                    cout << "   -> " << info(M).namaMenu
                         << " | Stok: " << info(M).stok
                         << " | Kat: " << info(M).kategori << endl;
                    M = next(M);
                }
            } else {
                cout << "   (Belum ada menu)" << endl;
            }

            cout << "--------------------------" << endl;
            K = next(K);
        }

    } else {
        cout << "Data kosong melompong." << endl;
    }
}

// IS L terdefinisi, namaKantin terdefinisi, namaMenu terdefinisi
// LS Menu yang di input dihapus dari kantin yang di inputkan
void deleteMenu(List &L, string namaKantin, string namaMenu) {
   adrKantin K = searchKantin(L, namaKantin);

    if (K != nullptr) {
        adrMenu M = child(K);
        adrMenu prevM = nullptr;
        bool ketemu = false;

        while (M != nullptr && !ketemu) {
            if (info(M).namaMenu == namaMenu) {
                ketemu = true;
            } else {
                prevM = M;
                M = next(M);
            }
        }

        if (ketemu) {
            if (M == child(K)) {
                child(K) = next(M);
            } else {
                next(prevM) = next(M);
            }
            delete M;
            cout << "Menu berhasil dihapus." << endl;
        } else {
            cout << "Menu " << namaMenu << " gak ketemu di kantin ini." << endl;
        }
    }
}

// IS K terdfinisi / nullptr
// LS Menampilkan seluruh menu pada kantin yang di input
void showMenuDiKantin(adrKantin K) {
    if (K != nullptr) {
        adrMenu M = child(K);
        if (M != nullptr) {
            while (M != nullptr) {
                cout << "-> " << info(M).namaMenu
                     << " | Stok: " << info(M).stok
                     << " | Kat: " << info(M).kategori << endl;
                M = next(M);
            }
        } else {
            cout << "(Belum ada menu)" << endl;
        }
    } else {
        cout << "Kantin tidak ditemukan." << endl;
    }
}



// --- FITUR ANALISIS ---

// IS K mempunyai 0 / lebih menu
// LS mengembalikan jumlah menu pada kantin yang di tuju
int countMenu(adrKantin K) {
    int jum = 0;
    adrMenu M = child(K);
    while (M != nullptr) {
        jum++;
        M = next(M);
    }
    return jum;
}

// IS L terdefinisi
// LS Menampilkan kantin dengan menu terbanyak dan kantin dengan menu tersedikit
void showMinMax(List L) {
     if (first(L) != nullptr) {

        adrKantin K = first(L);
        adrKantin maxK = K;
        adrKantin minK = K;

        int maxCount = -1;
        int minCount = 9999;

        while (K != nullptr) {
            int jumlah = countMenu(K);

            if (jumlah > maxCount) {
                maxCount = jumlah;
                maxK = K;
            }
            if (jumlah < minCount) {
                minCount = jumlah;
                minK = K;
            }

            K = next(K);
        }

        cout << "\n=== HASIL ANALISIS ===" << endl;
        cout << "Kantin Dengan Menu Paling Banyak: "
             << info(maxK).namaKantin << " (" << maxCount << " menu)" << endl;
        cout << "Kantin Dengan Menu Paling Sedikit: "
             << info(minK).namaKantin << " (" << minCount << " menu)" << endl;

    } else {
        cout << "Data kantin masih kosong." << endl;
    }
}
