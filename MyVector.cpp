#include <cstring>
#include "MyVector.h"
#include "iostream"

MyVector::MyVector(size_t size, ResizeStrategy resizeStrategy, float coef)
{
    if (size == 0)
    {
        this->_size = size;
        this->_capacity = 1;
        this->_data = new ValueType(size);
        this->strategy = resizeStrategy;
    }
    else
    {
        if (resizeStrategy == ResizeStrategy::Additive)
        {
            this->_size = size;
            this->_capacity = round(coef);
            this->_data = new ValueType(size);
            this->strategy = ResizeStrategy::Additive;
            for (int i = 0; i < size; i++)
            {
                this->_data[i] = 0.0;
            }
        }
        else
        {
            this->_size = size;
            this->_capacity = round(size * coef);
            this->_data = new ValueType();
            this->strategy = ResizeStrategy :: Multiplicative;
            for (int i = 0; i < size; i++)
            {
                this->_data[i] = 0.0;
            }
        }
    }
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy resizeStrategy, float coef)
{
    if (size == 0)
    {
        this->_size = size;
        this->_capacity = 1;
        this->_data = new ValueType(size);
        this->strategy = resizeStrategy;
    }
    else
    {
        if (resizeStrategy == ResizeStrategy::Additive)
        {
            this->_size = size;
            this->_capacity = size;
            this->_data = new ValueType(size);
            this->strategy = ResizeStrategy::Additive;
            for (int i = 0; i < size; i++)
            {
                this->_data[i] = value;
            }
        }
        else
        {
            this->_size = size;
            this->_capacity = size * coef;
            this->_data = new ValueType();
            this->strategy = ResizeStrategy::Multiplicative;
            for (int i = 0; i < size; i++)
            {
                this->_data[i] = value;
            }
        }
    }
}

MyVector::MyVector(const MyVector &copy)
{
    this->_data = new ValueType(copy._size);
    for (int i = 0; i < copy._size; i++)
    {
        this->_data[i] = copy._data[i];
        //std:: cout << _data[i] <<std::endl;
    }
    this->strategy = copy.strategy;
    this->_capacity = copy._capacity;
    this->_size = copy._size;
}

MyVector &MyVector::operator = (MyVector &copy){
    this->_data = new ValueType(copy._size);
    for (int i = 0; i < copy.size(); i++)
    {
        this->_data[i] = copy._data[i];
    }
    this->strategy = copy.strategy;
    this->_capacity = copy._capacity;
    this->_size = copy._size;
}

MyVector::~MyVector()
{
    this->_data = nullptr;
    delete[] this->_data;
}

size_t MyVector::capacity() const {
    return _capacity;
}

size_t MyVector::size() const {
    return _size;
}

float MyVector::loadFactor() {
    return this->_size / this->_capacity;
}

ValueType &MyVector::operator[](const size_t i) const
{
    return this->_data[i];
}

void MyVector::pushBack(const ValueType &value)
{
    if(this->_capacity < this->_size + 1)
    {
        reserve(this->_capacity + 1);
    }
    this->_data[_size] = value;
    this->_size++;
}

void MyVector::insert(const size_t i, const ValueType &value)
{
    if (loadFactor() < 1)
    {
        ValueType* newData = new ValueType(this->_capacity);
        for (int j = 0; j < i; j++)
        {
            newData[j] = this->_data[j];
        }
        newData[i] = value;
        for(int j = i + 1; j < this->_size + 1; j++)
        {
            newData[j] = this->_data[j - 1];
        }
        this->_data = newData;
        this->_size++;
    }
    else
    {
        ValueType* newData = new ValueType(this->_capacity + 1);
        for (int j = 0; j < i; j++)
        {
            newData[j] = this->_data[j];
        }
        newData[i] = value;
        for(int j = i + 1; j < this->_size + 1; j++)
        {
            newData[j] = this->_data[j - 1];
        }
        this->_data = newData;
        this->_size++;
    }
}

void MyVector::insert(const size_t i, const MyVector &value)
{
    if(this->_capacity - value._size >= 0)
    {
        ValueType* newData = new ValueType(this->_capacity);
        for (int j = 0; j < i; j++)
        {
            newData[j] = this->_data[j];
        }
        for (int j = i; j < i + value._size; j++)
        {
            newData[j] = value[j - i];
        }
        for (int j = i + value._size; j < this->_size + value._size; j++)
        {
            newData[j] = this->_data[j - value._size];
        }
        this->_data = newData;
    }
    else
    {
        ValueType* newData = new ValueType(this->_size + value._size);
        for (int j = 0; j < i; j++)
        {
            newData[j] = this->_data[j];
        }
        for (int j = i; j < i + value._size; j++)
        {
            newData[j] = value[j - i];
        }
        for (int j = i + value._size; j < this->_size + value._size; j++)
        {
            newData[j] = this->_data[j - value._size];
        }
        this->_data = newData;
    }
}

void MyVector::popBack()
{
    this->_size--;
    ValueType* newData = new ValueType();
    for(int i = 0; i < this->_size; i++)
    {
        newData[i] = this->_data[i];
    }
    this->_data = newData;
}

void MyVector::erase(const size_t i)
{
    ValueType* newData = new ValueType(this->_capacity);
    for (int j = 0; j < i; j++)
    {
        newData[j] = this->_data[j];
    }
    for (int j = i + 1; j < this->_size - 1; j++)
    {
        newData[j - 1] = this->_data[j];
    }
    this->_data = newData;
    this->_size--;
}

