/*exceptions declaration*/
namespace mtm
{
class BadInput : public std::exception
{
public:
    virtual const char* what() const noexcept;
};

}
/*end of exceptions declaration*/

/*exceptions implementation*/
const char* mtm::BadInput::what() const noexcept
{
    return "Error: The input is invalid";
}
/*end of exceptions implementation*/

template <class T>
std::vector<T> slice(std::vector<T> vec, int start, int step, int stop);

template <class T>
std::vector<T> slice(std::vector<T> vec, int start, int step, int stop)
{
    //check input validity
    if (start >= vec.size() || stop < 0 || stop > vec.size()|| step <= 0)
    {
        throw mtm::BadInput();
    }

    if (start >= stop)
    {
        std::vector<T> result(0);
        return result;
    }


    auto first = vec.begin() + start;
    auto last = vec.begin() + stop;

    //get to one step after the last index
    if (stop != vec.size())
    {
        last = vec.begin() + stop + 1;
    }

    std::vector<T> temp(first, last);

    int size = ((stop - start) / step);

    if (size == 0)
    {
        size++;
    }

    std::vector<T> result(size);


    int i , j = 0;
    
    while (i < stop-start)
    {
        result.at(j) = temp.at(i);
        j++;
        i += step;
    }

    return result;
}

class A {
public:
    std::vector<std::shared_ptr<int>> values;
    
    void add(int x)
    {
        values.push_back(std::shared_ptr<int>(new int(x)));
    }
    
    ~A()
    {
    }
};
