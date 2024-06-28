#include "mainmenu.h"
#include "../gfx/gfx.h"
#include "../gfx/gfxutils.h"
#include "../gfx/menu.h"
#include "tools.h"
#include "../hid/hid.h"
#include "../fs/menus/explorer.h"
#include <utils/btn.h>
#include <storage/nx_sd.h>
#include "tconf.h"
#include "../keys/keys.h"
#include "../storage/mountmanager.h"
#include "../storage/gptmenu.h"
#include "../storage/emummc.h"
#include <utils/util.h>
#include "../fs/fsutils.h"
#include <soc/fuse.h>
#include "../utils/utils.h"
#include "../config.h"
#include "../fs/readers/folderReader.h"
#include <string.h>
#include <mem/heap.h>
#include "../fs/menus/filemenu.h"

#define INCLUDE_BUILTIN_SCRIPTS 1
//#define SCRIPT_ONLY 1

#ifdef INCLUDE_BUILTIN_SCRIPTS
#include "../../build/ATLAS/script/builtin.h"
#endif

extern hekate_config h_cfg;

enum {
    #ifndef SCRIPT_ONLY
    MainInfo = 0,
    MainCredits,
    MainRefresh,
    // MainRebootNormal,
    // MainRebootAMS,
    // MainReloadRCM,
    MainShutdown, 
    MainHekate,
    MainExplore,
    // MainBrowseSd,
    // MainMountSd,
    // MainBrowseEmmc,
    // MainBrowseEmummc,
    // MainPartitionSd,
    MainToolbox,
    // MainPicofly,
    // MainInstinct,
    // MainHwfly,
    MainLockpick,
    // MainKeys,
    // MainAmiibos,
    // MainViewKeys,
    MainCleaner,
    // MainClean,
    // MainDelete,
    MainScripts,
    #endif
    // MainExit,
};

MenuEntry_t mainMenuEntries[] = {
    #ifndef SCRIPT_ONLY
    [MainInfo] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "-- ATLAS --"},
    [MainCredits] = {.optionUnion = COLORTORGB(COLOR_YELLOW), .name = "* Info & Credits\n"},
    [MainRefresh] = {.optionUnion = COLORTORGB(COLOR_LIME), .name = "* Refresh"}, 
    // [MainRebootNormal] = {.optionUnion = COLORTORGB(COLOR_BLACK), .name = "* Launch OFW"},
    // [MainRebootAMS] = {.optionUnion = COLORTORGB(COLOR_SILVER), .name = "* Launch CFW"},  
    // [MainReloadRCM] = {.optionUnion = COLORTORGB(COLOR_ORANGE), .name = "* Reload RCM"},
    [MainShutdown] = {.optionUnion = COLORTORGB(COLOR_PURPLE), .name = "* Shutdown"},
    [MainHekate] = {.optionUnion = COLORTORGB(COLOR_PURPLE), .name = "* Exit"}, 
    [MainExplore] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "\n\n-- TegraExplorer --"},
    // [MainBrowseSd] = {.optionUnion = COLORTORGB(COLOR_GREEN), .name = "* Browse SD"},
    // [MainMountSd] = {.optionUnion = COLORTORGB(COLOR_YELLOW)}, // To mount/unmount the SD
    // [MainBrowseEmmc] = {.optionUnion = COLORTORGB(COLOR_MAROON), .name = "* Browse eMMC"},
    // [MainBrowseEmummc] = {.optionUnion = COLORTORGB(COLOR_MAROON), .name = "* Browse emuMMC"},
    // [MainPartitionSd] = {.optionUnion = COLORTORGB(COLOR_ORANGE), .name = "Partition the SD Card"},
    [MainToolbox] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "\n\n-- Toolboxes --"},
    // [MainPicofly] = {.optionUnion = COLORTORGB(COLOR_NAVY), .name = "* Picofly Toolbox"},
    // [MainInstinct] = {.optionUnion = COLORTORGB(COLOR_TEAL), .name = "* INSTINCT Toolbox"},
    // [MainHwfly] = {.optionUnion = COLORTORGB(COLOR_GRAY), .name = "* Hwfly Toolbox"},
    [MainLockpick] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "\n\n-- Lockpick RCM --"},
    // [MainKeys] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "* Dump Keys"},
    // [MainAmiibos] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "* Dump Amiibo Keys"},
    // [MainViewKeys] = {.optionUnion = COLORTORGB(COLOR_OLIVE), .name = "* Check dumped keys"},
    [MainCleaner] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "\n\n-- ASAP-Cleaner --"},
    // [MainClean] = {.optionUnion = COLORTORGB(COLOR_BLUE), .name = "* Cleanup"},
    // [MainDelete] = {.optionUnion = COLORTORGB(COLOR_MAGENTA), .name = "* Delete Config"},
    [MainScripts] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "\n\n-- Scripts --"},
    #endif
    // [MainExit] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "\n-- Exit --"},
};

