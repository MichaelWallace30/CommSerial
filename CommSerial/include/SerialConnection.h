#pragma once
#include <string>
#include <functional>
#include <thread>
#include <memory>
#include <vector>
#include <mutex>
#include <queue>
#include "ConditionVariable.h"

namespace comser {
	class Serial;
	class Parser;

	typedef std::function<void(std::string)> RecvHandler;
	typedef std::function<void(int)> ErrHandler;
	class SerialConnection : public std::enable_shared_from_this<SerialConnection> {
	public:
		static const int RECV_SLEEP_MILLIS = 50;
		SerialConnection();

		virtual bool Start(const std::string& portName);

		void SetRecvHandler(const RecvHandler& recvHandler) {
			this->recvHandler = recvHandler;
		}

		void SetErrorHandler(const ErrHandler& errHandler) {
			this->errHandler = errHandler;
		}

		void Send(const std::string& data);

		void DefaultErrHandler(int err);

		virtual ~SerialConnection();
	protected:
		Serial* serial;
		Parser* parser;
		std::queue<std::string> sendQueue;
		std::mutex sendQueueMutex;
		virtual void SendRun();
		virtual void RecvRun();
		std::thread* sendThread;
		std::thread* recvThread;
		RecvHandler recvHandler;
		ErrHandler errHandler;
		std::atomic<bool> running;
		CommConditionVariable sendCondVar;
		CommConditionVariable recvCondVar;
	};
}