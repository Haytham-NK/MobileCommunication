#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

//Базовый класс тариф
class Tariff
{
protected:
	int price;
	string name;

public:
	Tariff(const string& name, int price) : name(name), price(price) {}// Конструктор класса

	virtual string display() // Вывод тарифа (виртуальная функция)
	{
		string result = "Тариф: " + name + ", Цена: " + to_string(price);
		return result;
	}

	string displayName() // Вывод имени
	{
		return name;
	}

	double displayPrice() // Вывод цены
	{
		return price;
	}

	void setPrice(int newPrice) // Установка цены
	{
		price = newPrice;
	}

	void setName(const string& newName) // Установка Имени
	{
		name = newName;
	}
};

// Безлимитный тариф
class UnlimitedTariff : public Tariff
{
private:
	string unlimitedService;

public:
	UnlimitedTariff(const string& name, int price, const string& unlimitedService)// Конструктор класса
		: Tariff(name, price), unlimitedService(unlimitedService) {}

	string display() override // Вывод тарифа
	{
		string result = "Тариф: " + name + ", Цена: " + to_string(price) + ", Безлимитные услуги: " + unlimitedService;
		return result;
	}
};

//Тариф на день
class DailyTariff : public Tariff
{
private:
	int days;

public:
	DailyTariff(const string& name, int price, const int days)// Конструктор класса
		: Tariff(name, price), days(days) {}

	string display() override // Вывод тарифа
	{
		std::string result = "Тариф: " + name + ", Цена: " + to_string(price) + ", Дней: " + to_string(days);
		return result;
	}
};

//Студенческий тариф
class StudentTariff : public Tariff
{
private:
	int discount;

public:
	StudentTariff(const string& name, int price, const int discount)// Конструктор класса
		: Tariff(name, price), discount(discount) {}

	string display() override // Вывод тарифа
	{
		string result = "Тариф: " + name + ", Цена: " + to_string(price) + ", Скидка: " + to_string(discount) + "%";
		return result;
	}
};
//Клиент
class Client
{
private:
	string name;
	string phoneNumber;
	Tariff* tariff;

public:
	Client(const std::string& name, const string& phoneNumber, Tariff* tariff) // Конструктор класса
		: name(name), phoneNumber(phoneNumber), tariff(tariff) {}

	~Client() //дестркуктор класса
	{
		delete tariff;
	}

	string display() //вывод информации о клиенте
	{
		std::string result = "Имя клиента: " + name + ", Номер клиента: " + phoneNumber + ", " + tariff->display();
		return result;
	}
};
//Компания
class Company
{
private:
	vector<Tariff*> tariffs;
	vector<Client*> clients;

public:
	~Company() // Деструктор класса
	{
		for (auto tariff : tariffs)
		{
			delete tariff;
		}

		for (auto client : clients)
		{
			delete client;
		}
	}

	string displayTariffs() const // Вывод списка тарифов
	{
		std::string output;
		int i = 1;
		for (const auto& tariff : tariffs) {
			output += i + "." + tariff->display() + "\n";
		}
		return output;
	}

	string displayClients() const // Вывод списка клиентов
	{
		string output;
		int i = 1;
		for (const auto& client : clients)
		{
			output += i + "." + client->display() + "\n";
		}
		return output;
	}

	void addTariff(Tariff* tariff) // Добавить тариф
	{
		tariffs.push_back(tariff);
	}

	void removeTariff(int index) // Удалить тариф
	{
		if (index >= 0 && index < tariffs.size())
		{
			delete tariffs[index];
			tariffs.erase(tariffs.begin() + index); // удаление 
		}
	}

	void addClient(Client* client) // Добавить клиента
	{
		clients.push_back(client);
	}

	void removeClient(int index) // Удалить клиента
	{
		if (index >= 0 && index < clients.size())
		{
			delete clients[index];
			clients.erase(clients.begin() + index);	// удаление 
		}
	}

	int getTotalClientsCount() const // Вывести количество клиентов
	{
		return clients.size();
	}

	int getTotalTariffsCount() // Вывести количество тарифов
	{
		return tariffs.size();
	}

	void sortTariffsByPrice() // Отсортировать по цене тарифы
	{
		sort(tariffs.begin(), tariffs.end(), [](Tariff* firstTariff, Tariff* secondTariff) {
			return firstTariff->display() < secondTariff->display();
			});
	}

	vector<Tariff*> findTariffsInRange(int minPrice, int maxPrice) const // Найти тариф по диапазону цены
	{
		std::vector<Tariff*> result; // Создание вектора с результатами
		for (const auto& tariff : tariffs) {
			if (tariff->displayPrice() >= minPrice && tariff->displayPrice() <= maxPrice) {
				result.push_back(tariff); // Добавление нового тарифа в список
			}
		}
		return result;
	}

