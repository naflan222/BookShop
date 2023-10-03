#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

int error;

void login(string& admin, string& password);
void employee(string& user, string& password);
void adminmenu();
void empmenu();
void deleteoptions();
void searchoptions();
void updateoptions();
void About();
void Contact();
void addbook();
void Displaybook();
void viewsales();
void logout();
void logoutstaff();
void searchingoptions();

HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

struct bookinfo
{
    string name;
    string Description;
    string Authour;
    int ID;
    int Price;
    int quantity;
    string catergory;
    string availability;
} b[20];

void fontsize()
{
    short font, x, y;
    do
    {
        error = 0;
        cout << " Enter font size: ";
        cin >> font;
        if (font >= 25 || font <= 5)
        {
            cout << "Please enter font size less than 25 and greater than 5 " << endl;
            error = 1;
            cin.clear();
            cin.ignore(80, '\n');
        }
        if (cin.fail())
        {
            cout << "Please enter valid font size " << endl;
            error = 1;
            cin.clear();
            cin.ignore();
        }
    } while (error == 1);

    x = font;
    y = 2 * x;
    HANDLE Hout = ::GetStdHandle(STD_OUTPUT_HANDLE);
    COORD fsize = { x, y };
    CONSOLE_FONT_INFOEX Font = { sizeof(font) };
    ::GetCurrentConsoleFontEx(Hout, FALSE, &Font);
    Font.dwFontSize = fsize;
    GetCurrentConsoleFontEx(Hout, 0, &Font);
    cin.clear();
    system("cls");
}

string getpass(const char* prompt, bool show_asterisk = true)
{
    const char BACKSPACE = 8;
    const char RETURN = 13;
    string password;
    unsigned char ch = 0;
    cout << "\n\n\t" << prompt;
    DWORD con_mode;
    DWORD dwRead;
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hIn, &con_mode);
    SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

    while (ReadConsoleA(hIn, &ch, 1, &dwRead, NULL) && ch != RETURN)
    {
        if (ch == BACKSPACE)
        {
            if (password.length() != 0)
            {
                if (show_asterisk)
                    cout << "\b \b";
                password.resize(password.length() - 1);
            }
        }
        else
        {
            password += ch;
            if (show_asterisk)
                cout << "*";
        }
    }
    cout << endl;
    return password;
}

void colourchange()
{
    int col;
    cout << "\n\t1. Black & White theme" << endl;
    cout << " \n\t2. White & Black theme \n\n\t0 Return" << endl;
    do
    {
        do
        {
            error = 0;
            cout << "# Enter selection: # " << endl;
            cin >> col;
            if (cin.fail())
            {
                cout << "Please enter a valid entry" << endl;
                error = 1;
                cin.clear();
                cin.ignore(80, '\n');
            }
        } while (error == 1);
        if (col == 1)
        {
            system("color 0F");
            system("cls");
            return;
        }
        else if (col == 2)
        {
            system("color F0");
            system("cls");
            return;
        }
    } while (col != 0);
    system("cls");
    return;
}

void help()
{
    int option;
    cout << "Welcome to the help Menu of GENIUS BOOK SHOP" << endl;
    cout << "\n\t1. About System \n\t2. Get Help \n" << endl;
    cout << "Enter Option: " << endl;
    cin >> option;
    switch (option)
    {
    case 1:
        About();
        break;
    case 2:
        Contact();
        break;
    }
}

void About()
{
    cout << "About System" << endl;
    cout << "\t" << endl;
    cout << "\t" << endl;
    cout << "This is a specially designed software for the genius bookshop. It can handle the daily activities in a bookshop." << endl;
    cout << "The software is easy to use interface technology" << endl;
    cout << "This consists of a fast-reactive system which saves time in transactions" << endl;
    cout << "The software is a never-before-seen completely installed system for a bookshop system handling activities" << endl;
}

void Contact()
{
    cout << "Developer's mail = naflan@live.co.uk" << endl;
    cout << "You can email us any future development of the system" << endl;
}