void MyVector::erase(const size_t i, const size_t len)
{
    ValueType* newData = new ValueType(this->_capacity);
    for (int j = 0; j < i; j++)
    {
        newData[j] = this->_data[j];
    }
    for (int j = i + len; j < this->_size - len; j++)
    {
        newData[j - len] = this->_data[j];
    }
    this->_data = newData;
    this->_size-= len;
}

long long int MyVector::find(const ValueType &value, bool isBegin) const
{
    if (isBegin)
    {
        for (int i = 0; i < this->_size; i++)
        {
            if (this->_data[i] == value)
                return _data[i];
        }
        return -1;
    }
    else
    {
        for (int i = this->_size - 1; i > -1; i--)
        {
            if (this->_data[i] == value)
                return _data[i];
        }
        return -1;
    }
}


void MyVector::reserve(const size_t capacity)
{
    if (capacity < this->_size)
        this->_size = this->_capacity;
    else
        this->_capacity = capacity;
    ValueType* newValue = new ValueType[capacity];
    for (int i = 0; i < this->_size; i++)
    {
        newValue[i] = this->_data[i];
    }
    this->_data = newValue;
}

void MyVector::resize(const size_t size, const ValueType value)
{
    if (this->_size == size)
        exit;
    if (this->_size < size)
    {
        ValueType* newData = new ValueType(size);
        for (int i = 0; i < this->_size; i++)
        {
            newData[i] = this->_data[i];
        }
        for (int i = this->_size; i < size; i++)
        {
            newData[i] = value;
        }
        this->_data = newData;
        this->_size = size;
    }
    if (this->_size > size)
    {
        ValueType* newData = new ValueType(size);
        for (int i = 0; i < size; i++)
        {
            newData[i] = this->_data[i];
        }
        this->_data = newData;
        this->_size = size;
        this->_capacity = size;
    }
}

void MyVector::clear()
{
    for (int i = 0; i < this->_size; i++)
    {
        this->_data[i] = 0.0;
    }
    this->_size = 0;
}

MyVector::Iterator::~Iterator()
{

}
bool MyVector::Iterator::operator==(const Iterator &i)
{
    return this->ptr == i.ptr;
}
bool MyVector::Iterator::operator!=(const Iterator &i)
{
    return this->ptr != i.ptr;
}
MyVector::Iterator & MyVector:: Iterator::operator++()
{
    this->ptr++;
    return *this;
}
MyVector::Iterator & MyVector:: Iterator::operator--()
{
    this->ptr--;
    return *this;
}

MyVector::Iterator::Iterator(ValueType *ptr)
{
    this->ptr = ptr;
}


MyVector::Iterator MyVector::begin()
{
    return Iterator(&this->_data[0]);
}

MyVector::Iterator MyVector::end()
{
    return Iterator(&this->_data[this->_size - 1]);
}

ValueType MyVector::getValue(Iterator i)
{
    return *i.ptr;
}

void MyVector::setValue(MyVector::Iterator i, ValueType value)
{
    *i.ptr = value;
}

void MyVector::sortedSquares( SortedStrategy strategy) {
    MyVector vec (*this);
    if (strategy == SortedStrategy::Descending)
    {
        int i = 0;
        int j = this->size() - 1;
        int k = 0;
        while(vec._data[i] < 0 && vec._data[j] >= 0)
        {
            if (abs(vec._data[i]) >= abs(vec._data[j]))
            {
                this->_data[k] = vec._data[i] * vec._data[i];
                //std:: cout << vector._data[k] << std::endl;
                i++;
                k++;
            }
            else
            {
                this->_data[k] = vec._data[j] * vec._data[j];
                //std:: cout << vector._data[k] << std:: endl;
                j--;
                k++;
            }
        }
        while(vec._data[i] < 0)
        {
            this->_data[k] = vec._data[i] * vec._data[i];
            i++;
            k++;
        }
        while(vec._data[j] >= 0)
        {
            this->_data[k] = vec._data[j] * vec._data[j];
            j--;
            k++;
        }
    }
    else
    {

        int i = 0;
        int j = this->size() - 1;
        int k = this->size() - 1;
        while(vec._data[i] < 0 && vec._data[j] >= 0)
        {
            if (abs(vec._data[i]) >= abs(vec._data[j]))
            {
                this->_data[k] = vec._data[i] * vec._data[i];
                //std:: cout << vector._data[k] << std::endl;
                i++;
                k--;
            }
            else
            {
                this->_data[k] = vec._data[j] * vec._data[j];
                //std:: cout << vector._data[k] << std:: endl;
                j--;
                k--;
            }
        }
        while(vec._data[i] < 0)
        {
            this->_data[k] = vec._data[i] * vec._data[i];
            i++;
            k--;
        }
        while(vec._data[j] >= 0)
        {
            this->_data[k] = vec._data[j] * vec._data[j];
            j--;
            k--;
        }
    }
}

MyVector::MyVector(MyVector &&moveVec) noexcept
{
    _data = moveVec._data;
    _size = moveVec._size;
    _capacity = moveVec._capacity;
    moveVec._data = nullptr;
    moveVec._capacity = 0;
    moveVec._size = 0;
}
