#include <string>
#include <iostream>
#include <map>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::property_tree;
using namespace std;

namespace requests{
    ptree get(string host, map<string,string> args){
        string request = "curl " + host;
        for (const auto& kv:args){
            request+="?"+kv.first+"="+kv.second;
        }
        request+=" > n.json";
        system(request.c_str());
        ifstream jsonFile("n.json");
        ptree pt;
        read_json(jsonFile, pt);
//        map<string,int1024_t> result;
//        for (auto & array_element: pt) {
//            for (auto & property: array_element.second) {
//                result[property.first] = property.second.get_value<int1024_t>();
//                cout << property.first << " = " << property.second.get_value < string > () << "\n";
//            }
//        }
        return pt;
    }
}