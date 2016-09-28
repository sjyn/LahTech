#pragma once
#include <atomic>
#include <thread>
#include <mutex>

class Runnable
{
public:
	Runnable() : m_stop(), m_thread() { }
	virtual ~Runnable() { try { stop(); } catch(...) { /*??*/ } }

	void stop() { m_stop = true; m_thread.join(); }
	void start() { m_thread = std::thread(&Runnable::run, this); }

protected:
	virtual void run() = 0;
	std::atomic<bool> m_stop;

private:
	std::thread m_thread;
};

