#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct Constituency {
    string name = "";

    Constituency* next = NULL;
    Constituency* prev = NULL;
};
struct Requests {

    string name_of_candidate = "";
    string constituency_of_candidate = "";
    string requested_party_name = "";
    bool req_accepted = false;

    Requests* next = NULL;
    Requests* prev = NULL;
};
struct Political_party {
    string name;
    string symbol;
    int symbol_id;

    string username;
    string password;

    int total_candidates = 0;
    int total_votes = 0;
    int total_candidates_won = 0;

    //did the party won the elections r not
    bool won = false;

    //requests of all the candidates tha want to register themselve against a party
    Requests* requests = NULL;

    Political_party* next = NULL;
    Political_party* prev = NULL;
};
struct Candidate {

    string name;
    string party_name;

    string dependet = "";
    int candidate_total_votes = 0;

    //basicaly names of the constituencys the candidate is gonna fight for
    string constituency;

    //did the candidate won the election or not
    bool won = false;

    //same symbol and symbol id if the candidate is dependant
    string symbol;
    int symbol_id;

    //request to send to a political party to register himsel against
    Requests request;

    Candidate* next = NULL;
    Candidate* prev = NULL;
};
struct Voter {
    string name;
    //a Voter can be registerd in only 1 constituency
    string already_registered = "false";

    string constituency_to_register_from = "";
    string CNIC;
    string password;

    string vote_casted = "false";

    Voter* next = NULL;
    Voter* prev = NULL;
};
struct EC_login {
    string name;
    int id;
    string password;
};

bool delete_LL(Political_party* pp = NULL, Constituency* Cons = NULL, Candidate* can = NULL,
    Voter* V = NULL) {


    if (pp != NULL) {
        Political_party* p_temp;
        while (pp->next != NULL) {
            p_temp = pp;
            pp = pp->next;
            delete p_temp;
        }
    }
    if (Cons != NULL) {
        Constituency* c_temp;
        while (Cons->next != NULL) {
            c_temp = Cons;
            Cons = Cons->next;
            delete c_temp;
        }
    }
    if (can != NULL) {
        Candidate* ca_temp;
        while (can->next != NULL) {
            ca_temp = can;
            can = can->next;
            delete ca_temp;
        }
    }
    if (V != NULL) {
        Voter* v_temp;
        while (V->next != NULL) {
            v_temp = V;
            V = V->next;
            delete v_temp;
        }
    }
    return 1;
}



