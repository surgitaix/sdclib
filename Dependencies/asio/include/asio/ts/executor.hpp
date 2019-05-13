//
// ts/executor.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_TS_EXECUTOR_HPP
#define ASIO_TS_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../../../../asio/include/asio/handler_type.hpp"
#include "../../../../asio/include/asio/async_result.hpp"
#include "../../../../asio/include/asio/associated_allocator.hpp"
#include "../../../../asio/include/asio/execution_context.hpp"
#include "../../../../asio/include/asio/is_executor.hpp"
#include "../../../../asio/include/asio/associated_executor.hpp"
#include "../../../../asio/include/asio/bind_executor.hpp"
#include "../../../../asio/include/asio/executor_work_guard.hpp"
#include "../../../../asio/include/asio/system_executor.hpp"
#include "../../../../asio/include/asio/executor.hpp"
#include "../../../../asio/include/asio/dispatch.hpp"
#include "../../../../asio/include/asio/post.hpp"
#include "../../../../asio/include/asio/defer.hpp"
#include "../../../../asio/include/asio/strand.hpp"
#include "../../../../asio/include/asio/packaged_task.hpp"
#include "../../../../asio/include/asio/use_future.hpp"

#endif // ASIO_TS_EXECUTOR_HPP
