#include "validator.h"
#include <iostream>

int main(){
    create();
    if (validate()) {
      std::cout << "not expired" << std::endl;
    } else {
      std::cout << "expired" << std::endl;
    }
    return 0;
}
