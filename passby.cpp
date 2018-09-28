#include <iostream>
#include <array>

// Pass an integer by value with a void return
void passBy__value__IN_int_OUT_void(int value) {
    value = 100;
    std::cout << __func__ << "  value = " << value << std::endl;
}

// Pass an integer by value with a int return
int passBy__value__IN_int_OUT_int(int value) {
    value = 200;
    std::cout << __func__ << "  value = " << value << std::endl;
    return value;
}

// Pass an integer by reference with a void return
void passBy__reference__IN_int_OUT_void(int &value) {
    value = 300;
    std::cout << __func__ << "  value = " << value << std::endl;
}

// Pass an integer by reference with a int return
int passBy__reference__IN_int_OUT_int(int &value) {
    value = 400;
    std::cout << __func__ << "  value = " << value << std::endl;
    return value;
}

// Pass an integer by address with a void return
void passBy__address__IN_int_OUT_void(int *value) {
    *value = 500;
    // value alone is the address so need to dereference it with * to get the value
    std::cout << __func__ << "  value = " << *value << std::endl;
}

// Pass an integer by address with a int return
int passBy__address__IN_int_OUT_int(int *value) {
    *value = 600;
    std::cout << __func__ << "  value = " << *value << std::endl;
    return *value;
}


// Pass an array by value with a void return
void passBy__value__IN_array_OUT_void(std::array<int, 10> myArray) {
    myArray[5] = 9999;
}


int main() {

    int value1   = 10;
    int value2   = 20;
    int value3   = 30;
    int value4   = 40;
    int value5   = 50;
    int value6   = 60;
    int value4_1;

    std::array<int, 10> thisArray = {1,2,3,4,5,6,7,8,9,10};

    std::cout << __func__ << " 1. value1 = " << value1 << std::endl;
    passBy__value__IN_int_OUT_void(value1);
    std::cout << __func__ << " 1. value1 = " << value1 << std::endl << std::endl;

    std::cout << __func__ << " 2. value2 = " << value2 << std::endl;
    value2 = passBy__value__IN_int_OUT_int(value2);
    std::cout << __func__ << " 2. value2 = " << value2 << std::endl << std::endl;

    std::cout << __func__ << " 3. value3 = " << value3 << std::endl;
    passBy__reference__IN_int_OUT_void(value3);
    std::cout << __func__ << " 3. value3 = " << value3 << std::endl << std::endl;

    std::cout << __func__ << " 5. value4   = " << value4 << std::endl;
    value4_1 = passBy__reference__IN_int_OUT_int(value4);
    std::cout << __func__ << " 5. value4_1 = " << value4_1 << std::endl;
    std::cout << __func__ << " 5. value4   = " << value4 << std::endl << std::endl;

    std::cout << __func__ << " 6. value5 = " << value5 << std::endl;
    passBy__address__IN_int_OUT_void(&value5);
    std::cout << __func__ << " 6. value5 = " << value5 << std::endl << std::endl;

    std::cout << __func__ << " 7. value6 = " << value6 << std::endl;
    value6 = passBy__address__IN_int_OUT_int(&value6);
    std::cout << __func__ << " 7. value6 = " << value6 << std::endl << std::endl;

    std::cout << __func__ << " 8. array = " << thisArray[5] << std::endl;
    passBy__value__IN_array_OUT_void(thisArray);
    std::cout << __func__ << " 8. array = " << thisArray[5] << std::endl << std::endl;

    return 0;
}