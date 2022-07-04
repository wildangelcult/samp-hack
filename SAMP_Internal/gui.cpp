#include "gui.h"

tWndProc oWndProc;

LRESULT CALLBACK hWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (G::menuVisible) {
        ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
        return 1;
    }
    else {
        return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
    }
}

void GUI::init() {
    D3DDEVICE_CREATION_PARAMETERS cp;
    G::devicePtr->GetCreationParameters(&cp);
    hWindow = cp.hFocusWindow;

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplWin32_Init(hWindow);
    ImGui_ImplDX9_Init(G::devicePtr);
    oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG_PTR)hWndProc);

    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 171, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_CheckMark, IM_COL32(0, 171, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, IM_COL32(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(30, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_ResizeGrip, IM_COL32(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, IM_COL32(30, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(30, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, IM_COL32(0, 171, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, IM_COL32(30, 171, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, IM_COL32(30, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(30, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_TabUnfocused, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_TabUnfocusedActive, IM_COL32(50, 50, 50, 255));

    G::guiInitialized = true;
}

std::vector<std::string> options;
char buf[200];
unsigned int i = 0;
void GUI::frame() {
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Super hagz for 1337 hagerz - Royale with cheese edition");

    ImGui::BeginTabBar("##mainTabs", ImGuiTabBarFlags_Reorderable);

    if (ImGui::BeginTabItem("Aimbot")) {
        ImGui::Checkbox("Enabled", &G::config.aimbot.enabled);
        ImGui::Text("Aimbot key");
        ImGui::SameLine();
        ImGui::RadioButton("Extra mouse button 1", (int*)&G::config.aimbot.aimKey, VK_XBUTTON1);
        ImGui::SameLine();
        ImGui::RadioButton("Extra mouse button 2", (int*)&G::config.aimbot.aimKey, VK_XBUTTON2);
        ImGui::SameLine();
        ImGui::RadioButton("Left Alt", (int*)&G::config.aimbot.aimKey, VK_LMENU);
        ImGui::Checkbox("Dont aim at teammates", &G::config.aimbot.dontShootMates);
        ImGui::SliderFloat("Virtual height modifier", &G::config.aimbot.heightChange, -1, 1, "%+.3f");
        ImGui::SliderFloat("FOV", &G::config.aimbot.fov, 0, 180);
        ImGui::Checkbox("Prediction", &G::config.aimbot.prediction);
        ImGui::SliderInt("Prediction level", (int*)&G::config.aimbot.predictionLvl, 0, 10);
        ImGui::Checkbox("Smooth aim", &G::config.aimbot.smoothAim);
        ImGui::SliderFloat("Smooth aim speed", &G::config.aimbot.smoothSpeed, 0, 100, "%.3f%%");
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("ESP")) {
        ImGui::Checkbox("ESP box", &G::config.esp.ESPBox);
        ImGui::SameLine();
        if (ImGui::ColorEdit4("##ESPBox", G::config.esp.ESPBoxColor, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
            G::config.esp.calcColors.ESPBoxColor = FLOATARR_2_D3DCOLOR(G::config.esp.ESPBoxColor);
        }

        ImGui::Checkbox("Check teammate", &G::config.esp.mateBox);
        ImGui::SameLine();
        if (ImGui::ColorEdit4("##mateBox", G::config.esp.mateBoxColor, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
            G::config.esp.calcColors.mateBoxColor = FLOATARR_2_D3DCOLOR(G::config.esp.mateBoxColor);
        }

        ImGui::Checkbox("Snap lines", &G::config.esp.snapLines);
        ImGui::SameLine();
        if (ImGui::ColorEdit4("##snapLines", G::config.esp.snapLinesColor, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
            G::config.esp.calcColors.snapLinesColor = FLOATARR_2_D3DCOLOR(G::config.esp.snapLinesColor);
        }

        ImGui::Checkbox("Health ESP", &G::config.esp.healthESP);
        ImGui::SameLine();
        if (ImGui::ColorEdit4("##healthESP", G::config.esp.healthESPColor, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
            G::config.esp.calcColors.healthESPColor = FLOATARR_2_D3DCOLOR(G::config.esp.healthESPColor);
        }

        ImGui::Checkbox("Armor ESP", &G::config.esp.armorESP);
        ImGui::SameLine();
        if (ImGui::ColorEdit4("##armorESP", G::config.esp.armorESPColor, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
            G::config.esp.calcColors.armorESPColor = FLOATARR_2_D3DCOLOR(G::config.esp.armorESPColor);
        }

        ImGui::Checkbox("Name ESP", &G::config.esp.nameESP);
        ImGui::SameLine();
        if (ImGui::ColorEdit4("##nameESP", G::config.esp.nameESPColor, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
            G::config.esp.calcColors.nameESPColor = FLOATARR_2_D3DCOLOR(G::config.esp.nameESPColor);
        }

        ImGui::Checkbox("Weapon ESP", &G::config.esp.weaponESP);
        ImGui::SameLine();
        if (ImGui::ColorEdit4("##weaponESP", G::config.esp.weaponESPColor, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
            G::config.esp.calcColors.weaponESPColor = FLOATARR_2_D3DCOLOR(G::config.esp.weaponESPColor);
        }

        ImGui::EndTabItem();
    }
    
    if (ImGui::BeginTabItem("Misc")) {
        ImGui::Checkbox("Freecam", &G::config.misc.freecam);
        ImGui::SliderFloat("Freecam speed", &G::config.misc.freecamSpeed, 0, 6);
        ImGui::Checkbox("Auto turn off radio", &G::config.misc.autoOffRadio);
        ImGui::Checkbox("Auto hold horn", &G::config.misc.holdHorn);
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Config")) {
        ImGui::InputText("", buf, 200);
        ImGui::SameLine();
        if (ImGui::Button("Create")) {
            CONFIG::save(std::string(buf));
        }

        options = CONFIG::list();

        if (options.size()) {

            for (i = 0; i < options.size(); ++i) {
                ImGui::Text("%s", options[i].c_str());
                ImGui::SameLine();
                if (ImGui::Button("Save")) {
                    CONFIG::save(options[i]);
                }
                ImGui::SameLine();
                if (ImGui::Button("Load")) {
                    CONFIG::load(options[i]);
                }
                ImGui::SameLine();
                if (ImGui::Button("Delete")) {
                    CONFIG::remove(options[i]);
                }
            }
        }

        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();

    ImGui::End();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void GUI::shutdown() {
    SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG_PTR)oWndProc);
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}