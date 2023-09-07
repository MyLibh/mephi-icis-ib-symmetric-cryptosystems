#include <array>
#include <format>
#include <iostream>
#include <vector>

constexpr std::array<const char* const, 11> hexes{
	"f9e4d9bff5bac624e2ce1bb3c4cce85336d650082caa9037eb48f6a5aedf9ff6f8f4daa2a3e358a783321dd0d09ffa57f9528f4551c65a726620117c81ff867786c50dfaed6056c670a8103b4dab6fe7cfae8bfb71803aa04023e0271b2bc012e10e09901d58c2d654d34004109da5ec79e55f8b42c624ce6c6befeb44edb8f36229c19e32fe40e7596bca",
	"ebf495b9e6f4912df6c10bfcc69ef3593294520461ad9b2fa400e3f1b1d79fbeb6ead8e3a5fe5eead73917d2d28fe312e944c20a6bc60931666e52729fe28c25c0d71ae1ec7756dd7eed532741b679ed9da39a8f3f993cba516eee720c64c85cb5391d95164f818500c808031e9daba1",
	"fae99cfcfabd8527a3d907b5d88bbc5a31994b0961839020b215acf4f9df98beb6ead8e3baf20da9d12802c9cf8dfc53fb49c41775831970696e556f84fa8c77818402e1f63219d438ab513b5bbf2de1dcfcc9ee7cd717b54623c3681121cf",
	"fae99cfcf7bd962ae6df1bb9ce98bc4b21995a0822ad9165a900e3e4f9c18effb3a5caadaee554bad7381dd3808be255e453c8116ece5a7d68215a6ecded9a7787cb01eaa27305927ba4403d5db479e7c5fa9abe239837a14b66e5271d3d8753b50f1c8b1c53c1d645d20314089fbaa562e30d8f4b813fd5687af4a649e0cacc6825df8362967bfc5863d6825c5365e3",
	"f7ee8cfcf0bb8865f78d18bdd898bc4f3cd65c0838e89465b81cb7a5b6d0cbfdb9f78fa8a8ee5eeac5231dd0808bae55fe5881126ecc5a62772b52748ce0802d85d74ee7ec3205c67dac5c3c56a12de1dcfcc9ee7cd71eb55a60a1551030c25cf7191a9e535ec99b4dd90e121881a9ec62e30dad4b8f20d7647c",
	"fae99caef1f48730e68d1babd9cce84223934d5d2eaed526b900b3f1b6d199ffa8edd6e3e0b759a2c22552cac883ed5aab56c8096a831174623e116e88ef9b3294d74efde37413927ebf5f3818bf62f7cfaed6a725833fb10870e8740b21d51eb51d069d5349ce97549c170e188ca6ec7ae44182078d35c2712eefae0abf8fe8736cc08b74d301f34761ded0485d7eff397146ba3e57082d2bf3973555225dd56c959411d999165fd45718ae",
	"fae99caef1f48730e68d1babd9cce84223934d5d2eaed526b209b7eabec48aeeb0fc95e3a2f948ead73913c9808be25ee456d24572cb1f31402147789fe284328ed04efaed3203c17ded52274db268a2dbe1c8ad34d727bb0861f3621e2f8746fd19489a1c59c3da00dd0e025180a0a92df9458f53c622c2707bf5b90cbecae8682993ad7dc044e75b63d69e45127fe239635aa97b4714353af8c37317707cc239829e11e8881b50da1e04b373",
	"f9e4d9bff5bac631e6c84fa8de89bc4b3c9f500961bf9d20b91ce3f1b1d3cbfdb0ecdfe3a4e40dbfcd3913cdd093ae5bed01c04571d1157f606e537499ac8024c0d70be0f63217dc7ced533a56b578efd8fd9aa33e8536f4586cf6620d64c140fa11488d1b5886934eca09141e81a3a963f90dc307a734ce215df4aa04a498",
	"efa1d1ace6bd9023f7c842b7d395b51b7393501e33b18531a216ada5aad583fbb5e08fb0b9f659afd071419dc186e95df948d50d6bd05631692f5c7881f5c936c0d41ce1e17712c76aa8103357b42de5d8e0dfbc30833aba4f23ea6206378b12f45c188b1c5ec39255ce05461780bcec68e34e9c5e9624ce6f69b0eb08a38ebc616cc3987dd544f1407cd6d0575d79ad7d734abe2255122920facd2a",
	"fae99cfcd7bb8821eade0afcf994fa5421927a1422bc9c2aa518b1fcf99ed9aee8b386e3a9f24ba3cd34019dc398f742ff4e810475830e79626e506f99ac8631c08419fceb661fdc7fed5f754ae67eedd1f8d3a036d730bb4c66f229",
	"fae99cfce7b18530e6d94fb1d39fef5a34931e1432f2d512a31cada5acc582f0bfa5cee3bee35fafc23c52dec99ae657f90d810b63d51f63273b4278cdf88132c0cf0bf7a27f19c07ded443d59a82dedd3eddf",
};

[[nodiscard]] static auto hex_to_bytes(const std::string& hex)
{
	std::vector<uint8_t> result;
	for (size_t i{}; i < hex.length(); i += 2)
		result.push_back(static_cast<uint8_t>(::strtol(hex.substr(i, 2).c_str(), nullptr, 16)));

	return result;
}

static constexpr void xorx(const uint8_t* a, const uint8_t* b, uint8_t* c, const size_t len)
{
	for (size_t i{}; i < len; ++i)
		c[i] = a[i] ^ b[i];
}

[[nodiscard]] static auto mix_with(const std::vector<uint8_t>& vec, std::string_view pattern)
{
	std::vector<std::string> res;
	if (pattern.length() > vec.size())
		pattern.remove_suffix(pattern.length() - vec.size());

	for (size_t i{}; i <= vec.size() - pattern.length(); ++i)
	{
		bool add = true;
		std::string str;
		for (size_t j{}; j < pattern.length(); ++j)
			if (const char c = vec[i + j] ^ pattern[j]; !(std::isalnum(c) || std::isspace(c) || std::ispunct(c)))
			{
				add = false;
				break;
			}
			else
				str += c;

		if (add)
			res.emplace_back(std::format("\t\'{}\' | {}-{} of {}", str, i, i + pattern.length(), vec.size()));
	}

	return res;
}

[[nodiscard]] static auto proceed(const std::string& hex1, const std::string& hex2, const std::string_view pattern)
{
	const auto lhs = hex_to_bytes(hex1);
	const auto rhs = hex_to_bytes(hex2);

	std::vector<uint8_t> out(std::min(std::size(lhs), std::size(rhs)));
	xorx(lhs.data(), rhs.data(), out.data(), std::size(out));
	return mix_with(out, pattern);
}

auto main() -> signed
{
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);

	const std::string patterns{ " the " };
	for (size_t i{}; i < std::size(hexes); ++i)
		for (size_t j{}; j < std::size(hexes); ++j)
			if (i < j)
				if (const auto res = proceed(hexes[i], hexes[j], pattern); !res.empty())
				{
					std::cout << std::format("[{}^{}]\n", i + 1, j + 1);
					for (const auto& str : res)
						std::cout << str << '\n';
				}
	
	return 0;
}
