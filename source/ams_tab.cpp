#include "ams_tab.hpp"

#include <filesystem>
#include <iostream>
#include <string>

#include "confirm_page.hpp"
#include "current_cfw.hpp"
#include "dialogue_page.hpp"
#include "download.hpp"
#include "extract.hpp"
#include "fs.hpp"
#include "utils.hpp"
#include "worker_page.hpp"
namespace i18n = brls::i18n;
using namespace i18n::literals;

AmsTab::AmsTab(const nlohmann::ordered_json& nxlinks, const bool erista) : brls::List()
{
    this->erista = erista;
    this->nxlinks = nxlinks;
    this->hekate = util::getValueFromKey(nxlinks, "hekate");
}

void AmsTab::RegisterListItemAction(brls::ListItem* listItem) {}

bool AmsTab::CreateDownloadItems(const nlohmann::ordered_json& cfw_links, bool hekate, bool ams)
{
    std::vector<std::pair<std::string, std::string>> links;
    links = download::getLinksFromJson(cfw_links);
    if (links.size() && !this->hekate.empty()) {  // non-empty this->hekate indicates internet connection
        auto hekate_link = download::getLinksFromJson(this->hekate);
        // std::string hekate_url = hekate_link[0].second;
        // std::string text_hekate = "menus/common/download"_i18n + hekate_link[0].first;

        for (const auto& link : links) {
            bool pack = link.first.contains("[PACK]");
            std::string url = link.second;
            std::string text("menus/common/download"_i18n + link.first + "menus/common/from"_i18n);
            listItem = new brls::ListItem(link.first);
            listItem->setHeight(LISTITEM_HEIGHT);
            listItem->getClickEvent()->subscribe([this, text, url, hekate, pack, ams](brls::View* view) {
                if (!erista && !std::filesystem::exists(MARIKO_PAYLOAD_PATH)) {
                    brls::Application::crash("menus/errors/mariko_payload_missing"_i18n);
                }
                else {
                    CreateStagedFrames(text, url, erista, ams);
                }
            });
            this->RegisterListItemAction(listItem);
            this->addView(listItem);
        }
        return true;
    }
    return false;
}

void AmsTab::CreateStagedFrames(const std::string& text, const std::string& url, bool erista, bool ams, bool hekate, const std::string& text_hekate, const std::string& hekate_url)
{
    brls::StagedAppletFrame* stagedFrame = new brls::StagedAppletFrame();
    stagedFrame->setTitle(this->type == contentType::ams_cfw ? "menus/ams_update/getting_ams"_i18n : "menus/ams_update/custom_download"_i18n);
    stagedFrame->addStage(
        new ConfirmPage(stagedFrame, text));
    stagedFrame->addStage(
        new WorkerPage(stagedFrame, "menus/common/downloading"_i18n, [&, url]() { util::downloadArchive(url, this->type); }));
    stagedFrame->addStage(
        new WorkerPage(stagedFrame, "menus/common/extracting"_i18n, [&]() { util::extractArchive(this->type); }));
    if (hekate) {
        stagedFrame->addStage(
            new DialoguePage_ams(stagedFrame, text_hekate, erista));
    }
    if (ams)
        stagedFrame->addStage(new ConfirmPage_AmsUpdate(stagedFrame, "menus/ams_update/reboot_rcm"_i18n, erista));
    else
        stagedFrame->addStage(new ConfirmPage_Done(stagedFrame, "menus/common/all_done"_i18n));
    brls::Application::pushView(stagedFrame);
}

AmsTab_Regular::AmsTab_Regular(const nlohmann::ordered_json& nxlinks, const bool erista) : AmsTab(nxlinks, erista)
{
    this->CreateLists();
}

bool AmsTab_Regular::CreateDownloadItems(const nlohmann::ordered_json& cfw_links, bool hekate, bool ams)
{
    if (!AmsTab::CreateDownloadItems(cfw_links, ams)) {
        brls::Label* description = new brls::Label(
            brls::LabelStyle::SMALL,
            "menus/main/links_not_found"_i18n,
            true);
        description->setHorizontalAlign(NVG_ALIGN_CENTER);
        this->addView(description);
        return true;
    }
    return false;
}

