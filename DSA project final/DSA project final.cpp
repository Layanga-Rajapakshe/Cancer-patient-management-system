#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

void displayCopyright() {
    // Set text color to yellow
    cout << "\033[1;33m";

    // Display the copyright message
    cout << "                             National Cancer Control Program 2023                                   \n\n";
    cout << "                                        project by:                                                      \n";
    cout << "          Piumantha H.D.B.A.A, Gunarathne A.N.G.T.N.B, Rajapakshe R.M.M.L.D          \n";
    cout << "                                  University of Ruhuna                                             \n";

    // Reset text color
    cout << "\033[0m";
}

void clearConsole() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

class node
{
public:

    node* left;
    node* right;
    node* parent;
    node* next;
    node* prev;
    int ID;
    string Name;
    int Age;
    string Address;
    int Phone;
    int G_Phone;
    string Doctor_in_Charge;

    node()
    {

        left = NULL;
        right = NULL;
        parent = NULL;
        ID = 0;
        Name = "";
        Age = 0;
        Address = "";
        Phone = 0;
        G_Phone = 0;
        Doctor_in_Charge = "";
    }
    node(double id, string name, int age, string address1, int phone, int g_phone, string d_incharge)
    {
        ID = id;
        Name = name;
        Age = age;
        Address = address1;
        Phone = phone;
        G_Phone = g_phone;
        Doctor_in_Charge = d_incharge;
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    node(int patientId) {
        ID = patientId;
        next = NULL;
    }
};

class  Waiting_List
{
public:
    node* root;
    int size;

    Waiting_List()
    {
        root = NULL;
        size = 0;

    }

    void insert_Patient(int id, string name, int age, string address1, int phone, int g_phone, string d_incharge)
    {
        node* temp = new node(id, name, age, address1, phone, g_phone, d_incharge);
        node* current = root;
        node* prev = NULL;
        while (current != NULL)
        {
            prev = current;
            if (id > current->ID)
            {
                current = current->right;

            }
            else if (id < current->ID)
            {
                current = current->left;

            }
            else if (id == current->ID)
            {
                cout << "There is already record on this NIC " << endl;
                return;
            }



        }
        if (prev == NULL)
        {
            root = temp;
        }
        else if (id > prev->ID)
        {
            prev->right = temp;
            temp->parent = prev;


        }
        else if (id < prev->ID)
        {
            prev->left = temp;
            temp->parent = prev;

        }
        size++;


    }

    node* search(int id)
    {
        node* temp = NULL;
        if (root == NULL)
        {
            cout << "Queue is Empty" << endl;
        }
        else
        {
            node* current = root;
            while (current != NULL)
            {
                if (id == current->ID)
                {
                    temp = current;
                    return temp;

                }
                else if (id < current->ID)
                {
                    current = current->left;
                }
                else if (id > current->ID)
                {
                    current = current->right;
                }
            }
            if (temp == NULL)
            {
                cout << "No record found!!" << endl;
                return NULL;
            }


        }
    }

    void show_patient()
    {
        int id;
        cout << "Enter patient Id: ";
        cin >> id;
        node* temp = search(id);
        if (temp == NULL)
        {
            cout << " " << endl;
        }
        else
        {
            cout << " Name     " << endl;
            cout << temp->Name << endl;
            cout << " Age     " << endl;
            cout << temp->Age << endl;
            cout << " ID Number  " << endl;
            cout << temp->ID << endl;
            cout << " Doctor In Charge " << endl;
            cout << temp->Doctor_in_Charge << endl;
            cout << " Phone Number " << endl;
            cout << temp->Phone << endl;
            cout << " Guardians Phone Number " << endl;
            cout << temp->G_Phone << endl;
        }

    }

