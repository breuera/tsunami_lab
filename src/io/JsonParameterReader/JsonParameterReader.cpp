/**
 * @author Bohdan Babii
 *
 * @section DESCRIPTION
 * IO-routine for reading config parameters.
 **/
#include "JsonParameterReader.h"

std::unordered_map<std::string, std::string> tsunami_lab::io::JsonParameterReader::readParameters(tsunami_lab::t_real* i_setups,
                                                                                                  tsunami_lab::t_real* i_hstar,
                                                                                                  tsunami_lab::configs::SimConfig* i_simConfig) {
    m_setups = i_setups;
    m_hstar = i_hstar;
    m_simConfig = i_simConfig;

    std::string i_filename = "../../../res/config.json";
    std::unordered_map<std::string, std::string> parameters;

    std::ifstream ifs(i_filename);
    if (!ifs.is_open()) {
        std::cerr << "Error: Unable to open file '" << i_filename << "'" << std::endl;
        return parameters;
    }

    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;

    JSONCPP_STRING errs;
    Json::Value root;

    try {
        Json::parseFromStream(builder, ifs, &root, &errs);

        if (!errs.empty()) {
            std::cerr << "Error while parsing JSON: " << errs << std::endl;
            return parameters;
        }

        // Check if 'parameters' key exists and is an object
        if (root.isObject() && root.isMember("parameters") && root["parameters"].isObject()) {
            const Json::Value& parametersObj = root["parameters"];

            // Iterate through 'parameters' object
            for (const auto& entry : parametersObj.getMemberNames()) {
                // Check if the value is convertible to either string or number
                if (parametersObj[entry].isConvertibleTo(Json::stringValue)) {
                    parameters[entry] = parametersObj[entry].asString();
                } else if (parametersObj[entry].isConvertibleTo(Json::intValue)) {
                    parameters[entry] = std::to_string(parametersObj[entry].asInt());
                } else if (parametersObj[entry].isConvertibleTo(Json::uintValue)) {
                    parameters[entry] = std::to_string(parametersObj[entry].asUInt());
                } else if (parametersObj[entry].isConvertibleTo(Json::realValue)) {
                    parameters[entry] = std::to_string(parametersObj[entry].asDouble());
                } else {
                    std::cerr << "Error: Parameter '" << entry << "' has an unsupported type in the JSON file." << std::endl;
                }
            }
        } else {
            std::cerr << "Error: 'parameters' key is not found or is not an object in the JSON file." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    ifs.close();

    return parameters;
}
