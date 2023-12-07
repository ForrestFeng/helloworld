#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <map>
#include <vector>

/*
The program parses a log item string into a map of string keys and string_view values. The string_view is a lightweight string type that provides a view into the string without making a copy.

The parse_logitem function takes a log item string as input and returns a map of string keys and string_view values. The function uses the find function to find the position of the '§' character in the string. It then uses the substr function to extract the substring from the start position to the end position. The extracted substring is then added to the map with the corresponding label as the key.

The main function initializes the Google Test framework and runs all the tests.

The ParseLogItemTest class contains a single test case ParseLogItem. This test case creates a log item string, parses it into a map of string keys and string_view values, and then checks that the values in the map match the expected values.

The EXPECT_EQ macro is used to check that the values in the map match the expected values. If the values do not match, the test case fails.

The RUN_ALL_TESTS function runs all the tests and returns the number of failed tests. If all tests pass, it returns 0.



*/
std::map<std::string, std::string_view> parse_logitem(const std::string& logItem1) {
    std::map<std::string, std::string_view> parts;
    size_t start = 0;
    size_t end = logItem1.find('§');
    int order = 0;

    std::vector<std::string> labels = {
        "sequenceid",
        "time",
        "logger",
        "level",
        "processid",
        "processname",
        "threadid",
        "threadname",
        "machinename",
        "message",
        "properties"
    };

    while (end != std::string::npos) {
        parts[labels[order]] = std::string_view(logItem1.c_str() + start, end - start);
        start = end + 1;
        end = logItem1.find('§', start);
        order++;
    }

    parts[labels[order]] = std::string_view(logItem1.c_str() + start, logItem1.size() - start);

    return parts;
}

TEST(ParseLogItemTest, ParseLogItem) {
    std::string logItem1 = "387667§2023-10-16 10:52:05.8720§EK.Capture.Imaging.Eclipse.LogState§Debug§10712§Csh.Xrs.Services.ImageProcessing§166§§EVOLUTIONEM11§New DiagPurpose ENR_LLI_POSTSTITCH should recalc preprocessed image.  current is enr: 0  new is enr: 1 :[3]:Eclipse_State.cpp(2726)§CaptureImageId∈";

    std::map<std::string, std::string_view> parts = parse_logitem(logItem1);

    EXPECT_EQ(parts["sequenceid"], "387667");
    EXPECT_EQ(parts["time"], "2023-10-16 10:52:05.8720");
    EXPECT_EQ(parts["logger"], "EK.Capture.Imaging.Eclipse.LogState");
    EXPECT_EQ(parts["level"], "Debug");
    EXPECT_EQ(parts["processid"], "10712");
    EXPECT_EQ(parts["processname"], "Csh.Xrs.Services.ImageProcessing");
    EXPECT_EQ(parts["threadid"], "166");
    EXPECT_EQ(parts["threadname"], "");
    EXPECT_EQ(parts["machinename"], "EVOLUTIONEM11"); 
    EXPECT_EQ(parts["message"], "New DiagPurpose ENR_LLI_POSTSTITCH should recalc preprocessed image.  current is enr: 0  new is enr: 1 :[3]:Eclipse_State.cpp(2726)");
    EXPECT_EQ(parts["properties"], "CaptureImageId∈");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}