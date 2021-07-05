#ifndef AQI_h
#define AQI_h

namespace AQI
{

    enum Pollutant
    {
        PM2_5,
        PM10,
    };

    class Measurement
    {
    public:
        Measurement(Pollutant, float);

        float getAQI();
        Pollutant getPollutant();
        float getValue();

    protected:
        Pollutant pollutant;
        int value;

    private:
        struct Breakpoint
        {
            float min;
            float max;
            float iMin;
            float iMax;
        };

        struct BreakpointDef
        {
            Breakpoint *breakpoints;
            int count;
        };

        struct Breakpoints
        {
            BreakpointDef PM2_5;
            BreakpointDef PM10;
        };

        Breakpoint *getBreakpoint();
        BreakpointDef *getBreakpointDef();

        static const int PM2_5_BREAKPOINT_COUNT;
        static Breakpoint PM2_5_BREAKPOINTS[7];
        static BreakpointDef PM2_5_DEF;

        static const int PM10_BREAKPOINT_COUNT;
        static Breakpoint PM10_BREAKPOINTS[7];
        static BreakpointDef PM10_DEF;
    };

    class Measurements
    {
    public:
        Measurements(Measurement *, int);

        float getAQI();
        Pollutant getPollutant();

    private:
        Measurement *measurements;
        int count;
        Measurement value;
        void calculateAQI();
    };
} // namespace AQI

#endif