extern bool sd_mounted;
extern bool is_sd_inited;
extern int launch_payload(char *path);

void ViewCredits(){
    gfx_clearscreen();
    WPRINTF("\n\n\n\n\n\n");
	WPRINTF("                         ___   ______  __     ___    _____ ");
	WPRINTF("                        /   | /_  __/ / /    /   |  / ___/ ");
	WPRINTF("                       / /| |  / /   / /    / /| |  \\__ \\ ");
	WPRINTF("                      / ___ | / /   / /___ / ___ | ___/ / ");
	WPRINTF("                     /_/  |_|/_/   /_____//_/  |_|/____/ ");
    WPRINTF("");
    WPRINTF("                                            only for ASAP");
    WPRINTF("\n\n\n");
    WPRINTF("                        A - ASAP Install Supporter");
    WPRINTF("                        T - TegraExplorer & Toolboxes");
    WPRINTF("                        L - Lockpick RCM");
    WPRINTF("                        A - ASAP-Cleaner");
    WPRINTF("                        S - Scripts");
    WPRINTF("\n\n\n\n");
    WPRINTF("                      Credits");
    WPRINTF("");
    WPRINTF("                      - Lockpick RCM  : shchmue");
    WPRINTF("                      - TegraExplorer : SuchMemeManySkill");
    WPRINTF("                      - Hekate & Nyx  : CTCaer");
    WPRINTF("");
    WPRINTF("                      - Hwfly Toolbox    : hwfly-nx");
    WPRINTF("                      - INSTINCT Toolbox : sthetix");
    WPRINTF("                      - PiCoFly Toolbox  : rehius");
    
    if (hidRead()->r)
        gfx_printf("%k\"I'm not even sure if it works\" - meme", COLOR_ORANGE);

    hidWait();    
}

void RefrashAtlas(){
    launch_payload("sd:/bootloader/payloads/ATLAS.bin");
}

void RebootToAMS(){
    launch_payload("sd:/atmosphere/reboot_payload.bin");
}

void RebootToHekate(){
    launch_payload("sd:/bootloader/update.bin");
}

void HandleSD(){
    gfx_clearscreen();
    TConf.curExplorerLoc = LOC_SD;
    if (!sd_mount() || sd_get_card_removed()){
        gfx_printf("SD Card is not mounted!");
        hidWait();
    }
    else
        FileExplorer("sd:/");
}

void HandleEMMC(){
   GptMenu(MMC_CONN_EMMC);
}

void HandleEMUMMC(){
    GptMenu(MMC_CONN_EMUMMC);
}

void MountOrUnmountSD(){
    gfx_clearscreen();
    if (sd_mounted)
        sd_unmount();
    else if (!sd_mount())
        hidWait();
}

void LoadPicofly(){
    launch_payload("sd:/");
}

void LoadInstict(){
    launch_payload("sd:/");
}

void LoadHwlfy(){
    launch_payload("sd:/");
}

void LoadPartials(){
    launch_payload("sd:/");
}

