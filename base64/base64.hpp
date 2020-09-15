#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <string>

namespace base64
{

	std::string encode(const std::string_view raw);
	std::string decode(const std::string_view b64);
	bool validate(const std::string_view b64);

	std::size_t encode(const std::string_view raw, std::uint8_t * out);
	std::size_t decode(const std::string_view b64, std::uint8_t * out);

} // namespace base64