void AmsTab_Regular::CreateLists()
{
    this->type = contentType::ams_cfw;
    auto cfws = util::getValueFromKey(this->nxlinks, "cfws");
    
    this->addView(new brls::Header("menus/about/asap_title"_i18n));
    this->addView(new brls::Label(brls::LabelStyle::DESCRIPTION, (CurrentCfw::running_cfw == CFW::ams ? "menus/ams_update/current_ams"_i18n + CurrentCfw::getAmsInfo() : "") + (erista ? "\n" + "menus/ams_update/erista_rev"_i18n : "\n" + "menus/ams_update/mariko_rev"_i18n), true));
    CreateDownloadItems(util::getValueFromKey(cfws, "ASAP"));
    
    this->addView(new brls::Header("menus/about/aio_title"_i18n));
    CreateDownloadItems(util::getValueFromKey(cfws, "AIO"));
}

std::string AmsTab_Regular::GetRepoName(const std::string& repo)
{
    return repo.substr(repo.find("/") + 1, repo.length());
}

std::set<std::string> AmsTab_Regular::GetLastDownloadedModules(const std::string& json_path)
{
    nlohmann::ordered_json package = fs::parseJsonFile(json_path);
    std::set<std::string> res;
    if (package.find("modules") != package.end()) {
        for (const auto& module : package.at("modules")) {
            res.insert(module.get<std::string>());
        }
    }
    return res;
}

AmsTab_Extra::AmsTab_Extra(const nlohmann::ordered_json& nxlinks, const bool erista) : AmsTab(nxlinks, erista)
{
    this->CreateLists();
}

bool AmsTab_Extra::CreateDownloadItems(const nlohmann::ordered_json& cfw_links, bool hekate, bool ams)
{
    if (!AmsTab::CreateDownloadItems(cfw_links, ams)) {
        brls::Label* description = new brls::Label(
            brls::LabelStyle::SMALL,
            "menus/main/links_not_found"_i18n,
            true);
        description->setHorizontalAlign(NVG_ALIGN_CENTER);
        this->addView(description);
        return true;
    }
    return false;
}

void AmsTab_Extra::CreateLists()
{
    this->type = contentType::extra;
    auto extra = util::getValueFromKey(this->nxlinks, "extra");

    this->addView(new brls::Header("menus/main/android_title"_i18n));
    CreateDownloadItems(util::getValueFromKey(extra, "android"));

    this->addView(new brls::Header("menus/main/l4t_title"_i18n));
    CreateDownloadItems(util::getValueFromKey(extra, "ubuntu"));

    this->addView(new brls::Header("menus/main/lakka_title"_i18n));
    CreateDownloadItems(util::getValueFromKey(extra, "lakka"));
}

AmsTab_Custom::AmsTab_Custom(const nlohmann::ordered_json& nxlinks, const bool erista) : AmsTab(nxlinks, erista)
{
    this->CreateLists();
}

void AmsTab_Custom::CreateLists()
{   
    this->type = contentType::ams_cfw;
    this->addView(new brls::Header("menus/main/tesla_title"_i18n));
    // this->addView(new brls::Label(
    //     brls::LabelStyle::DESCRIPTION,
    //     "menus/ams_update/custom_packs_ams"_i18n,
    //     true));
    CreateDownloadItems(util::getValueFromKey(this->nxlinks, "etc"), true);
    
    this->type = contentType::custom;
    auto custom = util::getValueFromKey(this->nxlinks, "custom");
           
    /*this->addView(new brls::Header("menus/main/tesla_title"_i18n));
    CreateDownloadItems(util::getValueFromKey(custom, "tesla"), false, false);*/

    /*this->addView(new brls::Header("menus/main/package_title"_i18n));
    CreateDownloadItems(util::getValueFromKey(custom, "package"), false, false);*/

    /*this->addView(new brls::Header("menus/main/sysclk_title"_i18n));
    CreateDownloadItems(util::getValueFromKey(custom, "sysclk"), false, false);*/

    this->addView(new brls::Header("menus/main/sys_title"_i18n));
    CreateDownloadItems(util::getValueFromKey(custom, "sys"), false, false);
    
    this->addView(new brls::Header("menus/main/home_title"_i18n));
    CreateDownloadItems(util::getValueFromKey(custom, "home"), false, false);

    this->addView(new brls::Header("menus/main/modchip_title"_i18n));
    CreateDownloadItems(util::getValueFromKey(custom, "modchip"), false, false);
}