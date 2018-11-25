#pragma once
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <functional>

class ThreadPool {
private:
  boost::asio::io_service io_service;
  boost::thread_group thread_pool;
  std::unique_ptr<boost::asio::io_service::work> work;

public:
  ThreadPool();
  ThreadPool(size_t num_workers);

  void add_task(std::function<void()> task);
  void wait_all();
};
