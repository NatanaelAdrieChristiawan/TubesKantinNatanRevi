#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED
#include <iostream>

using namespace std;

// Definisi Konstanta
#define first(L) L.first
#define next(P) P->next
#define info(P) P->info
#define child(P) P->child  // Pointer dari Parent ke Child pertama


// 1. Definisi Pointer
typedef struct elmKantin *adrKantin;
typedef struct elmMenu *adrMenu;

// 2 Definisi Infotype
struct infotypeKantin {
    string namaKantin;
};

struct infotypeMenu {
    string namaMenu;
    int stok;
    string kategori;
};

// 3. Definisi Element
struct elmMenu {
    infotypeMenu info;
    adrMenu next; // Pointer ke menu berikutnya (Singly)
};

struct elmKantin {
    infotypeKantin info;
    adrKantin next; // Pointer ke kantin berikutnya (Singly)
    adrMenu child;  // Pointer penghubung ke list Menu (Child)
};

// 4. Definisi List
struct List {
    adrKantin first; // Head dari list Kantin
};


// Persiapan Awal
void createList(List &L);
adrKantin newKantin(string nama);
adrMenu newMenu(string nama, int stok, string kat);

// Fitur Kantin (Parent)
void insertKantin(List &L, adrKantin P);         // Masukin kantin baru
adrKantin searchKantin(List L, string nama);     // Cari kantin by nama
void deleteKantin(List &L, string nama);         // Hapus kantin + semua menunya
void showAll(List L);                            // Tampilkan semua kantin & menu

// Fitur Menu (Child)
void insertMenu(List &L, string namaKantin, adrMenu P);       // Nambah menu ke kantin tertentu
void deleteMenu(List &L, string namaKantin, string namaMenu); // Hapus menu spesifik
void showMenuDiKantin(adrKantin K);                           // Liat menu di satu kantin aja

// Fitur Analisis (Stok & Hitungan)
int countMenu(adrKantin K); // Hitung ada berapa menu di satu kantin
void showMinMax(List L);    // Cari kantin paling lengkap & paling sepi


#endif // MLL_H_INCLUDED
