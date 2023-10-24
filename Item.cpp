
#include <iostream>
#include <fstream>
#include "Item.h"

using namespace std;

namespace sdds{

    Item::Item(){
        Name= nullptr;
        SKU[0]='\0';
        Price=0.0;
        qty=0;
        Taxed=false;
        displayFlag=0;
    }

    Item::Item(const Item& copy){
        *this=(copy);
    }

    Item& Item::operator=(const Item& copy){
        if(this!= &copy){
            if(strlen(copy.Name)<MAX_NAME_LEN){
                delete [] Name;
                Name= new char[strlen(copy.Name)+1];
                strcpy(Name,copy.Name);
            }
            strcpy(SKU,copy.SKU);
            Price=copy.Price;
            Taxed=copy.Taxed;
            qty=copy.qty;

        }
        return *this;
    }

    Item::~Item(){
        delete [] Name;
        Name= nullptr;
    }

    bool Item::operator==(const char* rightHand) const{
        return (strcmp(SKU,rightHand)==0);
    }

    bool Item::operator>(const Item& r) const{
        if(strcmp(Name,r.Name)>0){
            return true;
        };

        return false;
    }

    int Item::operator+=(int rightHand){
        qty+=rightHand;
        if(qty>MAX_STOCK_NUMBER){
            qty=MAX_STOCK_NUMBER;
            errMsg=ERROR_POS_QTY;
        }
        return qty;
    }

    int Item::operator-=(int rightHand){

        if(qty<rightHand){
            qty=0;
            errMsg=ERROR_POS_STOCK;
        }else{
            qty -=rightHand;
        }
        return qty;
    }


    char Item::itemType() const{
        return 'T';
    }


    Item& Item::displayType(int type){
        displayFlag=type;
        return *this;
    }

    int Item::quantity () const{
        return qty;
    }

    double Item::cost() const{

        return Price * (1 + Taxed * TAX);

    }

    char* Item::nameQuery() const{
        return Name;
    }

    //IO
    ostream& Item::write(ostream& os) const{
        if (errMsg.errorQuery()== nullptr) {
            if (displayFlag == 1) //if in pos list mode
            {
                os.setf(ios::left);
                os.width(MAX_SKU_LEN);
                os << SKU << "|";
                if (strlen(Name) > 20)
                {
                    string name;
                    name = Name;
                    os << name.substr(0, 20);
                }
                else
                {
                    os.width(20);
                    os <<Name;
                }
                os << "|";
                os.width(7);
                os.precision(2);
                os.unsetf(ios::left);
                os.setf(ios::fixed);
                os << Price;
                os << "|";
                if (Taxed)
                {
                    os << " X |";
                }
                else
                {
                    os << "   |";
                }
                os.width(4);
                os << qty;
                os << "|";
                os.width(9);
                os.precision(2);
                os << cost() * qty;
                os << "|";
                os.unsetf(ios::fixed);
            }
            else if (displayFlag == 2) //in POS_FORM mode
            {
                os << "=============v" << endl;
                os << "Name:        " << Name << endl;
                os << "Sku:         " << SKU << endl;
                os << "Price:       ";
                os.setf(ios::fixed);
                os.precision(2);
                os << Price << endl;
                os << "Price + tax: ";
                if (!Taxed)
                {
                    os << "N/A" << endl;
                }
                else
                {

                    os << cost() << endl;
                }
                os << "Stock Qty:   " << qty << endl;
            }
        }
        else {
            os << errMsg.errorQuery();
        }
        return os;
    }

