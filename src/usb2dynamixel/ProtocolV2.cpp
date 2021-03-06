#include "ProtocolV2.h"
#include "file_io.h"

#include <cstring>
#include <stdexcept>


namespace dynamixel {

namespace {

[[nodiscard]]
auto calculateChecksum(Parameter::const_iterator begin, Parameter::const_iterator end) -> Parameter {
	static const std::array<uint16_t, 256> crc_table = {
		0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
		0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
		0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
		0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
		0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
		0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
		0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
		0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
		0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
		0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
		0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
		0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
		0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
		0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
		0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
		0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
		0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
		0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
		0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
		0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
		0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
		0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
		0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
		0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
		0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
		0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
		0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
		0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
		0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
		0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
		0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
		0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202
	};


	uint16_t checkSum = 0;
	for (; begin != end; ++begin) {
		uint8_t index = ((checkSum >> 8) ^ static_cast<uint8_t>(*begin)) & 0xff;
		checkSum = (checkSum << 8) ^ crc_table[index];
	}
	return {std::byte(checkSum & 0xff), std::byte((checkSum >> 8) & 0xff)};
}

[[nodiscard]]
auto addEscapes(Parameter::const_iterator start, Parameter::const_iterator end) -> Parameter {
	Parameter escaped;
	int state{0};
	for (;start != end; ++start) {
		if (state == 0 and *start == std::byte{0xff}) {
			++state;
		} else if (state == 1 and *start == std::byte{0xff}) {
			++state;
		} else if (state == 2 and *start == std::byte{0xfd}) {
			escaped.emplace_back(std::byte{0xfd});
			state = 0;
		} else {
			state = 0;
		}
		escaped.emplace_back(*start);
	}
	return escaped;
}

[[nodiscard]]
auto removeEscapes(Parameter::const_iterator start, Parameter::const_iterator end) -> Parameter {
	Parameter unescaped;
	int state{0};
	for (;start != end; ++start) {
		unescaped.emplace_back(*start);
		if (state == 0 and *start == std::byte{0xff}) {
			++state;
		} else if (state == 1 and *start == std::byte{0xff}) {
			++state;
		} else if (state == 2 and *start == std::byte{0xfd}) {
			++state;
		} else if (state == 3 and *start == std::byte{0xfd}) {
			state = 0;
			unescaped.pop_back();
		} else {
			state = 0;
		}
	}
	return unescaped;
}

[[nodiscard]]
bool validatePacket(Parameter const& rxBuf) {
	if (rxBuf.size() > ((2<<16)-1)) {
		return false;
	}
	if (rxBuf.size() < 10) {
		return false;
	}

	bool success = true;
	success &= std::byte(0xff) == rxBuf[0];
	success &= std::byte(0xff) == rxBuf[1];
	success &= std::byte(0xfd) == rxBuf[2];
	success &= std::byte(0x00) == rxBuf[3];

	std::size_t len = static_cast<int>(rxBuf[5]) + (static_cast<int>(rxBuf[6]) << 8);

	success &= len + 7 == rxBuf.size();
	auto checksum = calculateChecksum(rxBuf.begin(), std::next(rxBuf.begin(), rxBuf.size()-2));

	success &= std::equal(checksum.begin(), checksum.end(), std::next(rxBuf.begin(), rxBuf.size()-2));
	return success;
}
}

auto ProtocolV2::createPacket(MotorID motorID, Instruction instr, Parameter data) const -> Parameter {
	auto escaped = addEscapes(data.begin(), data.end());
	Parameter txBuf(escaped.size() + 10);
	txBuf[0] = std::byte{0xff};
	txBuf[1] = std::byte{0xff};
	txBuf[2] = std::byte{0xfd};
	txBuf[3] = std::byte{0x00};
	txBuf[4] = std::byte(motorID);
	txBuf[5] = std::byte(((escaped.size() + 3) >> 0) & 0xff);
	txBuf[6] = std::byte(((escaped.size() + 3) >> 8) & 0xff);
	txBuf[7] = std::byte(instr);

	auto it = std::copy(escaped.begin(), escaped.end(), std::next(txBuf.begin(), 8));
	auto checkSumPart = calculateChecksum(txBuf.begin(), it);
	std::copy(checkSumPart.begin(), checkSumPart.end(), it);
	return txBuf;
}

Parameter ProtocolV2::synchronizeOnHeader(Timeout timeout, MotorID expectedMotorID, std::size_t numParameters, simplyfile::SerialPort const& port) const {
	Parameter preambleBuffer;
	struct __attribute__((packed)) Header {
		std::array<std::byte, 4> syncMarker;
		uint8_t id;
		uint16_t length;
		uint8_t instruction;
		uint8_t error;
	};
	std::array<std::byte, 4> syncMarker = {std::byte{0xff}, std::byte{0xff}, std::byte{0xfd}, std::byte{0x00}};
	auto startTime = std::chrono::high_resolution_clock::now();

	while (not ((timeout.count() != 0) and (std::chrono::high_resolution_clock::now() - startTime >= timeout))) {
		// figure out how many bytes have to be read
		int indexOfSyncMarker = 0;
		for (;indexOfSyncMarker <= static_cast<int>(preambleBuffer.size())-static_cast<int>(sizeof(syncMarker)); ++indexOfSyncMarker) {
			if (0 == std::memcmp(&preambleBuffer[indexOfSyncMarker], syncMarker.data(), sizeof(syncMarker))) {
				break;
			}
		}
		preambleBuffer.erase(preambleBuffer.begin(), preambleBuffer.begin()+indexOfSyncMarker);
		int bytesToRead = std::max(1, static_cast<int>(sizeof(Header)+2) - static_cast<int>(preambleBuffer.size()));
		auto buffer = file_io::read(port, bytesToRead);
		preambleBuffer.insert(preambleBuffer.end(), buffer.begin(), buffer.end());
		if (preambleBuffer.size() >= sizeof(Header)) {
			// test if this preamble contains the header of the packet we were looking for
			Header header;
			std::memcpy(&header, preambleBuffer.data(), sizeof(Header));
			if (header.syncMarker == syncMarker and header.length+4 >= static_cast<int>(numParameters)) {
				// found a synchronization token and a "matching" packet
				if (expectedMotorID != 0xfe) {
					if (expectedMotorID == header.id) {
						return preambleBuffer;
					}
					// received an unexpected header -> flush this header and continue reading
					preambleBuffer.clear();
				} else {
					return preambleBuffer;
				}
			}
		}
	}
	return {};
}

auto ProtocolV2::readPacket(Timeout timeout, MotorID expectedMotorID, std::size_t numParameters, simplyfile::SerialPort const& port) const -> std::tuple<bool, MotorID, ErrorCode, Parameter> {
	bool timeoutFlag = false;
	auto startTime = std::chrono::high_resolution_clock::now();

	while (not timeoutFlag) {
		Parameter rxBuf = synchronizeOnHeader(timeout, expectedMotorID, numParameters, port);
		if (rxBuf.size() < 9) {// if we could not synchronize on a header bail out
			break;
		}

		// this is the size of the entire packet [header + payload + checksum]
		std::size_t incomingLength = static_cast<int>(rxBuf[5]) + (static_cast<int>(rxBuf[6]) << 8) + 7;
		while (rxBuf.size() < incomingLength and not timeoutFlag) { // read the rest
			auto buffer = file_io::read(port, incomingLength - rxBuf.size());
			rxBuf.insert(rxBuf.end(), buffer.begin(), buffer.end());
			timeoutFlag = (timeout.count() != 0) and (std::chrono::high_resolution_clock::now() - startTime >= timeout);
		};
		if (timeoutFlag) {
			break;
		}

		auto  [motorID, errorCode, payload] = extractPayload(rxBuf);
		if (payload.size() != numParameters or motorID != expectedMotorID) {
			continue;
		}
		return std::make_tuple(false, motorID, errorCode, payload);
	}
	file_io::flushRead(port);
	return std::make_tuple(true, MotorIDInvalid, ErrorCode{}, Parameter{});
}

auto ProtocolV2::extractPayload(Parameter const& raw_packet) const -> std::tuple<MotorID, ErrorCode, Parameter> {
	if (not validatePacket(raw_packet)) {
		return std::make_tuple(MotorIDInvalid, ErrorCode{}, Parameter{});
	}

	auto motorID    = MotorID(raw_packet[4]);
	auto errorCode  = ErrorCode(raw_packet[8]);
	std::size_t len = static_cast<int>(raw_packet[5]) + (static_cast<int>(raw_packet[6]) << 8);
	Parameter payload;
	payload = Parameter(std::next(raw_packet.begin(), 9), std::next(raw_packet.begin(), 9+len-4));
	payload = removeEscapes(payload.begin(), payload.end());

	return std::make_tuple(motorID, errorCode, std::move(payload));
}

auto ProtocolV2::convertLength(size_t len) const -> Parameter {
	return {std::byte(len&0xff), std::byte((len >> 8) & 0xff)};
}

auto ProtocolV2::convertAddress(int addr) const -> Parameter {
	return {std::byte(addr&0xff), std::byte((addr >> 8) & 0xff)};
}

auto ProtocolV2::buildBulkReadPackage(std::vector<std::tuple<MotorID, int, size_t>> const& motors) const -> std::vector<std::byte> {
	std::vector<std::byte> txBuf;

	txBuf.reserve(motors.size()*5);
	for (auto const& [id, baseRegister, length] : motors) {
		txBuf.push_back(std::byte{id});
		for (auto b : convertAddress(baseRegister)) {
			txBuf.push_back(b);
		}
		for (auto b : convertLength(length)) {
			txBuf.push_back(b);
		}
	}

	return txBuf;
}


}