    void search_edit()
    {
        int id;
        cout << "Enter patient Id: ";
        cin >> id;
        node* temp = search(id);
        if (temp == NULL)
        {
            cout << " " << endl;
        }
        else
        {
            int p;
            int gp;
            cout << "Enter the new phone number - " << endl;
            cin >> p;
            cout << "Enter the new Guardians phone number" << endl;
            cin >> gp;
            temp->Phone = p;
            temp->G_Phone = gp;
            cout << "Numbers are Updated" << endl;
        }
    }

    void delete_a_patient()
    {
        int id;
        cout << "Enter patient Id to delete: ";
        cin >> id;
        node* temp = search(id);
        if (root == NULL)
        {
            cout << "The Queue is Empty!!" << endl;

        }
        else
        {
            node* current = root;
            while ((current != NULL) && (current->ID != id))
            {
                if (id < current->ID)
                {
                    current = current->left;
                }
                else if (id > current->ID)
                {
                    current = current->right;
                }
            }
            if (current == NULL)
            {
                cout << "No record found !!" << endl;
            }
            else
            {
                if ((current->left == NULL) && (current->right == NULL))
                {
                    if (current == root)
                    {
                        root = NULL;
                    }
                    else if (current->ID < current->parent->ID)
                    {
                        current->parent->left = NULL;
                    }
                    else
                    {
                        current->parent->right = NULL;
                    }
                    delete current;
                    size--;
                }
                else if (current->left == NULL)
                {
                    if (current == root)
                    {
                        root = current->right;
                        root->parent == NULL;

                    }
                    else if (current->ID < current->parent->ID)
                    {
                        current->parent->left = current->right;
                    }
                    else
                    {
                        current->parent->right = current->right;
                    }
                    delete current;
                    size--;

                }
                else if (current->right == NULL)
                {
                    if (current == root)
                    {
                        root = current->left;
                        root->parent == NULL;
                    }
                    else if (current->ID < current->parent->ID)
                    {
                        current->parent->left = current->left;
                    }
                    else
                    {
                        current->parent->right = current->left;
                    }
                    delete current;
                    size--;
                }
                else
                {
                    node* max = current->left;
                    while (max->right != NULL)
                    {
                        max = max->right;
                    }
                    current->ID = max->ID;
                    if (max == current->left)
                    {
                        current->left = max->left;
                        if (max->left != NULL)
                            max->left->parent = current;
                    }
                    else
                    {
                        max->parent->right = max->left;
                    }
                    size--;
                }
            }
        }

    }

    void patient_Onboarding()// 1st - Adding a patient to the queue
    {
        int ID;
        string Name;
        int Age;
        string Address1;
        int Phone;
        int G_Phone;

        string doc[10] = { "A","B","C","D","E","F","G","H","I","J" };
        cout << "Enter the Patient's NIC  : ";
        cin >> ID;
        cout << endl;

        cout << "Enter the Patient's Name : ";
        cin >> Name;
        cout << endl;
        

        cout << "Enter the Patient's Age  : ";
        cin >> Age;
        cout << endl;

        cout << "Enter the Patient's Address line1  : ";
        cin >> Address1;
        cout << endl;
        
        cout << "Enter the Patient's Phone Number   : ";
        cin >> Phone;
        cout << endl;

        cout << "Enter the Guardian's Phone Number  : ";
        cin >> G_Phone;
        cout << endl;



        string Doctor_In_Charge = doc[doctor_in_Charge(ID)];

        insert_Patient(ID, Name, Age, Address1, Phone, G_Phone, Doctor_In_Charge);


    }

    int doctor_in_Charge(int ID)
    {
        return (ID % 10) + 1;


    }

};

class Queue {
private:
    node* front;
    node* rear;
    int capacity;

public:
    Queue() {
        front = NULL;
        rear = NULL;
        capacity = 0;
    }

    void enqueue(int patientId) {
        node* newNode = new node(patientId);

        if (capacity == 0) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }

        capacity++;
    }

