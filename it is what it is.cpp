#include "Source.cpp"

class Election_Commission {
    Constituency* constituency = NULL;
    Political_party* political_party = NULL;
    Candidate* candidate = NULL;
    Voter* voter = NULL;



public:
    int total_vote_casted= 0;
    Requests* requests = NULL;
    Requests* requests_ptr = NULL;
    bool voting_started_flag = false;
    int total_voters = 0;
    bool voting_finnished = false;
    bool won = false;

    Election_Commission() {}
    //done
    bool create_or_update_constituency() { 
        if (!voting_started_flag) {
            ifstream A;
            ofstream B;
            A.open("constituencies.txt");
            if (A.is_open()) {
                cout << "file opened\n";
                int choice;
                cout << "1. Create constituency.\n";
                cout << "2. Update constituency.\n";
                cin >> choice;
                while (choice > 2 or choice < 1) { cerr << "wrong input, try agian: "; cin >> choice; }
                string name;
                if (choice == 1) {
                    bool flag = false;
                    do {
                        flag = false;
                        cout << "enter the name of the constituency: "; cin >> name;
                        string n;

                        while (A >> n) {
                            if (n == name) {
                                flag = true;
                                cout << "That name already exists\n";
                            }
                        }
                        A.clear();
                        A.seekg(0, ios::beg);

                    } while (flag == true);
                    A.close();
                    B.open("constituencies.txt", ios::app);
                    B << name << endl;
                    B.close();
                    if (A.is_open() or B.is_open()) {
                        A.close(); B.close();
                    }
                }
                else if (choice == 2) {
                    bool flag = false;
                    A.close();
                    B.close();
                    while (true) {
                        string old_name;
                        cout << "enter the name of the constituency to update: "; cin >> old_name;

                        flag = false;

                        A.open("constituencies.txt");
                        string name;
                        string* names = NULL;
                        int size = 0;
                        int index = 0;
                        int i = 0;

                        while (A >> name) {
                            if (name == old_name) {
                                // cout << flag << endl;
                                flag = true;//name found
                            }
                            size++;
                        }
                        bool flag2;
                        names = new string[size];
                        if (flag == true) {//found

                            while (1) {
                                flag2 = false;
                                string new_name;
                                cout << "enter the new name for the constituency: "; cin >> new_name;

                                i = 0;
                                A.clear();
                                A.seekg(0, ios::beg);

                                //storing names from file in an array
                                while (A >> names[i]) {
                                    i++;
                                }
                                index = 0;
                                for (int j = 0; j < size; j++) {
                                    if (names[j] == new_name) {
                                        flag2 = false;
                                        break;
                                    }
                                    else {
                                        flag2 = true;
                                    }
                                }
                                if (flag2 == true) {
                                    A.close();
                                    B.open("constituencies.txt");
                                    i = 0;
                                    while (i < size) {
                                        if (names[i] == old_name) {
                                            names[i] = new_name;
                                        }
                                        B << names[i] << endl;
                                        i++;
                                    }
                                    B.close();
                                    break;
                                }
                                else if (flag2 == false) {
                                    cout << "that name is already taken.\n";
                                    A.open("constituencies.txt");
                                }
                            }
                            delete[]names;
                            break;
                        }
                        else if (flag == false) {
                            cout << "constituency not found\n";
                            delete[]names;
                            break;
                        }

                    }
                    //  cout << "break\n";
                }
            }
            else {
                cout << "file not found\n";
                return 0;
            }
            A.close();
            B.close();
        }
        else {
        cout << "you cannot create or update a constituency, the voting has started.\n";
        }
        return 0;
    }

