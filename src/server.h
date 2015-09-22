/*
 * Copyright (C) 2015 deipi.com LLC and contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef XAPIAND_INCLUDED_SERVER_H
#define XAPIAND_INCLUDED_SERVER_H

#include "manager.h"
#include "server_base.h"

#include <list>
#include <vector>

#define HEARTBEAT_MIN 0.150
#define HEARTBEAT_MAX 0.400
#define HEARTBEAT_INIT (HEARTBEAT_MAX / 2)

class BaseServer;


class XapiandServer : public Task, public Worker {
private:
	pthread_mutex_t qmtx;
	pthread_mutexattr_t qmtx_attr;

	ev::async async_setup_node;

	std::vector<BaseServer *> servers;

	void destroy();

	void async_setup_node_cb(ev::async &watcher, int revents);

	void register_server(BaseServer *server);

public:
	static pthread_mutex_t static_mutex;
	static int total_clients;
	static int http_clients;
	static int binary_clients;

	inline XapiandManager * manager() const {
		return static_cast<XapiandManager *>(_parent);
	}

	XapiandServer(XapiandManager *manager_, ev::loop_ref *loop_);
	~XapiandServer();

	void run();
	void shutdown();

protected:
	friend class BaseClient;
	friend class XapiandManager;
};


#endif /* XAPIAND_INCLUDED_SERVER_H */
