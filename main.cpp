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
              //  int positiom = hospital_spec[spec].queue_length;
                cout << name << " ";
                if(hospital_spec[spec].status[person])
                    cout << "urgent\n";
                else
                    cout << "regular\n";
            }
            cout << endl;
        }
    }
}
void shift_left(int spec_pos, auto names[], auto status[]){
    int length = hospital_spec[spec_pos].queue_length;
    for (int i = 2; i <= length ; ++i) {
        names[i-1] = names[i];
        status[i-1] = status[i];
    }
    hospital_spec[spec_pos].queue_length--;
}

void shift_right(int spec_pos, auto names[], auto status[]){
    int length = hospital_spec[spec_pos].queue_length;
    for(int i = length; i >= 1; --i){
        names[i+1] = names[i];
        status[i+1] = status[i];
    }
    hospital_spec[spec_pos].queue_length++;
}

bool add_patient() {
    cout << "Enter specialization, name, status: ";
    string name;
    int status;
    int spec_pos;
    cin >> spec_pos >> name >> status;

    int pos = hospital_spec[spec_pos].queue_length +1;
    if (pos >=  MAX_QUEUE) {
        cout << "Sorry we can't add more patients for this specialization\n";
        return false;
    }

    if (status == 0) { // regular patient .. then add to end
        hospital_spec[spec_pos].name[pos] = name;
        hospital_spec[spec_pos].status[pos] = status;
        hospital_spec[spec_pos].queue_length++;
    }
    else {
        shift_right(spec_pos, hospital_spec[spec_pos].name, hospital_spec[spec_pos].status);
        hospital_spec[spec_pos].name[1] = name;
        hospital_spec[spec_pos].status[1] = status;
    }
    return true;
}
void get_next_patients() {
    cout << "Enter specialization: ";
    int spec_pos; cin >> spec_pos;
    int length = hospital_spec[spec_pos].queue_length;

    if (length == 0){
        cout << "No patients at the moment. Have rest, Dr\n";
        return;
    }
    // Let patient goes to doctor
    cout << hospital_spec[spec_pos].name[1] << " please go with the Dr\n";

    shift_left(spec_pos, hospital_spec[spec_pos].name, hospital_spec[spec_pos].status);
}

void system() {
    while (true) {
        int choice = menu();

        if (choice == 1)
            add_patient();
        else if (choice == 2)
            print_patient();
        else if(choice == 3)
            get_next_patients();
        else
            break;
    }
}

int main() {
    system();
    return 0;
}
