/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CThread.cpp
 * Author: hxw
 * 
 * Created on September 18, 2017, 3:55 PM
 */

#include <iostream>

#include "CThread.h"
#include "CThreadPool.h"

CThread_t::CThread_t() :
thread_pool_(NULL)
, pid(0) {

}

CThread_t::~CThread_t() {
}

int CThread_t::join() {
    return pthread_join(pid, NULL);
}

int CThread_t::start() {
    return pthread_create(&pid, NULL, thread_func, this);
}

int CThread_t::set_thread_pool(CThreadPool_t *thread_pool) {
    if (thread_pool_) {
        return -1;
    }
    thread_pool_ = thread_pool;
    return 0;
}

void CThread_t::run() {
    while (true) {
        auto task = thread_pool_->get();
        if (!task.function) {
            break;
        }
        task.function(task.argument);
    }
}

void *CThread_t::thread_func(void *arg) {
    CThread_t *This = (CThread_t*) arg;
    This->run();
    pthread_exit(NULL);
    return NULL;
}
