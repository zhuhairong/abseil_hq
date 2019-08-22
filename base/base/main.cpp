#include <cstdio>
#include <iostream>


#include "absl/base/log_severity.h"
void log_severity()
{
	std::cout << absl::LogSeverity::kError << "error!\n";
	std::cout << (absl::LogSeverity)5 << "hello from base!\n";
}

#include "absl/base/internal/raw_logging.h"
#include "absl/strings/str_cat.h"
void raw_logging()
{
	ABSL_RAW_LOG(INFO, "RAW INFO: %d", 1);
	ABSL_RAW_LOG(INFO, "RAW INFO: %d %d", 1, 2);
	ABSL_RAW_LOG(INFO, "RAW INFO: %d %d %d", 1, 2, 3);
	ABSL_RAW_LOG(INFO, "RAW INFO: %d %d %d %d", 1, 2, 3, 4);
	ABSL_RAW_LOG(INFO, "RAW INFO: %d %d %d %d %d", 1, 2, 3, 4, 5);
	ABSL_RAW_LOG(WARNING, "RAW WARNING: %d", 1);
	ABSL_RAW_LOG(ERROR, "RAW ERROR: %d", 1);

	ABSL_RAW_CHECK(true, "RAW CHECK");

	ABSL_INTERNAL_LOG(INFO, "Internal Log");
	std::string log_msg = "Internal Log";
	ABSL_INTERNAL_LOG(INFO, log_msg);
	ABSL_INTERNAL_LOG(INFO, log_msg + " 2");
	float d = 1.1f;
	ABSL_INTERNAL_LOG(INFO, absl::StrCat("Internal log ", 3, " + ", d));
}

#include "absl/base/casts.h"
template <int N>
struct marshall 
{
	char buf[N]; 
};
template <typename T>
void TestMarshall(const T values[], int num_values) {
	for (int i = 0; i < num_values; ++i) {
		T t0 = values[i];
		marshall<sizeof(T)> m0 = absl::bit_cast<marshall<sizeof(T)>>(t0);
		T t1 = absl::bit_cast<T>(m0);
		marshall<sizeof(T)> m1 = absl::bit_cast<marshall<sizeof(T)>>(t1);
		if(memcmp(&t0, &t1, sizeof(T)) == 0)
			ABSL_RAW_LOG(INFO, "Equal\n");
		if(memcmp(&m0, &m1, sizeof(T)) == 0)
			ABSL_RAW_LOG(INFO, "Equal\n");
	}
}
void cast()
{
	static const bool bool_list[] = { false, true };
	TestMarshall<bool>(bool_list, ABSL_ARRAYSIZE(bool_list));

	static const int32_t int_list[] = { 0, 1, 100, 2147483647, -1, -100, -2147483647, -2147483647 - 1 };
	TestMarshall<int32_t>(int_list, ABSL_ARRAYSIZE(int_list));
}
int main()
{
	log_severity();
	raw_logging();
	cast();



    return 0;
}