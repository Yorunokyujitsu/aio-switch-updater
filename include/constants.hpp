#pragma once

constexpr const char ROOT_PATH[] = "/";
constexpr const char APP_PATH[] = "/switch/ASAP-Updater/";
constexpr const char NRO_PATH[] = "/switch/ASAP-Updater/ASAP-Updater.nro";
constexpr const char NRO_PATH_REGEX[] = ".*(/switch/.*ASAP-Updater.nro).*";
constexpr const char DOWNLOAD_PATH[] = "/config/ASAP-Updater/";
constexpr const char CONFIG_PATH[] = "/config/ASAP-Updater/";
constexpr const char CONFIG_FILE[] = "/config/ASAP-Updater/config.json";
constexpr const char CONFIG_PATH_UNZIP[] = "config\\ASAP-Updater";

constexpr const char RCM_PAYLOAD_PATH[] = "romfs:/aio_rcm.bin";
constexpr const char MARIKO_PAYLOAD_PATH[] = "/payload.bin";
constexpr const char MARIKO_PAYLOAD_PATH_TEMP[] = "/payload.bin.aio";

constexpr const char CHANGELOG_URL[] = "https://asadayo.tistory.com/notice/472";

constexpr const char APP_URL[] = "https://github.com/Yorunokyujitsu/archive_aio/releases/download/Extra+/APP+.zip";
constexpr const char TAGS_INFO[] = "https://api.github.com/repos/Yorunokyujitsu/archive_aio/releases/latest";
constexpr const char APP_FILENAME[] = "/config/ASAP-Updater/Applications.zip";

constexpr const char NXLINKS_URL[] = "https://raw.githubusercontent.com/Yorunokyujitsu/archive_aio/main/misc/list_downloads/asap-updater_links.json";

constexpr const char CUSTOM_FILENAME[] = "/config/ASAP-Updater/User_Custom.zip";
constexpr const char HEKATE_IPL_PATH[] = "/bootloader/hekate_ipl.ini";

constexpr const char FIRMWARE_URL[] = "";
constexpr const char FIRMWARE_FILENAME[] = "/config/ASAP-Updater/Horizon_OS.zip";
constexpr const char FIRMWARE_PATH[] = "/Firmware/";

constexpr const char CFW_URL[] = "";
constexpr const char BOOTLOADER_FILENAME[] = "/config/ASAP-Updater/L4T.zip";

constexpr const char AMS_URL[] = "https://raw.githubusercontent.com/HamletDuFromage/nx-links/master/cfws.json";
constexpr const char SXOS_URL[] = "https://raw.githubusercontent.com/HamletDuFromage/nx-links/master/sxos.json";
constexpr const char AMS_FILENAME[] = "/config/ASAP-Updater/ASAP.zip";

constexpr const char HEKATE_URL[] = "https://raw.githubusercontent.com/HamletDuFromage/nx-links/master/hekate.json";

constexpr const char PAYLOAD_URL[] = "https://raw.githubusercontent.com/HamletDuFromage/nx-links/master/payloads.json";

constexpr const char DEEPSEA_META_JSON[] = "https://builder.teamneptune.net/meta.json";
constexpr const char DEEPSEA_BUILD_URL[] = "https://builder.teamneptune.net/build/";
constexpr const char DEEPSEA_PACKAGE_PATH[] = "/config/deepsea/customPackage.json";

constexpr const char CUSTOM_PACKS_PATH[] = "/config/ASAP-Updater/ASAP_packs.json";