int main()
{
    int choice;
    string user, password;

    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, 10);

    cout << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> > " << endl;
    cout << " ------------------------------ WELCOME TO GENIUS BOOKS SHOP ----------------------------------" << endl;
    cout << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << endl;
    cout << " \t " << endl;
    cout << " # This applications helps you to search and know about any book available at GENIUS BOOK SHOP # " << endl;
    cout << "************************************ Please Login here *********************************************" << endl;

    do
    {
        cin.clear();
        SetConsoleTextAttribute(color, 7);
        cout << "Select an option from here";
        cout << "\n\n\t\t1. Admin Login \n\n\t\t2. Employee Login \n\n\t\t3. Change font \n\n\t\t4.Change Theme \n\n\t\t5.Help \n\n\t\t0.Exit \n" << endl;

        do
        {
            error = 0;
            cout << " Enter option: " << endl;
            cin >> choice;
            if (cin.fail())
            {
                cout << "Please enter a valid option" << endl;
                error = 1;
                cin.clear();
                cin.ignore(50, '\n');
            }
        } while (error == 1);

        switch (choice)
        {
        case 1:
        {
            cout << " \tPlease enter the Admin Username: ";
            cin >> user;
            password = getpass("Please Enter Admin Password: ", true);
            login(user, password);
        }
        break;
        case 2:
        {
            cout << "\tPlease enter the Employee Username: ";
            cin >> user;
            password = getpass("Please enter Employee Password: ", true);
            employee(user, password);
        }
        break;
        case 3:
            fontsize();
            break;
        case 4:
            colourchange();
            break;
        case 5:
            help();
            break;
        case 0:
            return 0;
            break;
        default:
            cout << "Please enter a valid option" << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}

void login(string& admin, string& password)
{
    if (admin == "admin" && password == "admin")
    {
        SetConsoleTextAttribute(color, 14);
        cout << "\nLogin Successful!\n" << endl;
        adminmenu();
    }
    else
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nLogin Failed! Please try again.\n" << endl;
        main();
    }
}

void employee(string& user, string& password)
{
    if (user == "employee" && password == "employee")
    {
        SetConsoleTextAttribute(color, 11);
        cout << "\nLogin Successful!\n" << endl;
        empmenu();
    }
    else
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nLogin Failed! Please try again.\n" << endl;
        main();
    }
}

void adminmenu()
{
    int option;
    do
    {
        cout << "************************************ Admin Menu *********************************************" << endl;
        cout << "\n\n\t\t1. Add book \n\n\t\t2. Delete book \n\n\t\t3. Search book \n\n\t\t4. Update book \n\n\t\t5. View sales \n\n\t\t6. Logout \n\n\t\t0. Exit \n" << endl;
        do
        {
            error = 0;
            cout << " Enter option: ";
            cin >> option;
            if (cin.fail())
            {
                cout << "Please enter a valid option" << endl;
                error = 1;
                cin.clear();
                cin.ignore(50, '\n');
            }
        } while (error == 1);

        switch (option)
        {
        case 1:
            addbook();
            break;
        case 2:
            deleteoptions();
            break;
        case 3:
            searchoptions();
            break;
        case 4:
            updateoptions();
            break;
        case 5:
            viewsales();
            break;
        case 6:
            logout();
            break;
        case 0:
            return;
        default:
            cout << "Please enter a valid option" << endl;
            break;
        }
    } while (option != 0);
}

void empmenu()
{
    int option;
    do
    {
        cout << "************************************ Employee Menu *********************************************" << endl;
        cout << "\n\n\t\t1. Search book \n\n\t\t2. View sales \n\n\t\t3. Logout \n\n\t\t0. Exit \n" << endl;
        do
        {
            error = 0;
            cout << " Enter option: ";
            cin >> option;
            if (cin.fail())
            {
                cout << "Please enter a valid option" << endl;
                error = 1;
                cin.clear();
                cin.ignore(50, '\n');
            }
        } while (error == 1);

        switch (option)
        {
        case 1:
            searchingoptions();
            break;
        case 2:
            viewsales();
            break;
        case 3:
            logoutstaff();
            break;
        case 0:
            return;
        default:
            cout << "Please enter a valid option" << endl;
            break;
        }
    } while (option != 0);
}

