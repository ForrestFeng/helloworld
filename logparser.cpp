#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <map>
#include <vector>


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