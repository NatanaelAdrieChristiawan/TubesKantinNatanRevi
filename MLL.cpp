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
    // Telusuri satu-satu
    while (P != NULL) {
        if (info(P).namaKantin == nama) {
            return P; // Ketemu! balikin alamatnya
        }
        P = next(P);
    }
    return NULL; // Gak ketemu :(
}

void deleteKantin(List &L, string nama) {
    // Hapus kantin itu tricky, karena anak-anaknya (menu) harus dihapus dulu
    // biar gak jadi sampah memori (memory leak).

    // 1. Cari dulu posisinya
    adrKantin P = first(L);
    adrKantin prev = NULL;

    while (P != NULL && info(P).namaKantin != nama) {
        prev = P;
        P = next(P);
    }

    if (P == NULL) {
        cout << "Kantin " << nama << " gak ketemu, batal hapus." << endl;
        return;
    }

    // 2. Hapus semua MENU (Anak) milik kantin ini
    adrMenu M = child(P);
    while (M != NULL) {
        adrMenu hapus = M;
        M = next(M);
        delete hapus; // Hapus menu dari memori
    }

    // 3. Baru hapus KANTIN (Induk)
    if (P == first(L)) {
        // Kalau yg dihapus kantin pertama
        first(L) = next(P);
    } else {
        // Kalau yg dihapus di tengah/akhir
        next(prev) = next(P);
    }
    delete P; // Hapus kantin dari memori
    cout << "Kantin " << nama << " dan seluruh menunya berhasil dihapus." << endl;
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
    if (K == NULL) {
        cout << "Data kosong melompong." << endl;
        return;
    }

    // Loop Parent (Kantin)
    while (K != NULL) {
        cout << "[" << info(K).namaKantin << "]" << endl;

        // Loop Child (Menu)
        adrMenu M = child(K);
        if (M == NULL) {
            cout << "   (Belum ada menu)" << endl;
        } else {
            while (M != NULL) {
                cout << "   -> " << info(M).namaMenu
                     << " | Stok: " << info(M).stok
                     << " | Kat: " << info(M).kategori << endl;
                M = next(M);
            }
        }
        cout << "--------------------------" << endl;
        K = next(K);
    }
}

void deleteMenu(List &L, string namaKantin, string namaMenu) {
    // 1. Cari kantinnya
    adrKantin K = searchKantin(L, namaKantin);
    if (K == NULL) return;

    // 2. Cari menunya di dalam kantin itu
    adrMenu M = child(K);
    adrMenu prevM = NULL;

    while (M != NULL && info(M).namaMenu != namaMenu) {
        prevM = M;
        M = next(M);
    }

    if (M == NULL) {
        cout << "Menu " << namaMenu << " gak ketemu di kantin ini." << endl;
        return;
    }

    // 3. Proses hapus node menu
    if (M == child(K)) {
        // Hapus menu pertama (anak sulung)
        child(K) = next(M);
    } else {
        // Hapus menu di tengah/akhir
        next(prevM) = next(M);
    }
    delete M;
    cout << "Menu berhasil dihapus." << endl;
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
    if (first(L) == NULL) return;

    adrKantin K = first(L);
    adrKantin maxK = K;
    adrKantin minK = K;

    int maxCount = -1;
    int minCount = 9999;

    // Loop semua kantin
    while (K != NULL) {
        int jumlah = countMenu(K);

        // Cek rekor terbanyak
        if (jumlah > maxCount) {
            maxCount = jumlah;
            maxK = K;
        }
        // Cek rekor tersedikit
        if (jumlah < minCount) {
            minCount = jumlah;
            minK = K;
        }
        K = next(K);
    }

    cout << "\n=== HASIL ANALISIS ===" << endl;
    cout << "Kantin Dengan Menu Paling Banyak: " << info(maxK).namaKantin
         << " (" << maxCount << " menu)" << endl;
    cout << "Kantin Dengan Menu Paling Sedikit: " << info(minK).namaKantin
         << " (" << minCount << " menu)" << endl;
}