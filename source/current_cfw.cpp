#include "current_cfw.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <switch.h>

namespace CurrentCfw {

    namespace {

        bool isServiceRunning(const char* serviceName)
        {
            Handle handle;
            SmServiceName service_name = smEncodeName(serviceName);
            bool running = R_FAILED(smRegisterService(&handle, service_name, false, 1));
            svcCloseHandle(handle);
            if (!running)
                smUnregisterService(service_name);

            return running;
        }

        Result smAtmosphereHasService(bool* out, SmServiceName name, bool v019)
        {
            u8 tmp = 0;
            Result rc = v019 ? tipcDispatchInOut(smGetServiceSessionTipc(), 65100, name, tmp) : serviceDispatchInOut(smGetServiceSession(), 65100, name, tmp);
            if (R_SUCCEEDED(rc) && out)
                *out = tmp;
            return rc;
        }

        bool isPost019()
        {
            u64 version;
            if (R_SUCCEEDED(splGetConfig((SplConfigItem)65000, &version))) {
                if (((version >> 56) & ((1 << 8) - 1)) > 0 || ((version >> 48) & ((1 << 8) - 1)) >= 19) {
                    return true;
                }
            }
            return false;
        }
    }  // namespace

    CFW getCFW()
    {
        bool res = false;
        bool v019 = isPost019();  //AMS v0.19 introduced sm changes, and as such old AMS versions have to be treated differently
        if (R_SUCCEEDED(smAtmosphereHasService(&res, smEncodeName("rnx"), v019))) {
            if (res)
                return CFW::rnx;
            smAtmosphereHasService(&res, smEncodeName("tx"), v019);
            if (res)
                return CFW::sxos;
        }
        else {  // use old method just in case
            if (isServiceRunning("rnx")) return CFW::rnx;
            if (isServiceRunning("tx")) return CFW::sxos;
        }
        return CFW::ams;
    }
    
    std::string readVersionTagFromFile() {
        std::string filePath = "sdmc:/atmosphere/contents/010B6ECF3B30D000/03/0100B0E8EB470000";
        std::ifstream file(filePath);
        std::string line;
        if (file.is_open() && std::getline(file, line)) {
            file.close();
            return line;
        }
        return "NULL";
    }

    std::string getAmsInfo() {
        u64 version;
        std::string res;
        if (R_SUCCEEDED(splGetConfig((SplConfigItem)65000, &version))) {
            std::string amsVersion = std::to_string((version >> 56) & ((1 << 8) - 1)) + "." +
                                     std::to_string((version >> 48) & ((1 << 8) - 1)) + "." +
                                     std::to_string((version >> 40) & ((1 << 8) - 1));

            std::string nandType;
            if (R_SUCCEEDED(splGetConfig((SplConfigItem)65007, &version))) {
                nandType = version ? " | EmuNAND" : " | SysNAND";
            }

            std::string versionTag = readVersionTagFromFile();
            if (versionTag != "NULL") {
                std::istringstream iss(versionTag);
                std::string firstPart, secondPart, thirdPart;
                if (std::getline(iss, firstPart, '|') && std::getline(iss, secondPart, '|') && std::getline(iss, thirdPart)) {
                    firstPart.erase(remove_if(firstPart.begin(), firstPart.end(), isspace), firstPart.end());
                    secondPart.erase(remove_if(secondPart.begin(), secondPart.end(), isspace), secondPart.end());
                    thirdPart.erase(remove_if(thirdPart.begin(), thirdPart.end(), isspace), thirdPart.end());

                    if (thirdPart == "UPDATE") {
                        res = "Hekate " + firstPart + " | Atmosphère " + amsVersion + " | ASAP-" + secondPart + nandType;
                    } else if (thirdPart == "APP") {
                        res = "Atmosphère " + amsVersion + nandType;
                    } else if (thirdPart == "VENOM") {
                        res = "Hekate " + firstPart + " | Atmosphère " + amsVersion + " | NX Venom-" + secondPart + nandType;
                    } else if (thirdPart == "HATS") {
                        res = "Hekate " + firstPart + " | Atmosphère " + amsVersion + " | HATS-" + secondPart + nandType;
                    } else if (thirdPart == "KEFIR") {
                        res = "Hekate " + firstPart + " | Atmosphère " + amsVersion + " | Kefir-" + secondPart + nandType;
                    } else if (thirdPart == "DEEPSEA") {
                        res = "Hekate " + firstPart + " | Atmosphère " + amsVersion + " | DeepSea-" + secondPart + nandType;
                    } else {
                        res = "Atmosphère " + amsVersion + nandType;
                    }
                } else {
                    res = "ASAP 버전을 찾을 수 없습니다";
                }
            } else {
                res = "ASAP 버전을 찾을 수 없습니다";
            }
        } else {
            res = "ASAP 버전을 찾을 수 없습니다";
        }
        return res;
    }
}  // namespace CurrentCfw