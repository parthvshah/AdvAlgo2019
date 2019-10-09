#include "../include/dynamic_array.hpp"

using namespace std;

//Given just for reference. Only the class name and function names should match.
class dynamic_array_implementation : public dynamic_array
{
private:
    int size;
    int capacity;
    int *arr;
    double increase_factor;
    double decrease_factor;

public:
    dynamic_array_implementation();
    int get_size();
    int get_capacity();
    void set_increase_factor_table_size(double);
    void set_load_factor_reduction(double);
    void append(int);
    void pop();
    int get(int);
    ~dynamic_array_implementation();
};

dynamic_array_implementation::dynamic_array_implementation()
{
    size = 0;
    capacity = 0;
    increase_factor = 2;
    decrease_factor = 0.25;
}
int dynamic_array_implementation::get_size()
{
    return size;
}
int dynamic_array_implementation::get_capacity()
{
    return capacity;
}

void dynamic_array_implementation::set_increase_factor_table_size(double increase)
{
    increase_factor = increase;
    return;
}
void dynamic_array_implementation::set_load_factor_reduction(double decrease)
{
    decrease_factor = decrease;
    return;
}

void dynamic_array_implementation::append(int element)
{
    if(capacity == 0)
    {
        // arr = (int*) malloc(sizeof(int) * 1);
        arr = new int[1];
        arr[0] = element;
        size = 1;
        capacity = 1;
    }
    else if(size == capacity)
    {
        // int *newArr = (int*) malloc(sizeof(int) * size * increase_factor);
        double newSize = size * increase_factor;
        int newSizeI;
        if(int(newSize) == newSize)
            newSizeI = int(newSize);
        else
            newSizeI = int(newSize) + 1;
        int *newArr = new int[newSizeI];
        
        for(int i = 0; i<size; i++)
        {
            newArr[i] = arr[i];
        }
        int *freeArr = arr;
        arr = newArr;
        delete[] freeArr;

        arr[size] = element;
        capacity = size * increase_factor;
        size++;
        
    }
    else
    {
        arr[size] = element;
        size++;
    }

    return;
}

void dynamic_array_implementation::pop()
{
    if(size == 0)
        throw "no_arr";
    else if(size == 1)
    {
        size = 0;
        capacity = 0;
        delete[] arr;
    }
    else if((size-1) <= (int)(decrease_factor * capacity))
    {
        int newSize = capacity * (increase_factor * decrease_factor);
        int *newArr = new int[newSize];
        for(int i = 0; i<(size-1); i++)
        {
            newArr[i] = arr[i];
        }
        int *freeArr = arr;
        arr = newArr;
        delete[] freeArr;
        capacity = capacity * (increase_factor * decrease_factor);
        size--;
    }
    else
        size--;
    
    return;
}
int dynamic_array_implementation::get(int index)
{
    if(index >= 0 && index < size)
        return arr[index];
    else
        throw "out_of_range";
}

dynamic_array_implementation::~dynamic_array_implementation()
{
    if (capacity > 0)
    {
        delete[] arr;
    }
}