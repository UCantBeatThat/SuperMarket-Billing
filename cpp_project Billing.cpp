#include<iostream>
#include<stdio.h>
#include<clrscr.h>
#include<fstream>
#include<string.h>
using namespace std;

class product
{
private:
    int prono;
    char proname[100];
    float prorate,prodisc;

public:

    void create_product()
    {
        cout<<"\nEnter Product Number :";
        cin>>prono;
        cout<<"\nEnter Product Name :";
        cin.ignore();
        cin.getline(proname,100,'\n');
        cout<<"\nEnter the rate :";
        cin>>prorate;
        cout<<"\nEnter Discount Rate(%) :";
        cin>>prodisc;
    }

    void show_product()
    {
        cout<<"\nProduct Number :"<<prono;
        cout<<"\nProduct Name :"<<proname;
        cout<<"\nRate :"<<prorate;
        cout<<"\nDiscount(%) :"<<prodisc;
    }

    int retprono()
    {
        return prono;
    }

    char* retproname()
    {
        return proname;
    }

    float retprorate()
    {
        return prorate;
    }

    float retprodisc()
    {
        return prodisc;
    }
};

class Login
{
    char usrs[100];
    char pword[100];

    char* pass()
    {
        return "12345";
    }

    char* usr1()
    {
        return "Sandesh";
    }

    char* usr2()
    {
        return "Kausthubha";
    }

    char* usr3()
    {
        return "MICE";
    }

public:

    void login()
    {
        int i,flag=0;

        cout<<"\n\n\t\t\t\t\tUser Name  :";
        cin.getline(usrs,100,'\n');
        cout<<"\n\t\t\t\t\tPassword   :";
        cin.getline(pword,100,'\n');
        if((!strcmp(usrs,usr1()))||(!strcmp(usrs,usr2()))||(!strcmp(usrs,usr3())))
        {
            if(!strcmp(pass(),pword))
            {
                flag=1;
            }
        }
        if(flag==0)
        {
            cout<<"\n\nWrong Username or Password";
            exit(0);
        }
    }
};


void intro();
void cust_order();
void admin_menu();
void new_product();
void disp_products();
void disp_1pro();
void modify_product();
void delete_product();
void prod_menu();

fstream fp;
product pro;
Login log;

int main()
{
    int a;
    intro();
    do
    {
        clrscr();
        cout<<"\n\t\t\t|    MAIN MENU   |\t\t\t"<<"\n\t\t\t------------------";
        cout<<"\n\n\n\n\t\t\t(1) CUSTOMER MENU";
        cout<<"\n\n\t\t\t(2) ADMINISTRATOR MENU";
        cout<<"\n\n\t\t\t(3) QUIT";
        cout<<"\n\n\t\t\tChoose (1/2/3) :";
        cin>>a;
        switch(a)
        {
        case 1:
            cust_order();
            break;
        case 2:
            admin_menu();
            break;
        case 3:
            exit(0);
        }
    }while(a!=3);
}

void intro()
{
    cout<<"\n\n\t\t\t\t \t\t    BOMBAY SUPER BAZAR"<<"\n\n\t\t\t\t\t\t---------------------------";
    cout<<"\n\n\n\t\t\t\t\t\t\tWELCOME!"<<endl;
    log.login();
}