    bool create_political_party() {
        if (!voting_started_flag or voting_finnished==true) {
            ifstream A;
            ofstream B;

            political_party = new Political_party;
            cout << "enter name of the political party(no spaces): "; cin >> political_party->name;
            cout << "enter symbol name(no spaces): "; cin >> political_party->symbol;
            cout << "enter symbol ID: (integer): "; cin >> political_party->symbol_id;
            cout << "enter username(no spaces): "; cin >> political_party->username;
            cout << "enter password(no spaces): "; cin >> political_party->password;

            A.open("parties.txt");
            string* lines = NULL;
            string name, symb, user, pass;
            int total_parties = 0;
            int t_c ,t_v ,t_t_c_w , id = 0;
            bool t_w;
            bool flag_for_party_checking = false;

            if (A.is_open()) {

                flag_for_party_checking = false;
                while (getline(A, name)) {
                    total_parties++;
                }

                lines = new string[total_parties + 1];
                int k = 0;
                A.clear();
                A.seekg(0, ios::beg);

                while (getline(A, lines[k])) { 
                    //cout << lines[k] << endl;
                    k++; }
                k = 0;

                while (k <= total_parties) {

                    istringstream ss(lines[k]);
                    ss >> name >> symb >> id >> user >> pass >> t_c >> t_v >> t_t_c_w >> t_w;

                    if (name == political_party->name or symb == political_party->symbol or id == political_party->symbol_id
                        or user == political_party->username or pass == political_party->password) {
                        flag_for_party_checking = true;
                        if (name == political_party->name) {
                            cout << "a party with the same name already exists, party registration failed....\n";
                            break;
                        }
                        else if (symb == political_party->symbol) {
                            cout << "a party with the same symbol already exists, party registration failed....\n";
                            break;
                        }
                        else if (id == political_party->symbol_id) {
                            cout << "a party with the same symbol id already exists, party registration failed....\n";
                            break;
                        }
                        else if (user == political_party->username) {
                            cout << "a party with the same username already exists, party registration failed....\n";
                            break;
                        }
                        else if (pass == political_party->password) {
                            cout << "a party with the same password already exists, party registration failed....\n";
                            break;
                        }
                    }
                    k++;
                }
                if (flag_for_party_checking == true) {//if party alrerady exists
                    A.close();
                    delete political_party;
                    delete[]lines;
                    return 0;
                }
                else if (flag_for_party_checking == false) {
                    A.close();
                    B.open("parties.txt", ios::app);
                    if (B.is_open()) {
                        cout << "file opened\n";
                    }
                    B << political_party->name << "\t" << political_party->symbol << "\t" << political_party->symbol_id << "\t"
                        << political_party->username << "\t" << political_party->password << "\t" << political_party->total_candidates << "\t"
                        << political_party->total_votes << "\t" << political_party->total_candidates_won << "\t" << "false" << endl;
                    B.close();
                    delete political_party;
                }
            }
            else {
                cerr << "failed to open the parties.txt file\n";
            }
            delete[]lines;
            A.close();
            B.close();
        }
        else {
            cout << "you cannot create a political party, the voting has started.\n";
        }
        return 0;
    }