	bool hasTariff(const std::string& tariffName) const // Проверка на наличие тарифа
	{
		for (const auto& tariff : tariffs) {
			if (tariff->displayName() == tariffName) {
				return true;
			}
		}
		return false;
	}
};

void displayMenu() { // Вывод меню
	cout << "Меню:" << endl;
	cout << "1. Просмотреть список тарифов компании." << endl;
	cout << "2. Добавить новый тариф." << endl;
	cout << "3. Удалить тариф." << endl;
	cout << "4. Просмотреть список клиентов компании." << endl;
	cout << "5. Добавить нового клиента." << endl;
	cout << "6. Удалить клиента." << endl;
	cout << "7. Посчитать общую численность клиентов." << endl;
	cout << "8. Отсортировать тарифы по цене." << endl;
	cout << "9. Найти тариф по заданному диапазону параметров." << endl;
	cout << "10. Выход из программы." << endl;
}

int main()
{
	Company company;
	setlocale(LC_ALL, "ru");
	int choice = 0;

	// Регулярные функции для проверки введённых данных
	regex phoneRegex(R"(\+7 \(\d{3}\) \d{3}-\d{4})");
	regex discountRegex("^(100|[0-9]{1,3})$");
	regex nameRegex("^[A-Za-zА-ЯЁа-яё]{2,30}$");
	regex indexRegex("[0-9]{1,5}$");
	regex priceRegex("^(100000|[0-9]{1,5})$");

	displayMenu();

	while (choice != 10)
	{
		std::cout << "\nВведите номер операции: ";
		cin >> choice;
		// пользователю предлагается ввести номер операции
		switch (choice) 
		{
			case 1: // Вывод списка тарифов
			{ 
				cout << "Список тарифов компании:\n";
				cout << company.displayTariffs();
				break;
			}
			case 2: // Добавление нового тарифа
			{
				int tariffType;
				while (true)
				{
					cout << "Выберите тип тарифа:\n";
					cout << "1. Безлимитный тариф.\n";
					cout << "2. Тариф на день.\n";
					cout << "3. Студенческий тариф.\n";
					cout << "Ваш выбор: ";
					cin >> tariffType;

					string name;
					string checkPrice;
					string checkDiscount;
					string unlimitedService;
					int price;
					
					if (tariffType == 1) {
						while (true)
						{
							cout << "Введите название тарифа: ";
							cin.ignore(); // игнорирование символа
							getline(cin, name); // ввод данных
							cout << "Введите цену тарифа: ";
							cin >> checkPrice;
							cout << "Введите безлимитные услуги: ";
							cin.ignore();
							getline(cin, unlimitedService);
							// проверка на правильность введённых данных
							if (regex_match(name, nameRegex) && regex_match(checkPrice, priceRegex) && regex_match(unlimitedService, nameRegex))
							{
								price = stoi(checkPrice);
								break;
							}
							else
							{
								cout << "Введены неверные данные.\n";
							}
						}
							company.addTariff(new UnlimitedTariff(name, price, unlimitedService)); // создание нового тарифа
						break;
					}
					else if (tariffType == 2) {
						int days;
						string checkDays;

						while (true)
						{
							cout << "Введите название тарифа: ";
							cin.ignore();
							getline(cin, name);
							cout << "Введите цену тарифа: ";
							cin >> checkPrice;;
							cout << "Введите количество дней: ";
							cin >> checkDays;

							if (regex_match(name, nameRegex) && regex_match(checkPrice, priceRegex) && regex_match(checkDays, indexRegex))
							{
								price = stoi(checkPrice); // перенос данных из переменной типа string в int
								days = stoi(checkDays);
								break;
							}
							else
							{
								cout << "Введены неверные данные.\n";
							}
						}
						company.addTariff(new DailyTariff(name, price, days));
						break;
					}
					else if (tariffType == 3) {
						int discount;
						while (true)
						{
							cout << "Введите название тарифа: ";
							cin.ignore();
							getline(cin, name);
							cout << "Введите цену тарифа: ";
							cin >> checkPrice;
							cout << "Введите скидку (%): ";
							cin >> checkDiscount;
							if (regex_match(name, nameRegex) && regex_match(checkPrice, priceRegex) && regex_match(checkDiscount, discountRegex))
							{
								price = stoi(checkPrice);
								discount = stoi(checkDiscount);
								break;
							}
							else
							{
								cout << "Введены неверные данные.\n";
							}
						}
						company.addTariff(new StudentTariff(name, price, discount));
						cout << "Тариф успешно создан!\n";
						break;
					}
					else {
						cout << "Неверный выбор типа тарифа.\n";
					}
				}
				cout << "Тариф успешно создан.\n";
				break;
			}
			case 3: // Удаление тарифа
			{
				int index;
				while (true)
				{
					cout << "Введите номер тарифа: ";
					cin >> index;
					if ((company.getTotalTariffsCount() - 1) >= index)
					{
						company.removeTariff(index - 1);
						cout << "Тариф успешно удалён.\n";
						break;
					}
					else
					{
						cout << "Неверный выбор тарифа.\n";
					}
				}
				break;
			}
			case 4: // Вывод списка клиентов
			{
				cout << "Список клиентов компании:\n";
				cout << company.displayClients();
				break;
			}
			case 5: // Добавление нового пользователя
			{
				string name, phoneNumber;
				string tariffName;
				string checkPrice;
				int tariffPrice;
				bool haveTariff = false;
				
				cin.ignore();
				while (true)
				{
					cout << "Введите имя клиента: ";
					getline(cin, name);

					if (regex_match(name, nameRegex))
					{
						break;
					}
					else
					{
						cout << "Неверно введено имя.\n";
					}
				}
				while (true)
				{
					cout << "Введите номер телефона клиента в формате +7 (XXX) XXX-XXXX: ";
					getline(cin, phoneNumber);

					if (regex_match(phoneNumber, phoneRegex))
					{
						break;
					}
					else
					{
						cout << "Неверно введен номер телефона.\n";
					}
				}
				
				while (true)
				{
					cout << "Введите название тарифа: ";
					getline(cin, tariffName);

					if (company.hasTariff(tariffName) || tariffName == "")
					{
						if (tariffName == "")
						{
							haveTariff = false;
						}
						else
						{
							haveTariff = true;
						}
						break;
					}
					else
					{
						cout << "Неверно введено имя тарифа.\n";
					}
				}
				while (true)
				{
					if (haveTariff == false)
					{
						Tariff* tariff = new Tariff("absent", 0);
						company.addClient(new Client(name, phoneNumber, tariff));
						break;
					}
					else
					{
						cout << "Введите цену тарифа: ";
						cin >> checkPrice;

						if (regex_match(checkPrice, priceRegex))
						{
							tariffPrice = stoi(checkPrice);
							Tariff* tariff = new Tariff(tariffName, tariffPrice);
							company.addClient(new Client(name, phoneNumber, tariff));
							break;
						}
						else
						{
							cout << "Неверно введено имя тарифа.\n";
						}
					}
				}
				cout << "Клиент успешно добавлен!";
				break;
			}
			case 6: // Удаление клиента
			{
				string checkIndex;
				int index;
				while (true)
				{
					cout << company.displayClients();
					cout << "Введите номер клиента: ";
					cin >> checkIndex;
					if (regex_match(checkIndex, indexRegex))
					{
						index = stoi(checkIndex);
						break;
					}
					else
					{
						cout << "Неверный выбор клиента.\n";
					}
				}
				company.removeClient(index - 1);
				cout << "Клиент успешно удалён.\n";
				break;
			}
			case 7: // Вывод количества клиентов
			{
				cout << "Общая численность клиентов равна " + company.getTotalClientsCount() << endl;
				break;
			}
			case 8: // Сортировка тарифов по цене
			{
				company.sortTariffsByPrice();
				cout << "Тарифы отсортированы по цене.\n";
				break;
			}
			case 9: // Поиск тарифов по диапазону цен
			{
				int minPrice, maxPrice;
				string checkMin, checkMax;

				while (true)
				{
					cout << "Введите минимальную цену: ";
					cin >> checkMin;
					cout << "Введите максимальную цену: ";
					cin >> checkMax;

					if (regex_match(checkMin, priceRegex) && regex_match(checkMax, priceRegex))
					{
						minPrice = stoi(checkMin);
						maxPrice = stoi(checkMax);
						break;
					}
					else
					{
						cout << "Введены неверные данные.\n";
					}
				}
				vector<Tariff*> foundTariffs = company.findTariffsInRange(minPrice, maxPrice);
				cout << "Найденные тарифы:\n";
				for (const auto& tariff : foundTariffs)
				{
					cout << tariff->display() << endl;
				}
				break;
			}
			case 10: // Выход из программы
			{
				cout << "Выход из программы.\n";
				break;
			}
			default: // Если пользователь ввёл неверную цифру
			{
				cout << "Некорректный номер операции. Попробуйте ещё раз" << endl;
				break;
			}
		}
	}

	return 0;
}
