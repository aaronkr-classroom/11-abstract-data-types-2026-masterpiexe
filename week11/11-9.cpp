#include <iostream>
#include <ctime>

#include "Vec.h"

using namespace std;

int main()
{
    const Vec<int>::size_type count = 100000;

    Vec<int> v1, v2;

    // 2배 증가 방식
    clock_t begin = clock();

    for (Vec<int>::size_type i = 0; i < count; ++i)
    {
        v1.push_back(i);
    }

    clock_t end = clock();

    cout << "[grow : capacity 2배 증가]" << endl;

    cout << count
        << "개의 정수 저장 시간 : "
        << double(end - begin) / CLOCKS_PER_SEC
        << "초"
        << endl << endl;

    // 1칸 증가 방식
    begin = clock();

    for (Vec<int>::size_type i = 0; i < count; ++i)
    {
        v2.push_back_grow_once(i);
    }

    end = clock();

    cout << "[grow_once : capacity 1 증가]" << endl;

    cout << count
        << "개의 정수 저장 시간 : "
        << double(end - begin) / CLOCKS_PER_SEC
        << "초"
        << endl;

    return 0;
}