void LoadKeys(){
    launch_payload("sd:/");
}

void LoadAmiibos(){
    launch_payload("sd:/");
}

void ViewKeys(){
    gfx_clearscreen();
    for (int i = 0; i < 3; i++){
        gfx_printf("\nBis key 0%d:   ", i);
        PrintKey(dumpedKeys.bis_key[i], AES_128_KEY_SIZE * 2);
    }
    
    gfx_printf("\nMaster key 0: ");
    PrintKey(dumpedKeys.master_key, AES_128_KEY_SIZE);
    gfx_printf("\nHeader key:   ");
    PrintKey(dumpedKeys.header_key, AES_128_KEY_SIZE * 2);
    gfx_printf("\nSave mac key: ");
    PrintKey(dumpedKeys.save_mac_key, AES_128_KEY_SIZE);

    u8 fuseCount = 0;
    for (u32 i = 0; i < 32; i++){
        if ((fuse_read_odm(7) >> i) & 1)
            fuseCount++;
    }

    gfx_printf("\n\nPkg1 ID: '%s'\nFuse count: %d / 32", TConf.pkg1ID, fuseCount);

    hidWait();
}

void LoadClean(){
    launch_payload("sd:/");
}
void LoadDelete(){
    launch_payload("sd:/");
}

menuPaths mainMenuPaths[] = {
    #ifndef SCRIPT_ONLY
    [MainCredits] = ViewCredits,
    [MainRefresh] = RefrashAtlas,
    // [MainRebootNormal] = reboot_normal,
    // [MainRebootAMS] = RebootToAMS,
    // [MainReloadRCM] = reboot_rcm,
    [MainShutdown] = power_off, 
    [MainHekate] = RebootToHekate,
    // [MainBrowseSd] = HandleSD,
    // [MainMountSd] = MountOrUnmountSD,
    // [MainBrowseEmmc] = HandleEMMC,
    // [MainBrowseEmummc] = HandleEMUMMC,
    // [MainPartitionSd] = FormatSD,
    // [MainPicofly] = LoadPicofly,
    // [MainInstinct] = LoadInstict,
    // [MainHwfly] = LoadHwlfy,
    // [MainKeys] = LoadKeys,
    // [MainAmiibos] = LoadAmiibos,
    // [MainViewKeys] = ViewKeys,
    // [MainClean] = LoadClean, 
    // [MainDelete] = LoadDelete, 
    #endif  
};

