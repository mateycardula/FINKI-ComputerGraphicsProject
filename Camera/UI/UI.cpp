#include "UI.h"


int UI::width = 0;
int UI::height = 0;


bool UI::debugMode = true;
bool UI::renderWalls = true;
bool UI::regenerate = false;
bool UI::generatingWalls = false;

int UI::MAX_TILES;
int UI::MAX_WIDTH;
int UI::MAX_DEPTH;

int UI::numWalls = 0;
int UI::numFloors = 0;
int UI::FPS = 0;


UI::UI(int oWidth, int oHeight){
    width = oWidth;
    height = oHeight;
}

void  UI::render() {
    startDraw();
    drawDebugCheckbox();
    drawRenderWallsCheckbox();
    drawGenerationSettings();
    drawMeshesCount();
    writeText();
    endDraw();
}

void UI::drawDebugCheckbox() {

    ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.5f); // Slightly transparent background for better visibility
    ImGui::Begin("Debug Options", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                           ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    ImGui::Checkbox("Debug", &debugMode);

    ImGui::End();
}

void UI::writeText() {
    ImGui::SetNextWindowPos(ImVec2(10.0f, 70.0f), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(1.0f); // Slightly transparent background for better visibility
    ImGui::Begin("Text", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                           ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    ImGui::Text("Press TAB to lock or unlock the cursor");
    ImGui::End();
}

void UI::drawRenderWallsCheckbox() {
    ImGui::SetNextWindowPos(ImVec2(10.0f, 40.0f), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.5f); // Slightly transparent background for better visibility
    ImGui::Begin("Render walls", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                           ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    ImGui::Checkbox("Render walls", &renderWalls);

    ImGui::End();
}

void UI::startDraw() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UI::endDraw() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::drawGenerationSettings() {
    ImVec2 windowPos = ImVec2(width - 10.0f, 10.0f);
    ImVec2 windowPosPivot = ImVec2(1.0f, 0.0f);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
    ImGui::SetNextWindowSize(ImVec2(250.0f, 120.0f));

    ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);

    ImGui::DragInt("Max Tiles", &MAX_TILES, 1, 1, 50000);
    ImGui::DragInt("Max Width", &MAX_WIDTH, 1, 1, 1000);
    ImGui::DragInt("Max Depth", &MAX_DEPTH, 1, 1, 1000);

    if (ImGui::Button("Regenerate")) {
        regenerate = true;
    }


    ImGui::End();
}

void UI::drawMeshesCount() {
    ImVec2 windowPos = ImVec2(10.0f, height - 30.0f);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(500.0f, 50.0f));
    ImGui::SetNextWindowBgAlpha(0.5f);

    ImGui::Begin("Rendering Info", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings |
                                            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs);

    if(renderWalls)
    ImGui::Text("Rendering: %d walls and %d floors with %d FPS", numWalls, numFloors, FPS);
    else
        ImGui::Text("Rendering: %d walls and %d floors with %d FPS", 0, numFloors, FPS);


    ImGui::End();
}



