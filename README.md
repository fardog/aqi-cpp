# AQI

Performs an EPA AQI calculation for a given set of PM2.5 and PM10 measurements.

This library was written to support Arduino on an ESP8266, and has no external
dependencies. It should work fine in any environment.

**Note:** I don't really know C++, this library might be garbage. :shrug:

## Example

```cpp
#include <AQI.h>

using namespace AQI;

Measurement m[2] = {
    Measurement(Pollutant::PM2_5, 100),
    Measurement(Pollutant::PM10, 100),
};
Measurements measurements = Measurements(m, 2);

measurements.getAQI();  // 173.95264f
measurements.getPollutant();  // Pollutant::PM2_5
```

## Building

```shell
cmake .
make
```

## License

[MIT](./LICENSE)
