#include <iostream>
#include <cstring>
#include "PosApp.h"
#include "Perishable.h"
#include "NonPerishable.h"
using namespace std;

namespace sdds{

    PosApp::PosApp(){
        fileName[0]='\0';
    }

    PosApp::PosApp(const char *name){
        if(name!= nullptr){
            strcpy(fileName,name);
        }
    }

    PosApp::~PosApp(){
        for(int i=0; i<nptr;i++){
            delete Iptr[i];
            Iptr[i]= nullptr;
        }
        nptr = 0;
    }

    void PosApp::run(){
        int choice;
        bool flag = true;

        loadRecs();

        do {
            menu();
            cin >> choice;

            do {
                if (cin.fail()) {
                    cout << "Invalid Integer, try again: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin >> choice;
                } else if (!cin.fail()) {
                    if (choice < 0 || choice > 5) {
                        cout << "[0<=value<=5], retry: > ";
                        cin >> choice;
                    } else {
                        flag = false;
                    }
                }
            } while (flag);

            flag=true;

            switch (choice) {
                case 0:
                    saveRecs();
                    cout << "Goodbye!" << endl;
                    flag=false;
                    break;
                case 1:
                    listItems();
                    break;
                case 2:
                    addItem();
                    break;
                case 3:
                    removeItem();
                    break;
                case 4:
                    stockItem();
                    break;
                case 5:
                    POS();
                    break;
            }
        }while(flag);
    }

    void PosApp::menu(){

        cout << "The Sene-Store" << endl;
        cout << "1- List items" << endl;
        cout << "2- Add item" << endl;
        cout << "3- Remove item" << endl;
        cout << "4- Stock item" << endl;
        cout << "5- POS" << endl;
        cout << "0- exit program" << endl;

        cout<<"> ";
    }

    void PosApp::addItem(){
        actionTitle("Adding Item to the store");
        bool flag=true;
        do{
            if(nptr==MAX_NO_ITEMS-1){
                cout<<"Inventory Full!";
                flag=false;
            }else{
                Item* item={};
                char c;
                cout<<"Is the Item perishable? (Y)es/(N)o: ";
                cin>>c;
                if(c=='y'||c=='Y'){
                    item= new Perishable;

                }else if(c=='n'||c=='N'){
                    item= new NonPerishable;
                }

                item->read(cin);
                if(cin.fail()){
                    cin.clear();
                    cin.ignore();
                    cout<<item;
                    cout<<", try again...\n";
                }else{
                    Iptr[nptr]=item;
                    nptr++;
                    actionTitle("DONE!");
                    flag=false;
                }
            }
        }while(flag);

    }

    void PosApp::removeItem(){
        int row;

        actionTitle("Remove Item");
        row=selectItem();
        cout<<"Removing...."<<endl;
        Iptr[row-1]->displayType(POS_FORM);
        Iptr[row-1]->write(cout);
        delete Iptr[row-1];
        for(int i=(row-1);i<nptr;i++){
            Iptr[i]= Iptr[i+1];
        }
        delete Iptr[nptr];
        nptr-=1;
        actionTitle("DONE!");

    }

    void PosApp::stockItem(){
        int row;
        int m_qty;
        bool flag=true;
        actionTitle("Select an item to stock");
        row=selectItem();
        cout<<"Selected Item:\n";
        Iptr[row-1]->displayType(POS_FORM);
        Iptr[row-1]->write(cout);
        cout<<"Enter quantity to add: ";
        do{
            cin>>m_qty;

            if(cin.fail()){
                cout<<"Invalid Integer, try again: ";
            }else if(m_qty<=0||m_qty>(MAX_STOCK_NUMBER-Iptr[row-1]->quantity())){
                cout<<"[1<=value<="<<(MAX_STOCK_NUMBER-Iptr[row-1]->quantity())<<"], retry: Enter quantity to add: ";
            }else{
                Iptr[row-1]->operator+=(m_qty);
                actionTitle("DONE!");
                flag=false;
            }
            cin.clear();
            cin.ignore(1000,'\n');
        }while(flag);

    }

    void PosApp::listItems(){
        actionTitle("Listing Items");

        double tot_Assets=0.0;
        sort();

        cout<<" Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |"<<endl;
        cout<<"-----|--------|--------------------|-------|---|----|---------|-------------|"<<endl;
        for (int i=0; i<nptr;i++){
            Iptr[i]->Item::displayType(POS_LIST);
            cout.width(4);
            cout.fill(' ');
            cout<<i+1<<" | ";
            Iptr[i]->write(cout);
            cout<<endl;
            tot_Assets += Iptr[i]->Item::cost() * Iptr[i]->quantity();
        }
        cout<<"-----^--------^--------------------^-------^---^----^---------^-------------^"<<endl;
        cout<<"                               Total Asset: $  |";
        cout.width(14);
        cout.fill(' ');
        cout.setf(ios::fixed);
        cout.precision(2);
        cout<<tot_Assets<<"|"<<endl;
        cout.unsetf(ios::fixed);
        cout<<"-----------------------------------------------^--------------^"<<endl<<endl;

    }