    istream& Item::read(istream& is){
        char name[50];
        char choice='\0';

        cout<<"Sku"<<endl;
        do{
            cout<<"> ";
            is>>SKU;
            if(strlen(SKU)>MAX_SKU_LEN){
                SKU[0]='\0';
                errMsg=ERROR_POS_SKU;
            }
        }while(strlen(SKU)>MAX_SKU_LEN);

        cout<<"Name"<<endl;
        do{
            cout<<"> ";

            is.ignore(1000, '\n');
            is.clear();
            is.get(name, 50, '\n');

            if(strlen(name)<MAX_NAME_LEN){
                delete [] Name;
                Name= new char[strlen(name)+1];
                strcpy(Name,name);
            }else{
                if(is.fail()) {
                    delete[] Name;
                    errMsg = ERROR_POS_NAME;
                }
            }
        }while(strlen(name)>MAX_NAME_LEN);

        cout<<"Price"<<endl;

        do{
            cout<<"> ";
            is.ignore(1000, '\n');
            is>>Price;
            if(is.fail()||Price<0){
                Price=0;
                errMsg=ERROR_POS_PRICE;
            }
        }while(Price<0);

        cout<<"Taxed?"<<endl;

        do{
            cout<<"(Y)es/(N)o: ";
            is>>choice;
            if((choice!= 'y' && choice != 'n')){
                choice='\0';
                errMsg=ERROR_POS_TAX;
            }else if (choice=='y'){
                Taxed=true;
            }else{
                Taxed=false;
            }
        }while((choice!= 'y' && choice != 'n'));

        cout<<"Quantity"<<endl;

        do{
            cout<<"> ";
            is>>qty;
            if(is.fail()||qty>MAX_NO_ITEMS){
                qty=0;
                errMsg=ERROR_POS_QTY;
            }
        }while(qty>MAX_NO_ITEMS);

        return is;
    }



    ofstream& Item::save(ofstream& of) const{

        of << itemType();
        of<< ",";
        of << SKU;
        of << ",";
        of << Name ;
        of<< ",";
        of.precision(2);
        of.setf(ios::fixed);
        of << Price;
        of << "," << Taxed << "," << qty;
        if (errMsg.errorQuery() != nullptr)
        {
            cerr << errMsg << endl;
        }

        return of;
    }

    ifstream& Item::load(std::ifstream& ifs){

        char* name = new char[MAX_NAME_LEN + 2];
        char sku[MAX_SKU_LEN + 2] = { 0 };
        int quantity = 0;
        bool tax = false;
        double price = 0.0;
        char deliminator;

        errMsg.clear();
        ifs.get(sku, MAX_SKU_LEN + 2, ',');
        ifs.ignore(1000, ',');
        ifs.get(name, MAX_NAME_LEN + 2, ',');
        ifs.ignore(1000, ',');
        ifs >> price >> deliminator >> tax >> deliminator >> quantity;
        if (!ifs.fail()) {
            if (strlen(sku) > MAX_SKU_LEN) {
                sku[0] = '\0';
                errMsg = ERROR_POS_SKU;
            } else if (strlen(name) > MAX_NAME_LEN) {
                delete[] name;
                errMsg = ERROR_POS_NAME;
            } else if (price < 0) {
                price = 0;
                errMsg = ERROR_POS_PRICE;
            } else if (quantity > MAX_STOCK_NUMBER || quantity<0) {
                quantity = 0;
                errMsg = ERROR_POS_QTY;
            }else if (tax!=0 && tax!=1){
                tax=false;
                errMsg=ERROR_POS_TAX;
            }else{
                delete [] Name;
                Name= new char [strlen(name)+1];
                strcpy(Name, name);

                strcpy(SKU,sku);
                qty=quantity;
                Taxed=tax;
                Price=price;
            }
        }

        delete[] name;
        return ifs;
    }



    double operator+=(double& left, const Item& right){

        return left += right.quantity() * right.cost();
    }

    Item::operator bool () const{

        if(errMsg.errorQuery() == nullptr){
            return true;
        }
        return false;
    }

    ostream& Item::bprint(ostream& os) const{
        char* name= nullptr;
        os<<"| ";
        os.width(20);
        os.fill(' ');
        os.setf(ios::left);
        if(strlen(Name)>20){
            strcpy(name, Name);
            name[20]='\0';
            os<<name;
        }else{
            os<<Name;
        }
        os<<"|";
        os.width(10);
        os.fill(' ');
        os.precision(2);
        os.unsetf(ios::left);
        os.setf(ios::fixed);
        os<<cost()<< " |";
        os<< (Taxed ? "  T  |" : "     |")<<endl;

        return os;
    }


}