void EnterMainMenu(){
    int res = 0;
    while (1){
        if (sd_get_card_removed())
            sd_unmount();

        #ifndef SCRIPT_ONLY
        // -- ATLAS --
        mainMenuEntries[MainRefresh].hide = (!sd_mounted || !FileExists("sd:/bootloader/payloads/ATLAS.bin"));
        // mainMenuEntries[MainRebootAMS].hide = (!sd_mounted || !FileExists("sd:/atmosphere/reboot_payload.bin"));
        mainMenuEntries[MainHekate].hide = (!sd_mounted || !FileExists("sd:/bootloader/update.bin"));
        
        // -- TegraExplorer --
        // mainMenuEntries[MainBrowseSd].hide = !sd_mounted;
        // mainMenuEntries[MainMountSd].name = (sd_mounted) ? "Unmount SD" : "Mount SD";
        // mainMenuEntries[MainBrowseEmummc].hide = (!emu_cfg.enabled || !sd_mounted);
        // mainMenuEntries[MainPartitionSd].hide = (!is_sd_inited || sd_get_card_removed());
        
        // -- Toolboxes --
        // mainMenuEntries[MainPicofly].hide = (!sd_mounted || !FileExists("sd:/"));
        // mainMenuEntries[MainInstinct].hide = (!sd_mounted || !FileExists("sd:/"));
        // mainMenuEntries[MainHwfly].hide = (!sd_mounted || !FileExists("sd:/"));
        
        // -- Lockpick RCM --
        // mainMenuEntries[MainKeys].hide = (!sd_mounted || !FileExists("sd:/"));
        // mainMenuEntries[MainAmiibos].hide = (!sd_mounted || !FileExists("sd:/"));
        // mainMenuEntries[MainViewKeys].hide = !TConf.keysDumped;
        
        // -- ASAP-Cleaner --
        // mainMenuEntries[MainClean].hide = (!sd_mounted || !FileExists("sd:/"));
        // mainMenuEntries[MainDelete].hide = (!sd_mounted || !FileExists("sd:/"));
        #endif
        // -- Scripts --
        #ifndef INCLUDE_BUILTIN_SCRIPTS
        mainMenuEntries[MainScripts].hide = (!sd_mounted || !FileExists("sd:/backup/scripts"));
        #else
        mainMenuEntries[MainScripts].hide = ((!sd_mounted || !FileExists("sd:/backup/scripts")) && !EMBEDDED_SCRIPTS_LEN);
        #endif

        Vector_t ent = newVec(sizeof(MenuEntry_t), ARRAY_SIZE(mainMenuEntries));
        ent.count = ARRAY_SIZE(mainMenuEntries);
        memcpy(ent.data, mainMenuEntries, sizeof(MenuEntry_t) * ARRAY_SIZE(mainMenuEntries));
        Vector_t scriptFiles = {0};
        u8 hasScripts = 0;

        #ifdef INCLUDE_BUILTIN_SCRIPTS
        for (int i = 0; i < EMBEDDED_SCRIPTS_LEN; i++){
            MenuEntry_t m = {.name = embedded_scripts_g[i].name, .optionUnion = COLORTORGB(COLOR_AQUA), .icon = 128};
            vecAdd(&ent, m);
        }
        #endif

        if (sd_mounted && FileExists("sd:/backup/scripts")){
            scriptFiles = ReadFolder("sd:/backup/scripts", &res);
            if (!res){
                if (!scriptFiles.count){
                    FREE(scriptFiles.data);
                    mainMenuEntries[MainScripts].hide = 1;
                }
                else {
                    hasScripts = 1;
                    vecForEach(FSEntry_t*, scriptFile, (&scriptFiles)){
                        if (!scriptFile->isDir && StrEndsWith(scriptFile->name, ".te")){
                            MenuEntry_t a = MakeMenuOutFSEntry(*scriptFile);
                            vecAdd(&ent, a);
                        }
                    }

                    if (ent.count == ARRAY_SIZE(mainMenuEntries)){
                        clearFileVector(&scriptFiles);
                        hasScripts = 0;
                        mainMenuEntries[MainScripts].hide = 1;
                    }
                }
            }
        }
        

        gfx_clearscreen();
        gfx_putc('\n');
        
        res = newMenu(&ent, res, 79, 30, (ent.count == ARRAY_SIZE(mainMenuEntries)) ? ALWAYSREDRAW : ALWAYSREDRAW | ENABLEPAGECOUNT, ent.count - ARRAY_SIZE(mainMenuEntries));
        if (res < MainScripts && mainMenuPaths[res] != NULL)
            mainMenuPaths[res]();
        #ifndef INCLUDE_BUILTIN_SCRIPTS
        else if (hasScripts){
        #else
        else {
            if (res - ARRAY_SIZE(mainMenuEntries) < EMBEDDED_SCRIPTS_LEN){
                char *script = embedded_scripts_g[res - ARRAY_SIZE(mainMenuEntries)].script;
                RunScriptString(script, strlen(script));
            }
            else {
            #endif
                vecDefArray(MenuEntry_t*, entArray, ent);
                MenuEntry_t entry = entArray[res];
                FSEntry_t fsEntry = {.name = entry.name, .sizeUnion = entry.sizeUnion};
                RunScript("sd:/backup/scripts", fsEntry);
            #ifdef INCLUDE_BUILTIN_SCRIPTS
            }
            #endif
        }

        if (hasScripts){
            clearFileVector(&scriptFiles);
        }

        free(ent.data);
    }
}