    void PosApp::POS() {
        double cost = 0.0;
        bool flag = false;
        actionTitle("Starting Point of Sale");
        char m_sku[MAX_SKU_LEN];
        Item* selected[MAX_NO_ITEMS];
        int count=0;

        cout << "Enter SKU or <ENTER> only to end sale..." << endl << "> ";
        cin.ignore();

        while(cin.getline(m_sku, MAX_SKU_LEN) && strlen(m_sku)>0){
            if(!cin.fail()) {
                    for (int i = 0; i < nptr && !flag; i++) {
                        if (Iptr[i]->operator==(m_sku)) {
                            if (Iptr[i]->quantity() == 0) {
                                cout << "Item out of stock"<<endl;
                                flag = true;
                            } else if (Iptr[i]->quantity() > 0) {
                                Iptr[i]->displayType(POS_FORM);
                                Iptr[i]->operator-=(1);
                                Iptr[i]->write(cout);
                                cout << endl;
                                cout << ">>>>> Added to bill" << endl;
                                cout << ">>>>> Total: ";
                                cost += Iptr[i]->cost();
                                cout.setf(ios::fixed);
                                cout.precision(2);
                                cout << cost << endl;
                                cout.unsetf(ios::fixed);
                                selected[count] = Iptr[i];
                                count++;
                                flag = true;
                            }
                        }else if(!Iptr[i]->operator==(m_sku)){
                            flag=false;
                        }
                    }
                    if(!flag){
                        cout<<"!!!!! Item Not Found !!!!!"<<endl;
                    }
            }else{
                cout<<"SKU too long"<<endl;
                cin.clear();
            }
            flag=false;
            cout << "Enter SKU or <ENTER> only to end sale..." << endl << "> ";
        }

        cout<<"v---------------------------------------v"<<endl;
        cout<<"| 2023/03/31, 10:44                     |"<<endl;
        cout<<"+---------------------v-----------v-----+"<<endl;
        cout<<"| Item                |     Price | Tax +"<<endl;
        cout<<"+---------------------v-----------v-----+"<<endl;
        for(int i=0; i<count;i++){
            selected[i]->bprint(cout);
        }
        cout<<"+---------------------^-----------^-----+"<<endl;
        cout<<"| total:";
        cout.width(24);
        cout.fill(' ');
        cout.setf(ios::fixed);
        cout.precision(2);
        cout<<cost;
        cout.unsetf(ios::fixed);
        cout<<" |"<<endl;
        cout<<"^---------------------------------^"<<endl;

        }


    void PosApp::saveRecs(){
        actionTitle("Saving Data");
        ofstream ofs (fileName,ofstream ::out);
        for (int i=0; i<nptr;i++){
            ofs<<*Iptr[i]<<endl;
        }
        ofs.close();
    }

    void PosApp::loadRecs(){

        char c;
        actionTitle("Loading Items");
        ifstream ifs;

        ifs.open (fileName,ifstream::in);

        if(ifs.fail()){
            ifs.close();
        }else{

            while(ifs&& nptr< MAX_NO_ITEMS){
                    c='\0';
                    ifs>> c;
                    ifs.ignore();
                    if (nptr<MAX_NO_ITEMS){
                        if(c=='P'){

                            Iptr[nptr] =new Perishable;

                        }else if (c== 'N'){
                            Iptr[nptr] = new NonPerishable;
                        }
                        if(Iptr[nptr]){
                            ifs>>*Iptr[nptr];
                            nptr ++;
                        }

                    }
                }

            }
        ifs.close();
        }




    void PosApp::actionTitle(string name) {
        cout<<">>>> ";
        cout.width(72);
        cout.setf(ios::left);
        cout.fill('.');
        cout<< name;
        cout.unsetf(ios::left);
        cout<<endl;
    }


    int PosApp::selectItem(){
        int row;
        bool flag = true;

        actionTitle("Item Selection by row number");
        cout << "Press <ENTER> to start....";
        cin.get();
        cin.ignore();
        actionTitle("Listing Items");

        sort();
        cout<<" Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |"<<endl;
        cout<<"-----|--------|--------------------|-------|---|----|---------|-------------|"<<endl;
        for (int i=0; i<nptr;i++){

            Iptr[i]->Item::displayType(POS_LIST);
            cout.width(4);
            cout.fill(' ');
            cout<<i+1<<" | ";
            Iptr[i]->write(cout);
            cout<<endl;
        }
        cout<<"-----^--------^--------------------^-------^---^----^---------^-------------^"<<endl;
        cout<<"Enter the row number: ";

        do{
            cin>>row;
            if(!cin.fail()) {
                if (row < 1 || row > nptr) {
                    cout << "[1<=value<=" << nptr << "], retry: Enter the row number: ";
                } else {
                    flag = false;
                }
            }else {
                cout<<"Invalid Integer, try again: ";
            }
            cin.clear();
            cin.ignore(1000, '\n');
        }while(flag);

        return row;
    }

    void PosApp::sort(){
        Item *temp;
        for(int i=0;i<nptr-1;i++){
            for(int j=0;j<nptr-1;j++){
                if(strcmp(Iptr[j]->nameQuery(), Iptr[j+1]->nameQuery()) > 0){
                    temp=Iptr[j];
                    Iptr[j]= Iptr[j+1];
                    Iptr[j+1]=temp;
                }
            }
        }
    }
}


