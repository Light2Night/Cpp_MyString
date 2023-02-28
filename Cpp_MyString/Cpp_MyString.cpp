#include <iostream>
using namespace std;

// Свій клас string. class MyString

class MyString {
private:
	char *str = nullptr;
	unsigned int size;

	void Initialization(const char symbol) { // Метод ініціалізації символом
		delete[] str;

		if (symbol == '\0') {
			str = new char[1]{ '\0' };
			size = 0;
			return;
		}

		str = new char[2]{ symbol, '\0' };
		size = 1;
	}

	void Initialization(const char *text) { // Метод ініціалізації рядком
		delete[] str;

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
		delete[] str;

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
		delete[] str;

		for (unsigned int i = size; i < newSize; i++) {
			newStr[i] = text[i - size];
		}

		newStr[newSize] = '\0';

		size = newSize;
		str = newStr;
	}

	int StrCmp(const char *str1, const char *str2) const { // Порівняння двох рядків
		/* Повертає:
			0  - якщо рядки ідентичні
			1  - якщо перший відмінний символ рядка str1 має більший код символу в порівнянні з str2
			-1 - якщо перший відмінний символ рядка str1 має менший код символу в порівнянні з str2
		*/
		for (unsigned int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++) {
			if (str1[i] > str2[i])
				return 1;
			if (str1[i] < str2[i])
				return -1;
		}
		return 0;
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
		delete[] str;
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
		MyString buffer(other);
		Initialization(buffer.str);
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
		MyString buffer(other);
		Adding(buffer.str);
		return *this;
	}

	MyString operator + (const char symbol) const { // Оператор конкатинації і повернення об'єкту-результату (str = str2 + 'a';)
		MyString buffer(str);
		buffer += symbol;
		return buffer;
	}
	MyString operator + (const char *text) const { // Оператор конкатинації і повернення об'єкту-результату (str = str2 + "text";)
		MyString buffer(str);
		buffer += text;
		return buffer;
	}
	MyString operator + (const MyString &other) const { // Оператор конкатинації і повернення об'єкту-результату (str = str2 + str3;)
		MyString buffer(str);
		buffer += other.str;
		return buffer;
	}


	char operator [] (const unsigned int index) const { // Оператор індексування (Повертає значення, не дозволяє редагувати елементи)
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


	// Оператори порівняння рядків
	// В операторах порівняння символів немає необхідності, оскільки при передаванні символа ініціалізується рядок MyString
	bool operator == (const char *text) const {
		return StrCmp(this->str, text) == 0;
	}
	bool operator == (const MyString &other) const {
		return StrCmp(this->str, other.str) == 0;
	}

	bool operator != (const char *text) const {
		return StrCmp(this->str, text) != 0;
	}
	bool operator != (const MyString &other) const {
		return StrCmp(this->str, other.str) != 0;
	}

	bool operator > (const char *text) const {
		return StrCmp(this->str, text) > 0;
	}
	bool operator > (const MyString &other) const {
		return StrCmp(this->str, other.str) > 0;
	}

	bool operator >= (const char *text) const {
		return StrCmp(this->str, text) >= 0;
	}
	bool operator >= (const MyString &other) const {
		return StrCmp(this->str, other.str) >= 0;
	}

	bool operator < (const char *text) const {
		return StrCmp(this->str, text) < 0;
	}
	bool operator < (const MyString &other) const {
		return StrCmp(this->str, other.str) < 0;
	}

	bool operator <= (const char *text) const {
		return StrCmp(this->str, text) <= 0;
	}
	bool operator <= (const MyString &other) const {
		return StrCmp(this->str, other.str) <= 0;
	}


	void clear() { // Очищення рядка
		Initialization('\0');
	}

	void getline() { // Читання рядка з консолі
		clear();
		char symbol;
		while (true) {
			symbol = getchar();
			if (symbol == '\n')
				break;
			Adding(symbol);
		}
	}

	unsigned int len() const { // Вивід довжини рядка
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

	cin >> str;
	str.getline();

	return 0;
}