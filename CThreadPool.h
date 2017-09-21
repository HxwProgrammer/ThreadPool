/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CThreadPool.h
 * Author: hxw
 *
 * Created on September 18, 2017, 4:59 PM
 */

#ifndef CTHREADPOOL_H
#define CTHREADPOOL_H

#include <vector>
#include <mutex>
#include <condition_variable>

class CThread_t;
class Runable_t;

typedef void (*callback_t)(void *);

struct Task_t {
	callback_t function;
	callback_t destroy_func;
	void *argument;
};

class CThreadPool_t {
public:
	CThreadPool_t();
	int start(int thread_count, int queue_size);
	int destroy();
	int add(callback_t func, void *arg);
	int add(callback_t call_func, callback_t destroy_func, void *arg);
	Task_t get();
private:
	std::mutex lock_;
	std::condition_variable notify_;
	CThread_t *threads_;
	Task_t *task_;
	int thread_count_;
	int queue_size_;
	int task_count_;
	int head_;
	int tail_;
	bool started_;
	bool shudown_;

};

#endif /* CTHREADPOOL_H */

