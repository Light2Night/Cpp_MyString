#include <iostream>
using namespace std;

// Свій клас string. class MyString

class MyString {
private:
	char *str = nullptr;
	unsigned int size;

	void DeleteStr() {
		if (str != nullptr)
			delete[] str;
	}

	void Initialization(const char symbol) { // Метод ініціалізації символом
		DeleteStr();
		if (symbol == '\0')
			str = new char[1]{ '\0' };
		else
			str = new char[2]{ symbol, '\0' };

		size = strlen(str);
	}

	void Initialization(const char *text) { // Метод ініціалізації рядком
		DeleteStr();

		size = strlen(text);
		str = new char[size + 1];

		for (unsigned int i = 0; i < size; i++) {
			str[i] = text[i];
		}

		str[size] = '\0';
	}

	void Adding(const char symbol) { // Метод конкатинації з символом
		if (symbol == '\0')
			return;

		char *newStr = new char[size + 2];

		for (unsigned int i = 0; i < size; i++) {
			newStr[i] = str[i];
		}
		DeleteStr();

		newStr[size++] = symbol;
		newStr[size] = '\0';

		str = newStr;
	}

	void Adding(const char *text) { // Метод конкатинації з рядком
		unsigned int newSize = size + strlen(text);

		char *newStr = new char[newSize + 1];

		for (unsigned int i = 0; i < size; i++) {
			newStr[i] = str[i];
		}
		DeleteStr();

		for (unsigned int i = size; i < newSize; i++) {
			newStr[i] = text[i - size];
		}

		newStr[newSize] = '\0';

		size = newSize;
		str = newStr;
	}

	MyString ConcatinationOfText(const char *text) { // Метод, що вертає об'єкт-результат конкатинації двох об'єктів, або конкатинації об'єкта з рядком
		int tempSize = size + strlen(text);
		char *tempStr = new char[tempSize + 1];

		for (unsigned int i = 0; i < size; i++) {
			tempStr[i] = str[i];
		}

		for (unsigned int i = size; i < tempSize; i++) {
			tempStr[i] = text[i - size];
		}
		tempStr[tempSize] = '\0';

		MyString tempObject = tempStr;
		delete[] tempStr;

		return tempObject;
	}

public:
	MyString() { // Конструктор по заумовчуванню
		Initialization('\0');
	}

	MyString(const char symbol) { // Конструктор присвоєнная символа
		Initialization(symbol);
	}

	MyString(const char *text) { // Конструктор присвоєнная рядка
		Initialization(text);
	}

	MyString(const MyString &other) { // Конструктор копіювання (str = str2 + str3)
		Initialization(other.str);
	}

	~MyString() { // Деструктор
		DeleteStr();
	}



	MyString &operator = (const char symbol) { // Оператор повторного присвоєння символа (str = 'a';)
		Initialization(symbol);
		return *this;
	}

	MyString &operator = (const char *text) { // Оператор повторного присвоєння рядка (str = "new text";)
		Initialization(text);
		return *this;
	}

	MyString &operator = (const MyString &other) { // Оператор копіювання (str = str2;)
		int tempSize = strlen(other.str);
		char *tempStr = new char[tempSize + 1];
		for (int i = 0; i < tempSize; i++) {
			tempStr[i] = other.str[i];
		}
		tempStr[tempSize] = '\0';

		Initialization(tempStr);
		delete[] tempStr;
		return *this;
	}

	MyString &operator += (const char symbol) { // Оператор конкатинації з символом (str += 'a';)
		Adding(symbol);
		return *this;
	}

	MyString &operator += (const char *text) { // Оператор конкатинації з рядком (str += "new text";)
		Adding(text);
		return *this;
	}

	MyString &operator += (const MyString &other) { // Оператор конкатинації змінних (str += str2;)
		int tempSize = strlen(other.str);
		char *tempStr = new char[tempSize + 1];
		for (int i = 0; i < tempSize; i++) {
			tempStr[i] = other.str[i];
		}
		tempStr[tempSize] = '\0';

		Adding(tempStr);
		delete[] tempStr;
		return *this;
	}

	MyString operator + (const char *text) { // Оператор конкатинації і повернення об'єкту-результату (str = str2 + "text")
		return ConcatinationOfText(text);
	}

	MyString operator + (const MyString &other) { // Оператор конкатинації і повернення об'єкту-результату (str = str2 + str3)
		return ConcatinationOfText(other.str);
	}

	char operator [] (const unsigned int index) { // Оператор індексування (Повертає значення, не дозволяє редагувати елементи)
		if (index < size)
			return str[index];
		return '\0';
	}

	bool SetSymbol(const char symbol, const unsigned int index) { // Встановлення символа на певну дозволену позицію рядка
		if (index >= size || symbol == '\0') // Вийнятки
			return false;

		str[index] = symbol; // Редагування даних
		return true;
	}



	void clear() { // Очищення рядка
		Initialization('\0');
	}

	void getline() { // Читання рядка
		clear();
		char symbol;
		while (true) {
			symbol = getchar();
			if (symbol == '\n')
				break;
			Adding(symbol);
		}
	}

	unsigned int len() { // Вивід довжини рядка
		return size;
	}

	friend std::istream &operator >> (std::istream &in, MyString &value);
	friend std::ostream &operator << (std::ostream &out, const MyString &value);
};

std::istream &operator >> (std::istream &in, MyString &value) { // Ввід даних до пропуска через cin
	value.clear();
	char symbol;
	bool skip = true; // Змінна = true якщо ще не було введено даних
	while (true) {
		symbol = getchar();

		if (symbol == '\n' || symbol == ' ') {
			if (skip)
				continue;
			break;
		}
		value.Adding(symbol);
		skip = false;
	}
	return in;
}

std::ostream &operator << (std::ostream &out, const MyString &value) { // Вивід даних через cout
	out << value.str;
	return out;
}



int main() {
	MyString str;

	//cin >> str;
	//str.getline();

	cout << str << endl;

	return 0;
}