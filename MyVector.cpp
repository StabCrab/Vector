//
// Created by trykr on 05.04.2020.
//

#include <cstring>
#include "MyVector.h"

MyVector::MyVector(size_t size, ResizeStrategy resizeStrategy, float coef)
{
    if (resizeStrategy == ResizeStrategy::Additive)
    {
        this->_size = size;
        this->_capacity = size;
        this->_data = new ValueType(size);
        for (int i = 0; i < size; i++)
        {
            this->_data[i] = 0.0;
        }
    }
    else
    {
        this->_size = size;
        this->_capacity = size * coef;
        this->_data = new ValueType();
        for (int i = 0; i < size; i++)
        {
            this->_data[i] = 0.0;
        }
    }
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy resizeStrategy, float coef)
{
    if (resizeStrategy == ResizeStrategy::Additive)
    {
        this->_size = size;
        this->_capacity = size;
        this->_data = new ValueType(size);
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
        for (int i = 0; i < size; i++)
        {
            this->_data[i] = value;
        }
    }
}

MyVector::MyVector(const MyVector &copy)
{
    this->_data = copy._data;
    this->_capacity = copy._capacity;
    this->_size = copy._size;
}

MyVector &MyVector::operator = (const MyVector &copy){
    this->_data = copy._data;
    this->_capacity = copy._capacity;
    this->_size = copy._size;
}

MyVector::~MyVector()
{
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
    if (loadFactor() < 1)
    {
        this->_data[this->_size] = value;
        this->_size++;
    }
    else
    {
        ValueType* newData = new ValueType(this->_capacity + 1);
        memcpy(newData, this->_data, this->_size);
        newData[this->_size] = value;
        this->_size++;
        this->_data = newData;
    }
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
    this->_capacity += capacity;
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

