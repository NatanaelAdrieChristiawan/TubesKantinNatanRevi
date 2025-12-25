#include "MLL.h"

void createList(List &L) {
    first(L) = NULL;
}

adrKantin newKantin(string nama) {
    adrKantin P = new elmKantin;
    info(P).namaKantin = nama;
    next(P) = NULL;
    child(P) = NULL; // Awal dibuat, kantin belum punya menu (anak)
    return P;
}

adrMenu newMenu(string nama, int stok, string kat) {
    // Minta jatah memori buat menu baru
    adrMenu P = new elmMenu;
    info(P).namaMenu = nama;
    info(P).stok = stok;
    info(P).kategori = kat;
    next(P) = NULL;
    return P;
}


void insertKantin(List &L, adrKantin P) {
    // Pakai Insert Last supaya urutannya sesuai input
    if (first(L) == NULL) {
        // Kalau list masih kosong, ini jadi kantin pertama
        first(L) = P;
    } else {
        // Kalau udah ada isinya, jalan dulu sampai ujung
        adrKantin Q = first(L);
        while (next(Q) != NULL) {
            Q = next(Q);
        }
        // Sambungin yang baru di belakang
        next(Q) = P;
    }
}

adrKantin searchKantin(List L, string nama) {
    adrKantin P = first(L);
    adrKantin hasil = NULL;
    bool ketemu = false;

    while (P != NULL && !ketemu) {
        if (info(P).namaKantin == nama) {
            hasil = P;
            ketemu = true;
        } else {
            P = next(P);
        }
    }

    return hasil;
}

void deleteKantin(List &L, string nama) {
    adrKantin P = first(L);
    adrKantin prev = NULL;
    bool ketemu = false;

    while (P != NULL && !ketemu) {
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
        while (M != NULL) {
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

void insertMenu(List &L, string namaKantin, adrMenu P) {
    // Cari dulu kantinnya ada gak?
    adrKantin K = searchKantin(L, namaKantin);

    if (K == NULL) {
        cout << "Waduh, Kantin " << namaKantin << " gak ada." << endl;
    } else {
        // Masukin menu ke dalam list child milik Kantin K
        // Kita pakai Insert Last juga biar rapi
        if (child(K) == NULL) {
            child(K) = P;
        } else {
            adrMenu Q = child(K);
            while (next(Q) != NULL) {
                Q = next(Q);
            }
            next(Q) = P;
        }
    }
}

void showAll(List L) {
    adrKantin K = first(L);

    if (K != NULL) {

        // Loop Parent (Kantin)
        while (K != NULL) {
            cout << "[" << info(K).namaKantin << "]" << endl;

            // Loop Child (Menu)
            adrMenu M = child(K);
            if (M != NULL) {
                while (M != NULL) {
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

void deleteMenu(List &L, string namaKantin, string namaMenu) {
   adrKantin K = searchKantin(L, namaKantin);

    if (K != NULL) {
        adrMenu M = child(K);
        adrMenu prevM = NULL;
        bool ketemu = false;

        while (M != NULL && !ketemu) {
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

void showMenuDiKantin(adrKantin K) {
    if (K != NULL) {
        adrMenu M = child(K);
        if (M != NULL) {
            while (M != NULL) {
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

int countMenu(adrKantin K) {
    int jum = 0;
    adrMenu M = child(K);
    while (M != NULL) {
        jum++;
        M = next(M);
    }
    return jum;
}

void showMinMax(List L) {
     if (first(L) != NULL) {

        adrKantin K = first(L);
        adrKantin maxK = K;
        adrKantin minK = K;

        int maxCount = -1;
        int minCount = 9999;

        while (K != NULL) {
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
