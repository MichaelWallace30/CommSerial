#pragma once
#include "stdafx.h"
#include <memory>
#include <functional>
#include <unordered_map>

namespace comser {
	class Packet;
	class ObjStream;

	typedef std::function<void(std::shared_ptr<Packet>)> PacketCallback;

	class PackManager {
	public:
		PackManager();
		
		void RunCallback(uint8_t id, std::shared_ptr<ObjStream> in);

		void LinkCallback(Packet* packet, PacketCallback callback);

		bool GetPackSize(uint8_t id, uint8_t& size);

	private:
		std::unordered_map<uint8_t, std::pair<Packet*, PacketCallback>> callbacks;
	};
}
