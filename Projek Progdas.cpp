#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Struktur data untuk kontak
struct Contact {
    string name;
    string phone;
    string address;
};

// Fungsi untuk menampilkan menu utama
void displayMenu() {
    cout << "\n=== PHONEBOOK MENU ===" << endl;
    cout << "1. Tambah Kontak" << endl;
    cout << "2. Edit Kontak" << endl;
    cout << "3. Tampilkan Kontak" << endl;
    cout << "4. Hapus Kontak" << endl;
    cout << "5. Load Data Dari File" << endl;
    cout << "6. Simpan Data ke File" << endl;
    cout << "7. Keluar" << endl;
    cout << "Pilih opsi: " << endl;
}

// Fungsi utama
// Fungsi Tambah Kontak
void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "\n=== Tambah Kontak Baru ===" << endl;
    cout << "Nama     : "   ;
    getline(cin, newContact.name);
    cout << "Nomor HP : ";
    getline(cin, newContact.phone);
    cout << "Alamat   : ";
    getline(cin, newContact.address);

    contacts.push_back(newContact);
    cout << "Kontak berhasil ditambahkan!" << endl;
}

// Fungsi Tampilkan Kontak
void displayContacts(const vector<Contact>& contacts) {
    cout << "\n=== Daftar Kontak ===" << endl;
    if (contacts.empty()) {
        cout << "Tidak ada kontak yang tersimpan." << endl;
        return;
    }

    for (size_t i = 0; i < contacts.size(); i++) {
        cout << i + 1 << ". Nama     : " << contacts[i].name << endl;
        cout << "   Nomor HP : " << contacts[i].phone << endl;
        cout << "   Alamat   : " << contacts[i].address << endl;
        cout << "-----------------------" << endl;
    }
}

// Fungsi Edit Kontak
void editContact(vector<Contact>& contacts) {
    cout << "\n=== Edit Kontak ===" << endl;
    if (contacts.empty()) {
        cout << "Tidak ada kontak yang bisa diedit." << endl;
        return;
    }

    displayContacts(contacts);
    cout << "Pilih nomor kontak yang mau diedit: ";
    int index;
    cin >> index;
    cin.ignore(); // membersihkan input buffer

    if (index < 1 || index > contacts.size()) {
        cout << "Nomor kontak tidak valid!" << endl;
        return;
    }

    Contact& contactToEdit = contacts[index - 1];
    cout << "Edit Nama     : ";
    getline(cin, contactToEdit.name);
    cout << "Edit Nomor HP : ";
    getline(cin, contactToEdit.phone);
    cout << "Edit Alamat   : ";
    getline(cin, contactToEdit.address);

    cout << "Kontak berhasil diedit!" << endl;
}

// Fungsi Hapus Kontak
void deleteContact(vector<Contact>& contacts) {
    cout << "\n=== Hapus Kontak ===" << endl;
    if (contacts.empty()) {
        cout << "Tidak ada kontak yang bisa dihapus" << endl;
        return;
    }

    displayContacts(contacts);
    cout <<  "Pilih nomor kontak yang ingin dihapus: ";
    int index;
    cin >> index;
    cin.ignore(); //membersihkan input buffer

    if (index < 1 || index > contacts.size()) {
        cout << "Kontak tidak valid!" << endl;
    }
    else {
        contacts.erase(contacts.begin() + (index + 1));
        cout << "Kontak berhasil dihapus!" << endl;
    }
}

// Fungsi Load Data Dari File
void loadFromFile(vector<Contact>& contacts, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Gagal membuka file untuk load data." << endl;
        return;
    } 

    contacts.clear();
    Contact tempContact;
    while (getline(file, tempContact.name) &&
           getline(file, tempContact.phone) &&
           getline(file, tempContact.address)) {
            contacts.push_back(tempContact);
    }

    file.close();
    cout << "Data berhasil dimuat dari file!" << endl;
}

// Fungsi Save Data ke File
void saveToFile(const vector<Contact>& contacts, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data." << endl;
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.name << endl;
        file << contact.phone << endl;
        file << contact.address << endl;
    }

    file.close();
    cout << "Data berhasil disimpan ke file!" << endl;
}

int main() {
    vector<Contact> contacts; // menyimpan data kontak
    int choice;
    string filename = "phonebook.txt";

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // membersihkan input buffer

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                editContact(contacts);
                break;
            case 3:
                displayContacts(contacts);
                break;
            case 4:
                deleteContact(contacts);
                break;
            case 5:
                loadFromFile(contacts, filename);
                break;
            case 6:
                saveToFile(contacts, filename);
                break;
            case 7:
                cout << "Keluar dari program. Terima kasih!" << endl;
                break;
            default:
                cout << "Opsi tidak valid, coba lagi." << endl;
        }
    } while (choice != 7);
    return 0;
}