    bool party_login(string& party_name) { 
                
        int choice = -1;
        while (1) {


            cout << "\n\n0. to LOGOUT: \n";
            cout << "1. to show requests: \n";
            cout << "2. to show resuslts: \n";
            cout << "choose: \n"; cin >> choice;

            while (choice > 2 or choice < 0) {
                cout << "wrong option, try agian: "; cin >> choice;
            }
            Requests* ptr = requests;


            if (choice == 1) {
                system("cls");
                if (requests == NULL) {
                    cout << "no requests...\n";
                }
                else {
                    int i = 1;
                    int j = 0;
                    ptr = requests;
                    bool reqs_flag = false;

                    Candidate* can_ptr = create_candids_LL();

                    while (ptr != NULL) {
                        if (ptr->requested_party_name == party_name and ptr->req_accepted == false) {
                            if (j == 0) {
                                cout << "S.No\t\tNAME OF CANDIDATE\tCONSTITUENCY OF CANDIDATE\n";
                                j++;
                            }
                            cout << i << ".\t\t" << ptr->name_of_candidate << "\t\t\t" << ptr->constituency_of_candidate << endl;
                            reqs_flag = true;
                            i++;
                        }
                        ptr = ptr->next;
                        cout << endl;
                    }
                    ptr = requests;
                    if (reqs_flag) {
                        string req_to_accept;
                        cout << "enter the name of the candidate to accept his request or press 0 to exit: \n"; cin >> req_to_accept;

                        if (req_to_accept == "0") {}//do nothing
                        else {
                            reqs_flag = false;
                            i = 0;
                            ptr = requests;
                            while (ptr != NULL) {
                                if (ptr->requested_party_name == party_name and req_to_accept == ptr->name_of_candidate) {
                                    ptr->req_accepted = true;
                                    reqs_flag = true;
                                }
                                ptr = ptr->next;
                            }
                        }
                        if (reqs_flag and req_to_accept != "0") {
                            cout << "request accepted...\n";
                            update_cadidates_data_by_requests(&requests);
                        }
                        else if (req_to_accept != "0") {
                            cout << "wrong name entered...\n";
                        }
                    }
                    else {
                        cout << "no requests...\n";
                    }

                    delete_LL(NULL, NULL, can_ptr, NULL);
                }
            }
            else if (choice == 2) {
                system("cls");
                if (won == false and voting_finnished!=true) {
                    cout << "the voting has not completed or the election has'nt started yet.\n";
                }
                else {
                    system("cls");
                    cout << "if nothings showing up, please press any button to continue\n";
                    update_parties();
                    bool won_flag = false;
                    Political_party* party_ptr = create_party_LL();
                    Political_party* ptr = party_ptr;
                    Political_party* max_ptr = party_ptr;

                    while (ptr != NULL) {
                        if (max_ptr->total_candidates_won <= ptr->total_candidates_won) {
                            max_ptr = ptr;
                        }
                        ptr = ptr->next;
                    }
                    ptr = party_ptr;
                    
                    while (ptr != NULL) {
                        if (max_ptr == ptr) {
                            ptr->won = true;
                        }
                        else if (max_ptr != ptr) {
                            ptr->won = false;
                        }
                        
                        if (ptr->won == true and ptr->name == party_name) {
                            won_flag = true;
                        }
                        ptr = ptr->next;
                    }

                    if (won_flag) {
                        cout << "Congratulations, You'r party won the elections.\n";
                    }
                    else {
                        cout << "sorry, you lost the elections.\n";
                    }
                    delete_LL(party_ptr);
                }
            }
            else if (choice == 0) {
                system("cls");
                break;
            }
        }
        
        return 0;
    }

    bool send_req_to_party() {


        constituency = create_counstituency_LL();
        Constituency* ptr_consti = constituency;
        
        political_party = create_party_LL();
        Political_party* ptr_party = political_party;
        
        candidate = create_candids_LL();
        Candidate* ptr_cand = candidate;
        

        string from_name;
        string to_name;

        cout << "enter candidate's name: "; cin >> from_name;
        cout << "enter party's name(to register under): "; cin >> to_name;

        bool flag1 = false;
        bool flag2 = false;
        while (ptr_cand != NULL) {

            if (ptr_cand->name == from_name) {
                flag1 = true;
                break;
            }
            ptr_cand = ptr_cand->next;
        }

        while (ptr_party != NULL) {

            if (ptr_party->name == to_name) {
                flag2 = true;
                break;
            }
            ptr_party = ptr_party->next;
        }

        if (flag1 == false) {
            cout << "A candidate by that name doesnt exist.\n";
            cout << "Request failed.\n";
        }
        else if (flag2 == false) {
            cout << "A Party by that name doesnt exist.\n";
            cout << "Request failed.\n";
        }

        requests_ptr = requests;
        if (requests != NULL) {
            while (requests_ptr->next != NULL) {
                requests_ptr = requests_ptr->next;
            }
        }

        
        if (flag1 and flag2) {
            if (ptr_cand->dependet == "false") {
                if (requests == NULL) {
                    requests = new Requests;

                    requests->name_of_candidate = from_name;
                    requests->constituency_of_candidate = ptr_cand->constituency;
                    requests->requested_party_name = ptr_party->name;
                    requests->req_accepted = false;

                    requests_ptr = requests;
                }
                else {

                    requests_ptr->next = new Requests;
                    requests_ptr = requests_ptr->next;

                    requests_ptr->name_of_candidate = from_name;
                    requests_ptr->constituency_of_candidate = ptr_cand->constituency;
                    requests_ptr->requested_party_name = ptr_party->name;
                    requests_ptr->req_accepted = false;
                }
                cout << "request made\n";
            }
            else {
                cout << "the candidate is already registered under a party,request failed...\n";
            }
        }
        delete_LL(political_party, constituency, candidate, voter);
        if (1) {
            requests_ptr = requests;
            while (requests_ptr != NULL) {
                requests_ptr = requests_ptr->next;
            }
        }
        return 1;


        return 0;
    }