//sorting algorithems
//quick sort
Candidate* getTail(Candidate* cur) {

    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

Candidate* partition(Candidate* head, Candidate* end,
    Candidate** newHead,
    Candidate** newEnd) {

    Candidate* pivot = end;
    Candidate* prev = NULL, * cur = head, * tail = pivot;

    while (cur != pivot) {
        if (cur->symbol < pivot->symbol) {
            if ((*newHead) == NULL)
                (*newHead) = cur;

            prev = cur;
            cur = cur->next;
        }
        else // If cur node is greater than pivot
        {
            if (prev)
                prev->next = cur->next;
            Candidate* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == NULL)
        (*newHead) = pivot;

    (*newEnd) = tail;

    return pivot;
}

Candidate* quickSortRecur(struct Candidate* head,
    struct Candidate* end)
{
    if (!head || head == end)
        return head;

    Candidate* newHead = NULL, * newEnd = NULL;

    struct Candidate* pivot
        = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        struct Candidate* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        newHead = quickSortRecur(newHead, tmp);

        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

void quickSort(struct Candidate** headRef) {
    (*headRef)
        = quickSortRecur(*headRef, getTail(*headRef));
    return;
}


Candidate* sorted = NULL;
void sortedInsert(Candidate* newnode) {
    if (sorted == NULL || sorted->symbol_id >= newnode->symbol_id) {
        newnode->next = sorted;
        sorted = newnode;
    }
    else {
        Candidate* current = sorted;
        while (current->next != NULL
            && current->next->symbol_id < newnode->symbol_id) {
            current = current->next;
        }
        newnode->next = current->next;
        current->next = newnode;
    }
}

void insertionSort(Candidate* headref, Candidate** head) {

    sorted = NULL;
    Candidate* current = headref;
    while (current != NULL) {
        Candidate* next = current->next;
        sortedInsert(current);
        current = next;
    }
    *head = sorted;
}




bool ec_login() {
    EC_login log = { "Election_Commission_of_Pakistan",192837465,"qwerty123" };//what,mynameishwat,itschi1kach1ka
    int id; string name; string pass;
    cout << "enter ID of the Election Commission: "; cin >> id;
    cout << "enter Password of the Election Commission: "; cin >> pass;
    if (id == log.id and pass == log.password) {
        system("cls");
        return true;
    }
    else {
        system("cls");
        return false;
    }
}
bool pp_login(string& a) {
    fstream A;
    string username, password;
    cout << "enter username: "; cin >> username;
    cout << "enter password: "; cin >> password;
    string na, use, pas, sy;
    int id, s_id;
    string line;

    A.open("parties.txt", ios::in);
    if (A.is_open()) {

        while (!A.eof()) {
            getline(A, line);
            std::istringstream stream(line);
            stream >> na >> sy >> id >> use >> pas;
            if (username == use and password == pas) {
                cout << "party found\n";
                A.close();
                a = na;
                return true;
            }
        }
        return false;
    }
    else {
        cout << "parties file not found\n";
    }
    return false;
}






Constituency* create_counstituency_LL() {

    ifstream A;
    A.open("constituencies.txt");

    Constituency* con = NULL;
    Constituency* ptr = con;
    Constituency* temp = NULL;
    string name;
    A >> name;
    while (A >> name) {
        temp = new Constituency;

        if (ptr == NULL) {
            temp->name = name;
            ptr = temp;
            con = ptr;
        }
        else {
            temp->name = name;
            ptr->next = temp;
            temp->prev = ptr;
            ptr = ptr->next;
        }
    }

    A.close();
    return con;
}



//gets the data from file nad store it in a link list
Candidate* create_candid_node(string line) {

    istringstream ss(line);

    Candidate* temp;

    temp = new (nothrow) Candidate;
    if (temp == NULL) {
        cerr << "error creating memory in political party link list\n";
    }

    string dep, name, p_name, symbol, c_n;

    int t_v, s_id;

    ss >> name >> dep >> p_name >> t_v >> c_n >> symbol >> s_id;

    temp->name = name;
    temp->dependet = dep;
    temp->party_name = p_name;
    temp->candidate_total_votes = t_v;
    temp->constituency = c_n;
    temp->symbol = symbol;
    temp->symbol_id = s_id;

    temp->request.constituency_of_candidate = c_n;
    temp->request.name_of_candidate = name;
    temp->request.req_accepted = false;

    return temp;
}
Candidate* create_candids_LL() {
    ifstream A;
    A.open("candidates.txt");

    int size = 0;
    string line;
    string* lines;

    while (getline(A, line)) {
        size++;
    }
    A.clear();
    A.seekg(0, ios::beg);

    lines = new string[size + 1];
    
    Candidate* can = NULL;
    Candidate* ptr = can;
    
    int it = 0;
    while (!A.eof()) { 
        getline(A, lines[it++]);
    }

    it = 1;

    Candidate* temp = NULL;

    while (it < size) {

        if (ptr == NULL) {
            temp = create_candid_node(lines[it]);
            ptr = temp;
            can = ptr;
        }
        else {
            temp = create_candid_node(lines[it]);
            ptr->next = temp;
            temp->prev = ptr;
            ptr = ptr->next;
        }
        it++;
    }
    A.close();
    return can;
}


Political_party* create_party_node(const string& line) {

    istringstream ss(line);

    Political_party* temp;
    temp = new (nothrow) Political_party;
    if (temp == NULL) {
        cerr << "error creating memory in political party link list\n";
    }


    string name, symbol, user, pass;
    int  t_c, t_v, sym_id, t_c_w;
    bool won;

    ss >> name >> symbol >> sym_id >> user >> pass >> t_c >> t_v >> t_c_w >> won;


    temp->name = name;
    temp->symbol = symbol;
    temp->symbol_id = sym_id;
    temp->username = user;
    temp->password = pass;
    temp->total_candidates = t_c;
    temp->total_votes = t_v;
    temp->total_candidates_won = t_c_w;
    temp->won = won;


    return temp;
}
Political_party* create_party_LL() {

    ifstream A;
    A.open("parties.txt");
    int size = 0;
    string line;
    string* lines;

    while (getline(A, line)) {
        size++;
    }

    lines = new (nothrow) string[size + 1];
    if (lines == NULL) {
        cerr << "lines memory allocation failed.\n";
    }

    Political_party* can = NULL;
    Political_party* ptr = can;

    A.clear();
    A.seekg(0, ios::beg);
    cin.ignore();

    int it = 0;
    while (!A.eof()) {
        getline(A, lines[it++]);
    }

    it = 0;

    Political_party* temp = NULL;
    while (it < size) {

        if (ptr == NULL) {
            temp = create_party_node(lines[it]);
            ptr = temp;
            can = ptr;
        }
        else {
            temp = create_party_node(lines[it]);
            ptr->next = temp;
            temp->prev = ptr;
            ptr = ptr->next;
        }
        it++;
    }
    A.close();
    return can;

}


Voter* create_voter_node(const string& line) {
    istringstream ss(line);
    string name, registered, constituency, password, vote_casted, cnic;
    ss >> name >> registered >> constituency >> cnic >> password >> vote_casted;

    Voter* temp = NULL;
    temp = new Voter;

    temp->name = name;
    temp->password = password;
    temp->already_registered = registered;
    temp->CNIC = cnic;
    temp->constituency_to_register_from = constituency;
    temp->vote_casted = vote_casted;
    return temp;

}
Voter* create_voter_LL() {
    ifstream A;
    A.open("voters.txt");
    int size = 0;
    string line;
    string* lines;

    while (getline(A, line)) {
        size++;
    }

    lines = new (nothrow) string[size + 1];
    if (lines == NULL) {
        cerr << "lines memory allocation failed.\n";
    }

    Voter* can = NULL;
    Voter* ptr = can;

    A.clear();
    A.seekg(0, ios::beg);
    //cin.ignore();

    int it = 0;
    while (getline(A, lines[it++])) {
        if (A.eof()) {
            break;
        }
    }

    it = 1;
    Voter* temp = NULL;
    while (it < size) {

        if (ptr == NULL) {
            temp = create_voter_node(lines[it]);
            ptr = temp;
            can = ptr;
        }
        else {
            temp = create_voter_node(lines[it]);
            ptr->next = temp;
            temp->prev = ptr;
            ptr = ptr->next;
        }
        it++;
    }
    A.close();
    return can;

}


int countDistinct(string *arr, int n)
{
    int res = 1;

    // Pick all elements one by one
    for (int i = 1; i < n; i++) {
        int j = 0;
        for (j = 0; j < i; j++)
            if (arr[i] == arr[j])
                break;

        // If not printed earlier, then print it
        if (i == j)
            res++;
    }
    return res;
}
bool set_to_null(string *arr,int n){
    for (int i = 0; i < n; i++) {
        arr[i] = '\0';
    }
    return 0;
}



bool update_cadidates_data(Candidate* candidate) {
    ofstream A;

    A.open("candidates.txt", ios::trunc);
    A << "NAME\t\tDEPENDENT\tPARTY_NAME\tTOTAL_VOTES\tCONSTITUENCY\tSYMBOL\t\tSYMBOL_ID" << endl;
    while (candidate != NULL) {
        A << candidate->name << "\t\t" << candidate->dependet << "\t\t" << candidate->party_name
            << "\t\t" << candidate->candidate_total_votes << "\t\t" << candidate->constituency
            << "\t\t" << candidate->symbol << "\t\t" << candidate->symbol_id << endl;
        candidate = candidate->next;
    }
    A.close();
    delete_LL(NULL, NULL, candidate);

    return 1;
}
void update_cadidates_data_by_requests(Requests** req) {
    
    Requests* req_ptr = *req;
    Candidate* can_ptr = create_candids_LL();
    Candidate* can_ptr2 = can_ptr;

    ofstream A;
    A.open("candidates.txt",ios::trunc);
    
    while (req_ptr != NULL) {
        while (can_ptr2 != NULL) {
            if (req_ptr->name_of_candidate == can_ptr2->name and req_ptr->req_accepted == true) {
                can_ptr2->dependet = "true";
                can_ptr2->party_name = req_ptr->requested_party_name;
            }
            can_ptr2 = can_ptr2->next;
        }
        can_ptr2 = can_ptr;
        req_ptr = req_ptr->next;
    }
    can_ptr2 = can_ptr;
    req_ptr = *req;

    Political_party* party = create_party_LL();
    Political_party* party_ptr = party;

    while (can_ptr2 != NULL) {
        while (party_ptr!=NULL) {
            if (can_ptr2->party_name == party_ptr->name) {
                can_ptr2->symbol = party_ptr->symbol;
                can_ptr2->symbol_id= party_ptr->symbol_id;   
            }
            party_ptr = party_ptr->next;
        }
        party_ptr = party;
        can_ptr2 = can_ptr2->next;
    }
    
    int total_Candidates_per_party = 0;

    party_ptr = party;
    can_ptr2 = can_ptr;
    string* t_candidate = NULL;
    int s = 0;
    while(can_ptr2 != NULL) {
        s++;
        can_ptr2 = can_ptr2->next;
    }

    can_ptr2 = can_ptr;
    t_candidate = new string[s+1];
    int i = 0;
    //set_to_zero(t_candidate,s);
    party_ptr = party_ptr->next;


    while (party_ptr != NULL) {
        while (can_ptr2 != NULL) {
            if (can_ptr2->party_name == party_ptr->name) {
                t_candidate[i] = can_ptr2->name;
                i++;
            }
            can_ptr2 = can_ptr2->next;
        }
        party_ptr->total_candidates = countDistinct(t_candidate, s) - 1;
        set_to_null(t_candidate,s);
        can_ptr2 = can_ptr;
        party_ptr = party_ptr->next;
    }

    can_ptr2 = can_ptr;
    party_ptr = party;


    A << "NAME\t\tDEPENDENT\tPARTY_NAME\tTOTAL_VOTES\tCONSTITUENCY\tSYMBOL\t\tSYMBOL_ID" << endl;
    while (can_ptr2 != NULL) {
        A << can_ptr2->name <<"\t\t" << can_ptr2->dependet << "\t\t" << can_ptr2->party_name
            << "\t\t" << can_ptr2->candidate_total_votes << "\t\t" << can_ptr2->constituency
            << "\t\t" << can_ptr2->symbol << "\t\t" << can_ptr2->symbol_id << endl;
        can_ptr2 = can_ptr2->next;
    }


    A.close();
    A.open("parties.txt", ios::trunc);
    A << "NAME\tSYMBOL\tSYM_ID\tUSER\tPASS\tT_CAND\tT_V\tT_C_WON\tWON\n";
    party_ptr = party_ptr->next;

    while (party_ptr != NULL) {
        if(party_ptr->won==false)
        A << party_ptr->name << "\t" << party_ptr->symbol << "\t" << party_ptr->symbol_id << "\t"
            << party_ptr->username << "\t" << party_ptr->password << "\t" << party_ptr->total_candidates << "\t"
            << party_ptr->total_votes << "\t" << party_ptr->total_candidates_won << "\t" << "false" << endl;
        else
            A << party_ptr->name << "\t" << party_ptr->symbol << "\t" << party_ptr->symbol_id << "\t"
            << party_ptr->username << "\t" << party_ptr->password << "\t" << party_ptr->total_candidates << "\t"
            << party_ptr->total_votes << "\t" << party_ptr->total_candidates_won << "\t" << "true" << endl;
        party_ptr = party_ptr->next;
    }
    A.close();

    delete_LL(party, NULL, can_ptr);
    

}
bool update_voters_data(Voter* voter) {
    ofstream A;

    A.open("voters.txt", ios::trunc);
    A << "NAME\tREGISTERED\tCONSTITUENCY\tCNIC\t\tPASSWORD\tVOTE_CASTED" << endl;
    while (voter != NULL) {

        A << voter->name << "\t" << voter->already_registered << "\t\t" << voter->constituency_to_register_from << "\t\t" << voter->CNIC
            << "\t\t" << voter->password << "\t\t" << voter->vote_casted << endl;
        voter = voter->next;
    }
    A.close();
    delete_LL(NULL, NULL, NULL, voter);

    return 1;


    
    return 0;
}

void update_parties() {
    Candidate* can = create_candids_LL();
    Candidate* can_ptr = can;
    Candidate* max_can_ptr = can;
    Political_party* party = create_party_LL();
    Political_party* party_ptr = party;
    Political_party* max_pp_ptr= party;


    ofstream A;
    can = can->next;
    while (can_ptr != NULL) {
        if (max_can_ptr->candidate_total_votes <= can_ptr->candidate_total_votes) {
            max_can_ptr = can_ptr;
        }
        can_ptr = can_ptr->next;
    }

    can_ptr = can;
    while (can_ptr != NULL) {
        if (max_can_ptr == can_ptr) {
            can_ptr->won = true;
        }
        else if (max_can_ptr != can_ptr) {
            can_ptr->won = false;
        }
        can_ptr = can_ptr->next;
    }


    can_ptr = can;

    while (can_ptr != NULL) {
        while (party_ptr != NULL) {
            if (party_ptr->name == can_ptr->party_name) {
                if (can_ptr->won == true) {
                    party_ptr->total_candidates_won++;
                }
                party_ptr->total_votes += can_ptr->candidate_total_votes;
            }
            party_ptr = party_ptr->next;
        }
        party_ptr = party;
        can_ptr = can_ptr->next;
    }

    party_ptr = party;
    can_ptr = can;

    party_ptr = party;

    while (party_ptr != NULL) {
        if (max_pp_ptr->total_candidates_won <= party_ptr->total_candidates_won) {
            max_pp_ptr = party_ptr;
        }
        party_ptr = party_ptr->next;
    }

    party_ptr = party;

    while (party_ptr != NULL) {
        if (max_pp_ptr == party_ptr) {
            party_ptr->won = true;
        }
        else if (max_pp_ptr != party_ptr) {
            party_ptr->won = false;
        }
        party_ptr = party_ptr->next;
    }

    party_ptr = party;


    A.open("parties.txt", ios::trunc);
    
    A << "NAME\tSYMBOL\tSYM_ID\tUSER\tPASS\tT_CAND\tT_V\tT_C_W\tWON\n";
    party_ptr = party_ptr->next;
    while (party_ptr != NULL) {
        if (party_ptr->won == false) {
            A << party_ptr->name << "\t" << party_ptr->symbol << "\t" << party_ptr->symbol_id << "\t"
                << party_ptr->username << "\t" << party_ptr->password << "\t" << party_ptr->total_candidates << "\t"
                << party_ptr->total_votes << "\t" << party_ptr->total_candidates_won << "\t" << "false" << endl;
        }
        if (party_ptr->won == true) {
            A << party_ptr->name << "\t" << party_ptr->symbol << "\t" << party_ptr->symbol_id << "\t"
                << party_ptr->username << "\t" << party_ptr->password << "\t" << party_ptr->total_candidates << "\t"
                << party_ptr->total_votes << "\t" << party_ptr->total_candidates_won << "\t" << "true" << endl;
        }
        party_ptr = party_ptr->next;
    }


    delete_LL(party, NULL, can);
    A.close();


}



bool voter_login(bool& flag, int& total_vote_casted, int& total_voters,
    bool& voting_finnished, bool& won) {
    
    ifstream A;
    string cnic1;
    string password1;
    int t = 0;
    bool found_flag = false;
    Voter* vot = create_voter_LL();
    Voter* vot_ptr = vot;

    //vot_ptr = vot_ptr->next;
    while (vot_ptr != NULL) {
        t++;
        vot_ptr = vot_ptr->next;
    }
    total_voters = t;
    cout << "\ntotal voter are: " << total_voters << endl;
    vot_ptr = vot;
    
    cout << "enter cnicn: "; cin >> cnic1;
    cin.ignore();
    cout << "enter password: "; cin >> password1;
    cin.ignore();

    while (vot_ptr != NULL) {

        if (cnic1 == vot_ptr->CNIC and vot_ptr->password == password1) {
            system("cls");
            cout << "voter found\n\n\n";
            found_flag = true;
            break;
        }
        vot_ptr = vot_ptr->next;
    }

    if (found_flag) {
        if (vot_ptr->vote_casted == "false") {
            cout << "0. To LOGOUT.\n";
            cout << "1. show all candidates wth symbols.\n";
            cout << "2. cast vote.\n";
            int choice = 0;
            cout << "choose: "; cin >> choice;
            while (choice < 0 or choice >2) { cout << "wrong choice, choose again: "; cin >> choice; }

            int chooose_again = 0;
            Candidate* ptr = create_candids_LL();
            Candidate* ptr2 = ptr;
            int i = 1;
            bool already_shown = false;
            system("cls");
            bool shown = false;
            cout << "S.NO\tNAME\t\tCONSTITUENCY\tPARTY NAME\t\tSYMBOL\t\tSYMBOL ID\n\n";
            shown = false;
            while (1) {
                ptr2 = ptr;
                if (choice == 1) {
                    i = 1;
                    already_shown = true;
                    while (ptr2 != NULL) {
                        if (!shown) {
                            cout << i++ << ".  \t" << ptr2->name << "\t\t" << ptr2->constituency << "\t\t" << ptr2->party_name << "\t\t\t" << ptr2->symbol << "\t\t" << ptr2->symbol_id << endl;
                        }
                        ptr2 = ptr2->next;
                    }
                    cout << "\n\n0. To go back.\n";
                    cout << "1. To sort by symbol name.\n";
                    cout << "2.to sort by symbol id.\n";
                    cout << "choose: "; cin >> chooose_again;

                    while (chooose_again < 0 or chooose_again>2) { cout << "wrong choice, choose again: "; cin >> chooose_again; }

                    ptr2 = ptr;
                    system("cls");
                    if (chooose_again == 1) {
                        system("cls");
                        quickSort(&ptr);
                        ptr2 = ptr;
                        i = 1;
                        cout << "S.NO\tNAME\t\tCONSTITUENCY\tPARTY NAME\t\tSYMBOL\t\tSYMBOL ID\n\n";
                        shown = true;
                        while (ptr2 != NULL) {
                            cout << i++ << ".  \t" << ptr2->name << "\t\t" << ptr2->constituency << "\t\t" << ptr2->party_name << "\t\t\t" << ptr2->symbol << "\t\t" << ptr2->symbol_id  << endl;
                            ptr2 = ptr2->next;
                        }
                    }
                    else if (chooose_again == 2) {
                        shown = true;
                        system("cls");
                        insertionSort(ptr, &ptr);
                        ptr2 = ptr; 
                        i = 1;
                        cout << "S.NO\tNAME\t\tCONSTITUENCY\tPARTY NAME\t\tSYMBOL\t\tSYMBOL ID\n\n"; 
                        while (ptr2 != NULL) {
                            cout << i++ << ".  \t" << ptr2->name << "\t\t" << ptr2->constituency << "\t\t" << ptr2->party_name << "\t\t\t" << ptr2->symbol << "\t\t" << ptr2->symbol_id<<  endl;
                            ptr2 = ptr2->next;
                        }
                    }
                    else if (chooose_again == 0) {
                        system("cls");
                        cout << "0. To go back.\n";
                        cout << "1. show all candidates wth symbols.\n";
                        cout << "2. cast vote.\n";
                        cout << "choose: "; cin >> choice;
                        shown = false;
                        while (choice < 0 or choice >2) { cout << "wrong choice, choose again: "; cin >> choice; }
                        ptr = ptr2;
                        system("cls");
                        if (choice == 0) { break; }
                        cout << "S.NO\tNAME\t\tPARTY NAME\t\tSYMBOL\t\tSYMBOL ID\n\n";
                    }
                }
                else if (choice == 2) {
                    if (flag == true) {
                        string symbol_name;
                        system("cls");
                        cout << "enter the symbol name of the candidate tha you want to cast your vote for: "; cin >> symbol_name;
                        bool candid_found = false;
                        while (ptr2 != NULL) {
                            if (ptr2->symbol == symbol_name and ptr2->constituency == vot_ptr->constituency_to_register_from) {
                                candid_found = true;
                                break;
                            }
                            ptr2 = ptr2->next;
                        }
                        if (!candid_found) {
                            cout << "a candidade by that symbol doesnt exist or you doesnt belong to that constituency, plz check again.\n";
                            cout << "exiting...\n";
                            break;
                        }
                        else if (candid_found) {
                            cout << "vote successfully casted\n";
                            ptr2->candidate_total_votes++;
                            vot_ptr->vote_casted = "true";

                            update_cadidates_data(ptr);
                            update_voters_data(vot);
                            total_vote_casted++;
                            break;
                        }
                    }
                    else {
                        cout << "the voting hasn't started yet\n";
                        break;
                    }
                }
                else if (choice == 0) { system("cls");  break; }
            }
        }
        else {
            cout << "the voter has already casted his vote\n";
            delete_LL(NULL, NULL, NULL, vot_ptr);
        }
    }
    else if (!found_flag) {
        cout << "voter not found.\n";
    }
    
    if (total_vote_casted == total_voters) {
        voting_finnished = true;
        flag = false;
        won = true;
        cout << "Voting finneshed\n";
    }


    
    return false;
}




