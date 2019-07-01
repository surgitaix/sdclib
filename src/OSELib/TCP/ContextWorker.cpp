#include "OSELib/TCP/ContextWorker.h"
#include <assert.h>

namespace Network {

    ContextWorker::ContextWorker(int threads) :
        _started(false)
    {
         assert((threads >= 0) && "Working threads counter must not be negative!");

         _context = std::make_shared<asio::io_context>();
         for (int thread = 0; thread < threads; ++thread)
         {
             _threads.emplace_back(std::thread());
         }
          _strand = std::make_shared<asio::io_service::strand>(*_context);
    }

    size_t ContextWorker::workerThreadsCount()
    {
        return _threads.size();
    }

    bool ContextWorker::start()
    {
        if(_started)
        {
                return false;
        }
        auto self(this->shared_from_this());
        auto start_handler = [this, self]()
        {
             if(_started)
             {
                 return;
             }
        _started = true;
        };

        _strand->post(start_handler);

        for(size_t thread = 0; thread < _threads.size(); ++thread)
        {
            _threads[thread] = std::thread([this, self]() {serviceThread(self, _context);});
        }
        return true;
    }

    void ContextWorker::serviceThread(std::shared_ptr<ContextWorker> contextWorker, std::shared_ptr<asio::io_context> context)
    {
        try
        {
            asio::io_service::work work(*context);
            do
            {
                try
                {
                    //get all current work
                    context->poll();
                }
                catch (const asio::system_error& ex)
                {
                    std::error_code ec = ex.code();

                    // Skip Asio disconnect errors
                    if (ec == asio::error::not_connected)
                        continue;

                    throw;
                }
            } while (contextWorker->isStarted());
        }
        catch (const asio::system_error& ex)
        {
            contextWorker->sendError(ex.code());
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
        return _context;
    }


    bool ContextWorker::isStarted()
    {
        return _started;
    }

    bool ContextWorker::stop()
    {
    	assert(isStarted() && "Asio service is not started!");
    	    if (!isStarted())
    	        return false;

    	    // Post the stop routine
    	    auto self(this->shared_from_this());
    	    auto stop_handler = [this, self]()
    	    {
    	        if (!isStarted())
    	            return;

    	        // Stop Asio services
    	        _context->stop();

    	        // Update the started flag
    	        _started = false;

    	        // Call the service stopped handler
    	    };
    	    _strand->post(stop_handler);
    	    for (auto& thread : _threads)
    	    {
    	    	thread.join();
    	    }
    	    return true;
    }

    void ContextWorker::sendError(std::error_code ec)
    {
        //Skip end of file error
        if(ec == asio::error::eof)
        {
            return;
        }
    }
}
