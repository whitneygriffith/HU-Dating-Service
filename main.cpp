#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class addressType
{
  public:
    string streetAddressNum;
    string streetName;
    string streetType;
    string city;
    string stateInitials;
    string zipCode;
    string address;
    addressType();
    //Might not need this
    string getFullAddress();
};

addressType::addressType()
{
    string streetAddressNum = "";
    string streetName = "";
    string streetType = "";
    string city = "";
    string stateInitials = "";
    string zipCode = "";
    address = getFullAddress();
    return;
}

string addressType::getFullAddress()
{
    string fullAddress = streetAddressNum + " " + streetName + " " + streetType + " " + city + " " + stateInitials + " " + zipCode;
    return fullAddress;
}

class contact_infoType
{
  public:
    string get_emailAddress;
    contact_infoType();

  private:
    string emailAddress;
    string phoneNumber;
    string userName;
    string password;
};

contact_infoType::contact_infoType()
{
    emailAddress = "";
    phoneNumber = "";
    userName = "";
    password = "";
    get_emailAddress = "";
}


class personType
{
  public:
    //separate last name and first name
    string lastName;
    string firstName;
    //helper function to combine full name
    string fullName();
    //stores full name
    string name;
    string personNum;
    string personID;
    addressType address;
    string gender;
    personType();
    string getInterest1() const;
    void setInterest1(string input1);
    string getInterest2() const;
    void setInterest2(string input2);

  private:
    string interest1;
    string interest2;
    contact_infoType contact_Info;
};

personType::personType()
{
    string name = "";
    string firstName = "";
    string lastName = "";
    string person_no = "";
    addressType address;
    string gender = "";
    string personID = "";
}

string personType::fullName()
{
    lastName = lastName.substr(0, lastName.length() - 1);

    name = firstName + " " + lastName;
    return name;
}

void personType::setInterest1(string input1)
{
    interest1 = input1;
}

string personType::getInterest1() const
{
    return interest1;
}

void personType::setInterest2(string input2)
{
    interest2 = input2;
}

string personType::getInterest2() const
{
    return interest2;
}

class membershipType : public personType
{
  public:
    char membership_type;
    char membership_status;
    membershipType();                       // 1st constructor
    membershipType(char type, char status); // 2nd constructor
    void print_member_type();
};

membershipType::membershipType()
{
    membership_type = ' ';
    membership_status = ' ';
}

membershipType::membershipType(char type, char status)
{
    membership_type = type;
    membership_status = status;
}

void membershipType::print_member_type()
{

    cout << personNum << ". " << fullName() << endl;
    cout << "Personal ID: " << personID << endl;
    cout << "Membership Status: " << membership_status << endl;
    cout << "Membership Type: " << membership_type << endl;
    cout << "Interests: " << getInterest1() << ", " << getInterest2() << endl;
    cout << address.getFullAddress() << endl
         << endl;
}

//NODE for the linked list
struct NODE
{
    NODE *next;
    NODE *previous;
    membershipType member;
};

void print(NODE *members)
{

   NODE *current = members;
   int count = 1;

    while (current != NULL)
    {

        cout << count << ". " << current->member.fullName() << endl;
        cout << "Personal ID: " << current->member.personID<< endl;
        cout << "Membership Status: " << current->member.membership_status << endl;
        cout << "Membership Type: " << current->member.membership_type << endl;
        cout << "Interests: " << current->member.getInterest1() << ", " << current->member.getInterest2() << endl;
        cout << current->member.address.getFullAddress() << endl;
        cout << endl;
        current = current->next;
        ++ count;
    }
}


int main()
{

   //temporary memberType
   membershipType member_tmp;
   NODE* head;

   string x, i1, i2;

   int count = 0;

   ifstream myfile;
   myfile.open("infile.txt");
   for (int i = 0; i < 6; i++)
   {

       myfile >> member_tmp.lastName >> member_tmp.firstName >> member_tmp.personNum >> member_tmp.personID >> member_tmp.address.streetAddressNum >>
           member_tmp.address.streetName >> member_tmp.address.streetType >> member_tmp.address.city >> member_tmp.address.stateInitials >> member_tmp.address.zipCode >> member_tmp.gender;
       myfile >> i1 >> i2;
       member_tmp.setInterest1(i1);
       member_tmp.setInterest2(i2);
       myfile >> member_tmp.membership_type >> member_tmp.membership_status;

       if (i == 0)
       {
           head = new NODE;
           head->member = member_tmp;
           head->next = NULL;
       }

       else
       {

           NODE *newMember;
           newMember = new NODE;
           newMember->member = member_tmp;
           newMember->next = NULL;
           
           NODE *prev = NULL;
           NODE *current = head;


           //newMember is less than head so insert at beginning of list
           if (newMember->member.firstName < current->member.firstName)
           {
               NODE *temp = current;
               head = newMember;
               head->next = temp;
           }


           //quickly add at end of 1 member list if newMember is more than head
           else if (current->next == NULL && newMember->member.firstName > current->member.firstName)
           {
               current->next = newMember;
            }
        

            //newMember is not less than head so needs to be inserted somewhere AFTER head between two existing members
            else  {
                 while (current != NULL){

                    if (newMember->member.firstName > current->member.firstName)
                    {
                        //insert between list
                        if (current->next != NULL && newMember->member.firstName < current -> next ->member.firstName)
                        {

                            NODE *temp = current -> next;
                            current->next = newMember;
                            newMember ->next = temp;
                        }

                        //insert at end of list
                        if (current->next == NULL)
                        {
                            NODE *temp = current->next;
                            current->next = newMember;
                            newMember->next = temp;
                        }
                    }
                    current = current->next;
                }

            }
    

       }

    } // end of for loop
    print(head);
    myfile.close();


    system("pause");
    return 0;
}

/*

Output

1. Claude Claire
Personal ID: 2311
Membership Status: 1
Membership Type: 1
Interests: cooking, facebook
66 32nd Street Woodbridge, VA 44040

2. Francis Jerry
Personal ID: 6666
Membership Status: 1
Membership Type: 1
Interests: movies, roadtrips
2345 6th Street Woodbridge, VA 44040

3. Jill Herold
Personal ID: 2234
Membership Status: 2
Membership Type: 1
Interests: yoga, facebook
123 Main St. Washington, DC 20019

4. Stan Jackson
Personal ID: 3748
Membership Status: 4
Membership Type: 2
Interests: sports, movies
12 Douglas Ave. Baltimore, MD 30229

5. Stanley Smith
Personal ID: 3456
Membership Status: 1
Membership Type: 2
Interests: movies, dining
56 D Street Baltimore, MD 30229

6. Wilson Joan
Personal ID: 1234
Membership Status: 3
Membership Type: 2
Interests: romance, dining
12 Georgia Ave. Washington, DC 20019

*/