    // Function to dequeue (remove) a patient from the queue
    void dequeue() {
        if (capacity == 0) {
            cout << "Queue is empty. No patients to dequeue." << endl;
            return;
        }

        node* temp = front;
        front = front->next;

        //cout << "Patient with ID " << temp->data.id<< " removed from the queue." << endl;

        delete temp;
        capacity--;
    }

    void displayQueue() {
        if (capacity == 0) {
            cout << "Queue is empty. No patients to display." << endl;
            return;
        }

        cout << "List of patients in the queue:" << endl;
        node* current = front;
        while (current != NULL) {
            cout << current->ID << "  ";
            current = current->next;
        }
        cout << endl;
    }
};

void operation1(Queue& Therepy) {
    int x;
    cout << "1-Add patient\n2-Remove patient\n3-Display Queue: ";
    cin >> x;

    if (x == 1)
    {
        int y;
        cout << "Enter patient ID: ";
        cin >> y;
        Therepy.enqueue(y);
        cout << endl;
    }
    else if (x == 2) {
        Therepy.dequeue();
    }
    else if (x == 3) {
        Therepy.displayQueue();
        cout << endl;
    }
    else {
        cout << "Invalid operation " << endl;
    }

}

void operation2(Queue& Therepy) {
    int x;
    cout << "1-Display Queue: ";
    cin >> x;

    if (x == 1) {
        Therepy.displayQueue();
        cout << endl;
    }
    else {
        cout << "Invalid operation " << endl;
    }

}

//Main menu function for Queue Management
int askAdmin1() {
    int x;
    cout << "\n-----Patient Treatment Queue Management (Mode: Admin)-----\n" << endl;
    cout << "   1-Doctor consultation\n   2-Oncology\n   3-MRI\n   4-chemotherepy\n   5-Radiotherepy\n   6-Exit to main menu\n\nSelect option: ";
    cin >> x;
    cout << endl;
    return x;
}

int askAdmin2() {
    int x;
    cout << "\n-----Patient Treatment Queue Management (Mode: User)-----\n" << endl;
    cout << "   1-Doctor consultation\n   2-Oncology\n   3-MRI\n   4-chemotherepy\n   5-Radiotherepy\n   6-Exit to main menu\n\nSelect option: ";
    cin >> x;
    cout << endl;
    return x;
}

// Function to get the current date and time
string getCurrentDateTime() {
    time_t now = time(0);
    struct tm timeinfo;
    char buffer[80];
    localtime_s(&timeinfo, &now); // Use localtime_s instead of localtime
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    string dateTime(buffer);
    return dateTime;
}

// Function to save a patient to a file
void saveMRBToFile(int patientId, string time, string description) {
    ofstream file;
    string filename = "patient_" + to_string(patientId) + "MRB.txt";
    file.open(filename);

    if (file.is_open()) {
        file << "Patient ID: " << patientId << "\n";
        // file << "Patient Name: " << patientName << "\n";
        file << "Report add-time: " << time << "\n";
        file << "Current report: " << description << "\n";
        cout << "Patient information saved to file.\n";
        file.close();
    }
    else {
        cout << "Error: Unable to open the patient file for writing.\n";
    }
}

void newMedicalRecord(int patientId) {
    string time = getCurrentDateTime();
    string description;

    cout << "Patient ID:" << patientId << endl;
    cout << "Enter the the report: ";
    getline(cin, description);

    saveMRBToFile(patientId, time, description);
    cout << "New MRB for patient " << patientId << " created. To Edit MRB please Enter 3 below\n";
}

// Function to access the MRB of a patient
int AccessPatientMRB() {
    int patientId;
    cout << "Enter Patient ID:";
    cin >> patientId;
    return patientId;
}

void readPatientFromMRB(int i) {
    ifstream file;
    string filename = "patient_" + to_string(i) + "MRB.txt";
    file.open(filename);

    if (file.is_open()) {
        cout << "----Medical Record Book (Mode: View only)----\n";
        cout << "Patient Information for ID " << i << ":\n";
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    }
    else {
        cout << "Error: Unable to open the patient file for reading.\n";
    }
}

