/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: hxw
 *
 * Created on September 18, 2017, 3:43 PM
 */

#include <cstdlib>
#include <unistd.h>
#include <iostream>

#include "../CThreadPool.h"
#include "Runable.h"

using namespace std;
#define TASK_SIZE 10

/*
 * 
 */
int main(int argc, char** argv) {
    CThreadPool_t thread_pool;
    thread_pool.start(3, 1000);

    for (int i = 0; i < TASK_SIZE; ++i) {
        Runable_t * r = new Runable_t();
        r->set_task_id(i);
        thread_pool.add(Runable_t::run,Runable_t::destroy, r);
    }
    std::cout << "add end" << std::endl;
    sleep(2);
    thread_pool.destroy();


    return 0;
}

