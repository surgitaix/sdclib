#include "ContextWorker.h"
#include <assert.h>

namespace Network {

    ContextWorker::ContextWorker(int threads) :
        m_started(false)
    {
         assert((threads >= 0) && "Working threads counter must not be negative!");

         m_context = std::make_shared<asio::io_context>();
         for (int thread = 0; thread < threads; ++thread)
         {
             m_threads.emplace_back(std::thread());
         }
          m_strand = std::make_shared<asio::io_context::strand>(*m_context);
    }

    size_t ContextWorker::workerThreadsCount()
    {
        return m_threads.size();
    }

    bool ContextWorker::start()
    {
        if(m_started)
        {
                return false;
        }
        auto self{this->shared_from_this()};
        auto start_handler = [this, self]()
        {
             if(m_started)
             {
                 return;
             }
        m_started = true;
        };

        m_strand->post(start_handler);

        for(size_t thread = 0; thread < m_threads.size(); ++thread)
        {
            m_threads[thread] = std::thread([this, self]() {serviceThread(self, m_context);});
        }
        return true;
    }

    void ContextWorker::serviceThread(std::shared_ptr<ContextWorker> p_contextWorker, std::shared_ptr<asio::io_context> p_context)
    {
        try
        {
            asio::io_context::work work{*p_context};
            do
            {
                try
                {
//                	// Update once every second to reduce the resource consumption of the program
//                	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                	//get all current work
                	// p_context->poll()

                    p_context->run();
                }
                catch (const asio::system_error& ex)
                {
                    std::error_code ec = ex.code();

                    // Skip Asio disconnect errors
                    if (ec == asio::error::not_connected)
                    {
                    	std::cout << "Disconnect received" << std::endl;
                        continue;
                    }
                    throw;
                }
            } while (p_contextWorker->isStarted());
        }
        catch (const asio::system_error& ex)
        {
        	p_contextWorker->sendError(ex.code());
        }
        catch (const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "Asio service thread terminated!" << std::endl;
        }
    }

    std::shared_ptr<asio::io_context>& ContextWorker::getContext()
    {
        return m_context;
    }


    bool ContextWorker::isStarted()
    {
        return m_started;
    }

    bool ContextWorker::stop()
    {
    	if (!isStarted())
    	        return false;

    	    // Post the stop routine
    	    auto self(this->shared_from_this());
    	    auto stop_handler = [this, self]()
    	    {
    	        if (!isStarted())
    	            return;

    	        // Stop Asio services
    	        m_context->stop();

    	        // Update the started flag
    	        m_started = false;

    	        // Call the service stopped handler
    	    };
    	    m_strand->post(stop_handler);
    	    for (auto& thread : m_threads)
    	    {
    	    	thread.join();
    	    }
    	    return true;
    }

    void ContextWorker::sendError(std::error_code p_ec)
    {
        //Skip end of file error
        if(p_ec == asio::error::eof)
        {
            return;
        }
    }
}