void editPatientFromMRB(int i) {
    ifstream file1;
    string current;
    string filename = "patient_" + to_string(i) + "MRB.txt";
    file1.open(filename);

    if (file1.is_open()) {
        cout << "----Medical Record Book (Mode: Edit only)\n";
        cout << "Patient Information for ID " << i << ":\n";
        string line;
        while (getline(file1, line)) {
            getline(file1, current);
        }
        file1.close();
    }
    else {
        cout << "Error: Unable to open the patient file for reading.\n";
    }

    string time = getCurrentDateTime();
    string description;

    cout << "Patient ID:" << i << endl;
    cin.ignore();
    cout << "Enter the the new report: ";
    getline(cin, description);

    ofstream file2;
    file2.open(filename);
    if (file2.is_open()) {
        file2 << current << "\n";
        file2 << "Patient ID: " << i << "\n";
        file2 << "Report add-time: " << time << "\n";
        file2 << "Current report: " << description << "\n";
        cout << "Patient information saved to file.\n";
        file2.close();
    }
    else {
        cout << "Error: Unable to open the patient file for reading.\n";
    }
}

int main() {
    clearConsole();
    Queue Cheemotherepy;
    Queue Oncology;
    Queue MRItherepy;
    Queue Radiotherepy;
    Queue Doctorlist;

    Waiting_List Patient1;
    Patient1.insert_Patient(1, "Jhon", 45, "Badulla", 7976333, 572246233, "A");
    Patient1.insert_Patient(2, "Walter", 5, "Peradeniya", 7672385, 572624598, "B");
    Patient1.insert_Patient(3, "Kevin", 78, "Monaragala", 727875999, 574485698, "C");

    string username, password;
    int attempt = 3; // Login attempts

    //username and password
    string correctUsername1 = "admin";
    string correctPassword1 = "123";

    string correctUsername2 = "user";
    string correctPassword2 = "123";

    while (attempt > 0) {
        clearConsole();
        displayCopyright();
        cout << "     .----------------.  .----------------.  .----------------.  .----------------. " << endl;
        cout << "    | .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
        cout << "    | |     ______   | || |  _________   | || | ____    ____ | || |    _______   | |" << endl;
        cout << "    | |   .' ___  |  | || | |  _   _  |  | || ||_   \\  /   _|| || |   /  ___  |  | |" << endl;
        cout << "    | |  / .'   \\_|  | || | |_/ | | \\_|  | || |  |   \\/   |  | || |  |  (__ \\_|  | |" << endl;
        cout << "    | |  | |         | || |     | |      | || |  | |\\  /| |  | || |   '.___`-.   | |" << endl;
        cout << "    | |  \\ `.___.'\\  | || |    _| |_     | || | _| |_\\/_| |_ | || |  |`\\____) |  | |" << endl;
        cout << "    | |   `._____.'  | || |   |_____|    | || ||_____||_____|| || |  |_______.'  | |" << endl;
        cout << "    | |              | || |              | || |              | || |              | |" << endl;
        cout << "    | '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
        cout << "     '----------------'  '----------------'  '----------------'  '----------------' " << endl;
        cout << endl <<endl;

        cout << "----------Cancer Treatment Management System----------\n";
        cout << "                -----CTMS Log In-----\n";
        if (attempt < 3) {
            cout << "Incorrect username or password. " << attempt << " attempts remaining." << endl;
        }
        cout << "           Enter username: ";
        cin >> username;
        cout << "           Enter password: ";
        cin >> password;

        if (username == correctUsername1 && password == correctPassword1) {
            cout << "Login successful!" << endl;

            int choice;

            do {
                clearConsole();
                cout << "***Admin view***\n";
                cout << "----------Patient Management System----------\n\n";
                cout << "    1. Insert new patient\n";
                cout << "    2. View patients info\n";
                cout << "    3. Edit patient data\n";
                cout << "    4. Delete a patient\n";
                cout << "    5. Access Patient Treatment Queue Management\n";
                cout << "    6. Access Patient MRB Management\n";
                cout << "    7. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    clearConsole();
                    Patient1.patient_Onboarding();
                    break;
                case 2:
                    int choice3;
                    do {
                        cout << "----------View patient info----------\n\n";
                        cout << "    1. View patient data\n";
                        cout << "    2. Exit\n";
                        cout << "Enter your choice: ";
                        cin >> choice3;

                        switch (choice3) {
                        case 1:
                            Patient1.show_patient();
                            break;
                        case 2:
                            cout << "Exiting to main menu\n";
                            break;
                        }
                    } while (choice3 != 2);
                    break;
                case 3:
                    clearConsole();
                    Patient1.search_edit();
                    break;
                case 4:
                    clearConsole();
                    Patient1.delete_a_patient();
                    break;
                case 5:
                    clearConsole();
                    int num;
                    do {
                        num = askAdmin1();

                        switch (num)
                        {
                        case 1:
                            cout << " .----------------.  .----------------." << endl;
                            cout << "| .--------------. || .--------------. |" << endl;
                            cout << "| |  ________    | || |  _______     | |" << endl;
                            cout << "| | |_   ___ `.  | || | |_   __ \\    | |" << endl;
                            cout << "| |   | |   `. \\ | || |   | |__) |   | |" << endl;
                            cout << "| |   | |    | | | || |   |  __ /    | |" << endl;
                            cout << "| |  _| |___.' / | || |  _| |  \\ \\_  | |" << endl;
                            cout << "| | |________.'  | || | |____| |___| | |" << endl;
                            cout << "| |              | || |              | |" << endl;
                            cout << "| '--------------' || '--------------' |" << endl;
                            cout << " '----------------'  '----------------'  " << endl;
                            operation1(Doctorlist);
                            break;
                        case 2:
                            cout << "    .----------------.  .---------------- ." << endl;
                            cout << "   | .--------------. || .--------------. |" << endl;
                            cout << "   | |     ____     | || | ____  _____  | |" << endl;
                            cout << "   | |     ____     | || | ____  _____  | |" << endl;
                            cout << "   | |   .'    `.   | || ||_   \\|_   _| | |" << endl;
                            cout << "   | |  /  .--.  \\  | || |  |   \\ | |   | |" << endl;
                            cout << "   | |  | |    | |  | || |  | |\\ \\| |   | |" << endl;
                            cout << "   | |  \\  `- - '/  | || | _| |_\\   |_  | |" << endl;
                            cout << "   | |   `.____.'   | || ||_____|\\____| | |" << endl;
                            cout << "   | |              | || |              | |" << endl;
                            cout << "   | '--------------' || '--------------' |" << endl;
                            cout << "    '----------------'  '----------------'" << endl;

                            operation1(Oncology);
                            break;
                        case 3:
                            operation1(MRItherepy);
                            break;
                        case 4:
                            operation1(Cheemotherepy);
                            break;
                        case 5:
                            operation1(Radiotherepy);
                            break;
                        case 6:
                            cout << "Exiting to main menu.\n"; 
                            break;
                        default:
                            cout << "Enter a Valid Input";
                            break;
                        }
                    } while (num != 6);
                    break;
                case 6:
                    clearConsole();
                    int MRB_id;
                    MRB_id = AccessPatientMRB();
                    int choice2;
                    do {
                        cout << "-----Medical Record Management System-----\n";
                        cout << "  1. Add New Patient Medical Record\n";
                        cout << "  2. view Patient Medical Record\n";
                        cout << "  3. Edit Patient Medical Record\n";
                        cout << "  4. Exit\n";
                        cout << "Enter your choice: ";
                        cin >> choice2;
                        switch (choice2) {
                        case 1:
                            newMedicalRecord(MRB_id);
                            break;
                        case 2:
                            readPatientFromMRB(MRB_id);
                            break;
                        case 3:
                            editPatientFromMRB(MRB_id);
                            break;
                        case 4:
                            cout << "Exiting to main menu.\n";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                        }
                    } while (choice2 != 4);
                case 7:
                    cout << "Exiting the program.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
            } while (choice != 7);
        }
        else if (username == correctUsername2 && password == correctPassword2) {
            
            int choice;

            do {
                clearConsole();
                cout << "***User view***\n";
                cout << "----------Patient Management System----------\n\n";
                cout << "    1. View patients info\n";
                cout << "    2. Access Patient Treatment Queue Management\n";
                cout << "    3. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    int choice2;
                    do {
                        cout << "----------View patient info----------\n\n";
                        cout << "    1. View patient data\n";
                        cout << "    2. Exit\n";
                        cout << "Enter your choice: ";
                        cin >> choice2;

                        switch (choice2) {
                        case 1:
                            Patient1.show_patient();
                            break;
                        case 2:
                            cout << "Exiting to main menu\n";
                            break;
                        }
                    } while (choice2 != 2);
                    break;
                case 2:
                    
                    int num;
                    do {
                        num = askAdmin2();

                        switch (num)
                        {
                        case 1:
                            cout << " .----------------.  .----------------." << endl;
                            cout << "| .--------------. || .--------------. |" << endl;
                            cout << "| |  ________    | || |  _______     | |" << endl;
                            cout << "| | |_   ___ `.  | || | |_   __ \\    | |" << endl;
                            cout << "| |   | |   `. \\ | || |   | |__) |   | |" << endl;
                            cout << "| |   | |    | | | || |   |  __ /    | |" << endl;
                            cout << "| |  _| |___.' / | || |  _| |  \\ \\_  | |" << endl;
                            cout << "| | |________.'  | || | |____| |___| | |" << endl;
                            cout << "| |              | || |              | |" << endl;
                            cout << "| '--------------' || '--------------' |" << endl;
                            cout << " '----------------'  '----------------'  " << endl;
                            operation2(Doctorlist);
                            break;
                        case 2:
                            cout << "    .----------------.  .---------------- ." << endl;
                            cout << "   | .--------------. || .--------------. |" << endl;
                            cout << "   | |     ____     | || | ____  _____  | |" << endl;
                            cout << "   | |     ____     | || | ____  _____  | |" << endl;
                            cout << "   | |   .'    `.   | || ||_   \\|_   _| | |" << endl;
                            cout << "   | |  /  .--.  \\  | || |  |   \\ | |   | |" << endl;
                            cout << "   | |  | |    | |  | || |  | |\\ \\| |   | |" << endl;
                            cout << "   | |  \\  `- - '/  | || | _| |_\\   |_  | |" << endl;
                            cout << "   | |   `.____.'   | || ||_____|\\____| | |" << endl;
                            cout << "   | |              | || |              | |" << endl;
                            cout << "   | '--------------' || '--------------' |" << endl;
                            cout << "    '----------------'  '----------------'" << endl;

                            operation2(Oncology);
                            break;
                        case 3:
                            operation2(MRItherepy);
                            break;
                        case 4:
                            operation2(Cheemotherepy);
                            break;
                        case 5:
                            operation2(Radiotherepy);
                            break;
                        case 6:
                            cout << "Exiting to main menu.\n";
                            break;
                        default:
                            cout << "Enter a Valid Input";
                            break;
                        }
                    } while (num != 6);
                    break;
                case 3:
                    cout << "Exiting the program.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
            } while (choice != 3);
        }
        else {
            cout << "Incorrect username or password. " << attempt - 1 << " attempts remaining." << endl;
            attempt--;
        }
    }

    if (attempt == 0) {
        cout << "Too many failed login attempts. Access denied." << endl;
    }

    return 0;

}
