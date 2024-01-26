#include "UI.h"


UI::UI(int width, int height) : width(width), height(height) {}

void UI::render() {
    startDraw();
    drawCrosshair();
    endDraw();
}

void UI::drawCrosshair() {
    // Crosshair rendering logic
    ImGui::SetNextWindowPos(ImVec2(width / 2.0f, height / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(10.0f, 10.0f));
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::Begin("Crosshair", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
                                       ImGuiWindowFlags_NoBringToFrontOnFocus);
    ImGui::Text("+");
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
