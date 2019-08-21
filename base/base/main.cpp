#include <cstdio>
#include <iostream>


#include "absl/base/log_severity.h"
void log_severity()
{
	std::cout << absl::LogSeverity::kError << "error!\n";
	std::cout << (absl::LogSeverity)5 << "hello from base!\n";
}

#include "absl/base/internal/raw_logging.h"
void raw_logging()
{
	ABSL_RAW_LOG(ERROR, "print a:%d\n", 3);
	bool a = false;
	ABSL_RAW_CHECK(a, "a is false\n");
}

int main()
{
	log_severity();
	raw_logging();




    return 0;
}