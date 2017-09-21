/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CThreadPool.cpp
 * Author: hxw
 * 
 * Created on September 18, 2017, 4:59 PM
 */

#include <algorithm>
#include <iostream>

#include "CThreadPool.h"
#include "CThread.h"

CThreadPool_t::CThreadPool_t() :
threads_(NULL)
, task_(NULL)
, thread_count_(0)
, queue_size_(0)
, task_count_(0)
, head_(0)
, tail_(0)
, started_(false)
, shudown_(false) {
}

int CThreadPool_t::start(int thread_count, int queue_size) {
    std::lock_guard<decltype(lock_) > l(lock_);
    if (started_) {
        return -1;
    }
    queue_size_ = queue_size;

    threads_ = new CThread_t[thread_count];
    for (int i = 0; i < thread_count; ++i) {
        threads_[i].set_thread_pool(this);
        auto ret = threads_[i].start();
        if (0 != ret) {
            std::cout << "线程启动失败." << std::endl;
            destroy();
            return -1;
        }
        ++thread_count_;
    }

    task_ = new Task_t[queue_size];


    started_ = true;
    return 0;
}

int CThreadPool_t::destroy() {
    lock_.lock();

    if (shudown_) {
        lock_.unlock();
        return -1;
    }

    shudown_ = true;
    started_ = false;
    notify_.notify_all();
    lock_.unlock();

    for (int i = 0; i < thread_count_; ++i) {
        threads_[i].join();
    }


    if (threads_) {
        delete[] threads_;
        threads_ = NULL;
    }

    while (this->task_count_ != 0) {
        Task_t task = task_[head_];
        head_ = (head_ + 1) % queue_size_;
        --task_count_;
        if (task.destroy_func) {
            task.destroy_func(task.argument);
        }
    }


    if (task_) {
        delete[] task_;
        task_ = NULL;
    }

    return 0;
}

int CThreadPool_t::add(callback_t func, void *arg) {
    return add(func, NULL, arg);
}

int CThreadPool_t::add(callback_t call_func, callback_t destroy_func, void *arg) {
    if (call_func == NULL) {
        return -1;
    }
    std::lock_guard<decltype(lock_) > l(lock_);
    if (shudown_) {
        return -1;
    }
    if (task_count_ == queue_size_) {
        return -1;
    }

    task_[tail_].function = call_func;
    task_[tail_].destroy_func = destroy_func;
    task_[tail_].argument = arg;
    
    tail_ = (tail_ + 1) % queue_size_;
    ++task_count_;
    notify_.notify_one();

    return 0;
}

Task_t CThreadPool_t::get() {
    // std::lock_guard<decltype(lock_) > l(lock_);
    std::unique_lock<decltype(lock_) > ul(lock_);
    Task_t task;
    task.argument = NULL;
    task.function = NULL;
    while (true) {
        while ((!shudown_) && task_count_ == 0) {
            notify_.wait(ul);
        }
        if (shudown_) {
            return task;
        }

        task = task_[head_];
        head_ = (head_ + 1) % queue_size_;
        --task_count_;
        break;
    }
    return task;
}