void deleteoptions()
{
    string deletename;
    int option;

    cout << "************************************ Delete Menu *********************************************" << endl;
    cout << "\n\n\t\t1. Delete by name \n\n\t\t2. Delete by ID \n\n\t\t0. Return to main menu \n" << endl;

    do
    {
        error = 0;
        cout << " Enter option: ";
        cin >> option;
        if (cin.fail())
        {
            cout << "Please enter a valid option" << endl;
            error = 1;
            cin.clear();
            cin.ignore(50, '\n');
        }
    } while (error == 1);

    switch (option)
    {
    case 1:
        cout << "Enter the name of the book you want to delete: ";
        cin.ignore();
        getline(cin, deletename);
        for (int i = 0; i < 20; i++)
        {
            if (b[i].name == deletename)
            {
                b[i].name = "";
                b[i].Description = "";
                b[i].Authour = "";
                b[i].ID = 0;
                b[i].Price = 0;
                b[i].quantity = 0;
                b[i].catergory = "";
                b[i].availability = "";
                SetConsoleTextAttribute(color, 2);
                cout << "\nBook deleted successfully!\n" << endl;
                break;
            }
            if (i == 19)
            {
                SetConsoleTextAttribute(color, 12);
                cout << "\nBook not found!\n" << endl;
            }
        }
        break;
    case 2:
        int deleteID;
        cout << "Enter the ID of the book you want to delete: ";
        cin >> deleteID;
        for (int i = 0; i < 20; i++)
        {
            if (b[i].ID == deleteID)
            {
                b[i].name = "";
                b[i].Description = "";
                b[i].Authour = "";
                b[i].ID = 0;
                b[i].Price = 0;
                b[i].quantity = 0;
                b[i].catergory = "";
                b[i].availability = "";
                SetConsoleTextAttribute(color, 2);
                cout << "\nBook deleted successfully!\n" << endl;
                break;
            }
            if (i == 19)
            {
                SetConsoleTextAttribute(color, 12);
                cout << "\nBook not found!\n" << endl;
            }
        }
        break;
    case 0:
        return;
    default:
        cout << "Please enter a valid option" << endl;
        break;
    }
}

void searchoptions()
{
    int option;
    do
    {
        cout << "************************************ Search Menu *********************************************" << endl;
        cout << "\n\n\t\t1. Search by name \n\n\t\t2. Search by ID \n\n\t\t3. View all books \n\n\t\t0. Return to main menu \n" << endl;
        do
        {
            error = 0;
            cout << " Enter option: ";
            cin >> option;
            if (cin.fail())
            {
                cout << "Please enter a valid option" << endl;
                error = 1;
                cin.clear();
                cin.ignore(50, '\n');
            }
        } while (error == 1);

        switch (option)
        {
        case 1:
            searchingname();
            break;
        case 2:
            searchingID();
            break;
        case 3:
            displayallbooks();
            break;
        case 0:
            return;
        default:
            cout << "Please enter a valid option" << endl;
            break;
        }
    } while (option != 0);
}

void searchingoptions()
{
    int option;
    do
    {
        cout << "************************************ Search Menu *********************************************" << endl;
        cout << "\n\n\t\t1. Search by name \n\n\t\t2. Search by ID \n\n\t\t3. View all books \n\n\t\t0. Return to main menu \n" << endl;
        do
        {
            error = 0;
            cout << " Enter option: ";
            cin >> option;
            if (cin.fail())
            {
                cout << "Please enter a valid option" << endl;
                error = 1;
                cin.clear();
                cin.ignore(50, '\n');
            }
        } while (error == 1);

        switch (option)
        {
        case 1:
            searchingname();
            break;
        case 2:
            searchingID();
            break;
        case 3:
            displayallbooks();
            break;
        case 0:
            return;
        default:
            cout << "Please enter a valid option" << endl;
            break;
        }
    } while (option != 0);
}