void cust_order()
{
    int order_arr[50],quan[50],c=0;
    float amt,discamt,total=0;
    char ch;
    prod_menu();
    cout<<"\n\t\t\t   ============================";
    cout<<"\n \t\t\t\tPLACE YOUR ORDER";
    cout<<"\n\t\t\t   ============================\n";
    do{
        cout<<"\n\nEnter The Product No. Of The Product : ";
        cin>>order_arr[c];
        cout<<"\nQuantity in number : ";
        cin>>quan[c];
        c++;
        cout<<"\nDo You Want To Order Another Product ? (y/n)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    clrscr();
    cout<<"\n\n\t********************************INVOICE********************************\n";
    cout<<"\nProd No.\tProd Name\tQuantity \tPrice \tAmount \t  Amount after discount\n";
    for(int x=0; x<=c; x++)
    {
        fp.open("Sample.dat",ios::in);
        fp.read((char*)&pro,sizeof(product));
        while(!fp.eof())
        {
            if(pro.retprono()==order_arr[x])
            {
                amt=pro.retprorate()*quan[x];
                discamt=amt-(amt*pro.retprodisc()/100);
                cout<<"\n"<<order_arr[x]<<"\t\t"<<pro.retproname()<<"\t\t"<<quan[x]<<"\t\t"<<pro.retprorate()<<"\t"<<amt<<"\t\t  "<<discamt;
                total+=discamt;
            }
            fp.read((char*)&pro,sizeof(product));
        }
       fp.close();
    }
    cout<<"\n\n\n\t\t\t\t\t\t\t\t TOTAL = "<<total;
    cout<<"\n\n\t\tThank You For Placing The Order\n\t\t\tHAVE A NICE DAY!!";
    char enter;
    cout<<"\n\n Press Y to continue : ";
    cin>>enter;
}

void admin_menu()
{
    clrscr();
    int b;
    cout<<"\n\n\n\t\t\t   ADMIN MENU"<<"\n\t\t\t------------------";
    cout<<"\n(1)CREATE PRODUCT";
    cout<<"\n(2)DISPLAY ALL PRODUCTS";
    cout<<"\n(3)DISPLAY A PRODUCT: ";
    cout<<"\n(4)MODIFY PRODUCT";
    cout<<"\n(5)DELETE PRODUCT";
    cout<<"\n(6)VIEW PRODUCT MENU";
    cout<<"\n(7)BACK TO MAIN MENU";
    cout<<"\nEnter Your Choice (1-7) : ";
    cin>>b;
    switch(b)
    {
    case 1:
        new_product();
        break;
    case 2:
        disp_products();
        break;
    case 3:
        disp_1pro();
        break;
    case 4:
        modify_product();
        break;
    case 5:
        delete_product();
        break;
    case 6:
        prod_menu();
    }
}

void new_product()
{
    char enter;
    fp.open("Sample.dat",ios::out|ios::app);
    do{
    clrscr();
    pro.create_product();
    fp.write((char*)&pro,sizeof(product));
    cout<<"\nWant to create another product ? (Y/N)";
    cin>>enter;
    }while(enter == 'Y'||enter == 'y');
    fp.close();
    cout<<"\n\nThe Product Has Been Created!!";
}

void disp_products()
{
    clrscr();
    cout<<"\n\n\n\t\tALL ITEM DISPLAY\n\n";
    fp.open("Sample.dat",ios::in);
    while(fp.read((char*)&pro,sizeof(product)))
    {
        pro.show_product();
        cout<<"\n\n====================================\n";
    }
    fp.close();
     char enter;
    cout<<"\n\n Press Y to continue : ";
    cin>>enter;
}

void disp_1pro()
{
    int flag1=0;
    int n;
    clrscr();
    cout<<"\nEnter the number of the product to be displayed :";
    cin>>n;
    fp.open("Sample.dat",ios::in);
    while(fp.read((char*)&pro,sizeof(product)))
    {
        if(pro.retprono()==n)
        {
            clrscr();
            pro.show_product();
            flag1=1;
            fp.close();
            break;
        }
    }
    if(flag1==0)
        cout<<"\n\n\tRecord doesn't exist!!";
     char enter;
    cout<<"\n\n Press Y to continue : ";
    cin>>enter;
}

void modify_product()
{
    int n,pos,flag=0;
    clrscr();
    prod_menu();
    cout<<"\nEnter the number of the product to be modified :";
    cin>>n;
    fp.open("Sample.dat",ios::in|ios::out);
    while(fp.read((char*)&pro,sizeof(product)))
    {
        if(pro.retprono()==n)
        {
            pro.show_product();
            cout<<"\nEnter the details of the product to be modified:";
            pro.create_product();
            pos = -1*sizeof(pro);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&pro,sizeof(product));
            cout<<"\n\nProduct Details Modified\n\nRecords Updated!!";
            flag=1;
            fp.close();
            break;
        }
    }
    if(flag==0)
        cout<<"\n\n***\nERROR: Product number not found!!\n***";
     char enter;
    cout<<"\n\n Press Y to continue : ";
    cin>>enter;
}

void delete_product()
{
    int n;
    clrscr();
    prod_menu();
    cout<<"\nEnter the number of the product to be deleted:";
    cin>>n;
    fp.open("Sample.dat",ios::in);
    fstream fp1;
    fp1.open("Temp.dat",ios::out);
    while(fp.read((char*)&pro,sizeof(product)))
    {
        if(pro.retprono()!=n)
        {
            fp1.write((char*)&pro,sizeof(product));
        }
    }
    fp1.close();
    fp.close();
    remove("Sample.dat");
    rename("Temp.dat","Sample.dat");
    cout<<"\nProduct is Deleted!!\n\nRecords Updated!!";
     char enter;
    cout<<"\n\n Press Y to continue : ";
    cin>>enter;
}

void prod_menu()
{
    clrscr();
    fp.open("Sample.dat",ios::in);
    if(!fp)
    {
        cout<<"\n****ERROR : File couldn't be opened!!\n****\n\n Add a product in Administrator Menu\n\n\t Program is closing...........";
        exit(0);
    }
    cout<<"\n\n\t\t\t\t\tPRODUCT MENU\n";
    cout<<"\n\t\t\t====================================================";
    cout<<"\n\t\t\tP.NO.\t\tNAME\t\tPRICE";
    cout<<"\n\t\t\t====================================================\n";
    while(fp.read((char*)&pro,sizeof(product)))
    {
        cout<<"\t\t\t"<<pro.retprono()<<"\t\t"<<pro.retproname()<<"\t\t"<<pro.retprorate()<<"\n";
    }
    fp.close();
    char enter;
    cout<<"\n\nPress Y to continue :";
    cin>>enter;
}
