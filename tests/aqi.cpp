#include <math.h>
#include "gtest/gtest.h"

#include "AQI.h"

using namespace testing;
using namespace AQI;

TEST(Measurement, Constructor)
{
    Measurement m = Measurement(Pollutant::PM2_5, 100);
    EXPECT_EQ(m.getPollutant(), Pollutant::PM2_5);
    EXPECT_EQ(m.getValue(), 100);
}

TEST(Measurement, AQI_PM2_5)
{

    // zero measurement
    Measurement m1 = Measurement(Pollutant::PM2_5, 0);
    EXPECT_FLOAT_EQ(m1.getAQI(), 0);

    // overflow
    Measurement m2 = Measurement(Pollutant::PM2_5, 600);
    EXPECT_FLOAT_EQ(m2.getAQI(), -1);

    Measurement m3 = Measurement(Pollutant::PM2_5, 100);
    EXPECT_FLOAT_EQ(m3.getAQI(), 173.95264f);

    Measurement m4 = Measurement(Pollutant::PM2_5, 9.3f);
    EXPECT_FLOAT_EQ(m4.getAQI(), 37.190083f);

    Measurement m5 = Measurement(Pollutant::PM2_5, 15);
    EXPECT_FLOAT_EQ(m5.getAQI(), 57.072647f);

    Measurement m6 = Measurement(Pollutant::PM2_5, 49.5f);
    EXPECT_FLOAT_EQ(m6.getAQI(), 134.075f);

    Measurement m7 = Measurement(Pollutant::PM2_5, 235.4f);
    EXPECT_FLOAT_EQ(m7.getAQI(), 284.655f);
}

TEST(Measurement, AQI_PM10)
{
    // zero measurement
    Measurement m1 = Measurement(Pollutant::PM10, 0);
    EXPECT_FLOAT_EQ(m1.getAQI(), 0);

    // overflow
    Measurement m2 = Measurement(Pollutant::PM10, 800);
    EXPECT_FLOAT_EQ(m2.getAQI(), -1);

    Measurement m3 = Measurement(Pollutant::PM10, 100);
    EXPECT_FLOAT_EQ(m3.getAQI(), 73.050003f);

    Measurement m4 = Measurement(Pollutant::PM10, 55);
    EXPECT_FLOAT_EQ(m4.getAQI(), 51.0f);

    Measurement m5 = Measurement(Pollutant::PM10, 550);
    EXPECT_FLOAT_EQ(m5.getAQI(), 445.54999f);

    Measurement m6 = Measurement(Pollutant::PM10, 370.5f);
    EXPECT_FLOAT_EQ(m6.getAQI(), 222.21428f);

    Measurement m7 = Measurement(Pollutant::PM10, 235.4f);
    EXPECT_FLOAT_EQ(m7.getAQI(), 140.2f);
}

TEST(Measurements, getAQI)
{
    Measurement m1[2] = {
        Measurement(Pollutant::PM2_5, 100),
        Measurement(Pollutant::PM10, 100),
    };
    Measurements a1 = Measurements(m1, 2);
    EXPECT_FLOAT_EQ(a1.getAQI(), 173.95264f);
    EXPECT_EQ(a1.getPollutant(), Pollutant::PM2_5);

    Measurement m2[2] = {
        Measurement(Pollutant::PM2_5, 80),
        Measurement(Pollutant::PM10, 370.5f),
    };
    Measurements a2 = Measurements(m2, 2);
    EXPECT_FLOAT_EQ(a2.getAQI(), 222.21428f);
    EXPECT_EQ(a2.getPollutant(), Pollutant::PM10);
}
