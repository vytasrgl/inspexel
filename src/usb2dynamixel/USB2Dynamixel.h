#pragma once

#include "dynamixel.h"
#include "ProtocolBase.h"

#include <chrono>
#include <map>
#include <memory>
#include <mutex>
#include <string>

namespace dynamixel {

struct USB2Dynamixel {
	using Timeout = std::chrono::microseconds;

	USB2Dynamixel(int baudrate, std::vector<std::string> const& deviceNames);
	~USB2Dynamixel();

	[[nodiscard]] bool ping(MotorID motor, Timeout timeout);

	[[nodiscard]] auto read(MotorID motor, int baseRegister, uint8_t length, Timeout timeout) -> std::tuple<bool, bool, Parameter>;

	void write(MotorID motor, Parameter const& txBuf);

	void reset(MotorID motor);
	void reboot(MotorID motor);

	void sync_write(std::map<MotorID, Parameter> const& motorParams, int baseRegister);

private:
	std::unique_ptr<ProtocolBase> m_pimpl;
	std::mutex mMutex;

};

}
