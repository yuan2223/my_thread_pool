#include<assert.h>
#include<iostream>
#include<sstream>
#include "Thread_Pool.hpp"

namespace sola
{
	std::unique_ptr<logger_iface> active_logger = nullptr;

	static const char black[] = { 0x1b, '[', '1', ';', '3', '0', 'm', 0 };
	static const char red[] = { 0x1b, '[', '1', ';', '3', '1', 'm', 0 };
	static const char yellow[] = { 0x1b, '[', '1', ';', '3', '3', 'm', 0 };
	static const char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
	static const char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };

	logger::logger(log_level level)
		: m_level(level) {}

	
	void logger::debug(const std::string& msg, const std::string& file, std::size_t line) 
	{
		if (m_level >= log_level::debug)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			std::cout << "[" << black << "DEBUG" << normal << "][sola::logger][" << file << ":" << line << "] " << msg << std::endl;
		}
	}

	void logger::info(const std::string& msg, const std::string& file, std::size_t line) 
	{
		if (m_level >= log_level::info) 
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			std::cout << "[" << blue << "INFO " << normal << "][sola::logger][" << file << ":" << line << "] " << msg << std::endl;
		}
	}

	
	void logger::warn(const std::string& msg, const std::string& file, std::size_t line) 
	{
		if (m_level >= log_level::warn)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			std::cout << "[" << yellow << "WARN " << normal << "][sola::logger][" << file << ":" << line << "] " << msg << std::endl;
		}
	}

	void logger::error(const std::string& msg, const std::string& file, std::size_t line)
	{
		if (m_level >= log_level::error) 
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			std::cerr << "[" << red << "ERROR" << normal << "][sola::logger][" << file << ":" << line << "] " << msg << std::endl;
		}
	}

	void debug(const std::string& msg, const std::string& file, std::size_t line) 
	{
		if (active_logger)
		{
			active_logger->debug(msg, file, line);
		}
			
	}

	void info(const std::string& msg, const std::string& file, std::size_t line) 
	{
		if (active_logger)
			active_logger->info(msg, file, line);
	}

	void warn(const std::string& msg, const std::string& file, std::size_t line) 
	{
		if (active_logger)
			active_logger->warn(msg, file, line);
	}

	void error(const std::string& msg, const std::string& file, std::size_t line) 
	{
		if (active_logger)
			active_logger->error(msg, file, line);
	}

	static std::string
	get_tid() 
	{
		std::stringstream tmp;
		tmp << std::this_thread::get_id();
		return tmp.str();
	}

	thread_pool::thread_pool(int init_size)
	{
		m_init_threads_size = init_size;
		m_mutex;
		m_cond;
		m_is_started = false;
		start();
	}
	thread_pool::~thread_pool()
	{
		if (m_is_started)
		{
			stop();
		}
	}

	bool thread_pool::is_started()
	{
		return m_is_started;
	}

	void thread_pool::start()
	{
		assert(m_threads.empty());
		m_is_started = true;
		m_threads.reserve(m_init_threads_size);//预分配存储空间的大小
		for (int i = 0; i < m_init_threads_size; i++) //创建m_init_threads_size个线程 将线程的指针存放在m_threads中(线程的指针是new出来的)
		{
			//bind()创建一个可调用的函数对象，可以像函数一样调用，同时将this指针传递给 thread_loop，这样在其他线程也可以指行它
			m_threads.push_back(new std::thread(std::bind(&thread_pool::thread_loop, this)));
		}
	}
	void thread_pool::stop()
	{
		__SOLA_LOG(debug, "thread_pool::stop() stop.");
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_is_started = false;
			m_cond.notify_all();  //通知所有等待线程满足条件
			__SOLA_LOG(debug, "thread_pool::stop() notify_all().");
		}
		for (threads_t::iterator it = m_threads.begin(); it != m_threads.end(); it++)
		{
			(*it)->join();
			delete* it;
		}
		m_threads.clear();
	}

	void thread_pool::thread_loop()
	{
		__SOLA_LOG(debug, "thread_pool::thread_loop() tid: " + get_tid() + "start.");
		while (m_is_started)
		{
			task_t task = take();
			if (task)
			{
				task();
			}
		}
		__SOLA_LOG(debug, "thread_pool::thread_loop() tid: " + get_tid() + "exit.");
	}

	void thread_pool::add_task(const task_t& task)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_tasks.push_back(task);
		m_cond.notify_one();//选择一个等待的线程并唤醒它，使其从等待状态中返回。
	}

	thread_pool::task_t thread_pool::take()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (m_tasks.empty() && m_is_started)
		{
			__SOLA_LOG(debug, "thread_pool::take() tid : " + get_tid() + " wait.");
			m_cond.wait(lock);//m_mutex失去，等待消息，重新获取
		}
		__SOLA_LOG(debug, "thread_pool::take() tid : " + get_tid() + " wakeup.");

		task_t task;
		tasks_t::size_type size = m_tasks.size();
		if (!m_tasks.empty() && m_is_started)
		{
			task = m_tasks.front();
			m_tasks.pop_front();
			assert(size - 1 == m_tasks.size());
		}
		return task;
	}

}