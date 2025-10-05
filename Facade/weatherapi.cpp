#include <iostream>
#include <string>
#include <tuple>
#include <sstream>

class WorldWeatherAPI
{
public:
    std::tuple<float, float, std::string> getWeather(std::string location)
    {
        std::cout << "Calling worldWeather with location: " << location << std::endl;
    }
};

class FreeWeather
{
public:
    std::tuple<float, std::string> retrieve_weather(std::string location)
    {
        std::cout << "Calling freeWeather with location: " << location << std::endl;
        float temperature = 22.0f;
        std::string shortDescription  = "Sunny";
        return make_tuple(temperature, shortDescription);
    }
};

class RealtimeWeatherService
{
public:
    std::tuple<float, float, std::string> weatherConditions(std::string location)
    {
        std::cout << "Calling realtimeWeather with location: " << location << std::endl;
        float temperature = 19.5f;
        float humidity = 60.0f;
        std::string shortDescription = "Partly cloudy with a chance of rain";
        return make_tuple(temperature, humidity, shortDescription);
    }
};

class WeatherFacade
{
public:
    WeatherFacade(): m_WorldWeatherAPI(), m_FreeWeather(), m_RealtimeWeatherService() {}

    const std::string currentWeather (const std::string location)
    {
        std::tuple<float, float, std::string> worldWeatherResult = m_WorldWeatherAPI.getWeather(location);
        std::tuple<float, std::string> freeWeatherResult = m_FreeWeather.retrieve_weather(location);
        std::tuple<float, float, std::string> realtimeWeatherResult = m_RealtimeWeatherService.weatherConditions(location);

        float temperature = std::get<0>(worldWeatherResult);
        float humidity = std::get<1>(realtimeWeatherResult);
        std::string shortDescription = std::get<2>(realtimeWeatherResult);

        std::stringstream result;
        result << "Weather for " << location << std::endl
            << shortDescription << std::endl
            << "Temperature : " << temperature << " C " << std::endl
            << "Humidity: " << humidity << " %" << std::endl;

        return result.str();
    }

private:
    WorldWeatherAPI m_WorldWeatherAPI;
    FreeWeather m_FreeWeather;
    RealtimeWeatherService m_RealtimeWeatherService;
};

int main()
{
    auto const location = "Mumbai, India";

    WeatherFacade weather;
    //auto result = weather.currentWeather(location);
    std::string result = weather.currentWeather(location);
    std::cout << result;

    return 0;
}