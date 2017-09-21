/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Runable.cpp
 * Author: hxw
 * 
 * Created on September 21, 2017, 9:02 AM
 */

#include "Runable.h"
#include <unistd.h>
#include <iostream>

Runable_t::Runable_t() {
}

Runable_t::~Runable_t() {
    std::cout << "~Runable_t" << task_id << std::endl;
}

void Runable_t::set_task_id(int tid) {
    task_id = tid;
}

void Runable_t::run() {
    std::cout << "开始执行: " << task_id << " 线程id号是: " << pthread_self() << std::endl;
    usleep(1000000);
    std::cout << "结束执行: " << task_id << std::endl;
    destroy();
}

void Runable_t::destroy() {
    delete this;
}

void Runable_t::run(void *arg) {
    Runable_t *This = (Runable_t*) arg;
    This->run();
    return;
}

void Runable_t::destroy(void *arg) {
    Runable_t *This = (Runable_t*) arg;
    This->destroy();
}
