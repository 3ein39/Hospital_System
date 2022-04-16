#include <iostream>
using namespace std;

struct SPEC {
    string name[6];
    int status[6];
    int queue_length = 0;
};
SPEC hospital_spec[20];
int MAX_QUEUE = 5;

int menu() {
    int choice = -1;
    while (choice == -1) {
        cout << "\nEnter your choice:\n";
        cout << "1) Add new patient\n";
        cout << "2) Print all patients\n";
        cout << "3) Get next patient\n";
        cout << "4) Exit\n";

        cin >> choice;

        if (!(1 <= choice && choice <= 4)) {
            cout << "Invalid choice. Try again\n";
            choice = -1;	// loop keep working
        }
    }
    return choice;
}
void print_patient() {
    for (int spec = 1; spec <= 20 ; ++spec) {
        if(hospital_spec[spec].queue_length > 0){
            cout << "********************************\n";
            int len = hospital_spec[spec].queue_length;
            cout << "There are " << len << " patients in specialization " << spec << endl;
            for (int person = 1; person <= len ; ++person) {
                string name = hospital_spec[spec].name[person];
                int positiom = hospital_spec[spec].queue_length;
                cout << name << " regular" << endl;
            }
        }
        cout << endl;
    }
}

bool add_patient() {
    cout << "Enter specialization, name, status: ";
    string name;
    int status;
    int spec_pos;
    cin >> spec_pos >> name >> status;

    int pos = hospital_spec[spec_pos].queue_length;
    if (pos >=  MAX_QUEUE) {
        cout << "Sorry we can't add more patients for this specialization\n";
        return false;
    }

    if (status == 0) { // regular patient .. then add to end
        hospital_spec[spec_pos].name[pos] = name;
        hospital_spec[spec_pos].status[pos] = status;
        hospital_spec[spec_pos].queue_length++;
    }
    return true;
}


void system() {
    while (true) {
        int choice = menu();

        if (choice == 1)
            add_patient();
        else if (choice == 2)
            print_patient();
    }
}

int main() {
    system();
    return 0;
}
