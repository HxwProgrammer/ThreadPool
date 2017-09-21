/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Runable.h
 * Author: hxw
 *
 * Created on September 21, 2017, 9:02 AM
 */

#ifndef RUNABLE_H
#define RUNABLE_H

class Runable_t {
public:
	Runable_t();
	~Runable_t();
	void set_task_id(int tid);
	void run();
	void destroy();
	static void run(void *arg);
	static void destroy(void *arg);
private:
	int task_id;
};

#endif /* RUNABLE_H */