constexpr const char CHEATS_URL_TITLES[] = "https://github.com/HamletDuFromage/switch-cheats-db/releases/latest/download/titles.zip";
constexpr const char CHEATS_URL_CONTENTS[] = "https://github.com/HamletDuFromage/switch-cheats-db/releases/latest/download/contents.zip";
constexpr const char GFX_CHEATS_URL_TITLES[] = "https://github.com/HamletDuFromage/switch-cheats-db/releases/latest/download/titles_60fps-res-gfx.zip";
constexpr const char GFX_CHEATS_URL_CONTENTS[] = "https://github.com/HamletDuFromage/switch-cheats-db/releases/latest/download/contents_60fps-res-gfx.zip";
constexpr const char CHEATS_URL_VERSION[] = "https://github.com/HamletDuFromage/switch-cheats-db/releases/latest/download/VERSION";
constexpr const char LOOKUP_TABLE_URL[] = "https://raw.githubusercontent.com/HamletDuFromage/switch-cheats-db/master/versions.json";
constexpr const char LOOKUP_TABLE_CBOR[] = "https://github.com/HamletDuFromage/switch-cheats-db/raw/master/versions.cbor";
constexpr const char VERSIONS_DIRECTORY[] = "https://raw.githubusercontent.com/HamletDuFromage/switch-cheats-db/master/versions/";
constexpr const char CHEATS_DIRECTORY[] = "https://raw.githubusercontent.com/HamletDuFromage/switch-cheats-db/master/cheats/";
constexpr const char CHEATS_DIRECTORY_GBATEMP[] = "https://raw.githubusercontent.com/HamletDuFromage/switch-cheats-db/master/cheats_gbatemp/";
constexpr const char CHEATS_DIRECTORY_GFX[] = "https://raw.githubusercontent.com/HamletDuFromage/switch-cheats-db/master/cheats_gfx/";
constexpr const char CHEATSLIPS_CHEATS_URL[] = "https://www.cheatslips.com/api/v1/cheats/";
constexpr const char CHEATSLIPS_TOKEN_URL[] = "https://www.cheatslips.com/api/v1/token";
constexpr const char TOKEN_PATH[] = "/config/ASAP-Updater/token.json";
constexpr const char CHEATS_FILENAME[] = "/config/ASAP-Updater/cheats.zip";
constexpr const char CHEATS_EXCLUDE[] = "/config/ASAP-Updater/exclude.txt";
constexpr const char FILES_IGNORE[] = "/config/ASAP-Updater/preserve.txt";
constexpr const char INTERNET_JSON[] = "/config/ASAP-Updater/internet.json";
constexpr const char UPDATED_TITLES_PATH[] = "/config/ASAP-Updater/updated.dat";
constexpr const char CHEATS_VERSION[] = "/config/ASAP-Updater/cheats_version.dat";
constexpr const char AMS_CONTENTS[] = "/atmosphere/contents/";
constexpr const char REINX_CONTENTS[] = "/ReiNX/contents/";
constexpr const char SXOS_TITLES[] = "/sxos/titles/";
constexpr const char AMS_PATH[] = "/atmosphere/";
constexpr const char SXOS_PATH[] = "/sxos/";
constexpr const char REINX_PATH[] = "/ReiNX/";
constexpr const char CONTENTS_PATH[] = "contents/";
constexpr const char TITLES_PATH[] = "titles/";

constexpr const char COLOR_PICKER_URL[] = "https://git.io/jcpicker";
constexpr const char JC_COLOR_URL[] = "https://raw.githubusercontent.com/Yorunokyujitsu/archive_aio/main/misc/color_profiles/joycon_color_profiles.json";
constexpr const char JC_COLOR_PATH[] = "/config/ASAP-Updater/jc_profiles.json";
constexpr const char PC_COLOR_URL[] = "https://raw.githubusercontent.com/Yorunokyujitsu/archive_aio/main/misc/color_profiles/procon_color_profiles.json";
constexpr const char PC_COLOR_PATH[] = "/config/ASAP-Updater/pc_profiles.json";

constexpr const char PAYLOAD_PATH[] = "/payloads/";
constexpr const char BOOTLOADER_PATH[] = "/bootloader/";
constexpr const char BOOTLOADER_PL_PATH[] = "/";
constexpr const char UPDATE_BIN_PATH[] = "/bootloader/update.bin";
constexpr const char REBOOT_PAYLOAD_PATH[] = "/atmosphere/reboot_payload.bin";
constexpr const char FUSEE_SECONDARY[] = "/atmosphere/fusee-secondary.bin";
constexpr const char FUSEE_MTC[] = "/atmosphere/fusee-mtc.bin";

constexpr const char AMS_DIRECTORY_PATH[] = "/config/ASAP-Updater/atmosphere/";
constexpr const char SEPT_DIRECTORY_PATH[] = "/config/ASAP-Updater/sept/";
constexpr const char FW_DIRECTORY_PATH[] = "/Firmware/";

constexpr const char HIDE_TABS_JSON[] = "/config/ASAP-Updater/hide_tabs.json";
constexpr const char COPY_FILES_TXT[] = "/config/ASAP-Updater/copy_files.txt";
constexpr const char LANGUAGE_JSON[] = "/config/ASAP-Updater/language.json";
constexpr const char HOMEBREW[] = "/config/ASAP-Updater/language.json";

constexpr const char ROMFS_PATH[] = "romfs:/";
constexpr const char ROMFS_FORWARDER[] = "romfs:/aiosu-forwarder.nro";
constexpr const char FORWARDER_PATH[] = "/config/ASAP-Updater/aiosu-forwarder.nro";

constexpr const char DAYBREAK_PATH[] = "/switch/daybreak/daybreak.nro";

constexpr const char HIDDEN_AIO_FILE[] = "/config/ASAP-Updater/.ASAP-Updater";

constexpr const char LOCALISATION_FILE[] = "romfs:/i18n/{}/menus.json";

constexpr const int LISTITEM_HEIGHT = 50;

enum class contentType
{
    ams_cfw,
    HorizonOS,
    custom,
    extra,
    Cheats,
    BootLauncher,
    app
};

constexpr std::string_view contentTypeNames[5]{"cfws", "HorizonOS", "custom", "extra", "Cheats"};

enum class CFW
{
    rnx,
    sxos,
    ams,
};