    bool start_voting() {
        if (!voting_finnished) {
            if (!voting_started_flag) {
                voting_started_flag = true;
                if (voting_started_flag) {
                    system("cls");
                    cout << "the voting has started...\n";
                    total_vote_casted = 0;
                }
            }
            else {
                cout << "the voting is already started.\n";
            }
        }
        else if (voting_finnished) {
            cout << "the voting has finneshed, see the results section\n";
        }
        return 1;
    }

    bool register_candidate() {
        string can_name, can_symbol, can_constituency;
        int can_sym_id;

        cout << "enter candidate name: "; cin >> can_name;
        cout << "enter symbol id: "; cin >> can_sym_id;
        cout << "enter  symbol name: "; cin >> can_symbol;
        cout << "enter candidate constituency: "; cin >> can_constituency;

        Candidate* can_ptr = create_candids_LL();
        Candidate* ptr = can_ptr;
        
        Constituency* cons_ptr = create_counstituency_LL();
        Constituency* ptr2 = cons_ptr;
        ofstream A;

        bool is_unique = true;
        bool found= false;

        while (ptr != NULL) {
            if (ptr->symbol_id== can_sym_id) {
                cout << "that symbol id is already taken, failed to register the candidate.\nExiting...\n";
                is_unique = false;
                break;
            }
            if (ptr->symbol == can_symbol) {
                cout << "that symbol is already taken, failed to register the candidate.\nExiting...\n";
                is_unique = false;
                break;
            }
            if (ptr->name == can_name) {
                cout << "that name is already taken, failed to register the candidate.\nExiting...\n";
                is_unique = false;
                break;
            }
            ptr = ptr->next;
        }
        
        ptr = can_ptr;
        while (ptr2 != NULL) {
            if (ptr2->name == can_constituency) {
                found = true;
                break;
            }
            ptr2 = ptr2->next;
        }
        if (!found) {
            cout << "given constituency not found\n";
            cout << "Exiting...\n";
        }

        if (is_unique and found) {
            A.open("candidates.txt", ios::app);
            A << can_name << "\t\t" << "false" << "\t\t" << "none" << "\t\t" << 0 << "\t\t" << can_constituency << "\t\t" <<
                can_symbol << "\t\t" << can_sym_id << endl;
            cout << "candidate registered...\n";
            A.close();
        }

        delete_LL(NULL, cons_ptr, can_ptr);
        return 0;
    }

    bool register_voter() {
        string voter_name, voter_registered, voter_constituency, voter_cnic, voter_pass;

        cout << "enter voter name: "; cin >> voter_name;
        cout << "enter voter constituency: "; cin >> voter_constituency;
        cout << "enter  voter CNIC: "; cin >> voter_cnic;
        cout << "enter voter password : "; cin >> voter_pass;

        Voter* vot_ptr = create_voter_LL();
        Voter* ptr = vot_ptr;

        Constituency* cons_ptr = create_counstituency_LL();
        Constituency* ptr2 = cons_ptr;
        ofstream A;

        bool is_unique = true;
        bool found = false;

        while (ptr != NULL) {
            if (ptr->CNIC == voter_cnic) {
                cout << "that CNIC is already taken, failed to register the Voter.\nExiting...\n";
                is_unique = false;
                break;
            }
            if (ptr->name == voter_name) {
                cout << "that name is already taken, failed to register the voter.\nExiting...\n";
                is_unique = false;
                break;
            }
            if (ptr->password== voter_pass) {
                cout << "that password is too weak, failed to register the candidate.\nExiting...\n";
                is_unique = false;
                break;
            }
            ptr = ptr->next;
        }

        ptr = vot_ptr;

        while (ptr2 != NULL) {
            if (ptr2->name == voter_constituency) {
                found = true;
                break;
            }
            ptr2 = ptr2->next;
        }
        if (!found) {
            cout << "given constituency not found\n";
            cout << "Exiting...\n";
        }

        if (is_unique and found) {
            A.open("voters.txt", ios::app);
            A << voter_name << "\t" << "true" << "\t\t" << voter_constituency << "\t" << voter_cnic << "\t" << voter_pass << "\t\t" << "false" << endl;
            
            cout << "Voter registered...\n";
            A.close();
        }

        delete_LL(NULL, cons_ptr, NULL, vot_ptr);



        return 0;
    }
    