void updateoptions()
{
    int option;
    do
    {
        cout << "************************************ Update Menu *********************************************" << endl;
        cout << "\n\n\t\t1. Update name \n\n\t\t2. Update ID \n\n\t\t3. Update Description \n\n\t\t4. Update Authour \n\n\t\t5. Update Price \n\n\t\t6. Update Quantity \n\n\t\t7. Update Catergory \n\n\t\t8. Update Availability \n\n\t\t0. Return to main menu \n" << endl;
        do
        {
            error = 0;
            cout << " Enter option: ";
            cin >> option;
            if (cin.fail())
            {
                cout << "Please enter a valid option" << endl;
                error = 1;
                cin.clear();
                cin.ignore(50, '\n');
            }
        } while (error == 1);

        switch (option)
        {
        case 1:
            updatename();
            break;
        case 2:
            updateID();
            break;
        case 3:
            updateDescription();
            break;
        case 4:
            updateAuthour();
            break;
        case 5:
            updatePrice();
            break;
        case 6:
            updateQuantity();
            break;
        case 7:
            updateCatergory();
            break;
        case 8:
            updateAvailability();
            break;
        case 0:
            return;
        default:
            cout << "Please enter a valid option" << endl;
            break;
        }
    } while (option != 0);
}

void viewsales()
{
    int total;
    int choice;
    do
    {
        cout << "************************************ Sales Menu *********************************************" << endl;
        cout << "\n\n\t\t1. Total Sales \n\n\t\t2. Back \n" << endl;
        do
        {
            error = 0;
            cout << " Enter option: ";
            cin >> choice;
            if (cin.fail())
            {
                cout << "Please enter a valid option" << endl;
                error = 1;
                cin.clear();
                cin.ignore(50, '\n');
            }
        } while (error == 1);

        switch (choice)
        {
        case 1:
            for (int i = 0; i < 20; i++)
            {
                total = total + (b[i].Price * b[i].quantity);
            }
            SetConsoleTextAttribute(color, 15);
            cout << "Total Sales: " << total << endl;
            break;
        case 2:
            return;
        default:
            cout << "Please enter a valid option" << endl;
            break;
        }
    } while (choice != 0);
}

void addbook()
{
    int exist;
    int count;
    for (int i = 0; i < 20; i++)
    {
        if (b[i].name == "")
        {
            cout << "Enter the name of the book: ";
            cin.ignore();
            getline(cin, b[i].name);
            cout << "Enter the description of the book: ";
            getline(cin, b[i].Description);
            cout << "Enter the authour of the book: ";
            getline(cin, b[i].Authour);
            cout << "Enter the ID of the book: ";
            cin >> b[i].ID;
            cout << "Enter the price of the book: ";
            cin >> b[i].Price;
            cout << "Enter the quantity: ";
            cin >> b[i].quantity;
            cout << "Enter the catergory: ";
            cin.ignore();
            getline(cin, b[i].catergory);
            cout << "Enter the availability: ";
            getline(cin, b[i].availability);
            exist = 1;
            count = i;
            break;
        }
    }
    if (exist == 1)
    {
        SetConsoleTextAttribute(color, 2);
        cout << "\nBook added successfully!\n" << endl;
    }
    else
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nNo more space for books!\n" << endl;
    }
}

