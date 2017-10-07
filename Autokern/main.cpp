//
//  main.cpp
//  Autokern
//
//  Created by malith on 10/7/17.
//  Copyright © 2017 NMR. All rights reserved.
//

#include <iostream>
#include <thread>

void func(std::string msg);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::thread t1(func, "Hello");
    std::thread t2(func, "Hello");
    std::thread t3(func, "Hello");
    std::thread t4(func, "Hello");

    t1.join();
    t2.join();
    t3.join()  ;
    t4.join();
    
    return 0;
}

void func(std::string msg){
    
    int count=0;
    std::cout << msg << "\n" ;
    for(double i=0; i<100000;i++){
        for(double i=0; i<100000;i++){
            count++;
            
        }
        
    }
}
