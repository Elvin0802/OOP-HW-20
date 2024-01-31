#pragma once


class Contact
{
	string _name = "";
	string _phoneNumber = "";
	string _relation = "";

public:

	// Constructors
	Contact(string Name, string PhoneNumber, string Relation)
	{
		this->Set_Name(Name);
		this->Set_PhoneNumber(PhoneNumber);
		this->Set_Relation(Relation);
	}
	Contact(const Contact& other)
		: Contact(other._name, other._phoneNumber, other._relation) {}

	// Copy assigment operator
	Contact& operator=(const Contact& other)
	{
		this->_name = other._name;
		this->_phoneNumber = other._phoneNumber;
		this->_relation = other._relation;
		return (*this);
	}

	// Filed Set Methods 
	void Set_Name(string Name)
	{
		if (Name.length() < 2)
		{
			throw length_error("Adin Uzunluqu 2 den Chox Olmalidir.");
		}
		this->_name = Name;
	}
	void Set_PhoneNumber(string PhoneNumber)
	{
		if (PhoneNumber.length() < 8)
		{
			throw length_error("Telefon Nomresi Uzunluqu 8-den Chox Olmalidir.");
		}
		this->_phoneNumber = PhoneNumber;
	}
	void Set_Relation(string Relation)
	{
		if (Relation.length() < 2)
		{
			throw length_error("Munasibetin Uzunluqu 2 den Chox Olmalidir.");
		}
		this->_relation = Relation;
	}

	// Filed Get Methods 
	string Get_Name() const { return _name; }
	string Get_PhoneNumber() const { return _phoneNumber; }
	string Get_Relation() const { return _relation; }

	// Other Methods
	void Show()
	{
		cout << "\nContact Name : " << this->_name;
		cout << "\nContact Phone Number : " << this->_phoneNumber;
		cout << "\nContact Relation : " << this->_relation << endl;
	}
};

class DataBase
{
	Contact** _contacts;
	size_t _count;

public:

	// Constructors
	DataBase()
	{
		this->_contacts = nullptr;
		this->_count = 0;
	}
	DataBase(const DataBase& db)
	{
		this->_count = db._count;
		this->_contacts = new Contact * [db._count];
		for (size_t i = 0; i < db._count; i++)
			_contacts[i] = new Contact(*(db._contacts[i]));
	}
	DataBase& operator=(const DataBase& db)
	{
		this->Delete_AllContacts();

		this->_count = db._count;
		this->_contacts = new Contact * [db._count];
		for (size_t i = 0; i < db._count; i++)
			_contacts[i] = new Contact(*(db._contacts[i]));

		return (*this);
	}

	// Filed Get Methods 
	auto GetCount()const { return _count; }
	auto GetContacts()const { return _contacts; }

	Contact* GetContact(string phoneNumber) const
	{
		for (size_t i = 0; i < _count; i++)
			if (_contacts[i]->Get_PhoneNumber() == phoneNumber)
				return _contacts[i];

		return nullptr;
	}

	// Other Methods

	void Show_AllContacts()
	{
		cout << "\n\t>>>>  All Contacts  <<<<\n";
		for (size_t x = 0; x < _count; x++)
		{
			_contacts[x]->Show();
			cout << "-----------------------------------------\n";
		}
	}

	void Show_ContactsByName(string name) const
	{
		for (size_t i = 0; i < _count; i++)
		{
			if (_contacts[i]->Get_Name() == name)
			{
				_contacts[i]->Show();
				cout << "-----------------------------------------\n";
			}
		}
	}

	void Show_ContactByPhoneNumber(string phoneNumber) const
	{
		if (CheckPhoneNumber(phoneNumber))
		{
			for (size_t i = 0; i < _count; i++)
			{
				if (_contacts[i]->Get_PhoneNumber() == phoneNumber)
				{
					_contacts[i]->Show();
					cout << "-----------------------------------------\n";
				}
			}
		}
	}

	bool CheckPhoneNumber(string pNumber)const
	{
		for (size_t i = 0; i < _count; i++)
		{
			if (pNumber == _contacts[i]->Get_PhoneNumber())
				return true;
		}
		return false;
	}

	size_t CountOfName(string name) const
	{
		size_t nCount = 0;

		for (size_t i = 0; i < _count; i++)
			if (_contacts[i]->Get_Name() == name)
				nCount++;
		return nCount;
	}

	void Add_Contact(const Contact* newContact)
	{
		if (_count == 0)
		{
			_contacts = new Contact * [1];
			_contacts[_count++] = new Contact(*newContact);
			return;
		}
		auto Contacts = new Contact * [_count + 1];

		for (size_t i = 0; i < _count; i++)
			Contacts[i] = _contacts[i];

		Contacts[_count++] = new Contact(*newContact);
		delete[] _contacts;
		_contacts = Contacts;
	}

	void Delete_ContactsByName(const string name)
	{
		size_t nameCount = CountOfName(name);

		if (nameCount > 0)
		{
			auto Contacts = new Contact * [_count - nameCount];
			size_t cIndex = 0;

			for (size_t i = 0; i < _count; i++)
			{
				if (_contacts[i]->Get_Name() == name)
				{
					delete _contacts[i];
					continue;
				}
				Contacts[cIndex++] = _contacts[i];
			}
			_count -= nameCount;
			delete[] _contacts;
			_contacts = Contacts;
		}
	}

	void Delete_ContactByPhoneNumber(const string pNumber)
	{
		if (!CheckPhoneNumber(pNumber))
			return;

		auto Contacts = new Contact * [_count - 1];
		size_t cIndex = 0;

		for (size_t i = 0; i < _count; i++)
		{
			if (_contacts[i]->Get_PhoneNumber() == pNumber)
			{
				delete _contacts[i];
				continue;
			}
			Contacts[cIndex++] = _contacts[i];
		}
		_count--;
		delete[] _contacts;
		_contacts = Contacts;
	}

	void Delete_AllContacts()
	{
		if (_contacts != nullptr)
		{
			for (size_t i = 0; i < _count; i++) {
				if (_contacts[i] != nullptr)
					delete _contacts[i];
			}

			delete[] _contacts;
			_contacts = nullptr;
			_count = 0;
		}
	}


	// File Read and Write Methods

	void ReadAllContacts(string dest)
	{
		ifstream file(dest, ios::in);

		if (!file.is_open())
		{
			cout << "\nFile is not opened.\n" << endl; return;
		}

		string name = "", phoneNumber = "", relation = "", index = "";

		this->Delete_AllContacts();

		while (!file.eof())
		{
			file >> index;

			if (!file.eof())
			{
				file >> name >> phoneNumber >> relation;

				this->Add_Contact(new Contact(name, phoneNumber, relation));
			}
		}
		file.close();
	}

	void WriteAllContacts(string dest)
	{
		ofstream file(dest, ios::out);

		if (!file.is_open())
		{
			cout << "\nFile is not opened.\n" << endl; return;
		}

		for (size_t x = 0; x < _count; x++)
		{
			if (_contacts[x] != nullptr)
			{
				file << (x + 1) << ". "
					<< _contacts[x]->Get_Name() << " "
					<< _contacts[x]->Get_PhoneNumber() << " "
					<< _contacts[x]->Get_Relation() << "\n";
			}
		}
		file.close();
	}

	// Destructor
	~DataBase() { this->Delete_AllContacts(); }
};