
#include <iostream>

#include "base64.hpp"

int main()
{
	std::string text = "pleasure."; //cGxlYXN1cmUu
	std::string b64_text = base64::encode(text);

	std::cout << b64_text << std::endl;
}
/*
TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIH
Bhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLHdoaWNoIGlzIGEgbHVzdCBvZiB0aGUgbWluZCwgdGhhdCBieSBhIHBlcnN
ldmVyYW5jZSBvZiBkZWxpZ2h0IGluIHRoZSBjb250aW51ZWQgYW5kIGluZGVmYX
RpZ2FibGUgZ2VuZXJhdGlvbiBvZiBrbm93bGVkZ2UsIGV4Y2VlZHMgdGhlIHNob3J0IHZlaGVtZW5jZSBvZiBhbnkgY2FybmFsIHBsZWFzdXJlLg
*/