void searchingname()
{
    string searchname;
    int found = 0;

    cout << "Enter the name of the book you want to search: ";
    cin.ignore();
    getline(cin, searchname);

    for (int i = 0; i < 20; i++)
    {
        if (b[i].name == searchname)
        {
            displaybook(i);
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nBook not found!\n" << endl;
    }
}

void searchingID()
{
    int searchID;
    int found = 0;

    cout << "Enter the ID of the book you want to search: ";
    cin >> searchID;

    for (int i = 0; i < 20; i++)
    {
        if (b[i].ID == searchID)
        {
            displaybook(i);
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nBook not found!\n" << endl;
    }
}

void displayallbooks()
{
    cout << "************************************ List of Books *********************************************" << endl;
    for (int i = 0; i < 20; i++)
    {
        if (b[i].name != "")
        {
            displaybook(i);
        }
    }
}

void displaybook(int index)
{
    cout << "\nName: " << b[index].name << endl;
    cout << "Description: " << b[index].Description << endl;
    cout << "Authour: " << b[index].Authour << endl;
    cout << "ID: " << b[index].ID << endl;
    cout << "Price: " << b[index].Price << endl;
    cout << "Quantity: " << b[index].quantity << endl;
    cout << "Catergory: " << b[index].catergory << endl;
    cout << "Availability: " << b[index].availability << endl;
}

void updatename()
{
    string searchname;
    int found = 0;

    cout << "Enter the name of the book you want to update: ";
    cin.ignore();
    getline(cin, searchname);

    for (int i = 0; i < 20; i++)
    {
        if (b[i].name == searchname)
        {
            cout << "Enter the new name: ";
            getline(cin, b[i].name);
            SetConsoleTextAttribute(color, 2);
            cout << "\nBook name updated successfully!\n" << endl;
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nBook not found!\n" << endl;
    }
}

void updateID()
{
    int searchID;
    int found = 0;

    cout << "Enter the ID of the book you want to update: ";
    cin >> searchID;

    for (int i = 0; i < 20; i++)
    {
        if (b[i].ID == searchID)
        {
            cout << "Enter the new ID: ";
            cin >> b[i].ID;
            SetConsoleTextAttribute(color, 2);
            cout << "\nBook ID updated successfully!\n" << endl;
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nBook not found!\n" << endl;
    }
}

void updateDescription()
{
    string searchname;
    int found = 0;

    cout << "Enter the name of the book you want to update: ";
    cin.ignore();
    getline(cin, searchname);

    for (int i = 0; i < 20; i++)
    {
        if (b[i].name == searchname)
        {
            cout << "Enter the new Description: ";
            getline(cin, b[i].Description);
            SetConsoleTextAttribute(color, 2);
            cout << "\nBook Description updated successfully!\n" << endl;
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nBook not found!\n" << endl;
    }
}

void updateAuthour()
{
    string searchname;
    int found = 0;

    cout << "Enter the name of the book you want to update: ";
    cin.ignore();
    getline(cin, searchname);

    for (int i = 0; i < 20; i++)
    {
        if (b[i].name == searchname)
        {
            cout << "Enter the new Authour: ";
            getline(cin, b[i].Authour);
            SetConsoleTextAttribute(color, 2);
            cout << "\nBook Authour updated successfully!\n" << endl;
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nBook not found!\n" << endl;
    }
}

void updatePrice()
{
    int searchID;
    int found = 0;

    cout << "Enter the ID of the book you want to update: ";
    cin >> searchID;

    for (int i = 0; i < 20; i++)
    {
        if (b[i].ID == searchID)
        {
            cout << "Enter the new Price: ";
            cin >> b[i].Price;
            SetConsoleTextAttribute(color, 2);
            cout << "\nBook Price updated successfully!\n" << endl;
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nBook not found!\n" << endl;
    }
}

void updateQuantity()
{
    int searchID;
    int found = 0;

    cout << "Enter the ID of the book you want to update: ";
    cin >> searchID;

    for (int i = 0; i < 20; i++)
    {
        if (b[i].ID == searchID)
        {
            cout << "Enter the new Quantity: ";
            cin >> b[i].quantity;
            SetConsoleTextAttribute(color, 2);
            cout << "\nBook Quantity updated successfully!\n" << endl;
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nBook not found!\n" << endl;
    }
}

void updateCatergory()
{
    string searchname;
    int found = 0;

    cout << "Enter the name of the book you want to update: ";
    cin.ignore();
    getline(cin, searchname);

    for (int i = 0; i < 20; i++)
    {
        if (b[i].name == searchname)
        {
            cout << "Enter the new Catergory: ";
            getline(cin, b[i].catergory);
            SetConsoleTextAttribute(color, 2);
            cout << "\nBook Catergory updated successfully!\n" << endl;
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nBook not found!\n" << endl;
    }
}

void updateAvailability()
{
    string searchname;
    int found = 0;

    cout << "Enter the name of the book you want to update: ";
    cin.ignore();
    getline(cin, searchname);

    for (int i = 0; i < 20; i++)
    {
        if (b[i].name == searchname)
        {
            cout << "Enter the new Availability: ";
            getline(cin, b[i].availability);
            SetConsoleTextAttribute(color, 2);
            cout << "\nBook Availability updated successfully!\n" << endl;
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        SetConsoleTextAttribute(color, 12);
        cout << "\nBook not found!\n" << endl;
    }
}

void logout()
{
    main();
}

void logoutstaff()
{
    main();
}
