
#include "gtest_helpers.h"
#include "inertial_sense_ros.h"

TEST(ReconnectionTestSuite, ntripUrlFromYamlDoesNotRequireLegacyApi)
{
    std::string yaml = "rtk_rover:\n"
                       "  correction_input:\n"
                       "    select: ntrip_example\n"
                       "    ntrip_example:\n"
                       "      type: ntrip\n"
                       "      format: RTCM3\n"
                       "      ip_address: '66.219.246.93'\n"
                       "      ip_port: 7777\n"
                       "      mount_point: 'mountabc'\n"
                       "      username: 'myusername'\n"
                       "      password: 'yourpassword'\n";

    YAML::Node config = YAML::Load(yaml);
    ASSERT_TRUE(config.IsDefined());

    RtkRoverProvider provider(config["rtk_rover"]);
    ASSERT_NE(provider.correction_input, nullptr);

    auto* ntrip = static_cast<RtkRoverCorrectionProvider_Ntrip*>(provider.correction_input);
    EXPECT_EQ(ntrip->get_ntrip_url(), "ntrip://myusername:yourpassword@66.219.246.93:7777/mountabc");

    // Must not abort the process when no InertialSense instance is attached.
    ntrip->connect_rtk_client();
    SUCCEED();
}
