// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    this->MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    this->MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return this->BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->BitField.GetLength();
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem >= 0 && Elem < this->BitField.GetLength())
        return this->BitField.GetBit(Elem);
    else
        return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= this->BitField.GetLength())
        throw "Error";
    else
        this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= this->BitField.GetLength())
        throw "Error";
    else
        this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (this == &s)
        return *this;
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;

    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    if (this->MaxPower == s.MaxPower && this->BitField == s.BitField)
        return 1;
    else
        return 0;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet& s) // объединение
{
    int maxPower = std::max(this->MaxPower, s.MaxPower);
    TSet p(maxPower);

    for (int i = 0; i < this->MaxPower; ++i) {
        if (BitField.GetBit(i)) {
            p.BitField.SetBit(i);
        }
    }

    for (int i = 0; i < s.MaxPower; ++i) {
        if (s.BitField.GetBit(i)) {
            p.BitField.SetBit(i);
        }
    }

    return p;

}

TSet TSet::operator+(const int Elem) // объединение с элементом
{

    if (Elem < 0 || Elem >= this->MaxPower)
        throw "Element is out of range";
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res(*this);
    if (res.IsMember(Elem) == 1) {
        res.DelElem(Elem);
    }
    return res;

}

TSet TSet::operator*(const TSet& s) // пересечение
{
    int new_size = max(this->MaxPower, s.MaxPower);
    TSet res(new_size);

    for (int i = 0; i < min(this->MaxPower, s.MaxPower); i++) {
        if (this->IsMember(i) && s.IsMember(i)) {
            res.InsElem(i);
        }
    }

    return res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(*this);
    res.BitField = ~res.BitField;
    return res;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    int elem;
    while (istr >> elem)
    {
        s.InsElem(elem);
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    for (int i = 0; i < s.GetMaxPower(); ++i)
    {
        if (s.IsMember(i))
            ostr << i << " ";

    }
    return ostr;
}