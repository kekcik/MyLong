//
//  main.cpp
//  plusi
//
//  Created by Иван Трофимов on 09.06.16.
//  Copyright © 2016 Иван Трофимов. All rights reserved.
//
#include <iostream>
#include <string>
#include <stdio.h>
#include "big_integer.h"
using namespace std;
int main () {
    std::string s1, s2;
    cin >> s1;
    big_integer a (s1);
    cout << a + 1 <<endl; 
}