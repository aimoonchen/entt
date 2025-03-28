#include <SDL3/SDL_render.h>
#include <app/context.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <imgui.h>

namespace testbed {

namespace internal {

static constexpr const char *window_default_title = "testbed";
static constexpr int window_default_width = 1280;
static constexpr int window_default_height = 720;

} // namespace internal

context::context()
    : sdl_window{SDL_CreateWindow(internal::window_default_title, internal::window_default_width, internal::window_default_height, SDL_WINDOW_HIGH_PIXEL_DENSITY)},
      sdl_renderer{SDL_CreateRenderer(sdl_window, nullptr)} {
    SDL_SetRenderVSync(sdl_renderer, SDL_RENDERER_VSYNC_ADAPTIVE);

    SDL_SetWindowResizable(sdl_window, true);
    SDL_SetWindowPosition(sdl_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(sdl_window, sdl_renderer);
    ImGui_ImplSDLRenderer3_Init(sdl_renderer);
}

context ::~context() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
}

SDL_Window *context::window() const noexcept {
    return *this;
}

SDL_Renderer *context::renderer() const noexcept {
    return *this;
}

context::operator SDL_Window *() const noexcept {
    return sdl_window;
}

context::operator SDL_Renderer *() const noexcept {
    return sdl_renderer;
}

} // namespace testbed
