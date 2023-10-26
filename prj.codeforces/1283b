#include <iostream>
#include <vector>

int main() {

	int t = 0;
	std::cin >> t;
	while (t > 0) {
		t -= 1;

		int n, k;
		std::cin >> n >> k;
		int ans = n - n % k;
		if (k / 2 < n % k) ans += k / 2;
		else ans += n % k;
		std::cout << ans << std::endl;
	}


	return 0;
}