    bool results(int choice) { 
        ofstream A;

        if (voting_finnished == true){
            
            political_party = create_party_LL();
            candidate = create_candids_LL();

            Candidate* can_ptr = candidate;
            Political_party* pp_ptr = political_party;
            
            Candidate* max_can_ptr = candidate;
            Political_party* max_pp_ptr = political_party;

            while (can_ptr != NULL) {
                if (max_can_ptr->candidate_total_votes <= can_ptr->candidate_total_votes) {
                    max_can_ptr = can_ptr;
                }
                can_ptr = can_ptr->next;
            }

            can_ptr = candidate;
            while (can_ptr != NULL) {
                if (max_can_ptr == can_ptr) {
                    can_ptr->won = true;
                }
                else if(max_can_ptr != can_ptr) {
                    can_ptr->won = false;
                }
                can_ptr = can_ptr->next;
            }
            
            A.open("candidates.txt", ios::trunc);
            can_ptr = candidate;
            can_ptr = can_ptr->next;
            
            A << "NAME\t\tDEPENDENT\tPARTY_NAME\tTOTAL_VOTES\tCONSTITUENCY\tSYMBOL\t\tSYMBOL_ID" << endl;
            
            can_ptr = candidate;
            while (can_ptr != NULL) {
                

                A << can_ptr->name << "\t\t" << can_ptr->dependet << "\t\t" << can_ptr->party_name
                    << "\t\t" << can_ptr->candidate_total_votes << "\t\t" << can_ptr->constituency
                    << "\t\t" << can_ptr->symbol << "\t\t" << can_ptr->symbol_id << endl;

                can_ptr = can_ptr->next;
            }
            A.close();

            A.open("parties.txt", ios::trunc);
            can_ptr = candidate;

            while (can_ptr != NULL) {
                while (pp_ptr!=NULL) {
                    if (can_ptr->won == true and can_ptr->party_name==pp_ptr->name) {
                        pp_ptr->total_votes++;
                        pp_ptr->total_candidates_won++;
                    }
                    pp_ptr = pp_ptr->next;
                }
                pp_ptr = political_party;
                can_ptr = can_ptr->next;
            }

            pp_ptr = political_party;
            
            while (pp_ptr != NULL) {
                if (max_pp_ptr->total_candidates_won <= pp_ptr->total_candidates_won) {
                    max_pp_ptr = pp_ptr;
                }
                pp_ptr = pp_ptr->next;
            }
            
            pp_ptr = political_party;

            while (pp_ptr != NULL) {
                if (max_pp_ptr == pp_ptr) {
                    pp_ptr->won = true;
                    won = true;
                }
                else if (max_pp_ptr != pp_ptr) {
                    pp_ptr->won = false;
                }
                pp_ptr = pp_ptr->next;
            }

            pp_ptr = political_party;
            pp_ptr = pp_ptr->next;
            A << "NAME\tSYMBOL\tSYM_ID\tUSER\tPASS\tT_CAND\tT_V\tT_C_WON\tWON\n";
            while (pp_ptr != NULL) {
                if (pp_ptr->won == false) {
                    A << pp_ptr->name << "\t" << pp_ptr->symbol << "\t" << pp_ptr->symbol_id << "\t" << pp_ptr->username
                        << "\t" << pp_ptr->password << "\t" << pp_ptr->total_candidates << "\t" << pp_ptr->total_votes
                        << "\t" << pp_ptr->total_candidates_won << "\t" << "false" << endl;
                }
                if (pp_ptr->won == true) {
                    A << pp_ptr->name << "\t" << pp_ptr->symbol << "\t" << pp_ptr->symbol_id << "\t" << pp_ptr->username
                        << "\t" << pp_ptr->password << "\t" << pp_ptr->total_candidates << "\t" << pp_ptr->total_votes
                        << "\t" << pp_ptr->total_candidates_won << "\t" << "true" << endl;
                }
                pp_ptr = pp_ptr->next;
            }

            A.close();



            can_ptr = candidate;
            pp_ptr = political_party;
            int i = 1;
            if (choice == 1) {
                cout << "S.NO \tCandidate name\t\tConstunecy\t\tParty_name\t\tWon By\n";
                while (can_ptr != NULL) {
                    if (1) {
                        cout << i++ <<"\t" << can_ptr->name <<"\t\t\t" << can_ptr->constituency << "\t\t\t" << can_ptr->party_name << "\t\t\t" << can_ptr->candidate_total_votes << " Votes." << endl;
                    
                    }
                    can_ptr = can_ptr->next;
                }
            }
            else if (choice == 2) {
                string name;
                cout << "enter the name of the constituency\n"; cin >> name;
                cout << "S.NO\tCandidate name\t\tConstunecy\t\tParty_name\t\tWon By\n";
                while (can_ptr != NULL) {
                    if ( can_ptr->constituency==name) {
                        cout << i++ << "\t" << can_ptr->name << "\t\t" << can_ptr->constituency << "\t\t" << can_ptr->party_name << "\t\t" << can_ptr->candidate_total_votes << " Votes." << endl;
                    }
                    can_ptr = can_ptr->next;
                }
            }


            delete_LL( political_party,NULL,candidate);
        }
        else if (!voting_finnished) {
            cout << "the voting hasn't finnished yet\n";
        }
    
        return 0;
    }

};




