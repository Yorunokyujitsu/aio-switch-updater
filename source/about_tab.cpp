#include "about_tab.hpp"

namespace i18n = brls::i18n;
using namespace i18n::literals;

AboutTab::AboutTab()
{
    // Links
    this->addView(new brls::Header("menus/about/notice_title"_i18n));
    brls::Label* links = new brls::Label(
        brls::LabelStyle::SMALL,
        "menus/about/notice"_i18n,
        true);
    this->addView(links);

    // Steps
    this->addView(new brls::Header("menus/about/step_title"_i18n));
    brls::Label* Steps = new brls::Label(
        brls::LabelStyle::SMALL,
        "menus/about/step"_i18n,
        true);
    this->addView(Steps);
}