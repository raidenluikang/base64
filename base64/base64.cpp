

#include "base64.hpp"

namespace
{

	constexpr std::uint8_t base64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	struct decode_table_t
	{
		std::uint8_t array[256];
	};

	constexpr decode_table_t make_decode_table() noexcept
	{
		decode_table_t table = {};

		for (::std::size_t i = 0; i < 256; ++i)
			table.array[i] = 0x80;

		for (::std::size_t i = 0; i < 64; ++i)
			table.array[base64_table[i]] = (std::uint8_t)i;

		return table;
	}

	constexpr decode_table_t base64_decode_table = make_decode_table();

} // end unnoumous namespace

std::string base64::encode(const std::string_view raw)
{
	const std::size_t b64_size = raw.size() * 4 / 3 + 4;
	std::string b64(b64_size, '\0');
	std::uint8_t* out = (std::uint8_t*)b64.data();
	encode(raw, out);

	return b64;
}

std::string base64::decode(const std::string_view b64)
{
	std::size_t raw_size = b64.size();
	std::string raw(raw_size, '\0');
	std::uint8_t* raw_out = (std::uint8_t*)raw.data();
	decode(b64, raw_out);
	return raw;
}

bool base64::validate(const std::string_view b64)
{
	for (unsigned char c : b64)
	{
		if (base64_decode_table.array[c] == 0x80)
			return false;
	}

	return true;
}

std::size_t base64::encode(const std::string_view raw, std::uint8_t * out)
{
	std::size_t out_len = 0;
	const std::uint8_t * in = (const std::uint8_t*)raw.data();
	const std::uint8_t * in_end = in + raw.size();
	for (; in_end - in >= 3; in += 3)
	{
		out[out_len++] = base64_table[in[0] >> 2];
		out[out_len++] = base64_table[(in[0] & 0x03) << 4 | (in[1] >> 4)];
		out[out_len++] = base64_table[(in[1] & 0x0f) << 2 | (in[2] >> 6)];
		out[out_len++] = base64_table[in[2] & 0x3f];
	}

	if (in_end - in)
	{
		out[out_len++] = base64_table[in[0] >> 2];

		if (in_end - in == 1)
		{
			out[out_len++] = base64_table[(in[0] & 0x03) << 4];
			out[out_len++] = '=';//padding.
		}
		else
		{
			out[out_len++] = base64_table[(in[0] & 0x03) << 4 | in[1] >> 4];
			out[out_len++] = base64_table[(in[1] & 0x0f) << 2];
		}
		out[out_len++] = '='; //padding.
	}

	return out_len;
}

std::size_t base64::decode(const std::string_view b64, std::uint8_t * out)
{
	std::uint8_t block[4];
	int n = 0, pad = 0;
	std::uint8_t * p = out;

	for (const std::uint8_t c : b64)
	{
		std::uint8_t t = base64_decode_table.array[c];
		if (t == 0x80)continue;
		if (c == '=')
			pad++;
		block[n++] = t;

		if (n == 4)
		{
			n = 0;
			*p++ = (std::uint8_t)((block[0] << 2) | (block[1] >> 4));
			*p++ = (std::uint8_t)((block[1] << 4) | (block[2] >> 2));
			*p++ = (std::uint8_t)((block[2] << 6) | block[3]);
			if (pad)
			{
				if (pad == 1)
					p--;
				else if (pad == 2)
					p -= 2;
				else
				{
					//invalid padding.
				}
				break;
			}
		}
	}
	return p - out;
}