int main() {
    system("color 0b");
    int choice = 0;
    int which_log_in = 0;//1 for election commision login, 2 for political party login

    Election_Commission EC;
    
    

    while (1) {
        //system("cls");
        cout << "1. Election Commision Log in\n";
        cout << "2. Political Party Log in\n";
        cout << "3. voter Log in\n";

        cin >> which_log_in;
        while (which_log_in > 3 or which_log_in < 1) { cerr << "wrong input, try again: "; cin >> which_log_in; }

        if (which_log_in == 1 ) {
            system("cls");
            if (ec_login() == true) {
                while (true) {
                    
                    //system("cls");
                    cout << "***********************MAIN MENU***********************" << endl;;
                    cout << "1. create/update a constituency\n";
                    cout << "2. create a political party\n";
                    cout << "3. register a candidate\n";
                    cout << "4. send request of a constituent to register against a party(for constituents only)\n";
                    cout << "5. register a Voter\n";
                    cout << "6. start voting\n";
                    cout << "7. show results voting\n";
                    cout << "8. TO LOGOUT\n";
                    cout << "choose: "; cin >> choice;
                    while (choice > 9 or choice < 1) { cerr << "wrong choice, try again: "; cin >> choice; }

                    if (choice == 1) {
                        system("cls");
                        EC.create_or_update_constituency();
                    }
                    else if (choice == 2) {
                        system("cls");

                        EC.create_political_party();
                    }
                    else if (choice == 3) {
                        system("cls");

                        EC.register_candidate();
                    }
                    else if (choice == 4) {
                        system("cls");

                        EC.send_req_to_party();
                    }
                    else if (choice == 5) {
                        system("cls");

                        EC.register_voter();
                    }
                    else if (choice == 6) {
                        system("cls");
                        cout << "******************************VOTING******************************\n";

                        EC.start_voting();
                    }
                    else if (choice == 7) {
                        system("cls");

                        cout << "******************************RESULTS******************************\n";
                        cout << "1. show results of all constituents\n";
                        cout << "2. show results of a particular constituency\n";
                        cout << "choose: "; cin >> choice;
                        while (choice < 1 or choice > 2) { cerr << "wrong choice, choose again: "; cin >> choice; }
                        if (choice == 1 or choice == 2) {
                            EC.results(choice);
                        }
                    }
                    else if (choice == 8) { break; }
                }
            }
            else {
                cout << "wrong id or password entered.\n";
            }
        }

        else if (which_log_in == 2) {
            system("cls");
            string party_name;
            if (pp_login(party_name)) {
                system("cls");
                EC.party_login(party_name);
            }
            else { cerr << "wrong id or password\n"; }
        }

        else if (which_log_in == 3) {
            system("cls");
            voter_login(EC.voting_started_flag,
                        EC.total_vote_casted,
                        EC.total_voters,EC.voting_finnished, EC.won);
        }
    }



    cout << "Hello World!\n";


    return 0;
}
