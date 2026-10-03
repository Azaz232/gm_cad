#include "CustomWindow.h"
#include "SharpenFilter.h"
#include "EmbossFilter.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <portable-file-dialogs.h>
#include <iostream>

CustomWindow::~CustomWindow()
{
	if (originalTexture) glDeleteTextures(1, &originalTexture);
	if (processedTexture) glDeleteTextures(1, &processedTexture);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	if (window) glfwDestroyWindow(window);
	glfwTerminate();
}

bool CustomWindow::Init()
{
	if (!glfwInit()) return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1280, 720, "CAD Image Filters", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); 

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//ImGui::StyleColorsDark(); 

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	return true;
}

void CustomWindow::UpdateTexture(const Image& img, GLuint& textureId)
{
    if (textureId == 0)
    {
        glGenTextures(1, &textureId);
    }
    glBindTexture(GL_TEXTURE_2D, textureId);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.GetWidth(), img.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getRawData());
}

void CustomWindow::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int window_w, window_h;
        glfwGetWindowSize(window, &window_w, &window_h);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2((float)window_w, (float)window_h));

        ImGui::Begin("Main Canvas", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);

        if (ImGui::Button("Open Image...", ImVec2(130, 35)))
        {
            auto selections = pfd::open_file("Select an image", "", { "Images (.png .jpg)", "*.png *.jpg *.jpeg" }).result();
            if (!selections.empty())
            {
                if (originalImage.loadFromFile(selections[0]))
                {
                    UpdateTexture(originalImage, originalTexture);
                    imageIsLoaded = true;
                    filterIsApplied = false;
                }
            }
        }

        if (imageIsLoaded)
        {
            ImGui::SameLine(0, 20);
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Filter:");
            ImGui::SameLine();
            if (ImGui::RadioButton("Sharpen", selectedFilter == 1)) selectedFilter = 1;
            ImGui::SameLine();
            if (ImGui::RadioButton("Emboss", selectedFilter == 2)) selectedFilter = 2;

            if (selectedFilter > 0)
            {
                ImGui::SameLine(0, 20);
                if (ImGui::Button("APPLY FILTER", ImVec2(130, 35)))
                {
                    processedImage = originalImage;

                    if (selectedFilter == 1)
                    {
                        SharpenFilter filter;
                        filter.Apply(processedImage);
                    }
                    else if (selectedFilter == 2)
                    {
                        EmbossFilter filter;
                        filter.Apply(processedImage);
                    }

                    UpdateTexture(processedImage, processedTexture);
                    filterIsApplied = true;
                }
            }

            ImGui::Separator();
            ImGui::Spacing();

            ImGui::Columns(2, "Viewports", true);

            ImGui::Text("ORIGINAL IMAGE:");
            if (originalTexture)
            {

                float availWidth = ImGui::GetColumnWidth() - 20;
                float aspect = (float)originalImage.GetHeight() / originalImage.GetWidth();

                ImGui::Image((void*)(intptr_t)originalTexture, ImVec2(availWidth, availWidth * aspect));
            }

            ImGui::NextColumn();

            ImGui::Text("PROCESSED IMAGE:");
            if (filterIsApplied && processedTexture)
            {
                float availWidth = ImGui::GetColumnWidth() - 20;
                float aspect = (float)processedImage.GetHeight() / processedImage.GetWidth();

                ImGui::Image((void*)(intptr_t)processedTexture, ImVec2(availWidth, availWidth * aspect));
            }
        }
        else
        {
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Please open an image to start processing.");
        }

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.11f, 0.12f, 0.13f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}