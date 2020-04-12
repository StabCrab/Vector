#pragma once
#include <cstdlib>
#include <cmath>
// стратегия изменения capacity
enum class SortedStrategy {
    Ascending,
    Descending
};
enum class ResizeStrategy {
	Additive,
	Multiplicative
};

// тип значений в векторе
// потом будет заменен на шаблон
using ValueType = double;

class MyVector
{
public:
    class Iterator;
	MyVector(size_t size = 0, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);
	MyVector(size_t size, ValueType value, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);
	MyVector(MyVector &&moveVec) noexcept ;
	MyVector(const MyVector& copy);
	MyVector& operator=(MyVector& copy);


	~MyVector();

	// для умненьких — реализовать конструктор и оператор для перемещения

	size_t capacity() const;
	size_t size() const;
	float loadFactor();

	// доступ к элементу, 
	// должен работать за O(1)
	ValueType& operator[](const size_t i) const;

	// добавить в конец,
	// должен работать за amort(O(1))
	void pushBack(const ValueType& value);
	// вставить,
	// должен работать за O(n)
	void insert(const size_t i, const ValueType& value);	// версия для одного значения
	void insert(const size_t i, const MyVector& value);		// версия для вектора

	// удалить с конца,
	// должен работать за amort(O(1))
	void popBack();
	// удалить
	// должен работать за O(n)
	void erase(const size_t i);
	void erase(const size_t i, const size_t len);			// удалить len элементов начиная с i

	// найти элемент,
	// должен работать за O(n)
	// если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
	// если искомого элемента нет, вернуть -1
	long long int find(const ValueType& value, bool isBegin = true) const;	

	// зарезервировать память (принудительно задать capacity)
	void reserve(const size_t capacity);

	// изменить размер
	// если новый размер больше текущего, то новые элементы забиваются дефолтными значениями
	// если меньше - обрезаем вектор
	void resize(const size_t size, const ValueType = 0.0);

	// очистка вектора, без изменения capacity
	void clear();
	Iterator begin();
	Iterator end();
	ValueType getValue(Iterator i);
	void setValue(Iterator i, ValueType value);
    void sortedSquares(SortedStrategy strategy);
private:
	ValueType* _data;
	size_t _size;
	size_t _capacity;
};
class MyVector :: Iterator
{
public:
    Iterator(ValueType *ptr);
    ~Iterator();
    bool operator==(const Iterator &i);
    bool operator!=(const Iterator &i);
    Iterator &operator++();
    Iterator &operator--();
private:
    ValueType* ptr;
    friend class MyVector;
};
