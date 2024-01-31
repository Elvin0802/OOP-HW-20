#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

#include "Contact Database.h"


void main()
{
	DataBase* db = new DataBase();

TRY1:
	try
	{
		db->ReadAllContacts("ContactsFile.txt");
	}
	catch (exception& ex)
	{
		cout << endl << ex.what() << endl;
		system("pause");
		goto TRY1;
	}

	string menu1 = R"(
				[ 1 ] --> Add New Contact
				[ 2 ] --> Delete Contacts By Name
				[ 3 ] --> Delete All Contacts
				[ 4 ] --> Delete Contact By Phone Number
				[ 5 ] --> Show All Contacts
				[ 6 ] --> Show Contacts By Name
				[ 7 ] --> Show Contact By Phone Number
				[ 8 ] --> Update Contact By Phone Number
				[ 0 ] --> Exit

)";
	int sechim1;

TRY2:
	try
	{
		while (true)
		{
			system("cls");
			cout << menu1 << "Menudan Sechim Edin : ";
			cin >> sechim1;

			if (sechim1 == 1)
			{
				cin.ignore();
				string name, phoneNumber, relation;
				cout << "\nKontaktin Adini Daxil Edin : "; getline(cin, name);
				cout << "\nKontaktin Telefon Nomresini Daxil Edin : "; getline(cin, phoneNumber);
				cout << "\nKontaktin Sizinle Olan Munasibetini Daxil Edin : "; getline(cin, relation);

				db->Add_Contact(new Contact(name, phoneNumber, relation));
				cout << "\nKontakt Elave Olundu.\n\n"; system("pause");
			}
			else if (sechim1 == 2)
			{
				cin.ignore();
				string name;
				cout << "\nSilinecek Kontaktlarin Adini Daxil Edin : "; getline(cin, name);

				size_t count = db->CountOfName(name);
				if (count > 0)
				{
					db->Delete_ContactsByName(name);
					cout << "\n" << count << " Kontakt Silindi.\n\n";
				}
				else
					cout << "\nVerilmish Ad-da Kontakt Tapilmadi.\n\n";
				system("pause");
			}
			else if (sechim1 == 3)
			{
				db->Delete_AllContacts();
				cout << "\nButun Kontaktlar Silindi.\n\n"; system("pause");
			}
			else if (sechim1 == 4)
			{
				cin.ignore();
				string phoneNumber;
				cout << "\nSilinecek Kontaktin Tel Nomresini Daxil Edin : "; getline(cin, phoneNumber);

				if (db->CheckPhoneNumber(phoneNumber))
				{
					db->Delete_ContactByPhoneNumber(phoneNumber);
					cout << "\nKontakt Silindi.\n";
				}
				else
					cout << "\nVerilmish Tel Nomreli Kontakt Tapilmadi.\n";
				system("pause");
			}
			else if (sechim1 == 5)
			{
				db->Show_AllContacts();
				system("pause");
			}
			else if (sechim1 == 6)
			{
				cin.ignore();
				string name;
				cout << "\nGosterilecek Kontaktlarin Adini Daxil Edin : "; getline(cin, name);

				size_t count = db->CountOfName(name);
				if (count > 0)
					db->Show_ContactsByName(name);
				else
					cout << "\nVerilmish Ad-da Kontakt Tapilmadi.\n\n";
				system("pause");
			}
			else if (sechim1 == 7)
			{
				cin.ignore();
				string phoneNumber;
				cout << "\nGosterilecek Kontaktin Tel Nomresini Daxil Edin : "; getline(cin, phoneNumber);

				if (db->CheckPhoneNumber(phoneNumber))
					db->Show_ContactByPhoneNumber(phoneNumber);
				else
					cout << "\nVerilmish Tel Nomreli Kontakt Tapilmadi.\n";
				system("pause");
			}
			else if (sechim1 == 8)
			{
				cin.ignore();
				string phoneNumber;
				cout << "\nGuncellenecek Kontaktin Tel Nomresini Daxil Edin : "; getline(cin, phoneNumber);

				if (db->CheckPhoneNumber(phoneNumber))
				{
					string menu2 = R"(

				[ 1 ] --> Change Name
				[ 2 ] --> Change Phone Number
				[ 3 ] --> Change Relation
				[ 0 ] --> Exit

)";
					auto update = db->GetContact(phoneNumber);
					int sechim3;

					while (true)
					{
						system("cls");
						cout << menu2 << "\nMenudan Sechim Edin : ";
						cin >> sechim3;

						if (sechim3 == 1)
						{
							cin.ignore();
							string name;
							cout << "\nYeni Ad-i Daxil Edin : "; getline(cin, name);

							update->Set_Name(name);

							cout << "\nAd Ugurla Deyishdi.\n\n";
							system("pause");
						}
						else if (sechim3 == 2)
						{
							cin.ignore();
							string pNum;
							cout << "\nYeni Tel Nomresini Daxil Edin : "; getline(cin, pNum);

							update->Set_PhoneNumber(pNum);

							cout << "\nTel Nomresi Ugurla Deyishdi.\n\n";
							system("pause");
						}
						else if (sechim3 == 3)
						{
							cin.ignore();
							string relation;
							cout << "\nYeni Munasibeti Daxil Edin : "; getline(cin, relation);
							update->Set_Relation(relation);

							cout << "\nMunasibet Ugurla Deyishdi.\n\n";
							system("pause");
						}
						else if (sechim3 == 0)
						{
							break;
						}
						else
						{
							cout << "\nMenudan Duzgun Sechim Edin.\n\n";
							system("pause");
						}
					}
				}
				else
					cout << "\nVerilmish Tel Nomreli Kontakt Tapilmadi.\n";
				system("pause");
			}
			else if (sechim1 == 0)
			{
				db->WriteAllContacts("ContactsFile.txt");
				cout << "\nExiting...\n";
				break;
			}
			else
			{
				cout << "\nMenudan Duzgun Sechim Edin !\n";
				system("pause");
			}
		}
	}
	catch (exception& ex)
	{
		cout << endl << ex.what() << endl;
		system("pause");
		goto TRY2;
	}
}