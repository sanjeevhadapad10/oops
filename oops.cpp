#include <iostream>
#include <string>
#include <limits>
using namespace std;

/* ================= USER-DEFINED EXCEPTION ================= */
class ServiceException {};

/* ================= BASE ABSTRACT CLASS ================= */
class PublicService
{
protected:
    string serviceListName;
    string services[5];
    int charges[5];
    bool active[5];
    int count;

public:
    static int totalServiceLists;     // STATIC DATA MEMBER

    // DEFAULT ARGUMENT
    PublicService(string name = "Smart City Services")
    {
        serviceListName = name;
        count = 0;
        totalServiceLists++;
        for (int i = 0; i < 5; i++)
            active[i] = false;
    }

    // PURE VIRTUAL FUNCTION → ABSTRACT CLASS
    virtual void serviceMode() = 0;

    // INLINE FUNCTION
    inline int calculateGST(int amount)
    {
        return amount * 0.18;
    }

    // FUNCTION OVERLOADING
    void addService(string service, int charge)
    {
        if (count >= 5)
            throw ServiceException();

        services[count] = service;
        charges[count] = charge;
        active[count] = false;
        count++;
    }

    void addService(string service, int charge, bool isActive)
    {
        if (count >= 5)
            throw ServiceException();

        services[count] = service;
        charges[count] = charge;
        active[count] = isActive;
        count++;
    }

    // this POINTER
    void renameServiceList(string name)
    {
        this->serviceListName = name;
    }

    // RETURNING VALUE
    int totalCharge() const
    {
        int total = 0;
        for (int i = 0; i < count; i++)
            total += charges[i];
        return total;
    }

    // OPERATOR OVERLOADING
    bool operator>(PublicService &p)
    {
        return totalCharge() > p.totalCharge();
    }

    // DATA CONVERSION OPERATOR
    operator int()
    {
        return totalCharge();
    }

    // FRIEND FUNCTION
    friend void showTotalServiceLists();

    virtual void display()
    {
        cout << "\nService List: " << serviceListName << "\n";
        for (int i = 0; i < count; i++)
        {
            cout << i + 1 << ". " << services[i]
                 << " - Rs." << charges[i];
            if (active[i])
                cout << " [Active]";
            cout << endl;
        }
    }

    void activateService(int index)
    {
        if (index < 0 || index >= count)
            throw ServiceException();
        active[index] = true;
    }

    virtual ~PublicService() {}
};

int PublicService::totalServiceLists = 0;

/* ================= INHERITANCE ================= */
class UtilityService : public PublicService
{
public:
    UtilityService(string name = "Utility Services") : PublicService(name) {}

    void serviceMode() override
    {
        cout << "Utility Mode: Water, Electricity, Gas\n";
    }
};

class TransportService : public UtilityService
{
public:
    TransportService(string name = "Transport Services") : UtilityService(name) {}

    void serviceMode() override
    {
        cout << "Transport Mode: Bus, Metro, Smart Parking\n";
    }
};

/* ================= FRIEND FUNCTION ================= */
void showTotalServiceLists()
{
    cout << "\nTotal Service Lists Created: " << PublicService::totalServiceLists << endl;
}

/* ================= REFERENCE ARGUMENT ================= */
void discountCharge(int &charge)
{
    charge -= 100;
}

/* ================= RECURSION ================= */
int factorial(int n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

/* ================= ARRAY PASSED TO FUNCTION ================= */
void showServices(string arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}

/* ================= RETURNING OBJECT ================= */
UtilityService createSampleService()
{
    UtilityService s("Sample Smart City Services");
    return s;
}

/* ================= MULTIDIMENSIONAL ARRAY ================= */
void zoneMatrix()
{
    int zones[2][3] = {{1, 1, 0}, {1, 0, 1}};
    cout << "\nCity Zone Service Matrix:\n";
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << zones[i][j] << " ";
        cout << endl;
    }
}

/* ================= MAIN FUNCTION ================= */
int main()
{
    // POINTERS TO OBJECTS
    PublicService *utility = new UtilityService();
    PublicService *transport = new TransportService();

    int choice, charge, serviceNo;
    char listChoice;
    string serviceName, newName;

    do
    {
        cout << "\n===== SMART CITY PUBLIC SERVICE SYSTEM =====";
        cout << "\n1. Utility Mode";
        cout << "\n2. Transport Mode";
        cout << "\n3. Add Service";
        cout << "\n4. Display Services";
        cout << "\n5. Compare Total Charges";
        cout << "\n6. Activate Service";
        cout << "\n7. Rename Service List";
        cout << "\n8. Show Zone Matrix";
        cout << "\n9. Show Total Service Lists";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try
        {
            switch (choice)
            {
            case 1:
                utility->serviceMode();
                break;

            case 2:
                transport->serviceMode();
                break;

            case 3:
                cout << "Add to which list? (U/T): ";
                cin >> listChoice;
                cin.ignore();

                cout << "Service Name: ";
                getline(cin, serviceName);
                cout << "Charge: ";
                cin >> charge;

                discountCharge(charge);

                if (listChoice == 'U' || listChoice == 'u')
                    utility->addService(serviceName, charge);
                else
                    transport->addService(serviceName, charge);
                break;

            case 4:
                utility->display();
                transport->display();
                break;

            case 5:
                if (*transport > *utility)
                    cout << "Transport services cost more\n";
                else
                    cout << "Utility services cost more\n";
                break;

            case 6:
                cout << "Activate from which list? (U/T): ";
                cin >> listChoice;
                cout << "Service number: ";
                cin >> serviceNo;

                if (listChoice == 'U' || listChoice == 'u')
                    utility->activateService(serviceNo - 1);
                else
                    transport->activateService(serviceNo - 1);
                cout << "Service activated successfully\n";
                break;

            case 7:
                cout << "New name: ";
                getline(cin, newName);
                utility->renameServiceList(newName);
                break;

            case 8:
                zoneMatrix();
                break;

            case 9:
                showTotalServiceLists();
                cout << "Factorial demo (5): " << factorial(5) << endl;
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
            }
        }
        catch (ServiceException)
        {
            cout << "Error: Operation not allowed\n";
        }

    } while (choice != 0);

    delete utility;
    delete transport;
    return 0;
}