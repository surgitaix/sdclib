#ifndef CONTEXTWORKER_H
#define CONTEXTWORKER_H
#include <iostream>
#include <memory>
#include <thread>

#include "asio.hpp"


namespace Network {

    /**
     * @brief The ContextWorker class
     * Worker class that is responsible for the function calls to the asio context
     */
    class ContextWorker : public std::enable_shared_from_this<ContextWorker>
    {
    public:
        ContextWorker(int threads = 1);

        //Noncopyable
        ContextWorker(const ContextWorker&) = delete;
        ContextWorker(ContextWorker&&) = delete;
        ContextWorker& operator=(const ContextWorker&) = delete;
        ContextWorker& operator=(ContextWorker&&) = delete;

        ~ContextWorker() = default;

        /**
         * @brief workerThreadsCount
         * @return size_t number of running threads for a single worker
         */
        size_t workerThreadsCount();

        /**
         * @brief start
         * For each thread the io_context is assigned
         * @return true if the contextWorker was not already started
         */
        bool start();

        /**
         * @brief stop
         * @return
         */
        bool stop();

        /**
         * @brief getContext
         * @return std::shared_ptr<asio::io_context> context the ContextWorker is assigned to
         */
        std::shared_ptr<asio::io_context>& getContext();
        bool isStarted();

    private:
        /**
         * @brief serviceThread
         * assignes the work from the context to the given contextWorker
         * @param contextWorker contextWorker to do the work.
         * @param context asio::io_context the work is polled from.
         */
        static void serviceThread(std::shared_ptr<ContextWorker> p_contextWorker, std::shared_ptr<asio::io_context> p_context);

        void sendError(std::error_code p_ec);

    private:
        std::shared_ptr<asio::io_context> m_context;
        std::vector<std::thread> m_threads;
        std::shared_ptr<asio::io_context::strand> m_strand;
        std::atomic<bool> m_started;
    };


}

#endif // CONTEXTWORKER_H
