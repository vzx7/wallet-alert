#ifndef BIG_INT_H
#define BIG_INT_H
/**
 * @author https://programforyou.ru/poleznoe/dlinnaya-arifmetika-kak-operirovat-chislami-ne-pomeshchayushchimisya-ni-v-odin-iz-chislovyh-tipov#:~:text=%D0%92%20%D1%8F%D0%B7%D1%8B%D0%BA%D0%B0%D1%85%20C%20%D0%B8%20C%2B%2B,long%20%D0%BE%D1%82%20-9223372036854775808%20%D0%B4%D0%BE%209223372036854775807%20
 */
#include <iostream>
#include <string>

class BigInt {
	std::string value; // значение числа
	bool isNeg; // флаг отрицательности

	static BigInt karatsuba_mul(const BigInt &a, const BigInt &b); // умножение методом Карацубы

public:
	BigInt(); // конструктор умолчания (число равно нулю)
	BigInt(long x); // конструктор преобразования из обычного целого числа
	BigInt(const std::string &value); // конструктор преобразования из строки
	BigInt(const BigInt& bigInt); // конструктор копирования

	const std::string &getValue() const; // получение содержимого строки (строка модуля числа)

	const bool getIsNeg() const; // получение флага отрицательности числа
	void setIsNeg(bool isNeg); // установка флага отрицательности числа

	int sign() const; // получение знака числа
	const bool isEven() const; // проверка на чётность

	BigInt abs() const; // получение модуля числа
	BigInt pow(long n) const; // получение числа в степени n
	BigInt sqrt(long n = 2) const; // вычисление корня n-ой степени из числа

	// операции сравнения
	const bool operator==(const BigInt &bigInt) const;
	const bool operator!=(const BigInt &bigInt) const;

	const bool operator<(const BigInt &bigInt) const;
	const bool operator>(const BigInt &bigInt) const;
	const bool operator<=(const BigInt &bigInt) const;
	const bool operator>=(const BigInt &bigInt) const;

	// операция присваивания
	BigInt &operator=(const BigInt &bigInt);

	// унарные плюс и минус
	BigInt operator+() const &&;
	BigInt operator-() const &&;

	// арифметические операции
	BigInt operator+(const BigInt &bigInt) const;
	BigInt operator-(const BigInt &bigInt) const;
	BigInt operator*(const BigInt &bigInt) const;
	BigInt operator/(const BigInt &bigInt) const;
	BigInt operator%(const BigInt &bigInt) const;
	BigInt operator<<(size_t n) const;
	BigInt operator>>(size_t n) const;

	// краткая форма операций
	BigInt &operator+=(const BigInt &bigInt);
	BigInt &operator-=(const BigInt &bigInt);
	BigInt &operator*=(const BigInt &bigInt);
	BigInt &operator/=(const BigInt &bigInt);
	BigInt &operator%=(const BigInt &bigInt);
	BigInt &operator<<=(size_t n);
	BigInt &operator>>=(size_t n);

	// префиксная форма
	BigInt &operator++(); // ++v
	BigInt &operator--(); // --v

	// постфиксная форма
	BigInt operator++(int); // v++
	BigInt operator--(int); // v--


	friend std::ostream &operator<<(std::ostream &stream, const BigInt &bigInt); // вывод числа в выходной поток
	friend std::istream &operator>>(std::istream &stream, BigInt &bigInt); // ввод числа из входного потока
};

#endif