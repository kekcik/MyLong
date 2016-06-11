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
    int n;
    cin >> n;
    big_integer a ("1");
    big_integer b ("2");
    for (int i = 2; i <= n; i++) {
        a *= b;
        b += big_integer(1);
    }
    cout << a << endl;
}