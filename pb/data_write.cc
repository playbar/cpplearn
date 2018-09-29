// See README.txt for information and build instructions.
// protoc style.proto --cpp_out=.

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "data.pb.h"

using namespace std;

// This function fills in a Person message based on user input.
void PromptForAddress(tutorial::Person* person) {
    cout << "Enter person ID number: ";
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');

    cout << "Enter name: ";
    getline(cin, *person->mutable_name());

    cout << "Enter email address (blank for none): ";
    string email;
    getline(cin, email);
    if (!email.empty()) {
        person->set_email(email);
    }

    while (true) {
        cout << "Enter a phone number (or leave blank to finish): ";
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }

        tutorial::PhoneNumber* phone_number = person->add_phones();
        phone_number->set_number(number);

        cout << "Is this a mobile, home, or work phone? ";
        string type;
        getline(cin, type);
        if (type == "mobile") {
            phone_number->set_type(tutorial::MOBILE);
        } else if (type == "home") {
            phone_number->set_type(tutorial::HOME);
        } else if (type == "work") {
            phone_number->set_type(tutorial::WORK);
        } else {
            cout << "Unknown phone type.  Using default." << endl;
        }
    }

}

void PromptForData(tutorial::Person* person)
{
    static int id = 1;
    person->set_id(id);
    ++id;
    person->set_name("name");
    person->set_email("email");

    for( int i = 0; i < 5; ++i )
    {
        tutorial::PhoneNumber* phone_number = person->add_phones();
        char szTmp[100];
        sprintf(szTmp, "number%d", i + 1);
        string num = szTmp;
        phone_number->set_number(num);
        phone_number->set_type(tutorial::MOBILE);
    }


}

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
int main(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

//  if (argc != 2) {
//    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
//    return -1;
//  }
    const char *pname = "data.dat";
    remove(pname);
    tutorial::AddressBook address_book;

    {
        // Read the existing address book.
        fstream input(pname, ios::in | ios::binary);
        if (!input) {
            cout << pname << ": File not found.  Creating a new file." << endl;
        } else if (!address_book.ParseFromIstream(&input)) {
            cerr << "Failed to parse address book." << endl;
            return -1;
        }
    }

    // Add an address.

    for( int j = 0; j < 4; ++j ) {
        PromptForData(address_book.add_people());
    }

    {
        // Write the new address book back to disk.
        fstream output(pname, ios::out | ios::trunc | ios::binary);
        if (!address_book.SerializeToOstream(&output)) {
            cerr << "Failed to write address book." << endl;
            return -1;
        }
    }

    string book = address_book.SerializePartialAsString();

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
