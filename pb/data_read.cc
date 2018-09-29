// See README.txt for information and build instructions.

#include <fstream>
#include <iostream>
#include <string>

#include "data.pb.h"

using namespace std;

// Iterates though all people in the AddressBook and prints info about them.
void ListPeople(const tutorial::AddressBook& address_book) {
    for (int i = 0; i < address_book.people_size(); i++) {
        const tutorial::Person& person = address_book.people(i);

        cout << "Person ID: " << person.id() << endl;
        cout << "  Name: " << person.name() << endl;
        if (person.email() != "") {
            cout << "  E-mail address: " << person.email() << endl;
        }

        for (int j = 0; j < person.phones_size(); j++) {
            const tutorial::PhoneNumber& phone_number = person.phones(j);

            switch (phone_number.type()) {
                case tutorial::MOBILE:
                    cout << "  Mobile phone #: ";
                    break;
                case tutorial::HOME:
                    cout << "  Home phone #: ";
                    break;
                case tutorial::WORK:
                    cout << "  Work phone #: ";
                    break;
                default:
                    cout << "  Unknown phone #: ";
                    break;
            }
            cout << phone_number.number() << endl;
        }
    }
}

// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int main(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    const char *pname = "data.dat";

//  if (argc != 2) {
//    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
//    return -1;
//  }

    tutorial::AddressBook address_book;
    FILE *fp = fopen(pname, "rb");
    fseek(fp, 0, SEEK_END);
    int nFileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET );
    char *fileBuffer = new char[nFileSize + 1 ];
    memset(fileBuffer, 0, nFileSize + 1);
    fread(fileBuffer, nFileSize, 1, fp );
    fclose(fp);
    address_book.ParseFromArray(fileBuffer, nFileSize);

    delete []fileBuffer;

//    {
//        // Read the existing address book.
//        fstream input(pname, ios::in | ios::binary);
//        if (!address_book.ParseFromIstream(&input)) {
//            cerr << "Failed to parse address book." << endl;
//            return -1;
//        }
//    }

    ListPeople(address_book);

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
