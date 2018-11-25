#include "thread_pool.h"
#include <thread>

ThreadPool::ThreadPool() : io_service(), thread_pool() {
  work = std::make_unique<boost::asio::io_service::work>(io_service);
  for (unsigned i = 0; i < std::thread::hardware_concurrency(); i++) {
    thread_pool.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
  }
}

ThreadPool::ThreadPool(size_t num_workers) : ThreadPool() {
  for (size_t i = 0; i < num_workers; i++) {
    thread_pool.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
  }
}

void ThreadPool::add_task(std::function<void()> task) { io_service.post(task); }

void ThreadPool::wait_all() {
  work.reset();
  thread_pool.join_all();
  io_service.stop();
}
