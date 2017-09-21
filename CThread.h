/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CThread.h
 * Author: hxw
 *
 * Created on September 18, 2017, 3:55 PM
 */

#ifndef CTHREAD_H
#define CTHREAD_H
#include <string>
#include <pthread.h>

#include "CThreadPool.h"
class CThreadPool_t;

class CThread_t {
public:
	CThread_t();
	~CThread_t();
	int join();
	int start();

	int set_thread_pool(CThreadPool_t *thread_pool);

protected:
	void run();

	static void *thread_func(void *arg);

private:
	CThreadPool_t *thread_pool_;
	pthread_t pid;
};

#endif /* CTHREAD_H */

